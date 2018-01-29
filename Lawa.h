#ifndef LAWA_H_
#define LAWA_H_

#include <limits>

#include <iostream>
#include <sstream>

#include <algorithm>

#include <vector>
#include <string>
#include <list>
#include <queue>

#include "LineageAwareTemporalWindow.h"
#include "Tuple_Ts_Comparator.h"
#include "Tuple_Te_Comparator.h"

using namespace std;

class Lawa {

public:

	vector<Tuple> rTuples;
	vector<Tuple> sTuples;
	long long rTuples_Index;
	long long sTuples_Index;

	long long currFact;
	long long prevWindTe;
	int valid_rTuple_pos;
	int valid_sTuple_pos;

	Lawa(const vector<Tuple>& TuplesOFr,
			const vector<Tuple>& TuplesOFs) {

		rTuples = TuplesOFr;
		sTuples = TuplesOFs;
		rTuples_Index = 0;
		sTuples_Index = 0;

		currFact = -1;
		prevWindTe = -1;
		valid_rTuple_pos = -1;
		valid_sTuple_pos = -1;

		cout << "Lawa Initialized" << endl;
	}

	long long minimum_of_candidates(vector<long long> Te_candidates) {

		if (Te_candidates.empty())
			return -1;

		long long min_Te = numeric_limits<long long>::max();
		for (const auto& t : Te_candidates) {
			if (t < min_Te) {
				min_Te = t;
			}
		}
		return min_Te;

	}

	LineageAwareTemporalWindow main_lawa() {

		LineageAwareTemporalWindow outputWindow = LineageAwareTemporalWindow();

		// Determine the win_Ts
		if (valid_rTuple_pos == -1 && valid_sTuple_pos == -1) {

			// No more tuples from r - Only work with tuples from s
			if (rTuples_Index == rTuples.size()
					&& sTuples_Index < sTuples.size()) {
				outputWindow.wind_Ts = sTuples[sTuples_Index].ts;
				currFact = sTuples[sTuples_Index].fact;
			}
			// No more tuples from s - Only work with tuples from r
			else if (rTuples_Index < rTuples.size()
					&& sTuples_Index == sTuples.size()) {
				outputWindow.wind_Ts = rTuples[rTuples_Index].ts;
				currFact = rTuples[rTuples_Index].fact;
			}
			// There are tuples in both relations (They can't be empty because this was checked before this function was called)
			else {
				if (rTuples[rTuples_Index].fact == currFact
						&& sTuples[sTuples_Index].fact != currFact) {
					outputWindow.wind_Ts = rTuples[rTuples_Index].ts;
				}
				// Time Gap - there are still tuples of s with the same fact as currFact
				else if (sTuples[sTuples_Index].fact == currFact
						&& rTuples[rTuples_Index].fact != currFact) {
					outputWindow.wind_Ts = sTuples[sTuples_Index].ts;
					currFact = sTuples[sTuples_Index].fact;
				}
				// Time Gap - there are still tuples of both relations with the same fact as currFact
				// In this case we choose the one with the smallest ts
				else {

					if (rTuples[rTuples_Index].ts < sTuples[sTuples_Index].ts) {
						outputWindow.wind_Ts = rTuples[rTuples_Index].ts;
						currFact = rTuples[rTuples_Index].fact;
					} else {
						outputWindow.wind_Ts = sTuples[sTuples_Index].ts;
						currFact = sTuples[sTuples_Index].fact;
					}
				}
			}
		} else {
			outputWindow.wind_Ts = prevWindTe;
		}

		// Update rValid, r
		if (rTuples[rTuples_Index].fact == currFact
				&& rTuples[rTuples_Index].ts == outputWindow.wind_Ts) {
			valid_rTuple_pos = rTuples_Index;
			rTuples_Index++;
		}

		// Update sValid, s
		if (sTuples[sTuples_Index].fact == currFact
				&& sTuples[sTuples_Index].ts == outputWindow.wind_Ts) {
			valid_sTuple_pos = sTuples_Index;
			sTuples_Index++;
		}

		// Determine the win_Te
		vector<long long> Te_candidates;
		vector<long long>::iterator te_it;

		te_it = Te_candidates.begin();

		if (rTuples_Index <= rTuples.size()
				&& rTuples[rTuples_Index].fact == currFact) {
			te_it = Te_candidates.insert(te_it, rTuples[rTuples_Index].ts);
		}
		if (sTuples_Index <= sTuples.size()
				&& sTuples[sTuples_Index].fact == currFact) {
			te_it = Te_candidates.insert(te_it, sTuples[sTuples_Index].ts);
		}
		if (valid_rTuple_pos != -1) {
			te_it = Te_candidates.insert(te_it, rTuples[valid_rTuple_pos].te);
		}
		if (valid_sTuple_pos != -1) {
			te_it = Te_candidates.insert(te_it, sTuples[valid_sTuple_pos].te);
		}

		outputWindow.wind_Te = minimum_of_candidates(Te_candidates);
		outputWindow.currFact = currFact;


		// Assign lambda_r, lambda_s
		if (valid_rTuple_pos != -1) {
			outputWindow.lambda_r = string(rTuples[valid_rTuple_pos].lambda);
		}
		if (valid_sTuple_pos != -1) {
			outputWindow.lambda_s = string(sTuples[valid_sTuple_pos].lambda);
		}


		// Update rValid, sValid, prevWindTe
		if (valid_rTuple_pos != -1 && rTuples[valid_rTuple_pos].te == outputWindow.wind_Te) {
			valid_rTuple_pos = -1;
		}

		if (valid_sTuple_pos != -1 && sTuples[valid_sTuple_pos].te == outputWindow.wind_Te) {
			valid_sTuple_pos = -1;
		}

		prevWindTe = outputWindow.wind_Te;

		return outputWindow;

	}

};

#endif