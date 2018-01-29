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
#include "TupleTsComparator.h"
#include "TupleTeComparator.h"

using namespace std;

class Lawa {

public:

	vector<Tuple> rTuples;
	vector<Tuple> sTuples;
	long long rTuplesIndex;
	long long sTuplesIndex;

	long long currFact;
	long long prevWindTe;
	int validRtuplePos;
	int validStuplePos;

	Lawa(const vector<Tuple>& TuplesOFr,
			const vector<Tuple>& TuplesOFs) {

		rTuples = TuplesOFr;
		sTuples = TuplesOFs;
		rTuplesIndex = 0;
		sTuplesIndex = 0;

		currFact = -1;
		prevWindTe = -1;
		validRtuplePos = -1;
		validStuplePos = -1;

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
		if (validRtuplePos == -1 && validStuplePos == -1) {

			// No more tuples from r - Only work with tuples from s
			if (rTuplesIndex == rTuples.size()
					&& sTuplesIndex < sTuples.size()) {
				outputWindow.wind_Ts = sTuples[sTuplesIndex].ts;
				currFact = sTuples[sTuplesIndex].fact;
			}
			// No more tuples from s - Only work with tuples from r
			else if (rTuplesIndex < rTuples.size()
					&& sTuplesIndex == sTuples.size()) {
				outputWindow.wind_Ts = rTuples[rTuplesIndex].ts;
				currFact = rTuples[rTuplesIndex].fact;
			}
			// There are tuples in both relations (They can't be empty because this was checked before this function was called)
			else {
				if (rTuples[rTuplesIndex].fact == currFact
						&& sTuples[sTuplesIndex].fact != currFact) {
					outputWindow.wind_Ts = rTuples[rTuplesIndex].ts;
				}
				// Time Gap - there are still tuples of s with the same fact as currFact
				else if (sTuples[sTuplesIndex].fact == currFact
						&& rTuples[rTuplesIndex].fact != currFact) {
					outputWindow.wind_Ts = sTuples[sTuplesIndex].ts;
					currFact = sTuples[sTuplesIndex].fact;
				}
				// Time Gap - there are still tuples of both relations with the same fact as currFact
				// In this case we choose the one with the smallest ts
				else {

					if (rTuples[rTuplesIndex].ts < sTuples[sTuplesIndex].ts) {
						outputWindow.wind_Ts = rTuples[rTuplesIndex].ts;
						currFact = rTuples[rTuplesIndex].fact;
					} else {
						outputWindow.wind_Ts = sTuples[sTuplesIndex].ts;
						currFact = sTuples[sTuplesIndex].fact;
					}
				}
			}
		} else {
			outputWindow.wind_Ts = prevWindTe;
		}

		// Update rValid, r
		if (rTuples[rTuplesIndex].fact == currFact
				&& rTuples[rTuplesIndex].ts == outputWindow.wind_Ts) {
			validRtuplePos = rTuplesIndex;
			rTuplesIndex++;
		}

		// Update sValid, s
		if (sTuples[sTuplesIndex].fact == currFact
				&& sTuples[sTuplesIndex].ts == outputWindow.wind_Ts) {
			validStuplePos = sTuplesIndex;
			sTuplesIndex++;
		}

		// Determine the win_Te
		vector<long long> Te_candidates;
		vector<long long>::iterator te_it;

		te_it = Te_candidates.begin();

		if (rTuplesIndex <= rTuples.size()
				&& rTuples[rTuplesIndex].fact == currFact) {
			te_it = Te_candidates.insert(te_it, rTuples[rTuplesIndex].ts);
		}
		if (sTuplesIndex <= sTuples.size()
				&& sTuples[sTuplesIndex].fact == currFact) {
			te_it = Te_candidates.insert(te_it, sTuples[sTuplesIndex].ts);
		}
		if (validRtuplePos != -1) {
			te_it = Te_candidates.insert(te_it, rTuples[validRtuplePos].te);
		}
		if (validStuplePos != -1) {
			te_it = Te_candidates.insert(te_it, sTuples[validStuplePos].te);
		}

		outputWindow.wind_Te = minimum_of_candidates(Te_candidates);
		outputWindow.currFact = currFact;


		// Assign lambda_r, lambda_s
		if (validRtuplePos != -1) {
			outputWindow.lambda_r = string(rTuples[validRtuplePos].lambda);
		}
		if (validStuplePos != -1) {
			outputWindow.lambda_s = string(sTuples[validStuplePos].lambda);
		}


		// Update rValid, sValid, prevWindTe
		if (validRtuplePos != -1 && rTuples[validRtuplePos].te == outputWindow.wind_Te) {
			validRtuplePos = -1;
		}

		if (validStuplePos != -1 && sTuples[validStuplePos].te == outputWindow.wind_Te) {
			validStuplePos = -1;
		}

		prevWindTe = outputWindow.wind_Te;

		return outputWindow;

	}

};

#endif