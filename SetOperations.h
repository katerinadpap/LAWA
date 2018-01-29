#ifndef SETOPERATIONS_H_
#define SETOPERATIONS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>
#include <list>

#include "Lawa.h"
#include "Tuple_Ts_Comparator.h"
#include "Tuple_Te_Comparator.h"
#include "Tuple.h"
#include "Relation.h"
#include "LineageAwareTemporalWindow.h"

using namespace std;

class SetOperations {

public:
	Lawa it;
	int op;
	vector<Tuple> output;
	string land;
	string lor;
	string landNot;
	int baseLeft;
	int baseRight;

	SetOperations(Relation r, Relation s, int requestedOp, int leftIsBase, int rightIsBase) :it(r.tuples, s.tuples) {
		op = requestedOp;

		land = string("*");
		lor = string("+");
		landNot = string("*-");
		baseLeft = leftIsBase;
		baseRight = rightIsBase;
	}

	void set_union(Relation r, Relation s) {

		// Sort Tuples in R By Ts
		Tuple_Ts_Comparator sort_comp(vector<int> { 0, 1 });
		sort(r.tuples.begin(), r.tuples.end(), sort_comp);

		// Sort Tuples in S By Ts
		sort(s.tuples.begin(), s.tuples.end(), sort_comp);

		LineageAwareTemporalWindow w;
		while (it.sTuples_Index < it.sTuples.size()
				|| it.rTuples_Index < it.rTuples.size()) {

			w = it.main_lawa();

			if (w.lambda_r.compare("") != 0 || w.lambda_s.compare("") != 0) {
				Tuple t(w,lor, baseLeft, baseRight);
				output.push_back(t);
			}
		}

		if (it.valid_rTuple_pos != -1 || it.valid_sTuple_pos != -1) {
			w = it.main_lawa();
			Tuple t(w,lor, baseLeft, baseRight);
			output.push_back(t);
		}

	}

	void set_difference(Relation r, Relation s) {

		// Sort Tuples in R By Ts
		Tuple_Ts_Comparator sort_comp(vector<int> { 0, 1 });
		sort(r.tuples.begin(), r.tuples.end(), sort_comp);

		// Sort Tuples in S By Ts
		sort(s.tuples.begin(), s.tuples.end(), sort_comp);

		LineageAwareTemporalWindow w;
		while (it.rTuples_Index < it.rTuples.size()) {
			w = it.main_lawa();
			if (w.lambda_r.compare("") != 0) {
				Tuple t(w,landNot, baseLeft, baseRight);
				output.push_back(t);
			}
		}

		if (it.valid_rTuple_pos != -1) {
			w = it.main_lawa();
			Tuple t(w,landNot, baseLeft, baseRight);
			output.push_back(t);
		}
	}

	void set_intersection(Relation r, Relation s) {

		// Sort Tuples in R By Ts
		Tuple_Ts_Comparator sort_comp(vector<int> { 0, 1 });
		sort(r.tuples.begin(), r.tuples.end(), sort_comp);

		// Sort Tuples in S By Ts
		sort(s.tuples.begin(), s.tuples.end(), sort_comp);

		LineageAwareTemporalWindow w;
		while (it.sTuples_Index < it.sTuples.size()
				&& it.rTuples_Index < it.rTuples.size()) {

			w = it.main_lawa();

			if (w.lambda_r.compare("") != 0 && w.lambda_s.compare("") != 0) {
				Tuple t(w,land, baseLeft, baseRight);
				output.push_back(t);
			}
		}

	}
};

#endif
