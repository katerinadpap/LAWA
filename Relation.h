#ifndef RELATION_H_
#define RELATION_H_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "Tuple.h"

using namespace std;

class Relation {

public:
	vector<Tuple> tuples;
	long long relation_size;

	// Create Relation from Vector
	Relation(vector<Tuple> output) {
		tuples = output;
		relation_size = output.size();
	}

	// Read Relation From File
	Relation(const string& file_name) {
		ifstream file_stream(file_name);
		string line, attribute_name;
		relation_size = 0;
		while (getline(file_stream, line)) {
			Tuple t(line);
			tuples.push_back(t);
			relation_size++;
		}

		file_stream.close();

	}

	// Print Relation To Standard Output
	void printRelation() {
		for (const auto& t : tuples) {
			t.printTuple();
		}
	}

};

#endif
