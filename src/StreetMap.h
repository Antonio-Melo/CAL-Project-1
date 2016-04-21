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
#include <stdlib.h>

#include <map>
#include "Graph.h"
#include "Node.h"
#include "Road.h"
#include "POI.h"

using namespace std;

#define EARTH_RADIUS 6371.0
#define HIGHWAY_PRICE 0.1;

typedef struct itineraryPoint{
	int nodeID;
	string name;
};

class StreetMap {
	map<int,Node> nodes;
	map<int,Road> roads;

	vector<POI> pois;
	Graph<int> dist_graph;
	Graph<int> time_graph;
	Graph<int> dist_graph_no_tolls;
	Graph<int> time_graph_no_tolls;
	vector<itineraryPoint> itinerary;
	vector<int> path;
	Graph<int> graph;
	double latMin, longMin, latMax, longMax;

public:
	StreetMap(string path);
	virtual ~StreetMap();
	void loadFromTxt(const char *nodes_path, const char *roads_path, const char *subroads_path, const char *info_path, bool show_status);
	void generateGraph();
	GraphViewer* draw();
	void write();
	//const Graph<int>& getGraph() const;
	//void setGraph(const Graph<int>& graph);
	const vector<itineraryPoint>& getItinerary() const;
	void setItinerary(const vector<itineraryPoint>& itinerary);
	void addItinerary(const int nodeID, const string name);
	bool removeItinerary(const unsigned int index);
	const map<int, Node>& getNodes() const;
	void setNodes(const map<int, Node>& nodes);
	const map<int, Road>& getRoads() const;
	void setRoads(const map<int, Road>& roads);
	int getNodeID(const string road);
	int getNodeID(const string road1, const string road2);
	bool calculateItinerary(bool dist, bool tolls);
	bool calculateItineraryAux(int nodeID1, int nodeID2, Graph<int> *graph);
	void drawItinerary();
};

double nodeDistance(Node *n1, Node *n2);

#endif /* SRC_STREETMAP_H_ */
