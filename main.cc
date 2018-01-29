#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>
#include <list>

#include "Tuple.h"
#include "Relation.h"
#include "Operators.h"
#include "SetOperations.h"

#include <chrono>

using namespace std;

int main(int argc, char** argv) {

	// Read Relationa from Files
	Relation a("data/a.txt");
	cout << "Relation a: " << a.relation_size << " tuples" << endl;
	a.printRelation();
	cout << endl;

	Relation b("data/b.txt");
	cout << "Relation b: " << b.relation_size << " tuples" << endl;
	b.printRelation();
	cout << endl;

	Relation c("data/c.txt");
	cout << "Relation c: " << c.relation_size << " tuples" << endl;
	c.printRelation();
	cout << endl;


	// Example in Fig 1: (a UNION b) EXCEPT c
	SetOperations setOpsAB = SetOperations(a, b, SET_UNION, 1, 1);
	setOpsAB.setUnion(a, b);
	Relation intermediate(setOpsAB.output);
	SetOperations setOpsIC = SetOperations(c,intermediate,SET_DIFFERENCE, 1, 0);
	setOpsIC.setDifference(c,intermediate);

	cout << "Output (a UNION b) EXCEPT c: " << setOpsIC.output.size() << " tuples" << endl;
	for (const auto& t : setOpsIC.output) {
		t.printTuple();
	}

	cout << "\n" << endl;

	// Fig 3: a UNION c
	SetOperations setOpsACunion = SetOperations(a, c, SET_UNION, 1, 1);
	setOpsACunion.setUnion(a, c);
	cout << "Output a UNION c: " << setOpsACunion.output.size() << " tuples" << endl;
	for (const auto& t : setOpsACunion.output) {
		t.printTuple();
	}

	cout << endl << endl;

	// Fig 3: a INTERSECT c
	SetOperations setOpsACintersect = SetOperations(a, c, SET_INTERSECTION, 1, 1);
	setOpsACintersect.setIntersection(a, c);
	cout << "Output a INTERSECT c: " << setOpsACintersect.output.size() << " tuples" << endl;
	for (const auto& t : setOpsACintersect.output) {
		t.printTuple();
	}

	cout << "\n" << endl;

	// Fig 3: a EXCEPT c
	SetOperations setOpsACdifference = SetOperations(a, c, SET_DIFFERENCE, 1, 1);
	setOpsACdifference.setDifference(a, c);
	cout << "Output a EXCEPT c: " << setOpsACdifference.output.size() << " tuples" << endl;
	for (const auto& t : setOpsACdifference.output) {
		t.printTuple();
	}

	return 0;
}
