#ifndef IO_H_
#define IO_H_

#include <vector>
#include <queue>
#include <unordered_map>
#include "Types.h"

using namespace std;

char CommandLineCheck(int argc, char * argv[]);

void placeFacilities(vector<Facility> &facilities, unordered_map<int, Facility> &facilities_map);

void sparsePaths(priority_queue <Path> &pq, unordered_map<int, Facility> &facilities_map);

void ABOut(vector <Path> &paths, double &weight);

void COut(vector<unsigned int> &cycle, double &weight);

#endif
