/*
 * operations.h
 *
 *  Created on: 2 Apr 2017
 *      Author: katerina
 */

#ifndef LINEAGEAWARETEMPORALWINDOW_H_
#define LINEAGEAWARETEMPORALWINDOW_H_

using namespace std;

class LineageAwareTemporalWindow {

public:
	long long currFact;
	long long wind_Ts;
	long long wind_Te;
	string lambda_r;
	string lambda_s;

	LineageAwareTemporalWindow() {
		currFact = -1;
		wind_Ts = -1;
		wind_Te = -1;
		lambda_r = string("");
		lambda_s = string("");
	}
};

#endif /* OPERATORS_H_ */
