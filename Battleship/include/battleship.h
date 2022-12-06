#include "stdbool.h"

struct Location {
	int c;
	int r;
};

struct Vessel {
	char name[20];
	bool sunk;
	unsigned int length;
	struct Location vesselLocations[5];
	bool hits[5];
};
