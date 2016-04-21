/*
 * StreetMap.cpp
 *
 *  Created on: 19/04/2016
 *      Author: Telmo
 */

#include "StreetMap.h"
#include <cmath>
#include <stdlib.h>
#include <algorithm>

using namespace std;

StreetMap::StreetMap(string path) {
	loadFromTxt((path + "/nodes.txt").c_str(), (path + "/roads.txt").c_str(), (path + "/subroads.txt").c_str());

	generateGraph();

	graph.floydWarshallShortestPath();
}

StreetMap::~StreetMap() {
	// TODO Auto-generated destructor stub
}

void StreetMap::loadFromTxt(const char *nodes_path, const char *roads_path, const char *subroads_path){
	ifstream inFile;

	//Read nodes
	map<unsigned long int, int> tempconvN;
	map<unsigned long int, int> tempconvR;
	inFile.open(nodes_path,std::fstream::in);

	//Error opening nodes.txt
	if (!inFile) {
		cerr << "Unable to open file nodes.txt";
		exit(1);   // call system to stop
	}

	string   line;


	unsigned long int idNode=0;
	int fakeIDN = 0, fakeIDR = 0;
	double X_deg=0, X_rad = 0;
	double Y_deg=0, Y_rad = 0;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string         data;

		linestream >> idNode; //idNode

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> X_deg; //x_deg
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> Y_deg; //y_deg
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> X_rad; //x_rad
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> Y_rad; //y_rad
		//Insert to map nodes
		nodes.insert(pair<int,Node>(fakeIDN,Node(X_deg, Y_deg, X_rad, Y_rad)));
		tempconvN.insert(pair<unsigned long int, int>(idNode, fakeIDN));
		fakeIDN++;
	}
	//Close nodes.txt
	inFile.close();


	//Read roads
	inFile.open(roads_path,std::fstream::in);

	//Error opening roads.txt
	if (!inFile) {
		cerr << "Unable to open file roads.txt";
		exit(2);   // call system to stop
	}

	unsigned long int idRoad = 0;
	string nameRoad = "";
	bool is2Way;

	while(getline(inFile, line))
	{
		is2Way = true;
		stringstream linestream(line);
		string data;
		string type;
		string is2_Way;
		roadType rtype;


		linestream >> idRoad; //idRoad

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).

		getline(linestream, nameRoad, ';');  // read up-to the first ; (discard ;).

		if (nameRoad.find("Autoestrada") == 0){
			rtype = HIGHWAY;
		} else if (nameRoad.find("Nacional") == 0){
			rtype = NATIONAL;
		} else {
			rtype = ROUTE;
		}

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).

		linestream >> is2_Way;
		if(is2_Way == "true"){
			is2Way = false;
		}
		roads.insert(pair<int,Road>(fakeIDR,Road(nameRoad, is2Way,rtype)));
		tempconvR.insert(pair<unsigned long int, int>(idRoad, fakeIDR));
		fakeIDR++;
	}

	inFile.close();


	//Read Sub Roads
	inFile.open(subroads_path,std::fstream::in);

	//Error opening subroads.txt
	if (!inFile) {
		cerr << "Unable to open file subroads.txt";
		exit(3);   // call system to stop
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
		//Add sub nodes to Road
		if(roads.find(tempconvR.find(idRoad)->second)->second.getNodesID().size() == 0)
			roads.find(tempconvR.find(idRoad)->second)->second.addNodeID(tempconvN.find(oNode)->second);
		roads.find(tempconvR.find(idRoad)->second)->second.addNodeID(tempconvN.find(dNode)->second);
	}
	//Closing file
	inFile.close();
}

void StreetMap::generateGraph() {
	map<int, Node>::iterator it = nodes.begin();
	map<int, Node>::iterator ite = nodes.end();

	//Adding Vertexes
	while(it != ite){
		graph.addVertex(it->first);
		it++;
	}

	map<int, Road>::iterator itr = roads.begin();
	map<int, Road>::iterator itre = roads.end();

	//Adding Roads
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

GraphViewer* StreetMap::draw() {
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

	int edgeID = 0;

	while(itr != itre){
		for(unsigned int i = 0; i < itr->second.getNodesID().size() - 1; i++){
			int id1 = itr->second.getNodesID()[i];
			int id2 = itr->second.getNodesID()[i+1];

			if (itr->second.isIsTwoWay())
				gv->addEdge(edgeID,id1, id2, EdgeType::UNDIRECTED);
			else
				gv->addEdge(edgeID,id1, id2, EdgeType::DIRECTED);

			switch(itr->second.getType()){
			case HIGHWAY :
				gv->setEdgeColor(edgeID, BLUE);
				break;
			case NATIONAL :
				gv->setEdgeColor(edgeID, GREEN);
				break;
			case ROUTE :
				gv->setEdgeColor(edgeID, GRAY);
				break;
			default:
				break;
			}

			if(i == 0){
				gv->setEdgeLabel(edgeID, itr->second.getName());
			}

			gv->setEdgeThickness(edgeID,5);
			edgeID++;
		}
		itr++;
	}


	gv->rearrange();
	return gv;

}

void StreetMap::drawItinerary(){
	GraphViewer* gv;
	gv = draw();
	/*for(int i = 0; paths.size(); i++){
		gv->addEdge();
		gv->setEdgeColor();
	}*/
	gv->defineVertexColor(YELLOW);
	while(1){
		for(int i = 0; i < path.size(); i++){
			gv->setVertexSize(path[i], 15);
			gv->rearrange();
			Sleep(1000);
		}
		for(int i = 0; i < path.size(); i++){
			gv->setVertexSize(path[i], 1);
		}
		gv->rearrange();
	}
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
		for(unsigned int i = 0; i < itr->second.getNodesID().size(); i++){
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

bool StreetMap::removeItinerary(const unsigned int index) {
	//bool tmp = false;
	/*for (unsigned int i = 0; i < itinerary.size(); i++){
		if (itinerary[i].name == name){
			itinerary.erase(itinerary.begin() + i);
			tmp = true;
		}
	}*/
	if (index >= 0 && index <= itinerary.size()){
		itinerary.erase(itinerary.begin() + index);
		return true;
	}
	return false;
	//return tmp;
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
			for (unsigned int i = 0; i < it->second.getNodesID().size(); i++){
				tmp.push_back(it->second.getNodesID()[i]);
			}
			//tmp.resize(it->second.getNodesID().size());
				//tmp.insert(tmp.end(),it->second.getNodesID().begin(), it->second.getNodesID().end()); //not working because of memory issue
		}
		it++;
	}

	cout << tmp.size();

	if (tmp.size() != 0){
		cout << tmp.size();
		int r = rand() % tmp.size();
		return tmp[r];
	}
	return -1;
}

int StreetMap::getNodeID(const string road1, const string road2){
	vector<int> tmp1 = {};
	vector<int> tmp2 = {};

	map<int, Road>::iterator it = roads.begin();
	map<int, Road>::iterator ite = roads.end();

	while(it != ite){
		if(it->second.getName() == road1){
			//concatenate all node IDs
			for (unsigned int i = 0; i < it->second.getNodesID().size(); i++){
				tmp1.push_back(it->second.getNodesID()[i]);
			}
			//tmp1.insert(tmp1.end(),it->second.getNodesID().begin(), it->second.getNodesID().end());
		}
		if(it->second.getName() == road2){
			for (unsigned int i = 0; i < it->second.getNodesID().size(); i++){
				tmp2.push_back(it->second.getNodesID()[i]);
			}
			//tmp2.insert(tmp2.end(),it->second.getNodesID().begin(), it->second.getNodesID().end());
		}
		it++;
	}

	for (unsigned int i = 0; i < tmp1.size(); i++){
		if (find(tmp2.begin(),tmp2.end(), tmp1[i]) != tmp2.end())
			return tmp1[i];
	}
	return -1;
}

bool StreetMap::calculateItinerary() {
	path.clear();

	for(int i = 0; i < itinerary.size() - 1; i++){
		if (!(calculateItineraryAux(itinerary[i].nodeID, itinerary[i+1].nodeID)))
			return false;
	}

	for (unsigned int i = 0; i < path.size(); i++){
		cout << path[i] << endl;
	}

	return true;
}

bool StreetMap::calculateItineraryAux(int nodeID1, int nodeID2) {
	vector<int> tmp;
	tmp = graph.getfloydWarshallPath(nodeID1, nodeID2);

	path.insert(path.end(), tmp.begin(), tmp.end());

	return (path.size() != 0);
}
