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
/**
 * Radius of earth used in distance calculation with latitude and longitude
 */
#define EARTH_RADIUS 6371.0
/**
 * Price of highway by km
 */
#define HIGHWAY_PRICE 0.1;

/**
 * struct used to represent a point of the itinerary
 */
typedef struct itineraryPoint{
	int nodeID;
	string name;
};

/**
 *
 */
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
	/**
	 * Streetmap constrcutor to generate nodes, roads
	 * @param path folder that contain nodes.txt, roads.txt and subroads.txt used to graph costruction
	 */
	StreetMap(string path);
	/**
	 * Streetmap destructor
	 */
	virtual ~StreetMap();
	/**
	 * Loads information from txt's about nodes, roads, and nodes that compose all roads
	 * @param nodes_path nodes.txt path
	 * @param roads_path roads.txt path
	 * @param subroads_path subroads.txt path
	 */
	void loadFromTxt(const char *nodes_path, const char *roads_path, const char *subroads_path, bool show_status);
	/**
	 * Generate four graphs:
	 * Graph with distance info
	 * Graph with time info
	 * Graph with distance info without roads with tolls
	 * Graph with time info without roads with tolls
	 */
	void generateGraph();
	/**
	 * Creates a new window and draws all roads
	 * @return a pointer to the graphviewer(window) created
	 */
	GraphViewer* draw();
	/**
	 * Writes info about all roads and nodes that compose them
	 * Used for debugging purposes
	 */
	void write();
	//const Graph<int>& getGraph() const;
	//void setGraph(const Graph<int>& graph);
	/**
	 * Return the itinerary
	 * @return vector with all itinerary points
	 */
	const vector<itineraryPoint>& getItinerary() const;
	/**
	 * Sets the itinerary to a vector
	 * @param itinerary New vector to set
	 */
	void setItinerary(const vector<itineraryPoint>& itinerary);
	/**
	 * Adds a new point to the itinerary (the point is added after
	 * @param nodeID ID of the node to be added
	 * @param name Descriptor of the new point
	 */
	void addItinerary(const int nodeID, const string name);
	/**
	 * Removes point from itinerary 'list'
	 * @param index Index of the point to be removed in the itinerary list
	 * @return if the point is removed successfully or not
	 */
	bool removeItinerary(const unsigned int index);
	/**
	 * Return nodes
	 * @return Map with Node ID and other node info
	 */
	const map<int, Node>& getNodes() const;
	/**
	 * Return roads
	 * @return Map with Road ID and other road info
	 */
	const map<int, Road>& getRoads() const;
	/**
	 * Return a randomly Node ID from a road
	 * @param road Name of the road to find node
	 * @return Random Node ID from road
	 */
	int getNodeID(const string road);
	/**
	 * Return the Node ID from the intersection of two roads
	 * @param road1 Name of the first road
	 * @param road2 Name of the second road
	 * @return Node ID from the intersection of the two roads
	 */
	int getNodeID(const string road1, const string road2);
	/**
	 * Calculates the best way to travel from the first point of the itinerary to the last (passing all between them if existing)
	 * @param dist True to calculate best way by distance or False by time
	 * @param tolls True to include roads with tolls in calculation and False to not
	 * @return True if all points from the itinerary are reachable and false if they're not
	 */
	bool calculateItinerary(bool dist, bool tolls);
	/**
	 * Calculates the best way to travel from the one node to another (auxiliary function of calculateItinerary)
	 * Uses dijkstra Algorithm
	 * @param nodeID1 Source node ID
	 * @param nodeID2 Destination node ID
	 * @param graph Graph to search
	 * @return True if the destination node is reachable from the source node
	 */
	bool calculateItineraryAux(int nodeID1, int nodeID2, Graph<int> *graph);
	/**
	 * Draws a animation to explain the path
	 * Continuation of draw funtion
	 */
	void drawItinerary();
	/**
	 * Returns Points of Interest
	 * @return Vector with all Points of Interest in map
	 */
	const vector<POI>& getPois() const;
	/**
	 * Sets POI's to a new vector
	 * @param pois New vector to set
	 */
	void setPois(const vector<POI>& pois);
	void insertPOI(POI p,GraphViewer* gv);
	int closestPOIs(POIType type);

};

/**
 * Calculates the distance in kilometers given two nodes with latitude and longitude
 * @param n1 First node
 * @param n2 Second node
 * @return Distance between nodes in km(kilometers)
 */
	double nodeDistance(Node *n1, Node *n2);

#endif /* SRC_STREETMAP_H_ */
