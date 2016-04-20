/*
 * StreetMap.cpp
 *
 *  Created on: 19/04/2016
 *      Author: Telmo
 */

#include "StreetMap.h"
//#include <map>
#include <cmath>
#include <stdlib.h>
#include <algorithm>

using namespace std;

StreetMap::StreetMap(string path) {
	loadFromTxt((path + "/nodes.txt").c_str(), (path + "/roads.txt").c_str(), (path + "/subroads.txt").c_str());
}

StreetMap::~StreetMap() {
	// TODO Auto-generated destructor stub
}

void StreetMap::loadFromTxt(const char *nodes_path, const char *roads_path, const char *subroads_path){
	ifstream inFile;
	//Ler os nodes

	map<unsigned long int, int> tempconvN;
	map<unsigned long int, int> tempconvR;
	inFile.open(nodes_path,std::fstream::in);

	if (!inFile) {
		cerr << "Unable to open file nodes.txt";
		exit(1);   // call system to stop
	}

	std::string   line;


	unsigned long int idNode=0;
	int fakeIDN = 0, fakeIDR = 0;
	double X_deg=0, X_rad = 0;
	double Y_deg=0, Y_rad = 0;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string         data;

		linestream >> idNode;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> X_deg;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> Y_deg;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> X_rad;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> Y_rad;
		nodes.insert(pair<int,Node>(fakeIDN,Node(X_deg, Y_deg, X_rad, Y_rad)));
		tempconvN.insert(pair<unsigned long int, int>(idNode, fakeIDN));
		fakeIDN++;
	}

	inFile.close();


	//Ler as roads
	inFile.open(roads_path,std::fstream::in);

	if (!inFile) {
		cerr << "Unable to open file roads.txt";
		exit(1);   // call system to stop
	}

	unsigned long int idRoad = 0;
	string nameRoad = "";
	bool is2Way = false;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string data;


		linestream >> idRoad;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		getline(linestream, nameRoad,';'); //rea<< "+" << it->second.getLatitudeDeg()d name of road and discard ;
		linestream >> is2Way;
		roads.insert(pair<int,Road>(fakeIDR,Road(nameRoad, is2Way)));
		tempconvR.insert(pair<unsigned long int, int>(idRoad, fakeIDR));
		fakeIDR++;
	}

	inFile.close();


	//Ler as subroads
	inFile.open(subroads_path,std::fstream::in);

	if (!inFile) {
		cerr << "Unable to open file subroads.txt";
		exit(1);   // call system to stop
	}


	unsigned long int oNode = 0;
	unsigned long int dNode = 0;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string data;


		linestream >> idRoad;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> oNode;
		getline(linestream, data,';'); //read name of road and discard ;
		linestream >> dNode;
		if(roads.find(tempconvR.find(idRoad)->second)->second.getNodesID().size() == 0)
			roads.find(tempconvR.find(idRoad)->second)->second.addNodeID(tempconvN.find(oNode)->second);
		roads.find(tempconvR.find(idRoad)->second)->second.addNodeID(tempconvN.find(dNode)->second);
	}

	inFile.close();
}

void StreetMap::generateGraph() {
	map<int, Node>::iterator it = nodes.begin();
	map<int, Node>::iterator ite = nodes.end();

	while(it != ite){
		graph.addVertex(it->first);
		it++;
	}

	map<int, Road>::iterator itr = roads.begin();
	map<int, Road>::iterator itre = roads.end();

	while(itr != itre){
		for(unsigned int i = 0; i < itr->second.getNodesID().size() - 1; i++){
			int id1 = itr->second.getNodesID()[i];
			int id2 = itr->second.getNodesID()[i+1];
			//distance calculation
			double w = nodeDistance(&(nodes.find(id1)->second), &(nodes.find(id2)->second));
			graph.addEdge(id1, id2, w);
			if (itr->second.isIsTwoWay())
				graph.addEdge(id2, id1, w);
		}

		itr++;
	}
}

double nodeDistance(Node *n1, Node *n2) {
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = n1->getLatitudeRad();
	lon1r = n1->getLongitudeRad();
	lat2r = n2->getLatitudeRad();
	lon2r = n2->getLongitudeRad();
	u = sin((lat2r - lat1r)/2);
	v = sin((lon2r - lon1r)/2);
	return 2.0 * EARTH_RADIUS * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

void StreetMap::draw() {
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->setBackground("background.jpg");

	gv->createWindow(600, 600);
	int pixelY, pixelX;
	//= ((targetLat - minLat) / (maxLat - minLat)) * (maxYPixel - minYPixel)


	gv->defineVertexColor("blue");
	gv->defineEdgeCurved(false);
	gv->defineEdgeColor("black");

	map<int, Node>::iterator it = nodes.begin();
	map<int, Node>::iterator ite = nodes.end();

	while(it != ite){
		pixelY = ((it->second.getLatitudeDeg() - 41.17946) / (41.19294 - 41.17946)) * (600 - 0);
		pixelX = ((it->second.getLongitudeDeg() - -8.633804)/ (-8.627743 - -8.633804))*(600);
		gv->addNode(it->first,pixelX, -pixelY);
		gv->setVertexSize(it->first,1);
		it++;
	}

	map<int, Road>::iterator itr = roads.begin();
	map<int, Road>::iterator itre = roads.end();

	int kkk = 0;

	while(itr != itre){
		for(unsigned int i = 0; i < itr->second.getNodesID().size() - 1; i++){
			int id1 = itr->second.getNodesID()[i];
			int id2 = itr->second.getNodesID()[i+1];
			if (itr->second.isIsTwoWay())
				gv->addEdge(kkk,id1, id2, EdgeType::UNDIRECTED);
			else
				gv->addEdge(kkk,id1, id2, EdgeType::DIRECTED);
			gv->setEdgeThickness(kkk,5);
			kkk++;
		}
		itr++;
	}
	gv->rearrange();

}

void StreetMap::write() {

	map<int, Node>::iterator it = nodes.begin();
	map<int, Node>::iterator ite = nodes.end();

	cout << nodes.size() << endl;
	while(it != ite){
		cout << it->first << "  " << it->second.getLatitudeDeg() << "  " << it->second.getLongitudeDeg()<< "  " << it->second.getLatitudeRad() << "  "<< it->second.getLongitudeRad() << "\n";
		it++;
	}


	map<int, Road>::iterator itr = roads.begin();
	map<int, Road>::iterator itre = roads.end();

	while(itr != itre){
		cout << itr->first << "  " << itr->second.getName() << "  "  << itr->second.isIsTwoWay() << "  " ;
		for(int i = 0; i < itr->second.getNodesID().size(); i++){
			cout << itr->second.getNodesID()[i] << "  ";
		}
		cout << "\n";
		itr++;
	}
}

const Graph<int>& StreetMap::getGraph() const {
	return graph;
}

void StreetMap::setGraph(const Graph<int>& graph) {
	this->graph = graph;
}

const vector<itineraryPoint>& StreetMap::getItinerary() const {
	return itinerary;
}

void StreetMap::setItinerary(const vector<itineraryPoint>& itinerary) {
	this->itinerary = itinerary;
}

const map<int, Node>& StreetMap::getNodes() const {
	return nodes;
}

void StreetMap::setNodes(const map<int, Node>& nodes) {
	this->nodes = nodes;
}

const map<int, Road>& StreetMap::getRoads() const {
	return roads;
}

void StreetMap::addItinerary(const int nodeID, const string name) {
	itineraryPoint p;
	p.nodeID = nodeID;
	p.name = name;
	itinerary.push_back(p);
}

bool StreetMap::removeItinerary(const string name) {
	bool tmp = false;
	for (int i = 0; i < itinerary.size(); i++){
		if (itinerary[i].name == name){
			itinerary.erase(itinerary.begin() + i);
			tmp = true;
		}
	}
	return tmp;
}

void StreetMap::setRoads(const map<int, Road>& roads) {
	this->roads = roads;
}

int StreetMap::getNodeID(const string road){
	vector<int> tmp;
	map<int, Road>::iterator it = roads.begin();
	map<int, Road>::iterator ite = roads.end();

	while(it != ite){
		if(it->second.getName() == road){
			//concatenate all node IDs
			tmp.insert(tmp.end(),it->second.getNodesID().begin(), it->second.getNodesID().end());
		}
		it++;
	}
	if (tmp.size() != 0){
		int r = rand() % tmp.size();
		return tmp[r];
	}
	return -1;
}

int StreetMap::getNodeID(const string road1, const string road2){
	vector<int> tmp1;
	vector<int> tmp2;

	map<int, Road>::iterator it = roads.begin();
	map<int, Road>::iterator ite = roads.end();

	while(it != ite){
		if(it->second.getName() == road1){
			//concatenate all node IDs
			tmp1.insert(tmp1.end(),it->second.getNodesID().begin(), it->second.getNodesID().end());
		}
		if(it->second.getName() == road2){
			tmp2.insert(tmp2.end(),it->second.getNodesID().begin(), it->second.getNodesID().end());
		}
		it++;
	}

	for (int i = 0; i < tmp1.size(); i++){
		if (find(tmp2.begin(),tmp2.end(), tmp1[i]) != tmp2.end())
			return tmp1[i];
	}
	return -1;
}

bool StreetMap::calculateItinerary() {
	vector<int> tmp;
	graph.floydWarshallShortestPath();
	tmp = graph.getfloydWarshallPath(itinerary[0].nodeID, itinerary[1].nodeID);

	for (int i = 0; i < tmp.size(); i++){
		cout << tmp[i] << endl;
	}

	return (tmp.size() != 0);
}
