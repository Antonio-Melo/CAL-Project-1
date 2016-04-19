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
#include "Node.h"
#include "Road.h"

using namespace std;

class StreetMap {
	map<int,Node> nodes;
	map<int,Road> roads;
	//vector<Road> roads;

public:
	StreetMap();
	virtual ~StreetMap();
	void loadFromTxt(const char *nodes_path, const char *roads_path, const char *subroads_path);
};

#endif /* SRC_STREETMAP_H_ */
