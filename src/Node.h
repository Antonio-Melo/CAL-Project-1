#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Node {
	int id;
	double latitude_deg, longitude_deg, latitude_rad, longitude_rad;
public:
	Node(int id, double latitude_deg, double longitude_deg, double latitude_rad, double longitute_rad);
};

