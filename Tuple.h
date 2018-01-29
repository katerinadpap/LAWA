#ifndef TUPLE_H_
#define TUPLE_H_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "LineageAwareTemporalWindow.h"

using namespace std;

class Tuple {

public:
	// vector<int> fact;
	long long fact;
	long long ts;
	long long te;
	string lambda;

	// Store a file row as a tuple
	Tuple(const string& file_row){

		vector<string> tokens;
		string attribute;
		stringstream lineStream(file_row);

		while (getline(lineStream, attribute, '\t')) {
			tokens.push_back(attribute);
		}

		// Read lambda
		lambda = string(tokens[tokens.size() - 1]);
//		te = stol(tokens[tokens.size() - 1]);
		tokens.pop_back();

		// Read te
		const char *cstr = tokens[tokens.size() - 1].c_str();
		sscanf(cstr, "%lld", &te);
//		te = stol(tokens[tokens.size() - 1]);
		tokens.pop_back();

		// Read ts
		const char *cstr1 = tokens[tokens.size() - 1].c_str();
		sscanf(cstr1, "%lld", &ts);
//		ts = stol(tokens[tokens.size() - 1]);
		tokens.pop_back();

		// Read Fact
		const char *cstr2 = tokens[tokens.size() - 1].c_str();
		sscanf(cstr2, "%lld", &fact);
//		fact = stol(tokens[tokens.size() - 1]);
		tokens.pop_back();

//		lambda = "";
	}

	Tuple(LineageAwareTemporalWindow w, string lineage_op, int baseLeft, int baseRight) {

		// cout << "w.currFact = " << w.currFact << endl;
		// cout << "w.wind_Ts = " << w.wind_Ts << endl;
		// cout << "w.wind_Te = " << w.wind_Te << endl;
		// cout << "w.lambda_r = " << w.lambda_r << endl;
		// cout << "w.lambda_s = " << w.lambda_s << endl;

		fact = w.currFact;
		ts = w.wind_Ts;
		te = w.wind_Te;

		if (w.lambda_r.compare("") == 0) {
			lambda = w.lambda_s;
		} else if (w.lambda_s.compare("") == 0) {
			lambda = w.lambda_r;
		} else {
			if (baseLeft == 0) {
				lambda = "(" + w.lambda_r + ")" + lineage_op;
			} else {
				lambda = w.lambda_r + lineage_op;
			}

			if (baseRight == 0) {
				lambda = lambda + "(" + w.lambda_s + ")";
			} else {
				lambda = lambda + w.lambda_s;
			}
		}

		// cout << fact << ", " << ts << ", " << te << ", " << lambda << endl;

	}


	// Print Tuple
	void printTuple() const {
		cout << fact << ", " << ts << ", " << te << ", " << lambda << endl;
	}

};

#endif /* TUPLE_H_ */
