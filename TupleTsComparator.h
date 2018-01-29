/*
 * TupleTsComparator.h
 *
 *  Created on: 2 Apr 2017
 *      Author: katerina
 */

#ifndef TUPLE_TS_COMPARATOR_H_
#define TUPLE_TS_COMPARATOR_H_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "Tuple.h"

using namespace std;


class TupleTsComparator {

public:
	vector<int> sorting_attributes;

	TupleTsComparator(const vector<int>& attribute_positions) {
		sorting_attributes = attribute_positions;
	}

	bool operator()(const Tuple& t1, const Tuple& t2) {

		/* compare the facts of two tuples column by column
		   and push up the fact with the alphabetically first
		   fact
		*/
	 	if (t1.fact < t2.fact) {
			return true;
		}

	 	if (t1.fact > t2.fact) {
			return false;
		}

		// compare the ts values, if the facts are the same
		return t1.ts < t2.ts;
	}

};

#endif
