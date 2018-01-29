#ifndef TUPLE_TE_COMPARATOR_H_
#define TUPLE_TE_COMPARATOR_H_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "Tuple.h"

using namespace std;


class TupleTeComparator {

public:

	TupleTeComparator() {
	}

	bool operator()(const Tuple& t1, const Tuple& t2) {
		// compare the te values, if the facts are the same
		return t1.te < t2.te;
	}

};

#endif /* RELATION_SORTING_H_ */
