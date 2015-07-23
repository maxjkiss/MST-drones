#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <deque>
#include <queue>
#include "Types.h"
#include "Logic.h"
#include "io.h"

using namespace std;

double CMLWeight(0);

void kruskalPath(vector <Path> &paths, vector<Facility> &facilities, double &weight, priority_queue <Path> &priorityPaths, char& clientType) {

    vector<FacilityList> choices(facilities.size());
    for(unsigned int i=0; i < facilities.size(); i++) {
      FacilityList Fac;
      choices.push_back(Fac);
    }
    for(unsigned int i=0; i < facilities.size(); i++) choices[i].maxy.push_back(&facilities[i]);

//------------
	if(clientType != 'A'){
    for(unsigned int i=0; i < facilities.size(); i++) {
      for(unsigned int j = i+1; j < facilities.size(); j++) { 

        Path dumpPath(facilities[i], facilities[j]);

        if(clientType == 'C') {

          if(dumpPath.length < facilities[i].check1) {
          facilities[i].check2 = facilities[i].check1;
          facilities[i].check1 = dumpPath.length;
          }
          else if(dumpPath.length < facilities[i].check2) facilities[i].check2 = dumpPath.length;

          if(dumpPath.length < facilities[j].check1) {
            facilities[j].check2 = facilities[j].check1;
            facilities[j].check1 = dumpPath.length;
          }
          else if(dumpPath.length < facilities[j].check2) facilities[j].check2 = dumpPath.length;
          }
        priorityPaths.push(dumpPath);
      	}
      }
	}
//------------

    while(!priorityPaths.empty()) {
      Path dumpPath = priorityPaths.top();
      priorityPaths.pop();
      int parent1(facilities[dumpPath.start].parent);
      int parent2(facilities[dumpPath.end].parent);
      if(parent1 != parent2) {
        paths.push_back(dumpPath);
        weight += sqrt(dumpPath.length);
      if(choices[parent1].maxy.size() < choices[parent2].maxy.size()) {
        for(auto it = choices[parent2].maxy.begin(); it != choices[parent2].maxy.end(); ++it) (*it)->parent = parent1;
        choices[parent1].maxy.splice(choices[parent1].maxy.end(), choices[parent2].maxy);
        }
      else {
        for(auto it = choices[parent1].maxy.begin(); it != choices[parent1].maxy.end(); ++it) (*it)->parent = parent2;
        choices[parent2].maxy.splice(choices[parent2].maxy.end(), choices[parent1].maxy);
        }
      }
    }
    choices.clear();
	return;
}

void primsPath(vector<Facility> &facilities, vector <Path> &paths, double &weight, char &clientType) {

	vector<bool> visited(facilities.size(), 0);
	vector<double> nodeDist(facilities.size(), DBL_MAX);
	vector<int> nodeIndex(facilities.size(), -1);
	unsigned int source(-1), next(-1);
	double distNow(DBL_MAX);
	nodeDist[0] = 0;
	nodeIndex[0] = 0;
	Path testPath;
	visited[0] = true;

	for(unsigned int i = 1; i < facilities.size(); i++) {
		if(clientType != 'C' && double(facilities[0].x) * double(facilities[i].x) >= 0 && 
			(facilities[0].x != 0 || facilities[i].x != 0)) {
			nodeDist[i] = facilities[0].getD(facilities[i]);
			nodeIndex[i] = 0;
		}
		if(!visited[i] && nodeDist[i] < distNow) {
			next = i;
			distNow = nodeDist[i];
		}
	}

	for(unsigned int i = 0; i < visited.size() -1; ++i) {
		source = next;
		Path testPath(facilities[((source < (unsigned)nodeIndex[source]) ? source:nodeIndex[source])], 
			facilities[((source > (unsigned)nodeIndex[source]) ? source:nodeIndex[source])]);
		paths.push_back(testPath);
		weight += sqrt(testPath.length);
		visited[source] = true;
		next = -1;
		distNow = DBL_MAX;

		for(unsigned int i = 0; i != facilities.size(); i++) {
			if(clientType != 'C' && source != i && double(facilities[source].x) * double(facilities[i].x) >= 0 && 
				(facilities[source].x != 0 || facilities[i].x!= 0)) {
				double dist = facilities[source].getD(facilities[i]);
				if(!visited[i] && nodeDist[i] > dist) {
					nodeDist[i] = dist;
					nodeIndex[i] = source;
				}
			}
			else if(clientType != 'C' && source != i) {

				double dist = facilities[source].getD(facilities[i]);

				if(dist < facilities[source].check1) {
					facilities[source].check2 = facilities[source].check1;
					facilities[source].check1 = dist;
				}
				else if(dist < facilities[source].check2) facilities[source].check2 = dist;

				if(dist < facilities[i].check1) {
					facilities[i].check2 = facilities[i].check1;
					facilities[i].check1 = dist;
				}
				else if(dist < facilities[i].check2) facilities[i].check2 = dist;

				if(!visited[i] && nodeDist[i] > dist) {
					nodeDist[i] = dist;
					nodeIndex[i] = source;
				}
			}
			
			if(!visited[i] && nodeDist[i] < distNow) {
				next = i;
				distNow = nodeDist[i];
			}
		}
	}
	return;
}

double distanceUpdate(vector<unsigned int> &stops, vector<Facility> facilities) {
	double dump(0);
	dump += sqrt(facilities[0].getD(facilities[stops.back()]));
	for(int i=0; (unsigned)(i+1) < stops.size(); i++) dump += sqrt(facilities[stops[i]].getD(facilities[stops[i+1]]));
	return dump;
}

void nearestNeighbor(vector <unsigned int> &stops, double& weight, vector <Facility> &facilities) {
	vector<bool> checkPos(facilities.size(), true);
	weight = 0;
	checkPos[0] = false;
	stops.push_back(0);
	double oldDist(DBL_MAX), distNow(-1);
	int index(-1);

	while(stops.size() != facilities.size()) {

		for(unsigned int i = 1; i < checkPos.size(); i++) {
			// checks if at end of branch
			if(checkPos[i]) {
				distNow = facilities[i].getD(facilities[stops.back()]);
				if(distNow < oldDist) { // checks if distance at distNow is less than previous
					oldDist = distNow;
					index = i;
				}
			}
		}
		stops.push_back(index);
		checkPos[index] = false;
		weight += sqrt(distNow);
		oldDist = DBL_MAX;
	}
	weight += facilities[0].getD(facilities[stops.back()]); // update weight of neighbor
	return;
	
}

void TSP(vector<Facility> &facilities, vector<unsigned int> &stops, double &weight) {
	nearestNeighbor(stops, weight, facilities);

	for(auto it = facilities.begin(); it != facilities.end(); ++it) it->getMin();

	if(facilities.size() == 1) return;
	deque<unsigned> queue, stack;
	vector<unsigned int> newstops;

	for(unsigned int i = 1; i < stops.size(); i++) queue.push_back(stops[i]);

		for (unsigned int i = 1; i < stops.size()-2; i++) {
			double finalPath(weight), update(0);
			int finalI(-1), finalK(-1);

			for (unsigned int k = i + 2; k < stops.size(); k++) {
				
				update = weight;
				if(k == stops.size() -1) {
					update -= sqrt(facilities[stops[i]].getD(facilities[stops[i-1]])) + sqrt(facilities[stops[k]].getD(facilities[0]));
					update += sqrt(facilities[stops[i-1]].getD(facilities[stops[k]])) + sqrt(facilities[0].getD(facilities[stops[i]]));
				}
				else {
					update -= sqrt(facilities[stops[i]].getD(facilities[stops[i-1]])) + sqrt(facilities[stops[k]].getD(facilities[stops[k+1]]));
					update += sqrt(facilities[stops[i-1]].getD(facilities[stops[k]])) + sqrt(facilities[stops[k+1]].getD(facilities[stops[i]]));
				}
				if (update < finalPath) {
					finalPath = update;
					finalI = i;
					finalK = k;
				}
			}
			if(finalPath < weight) {
				switchStops(stops, newstops, finalI, finalK);
				stops = newstops;
				weight = distanceUpdate(stops, facilities);
			}
		}

	Permutation(queue,stack,weight,stops,facilities);
	return;
}

void Permutation(deque<unsigned>& queue, deque<unsigned>& stack, double &weight, vector<unsigned> &stops, vector<Facility> &facilities) { 
	unsigned k, permSize(queue.size());
	if (queue.empty()) {
		double dump(CMLWeight);
		dump += sqrt(facilities[0].getD(facilities[stack.back()]));
		if(dump <= weight) {
			weight = dump;
			stops.clear();
			stops.push_back(0);
			for(auto it = stack.begin(); it!=stack.end(); it++) stops.push_back(*it);
		}
		return;
	}
	else if(queue.size() == 1) {
		double dump(CMLWeight);
		dump += sqrt(facilities[stack.back()].getD(facilities[queue.front()]));
		dump += sqrt(facilities[0].getD(facilities[queue.front()]));
		if(dump <= weight) {
			stops.clear();
			weight = dump;
			stops.push_back(0);
			for(int i = 0; (unsigned)i < stack.size(); ++i) stops.push_back(stack[i]);
			stops.push_back(queue.front());
		}
		return;
	}
	if(!isPromising(queue, weight, facilities)) return;
	for(k = 0; k != permSize; k++) {
		CMLWeight += (stack.empty()) ? sqrt(facilities[0].getD(facilities[queue.front()])) : sqrt(facilities[stack.back()].getD(facilities[queue.front()]));
		stack.push_back(queue.front()); 
		queue.pop_front(); 
		Permutation(queue,stack,weight,stops,facilities);
		queue.push_back(stack.back()); 
		stack.pop_back(); 
		CMLWeight -= (stack.empty()) ? sqrt(facilities[0].getD(facilities[queue.back()])) : sqrt(facilities[stack.back()].getD(facilities[queue.back()]));
	}
}
