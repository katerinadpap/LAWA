/*
 * Tuple_Ts_Comparator.h
 *
 *  Created on: 2 Apr 2017
 *      Author: katerina
 */
#ifndef TUPLE_TE_COMPARATOR_H_
#define TUPLE_TE_COMPARATOR_H_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "Tuple.h"

using namespace std;


class Tuple_Te_Comparator {

public:

	Tuple_Te_Comparator() {
	}

	bool operator()(const Tuple& t1, const Tuple& t2) {

		/* compare the facts of two tuples column by column
		   and push up the fact with the alphabetically first
		   fact
		*/
//		for (const auto& a: sorting_attributes) {
//			if (t1.fact[a] < t2.fact[a]) {
//				return true;
//			}
//
//			if (t1.fact[a] > t2.fact[a]) {
//				return false;
//			}
//		}

		// compare the te values, if the facts are the same
		return t1.te < t2.te;
	}

};

#endif /* RELATION_SORTING_H_ */
