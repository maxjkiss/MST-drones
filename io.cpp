#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <sstream>
#include <iomanip>
#include <getopt.h>
#include "io.h"
#include "Types.h"

using namespace std;

char CommandLineCheck(int argc, char * argv[]) {
  const struct option longopts[] =
  {
    { "clientType", required_argument, NULL, 'c' },
    { "help", no_argument, NULL, 'h' },
    {0,0,0,0},
  };
  int index = 0, iarg = 0;
  char dump('Z');
  opterr=1; 
  iarg = getopt_long(argc, argv, "c:h", longopts, &index);
  while(iarg != -1) {
    switch (iarg) {
      case 'c':
        dump = *optarg;
        break;

      case 'h':
        cout << "This program routes drones.\n";
        exit(0);
        break;

      case '?':
        cerr << "error\n";
        exit(1);

      default:
        exit(0);
        
    }
    iarg = getopt_long(argc, argv, "c:h", longopts, &index);
  }
  return dump;
}

void placeFacilities(vector<Facility> &facilities, unordered_map<int, Facility> &facilities_map) {
  int numFac, dump, links(0), left(0), right(0);
  Facility Fac;
  string dump2;
  cin >> dump2 >> numFac;
  facilities.reserve(numFac);
  dump = 0;
  while(!cin.fail() && dump != numFac) {
    cin >> Fac.x >> Fac.y;
    Fac.parent = Fac.index = dump;
    dump++;
    facilities.push_back(Fac);
    facilities_map.insert(pair<int, Facility> (Fac.index, Fac));
    if(Fac.x == 0) links++;
    else if(Fac.x < 0) left++;
    else right++;
  }  
  return;
}

void sparsePaths(priority_queue <Path> &pq, unordered_map<int, Facility> &facilities_map) {

    int numPaths, dump, start, end;
    string dump2;
    cin >> dump2 >> numPaths;
    dump = 0;
    while(!cin.fail() && dump != numPaths) {
      cin >> start >> end;
      Path pathIn(facilities_map.at(start), facilities_map.at(end));
      pq.push(pathIn);
      dump++;
    }
  return;
} 

void ABOut(vector <Path> &paths, double &weight) {
  int start, end;
  cout << std::setprecision(2);
  cout << std::fixed;
  cout << weight << "\n";
  for(unsigned int i=0; i < paths.size(); ++i) {
    start = paths[i].start;
    end = paths[i].end;
    cout << start << " " << end << "\n";
  }
  return;
}

void COut(vector<unsigned int> &cycle, double &weight) {
  cout << std::setprecision(2);
  cout << std::fixed;
  cout << weight << "\n" << "0";
  for(unsigned int i=1; i < cycle.size(); ++i) cout << " " << cycle[i];
  cout << "\n";
  return;
}
