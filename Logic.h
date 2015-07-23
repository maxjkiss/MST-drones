#ifndef LOGIC_H
#define LOGIC_H

#include <vector>
#include <list>
#include <cmath>
#include <deque>
#include <climits>
#include "Types.h"

using namespace std;

extern double CMLWeight;

void kruskalPath(vector <Path> &paths, vector<Facility> &facilities, double &weight, priority_queue <Path> &pq, char& clientType);

inline void switchStops(vector<unsigned int> &stops, vector<unsigned> &newStops, int i, int k) {
	newStops.clear();
	newStops.assign(stops.begin(), stops.begin() + i);
	for(int j = k; j >= i; j--) newStops.push_back(stops[j]);
	for(unsigned int j = k + 1; j < stops.size(); j++) newStops.push_back(stops[j]);
	return;
}

inline double boundVal(deque<unsigned> &queue, vector<Facility> &facilities) {
	double dump(CMLWeight), check1(0), check2(0);
	check1 += facilities[0].minimum;
	check2 += check1;
	for(auto it=queue.begin(); it!=queue.end(); ++it) check1 += facilities[*it].minimum;
	dump += check1;
	return dump;
}

inline bool isPromising(deque<unsigned> &queue, double& weight, vector<Facility> &facilities) {
	if(boundVal(queue,facilities) > weight) return false;
	else return true;
}

double distanceUpdate(vector<unsigned int> &stops, vector<Facility> facilities);

void nearestNeighbor(vector <unsigned int> &stops, double& weight, vector <Facility> &facilities);

void primsPath(vector<Facility> &facilities, vector <Path> &paths, double &weight, char &clientType);

void TSP(vector<Facility> &facilities, vector<unsigned int> &stops, double &weight);

void Permutation(deque<unsigned>& q, deque<unsigned>& s, double &weight, vector<unsigned> &stops, vector<Facility> &facilities);

#endif
