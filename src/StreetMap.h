/*
 * StreetMap.h
 *
 *  Created on: 19/04/2016
 *      Author: Telmo
 */

#ifndef SRC_STREETMAP_H_
#define SRC_STREETMAP_H_

#include <string>
#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <map>
#include "Graph.h"
#include "Node.h"
#include "Road.h"

using namespace std;

#define EARTH_RADIUS 6371.0

class StreetMap {
	map<int,Node> nodes;
	map<int,Road> roads;
	Graph<int> graph;
	//vector<Road> roads;

public:
	StreetMap();
	virtual ~StreetMap();
	void loadFromTxt(const char *nodes_path, const char *roads_path, const char *subroads_path);
	void generateGraph();
	void draw();

};

double nodeDistance(Node *n1, Node *n2);

#endif /* SRC_STREETMAP_H_ */
