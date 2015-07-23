#include <iostream>
#include <unordered_map>
#include "io.h"
#include "Types.h"
#include "Logic.h"

using namespace std;

int main(int argc, char* argv[]) {
	char clientType = CommandLineCheck(argc, argv);
	double weight(0);
	vector<Facility> facilities;
	vector<Path> paths;
	vector<unsigned int> stops;
	priority_queue <Path> orderedPaths;
	unordered_map<int, Facility> facilitiesMap;

	placeFacilities(facilities, facilitiesMap);
	if (clientType == 'A') {
		sparsePaths(orderedPaths, facilitiesMap);
		kruskalPath(paths, facilities, weight, orderedPaths, clientType);
		ABOut(paths, weight);
	}
	else if (clientType == 'B') {
		primsPath(facilities, paths, weight, clientType);
		ABOut(paths, weight);
	}
	else if (clientType == 'C') {
		kruskalPath(paths, facilities, weight, orderedPaths, clientType);
		TSP(facilities, stops, weight);
		COut(stops, weight);
	}
	else {
		cerr << "Invalid Client\n";
		return 0;
	}
	return 0;
}
