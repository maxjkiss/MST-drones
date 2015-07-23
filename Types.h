#ifndef TYPES_H
#define TYPES_H

#include <cmath>
#include <vector>
#include <list>
#include <climits>
#include <cfloat>

using namespace std;

struct Facility {
	int x, y, index, parent;
	double check1, check2, minimum;

	Facility() :x(INT_MAX), y(INT_MAX), index(-1), parent(-1), check1(DBL_MAX), check2(DBL_MAX) {}
	Facility(int &x_in, int &y_in, int &index_in) :x(x_in), y(y_in), index(index_in), parent(index_in), check1(DBL_MAX), check2(DBL_MAX) {}

	inline double getD(Facility &facility_in) {
		double dX(x - facility_in.x), dY(y - facility_in.y);
		return dX * dX + dY * dY;
	}
	
	inline void getMin() {
		minimum = (sqrt(check1) + sqrt(check2))/2;
	}
};


struct Path {
	int start, end;
	double length;

	Path() { length = DBL_MAX; }

	Path(Facility &facility1, Facility &facility2):start(facility1.index), end(facility2.index) {
		length = facility1.getD(facility2);
	}

	inline int getDest(int source) {
		if(source != start && source!= end) exit(1);
		int result = (source == start) ? end : start;
		return result;
	}

	inline bool operator< (const Path &pathIn) const {return length > pathIn.length;}
};

struct FacilityList {
	list<Facility*> maxy;
	int parent;
};

#endif
