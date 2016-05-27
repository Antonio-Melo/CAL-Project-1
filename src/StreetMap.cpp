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
#include <time.h>
#include <math.h>

using namespace std;

StreetMap::StreetMap(string path) {
	loadFromTxt((path + "/nodes.txt").c_str(), (path + "/roads.txt").c_str(), (path + "/subroads.txt").c_str(), true);

	generateGraph();
	cout << "Graph generated !"<<endl;
}

StreetMap::~StreetMap() {
	// TODO Auto-generated destructor stub
}

void StreetMap::loadFromTxt(const char *nodes_path, const char *roads_path, const char *subroads_path, bool show_status){
	ifstream inFile;

	//Read nodes
	map<unsigned long int, int> tempconvN;
	map<unsigned long int, int> tempconvR;
	int count = 0;

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
	longMin = INT_INFINITY;
	longMax = -INT_INFINITY;
	latMin = INT_INFINITY;
	latMax = -INT_INFINITY;

	if (show_status) cout << "Loading nodes..." << endl;

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

		if(Y_deg < longMin) longMin = Y_deg;
		if(Y_deg > longMax) longMax = Y_deg;
		if(X_deg < latMin) latMin = X_deg;
		if(X_deg > latMax) latMax = X_deg;
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
	string nameRoad;
	bool is2Way;

	count = 0;
	if (show_status) cout << "Loading roads..." << endl;

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

		if (nameRoad.find("Autoestrada") != std::string::npos){
			rtype = HIGHWAY;
			if (show_status) cout << "HIGHWAY loaded! " <<endl;
		} else if (nameRoad.find("Nacional") != std::string::npos){
			rtype = NATIONAL;
			if (show_status) cout << "NATIONAL loaded! " <<endl;
		} else {
			rtype = ROUTE;
			if (show_status) cout << "ROAD loaded! " <<endl;
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

	count = 0;
	if (show_status) cout << "Loading subroads..." << endl;

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
		if(roads.find(tempconvR.find(idRoad)->second)->second.getNodesID().size() == 0){
			roads.find(tempconvR.find(idRoad)->second)->second.addNodeID(tempconvN.find(oNode)->second);
			nodes.find(tempconvN.find(oNode)->second)->second.addRoadsID(tempconvR.find(idRoad)->second);
		}
		roads.find(tempconvR.find(idRoad)->second)->second.addNodeID(tempconvN.find(dNode)->second);
		nodes.find(tempconvN.find(dNode)->second)->second.addRoadsID(tempconvR.find(idRoad)->second);

	}
	//Closing file
	inFile.close();


	//Choose random POI's
	int numofpois=2;
	int n;
	srand (time(NULL));
	if(nodes.size() > 100){
		numofpois = nodes.size()/100 *numofpois;
	}

	if (show_status) cout << "Loading Points of Interest..." <<endl;

	for(int i = 0;i < numofpois;i++){
		//Restaurants
		n = rand() % nodes.size();
		POI rest = POI(n,RESTAURANT);
		pois.push_back(rest);

		//Pomp Gas
		n = rand() % nodes.size();
		POI pomp = POI(n,POMPGAS);
		pois.push_back(pomp);

		//Hotels
		n = rand() % nodes.size();
		POI hotel = POI(n,HOTEL);
		pois.push_back(hotel);
	}

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
			double dist = nodeDistance(&(nodes.find(id1)->second), &(nodes.find(id2)->second));
			double time;
			bool toll = (itr->second.getType() == HIGHWAY);

			switch (itr->second.getType()){
			case HIGHWAY:
				time = 0.54545455 * dist;
				break;
			case NATIONAL:
				time = 0.75 * dist;
				break;
			case ROUTE:
				time = 1.5 * dist;
				break;
			default:
				time = 2 * dist;
				break;
			}
			graph.addEdge(id1, id2, dist, time, toll);
			if (itr->second.isIsTwoWay()){
				graph.addEdge(id2, id1, dist, time, toll);
			}

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
	GraphViewer *gv = new GraphViewer(DEFAULT_WIDTH, DEFAULT_HEIGHT, false);

	gv->setBackground("background.jpg");

	gv->createWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	int pixelY, pixelX;

	gv->defineVertexColor("blue");
	gv->defineEdgeCurved(false);
	gv->defineEdgeColor("black");

	map<int, Node>::iterator it = nodes.begin();
	map<int, Node>::iterator ite = nodes.end();

	while(it != ite){

		pixelY = ((it->second.getLatitudeDeg() - latMin) / (latMax - latMin)) * (-DEFAULT_HEIGHT) + DEFAULT_HEIGHT;
		pixelX = ((it->second.getLongitudeDeg() - longMin)/ (longMax - longMin))*(DEFAULT_WIDTH);
		gv->addNode(it->first,pixelX, pixelY);
		gv->setVertexSize(it->first,1);
		for(unsigned int i =0;i < pois.size();i++){
			if(pois.at(i).getNodeID() == it->first){
				gv->setVertexSize(it->first, 15);
				switch(pois.at(i).getType()){
				case POMPGAS:
					gv->setVertexIcon(it->first,"gastation.png");
					break;
				case RESTAURANT:
					gv->setVertexIcon(it->first,"dinner.png");
					break;
				case HOTEL:
					gv->setVertexIcon(it->first,"hotel.png");
					break;
				case FAVORITE:
					gv->setVertexIcon(it->first,"favourite.png");
					break;
				default:
					break;
				}
				break;
			}
		}

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

			gv->setEdgeThickness(edgeID,2);
			edgeID++;
		}
		itr++;
	}


	gv->rearrange();
	return gv;
}

const vector<POI>& StreetMap::getPois() const{
	return pois;
}

void StreetMap::setPois(const vector<POI>& pois) {
	this->pois = pois;
}

void StreetMap::drawItinerary(){
	GraphViewer* gv;
	gv = draw();

	gv->defineVertexColor(YELLOW);
	//print itinerary with other color
	for(unsigned int i = 0; i < path.size() - 1; i++){
		gv->addEdge(INT_INFINITY - i,path[i], path[i+1], EdgeType::DIRECTED);
		gv->setEdgeColor(INT_INFINITY - i, MAGENTA);

		gv->setEdgeThickness(INT_INFINITY - i,4);
	}
	gv->rearrange();

	string option = "A";
	while(option != "B"){
		for(unsigned int i = 0; i < path.size(); i++){
			gv->setVertexSize(path[i], 15);
			gv->setVertexIcon(path[i],"car.png");
			gv->rearrange();
			Sleep(1000);
		}
		for(unsigned int i = 0; i < path.size(); i++){
			gv->setVertexSize(path[i], 1);
			gv->setVertexIcon(path[i],"background.jpg");
		}
		gv->rearrange();
		cout << "Insert 'B' to go back to menu or other to repeat the animation" << endl;
		getline(cin, option);
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

const vector<itineraryPoint>& StreetMap::getItinerary() const {
	return itinerary;
}

void StreetMap::setItinerary(const vector<itineraryPoint>& itinerary) {
	this->itinerary = itinerary;
}

const map<int, Node>& StreetMap::getNodes() const {
	return nodes;
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
	if (index >= 0 && index < itinerary.size()){
		itinerary.erase(itinerary.begin() + index);
		return true;
	}
	return false;
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
	vector<int> tmp1;
	vector<int> tmp2;

	map<int, Road>::iterator it = roads.begin();
	map<int, Road>::iterator ite = roads.end();

	while(it != ite){
		if(it->second.getName() == road1){
			//concatenate all node IDs
			for (unsigned int i = 0; i < it->second.getNodesID().size(); i++){
				tmp1.push_back(it->second.getNodesID()[i]);
			}
		}
		if(it->second.getName() == road2){
			for (unsigned int i = 0; i < it->second.getNodesID().size(); i++){
				tmp2.push_back(it->second.getNodesID()[i]);
			}
		}
		it++;
	}

	for (unsigned int i = 0; i < tmp1.size(); i++){
		if (find(tmp2.begin(),tmp2.end(), tmp1[i]) != tmp2.end())
			return tmp1[i];
	}
	return -1;
}

bool StreetMap::calculateItinerary(bool dist, bool tolls) {
	path.clear();

	cout << "Calculating best way to your destination!" << endl;

	for(unsigned int i = 0; i < itinerary.size() - 1; i++){
		if (!(calculateItineraryAux(itinerary[i].nodeID, itinerary[i+1].nodeID, dist, tolls))){
			path.clear();
			return false;
		}
	}

	return true;
}

bool StreetMap::calculateItineraryAux(int nodeID1, int nodeID2, bool dist, bool tolls) {
	vector<int> tmp;

	graph.dijkstraShortestPath(nodeID1, dist, tolls);
	tmp = graph.getPath(nodeID1,nodeID2);

	path.insert(path.end(), tmp.begin(), tmp.end());

	return (tmp.size() > 1);
}

void StreetMap::insertPOI(POI p, GraphViewer* gv){
	pois.push_back(p);
	gv->setVertexIcon(p.getNodeID(),"favourite.png");
	gv->rearrange();
}


int StreetMap::closestPOIs(POIType type){

	double distance = INT_INFINITY;
	itineraryPoint iP;
	int id;
	iP = itinerary[itinerary.size()-1];

	for(int i = 0; i < pois.size(); i++){
		if(pois[i].getType() == type){
			if(distance > nodeDistance(&nodes.find(iP.nodeID)->second,&nodes.find(pois[i].getNodeID())->second)){
				distance = nodeDistance(&nodes.find(iP.nodeID)->second,&nodes.find(pois[i].getNodeID())->second);
				id = pois[i].getNodeID();
			}
		}
	}
	return id;
}

int StreetMap::checkRoadsID(Node n1, Node n2){
	for(int i = 0; i < n1.getRoadsID().size(); i++){
		for(int j = 0; j < n2.getRoadsID().size(); j++){
			if(n1.getRoadsID()[i] == n2.getRoadsID()[j])
				return n1.getRoadsID()[i];
		}
	}
}

string StreetMap::printItinerary(){
	stringstream ss;
	int tempID, lastID = -1;
	string tempRoad, leftOrright;
	tempID = checkRoadsID(nodes.find(path[0])->second, nodes.find(path[1])->second);
	lastID = checkRoadsID(nodes.find(path[0])->second, nodes.find(path[1])->second);
	ss << "Head to: " <<  roads.find(tempID)->second.getName() << endl;
	for(int i = 1; i < path.size()-1;i++){
		tempID = checkRoadsID(nodes.find(path[i])->second, nodes.find(path[i+1])->second);
		if(tempID != lastID){
			lastID = tempID;
			leftOrright = checkDirection(nodes.find(path[i-1])->second, nodes.find(path[i])->second, nodes.find(path[i+1])->second);
			tempRoad = roads.find(lastID)->second.getName();
			ss << "Turn " << leftOrright << " at " << tempRoad << endl;
		}
	}
	ss << "You arrived your destination!" << endl;
	cout << ss.str();
	return ss.str();
}

string StreetMap::checkDirection(Node n1, Node n2, Node n3){
	double lat_1, lat_2, lat_3, long_1, long_2, long_3;
	double angle;
	lat_1 = n1.getLatitudeDeg();
	long_1 = n1.getLongitudeDeg();
	lat_2 = n2.getLatitudeDeg();
	long_2 = n2.getLongitudeDeg();
	lat_3 = n3.getLatitudeDeg();
	long_3 = n3.getLongitudeDeg();

	double vect1coordx = long_1 - long_2;
	double vect1coordy = lat_1 -lat_2;
	double vect2coordx = long_3 - long_2;
	double vect2coordy = lat_3 -lat_2;
	double total, sqrt1;

	total = vect1coordx * vect2coordx + vect1coordy * vect2coordy;
	sqrt1 = sqrt(pow(vect1coordx,2) + pow(vect1coordy,2)) * sqrt(pow(vect2coordx,2) + pow(vect2coordy,2));

	angle = total/sqrt1;
	angle = acos(angle);

	double temp = vect2coordx*vect1coordy - vect2coordy*vect1coordx;

	if(temp > 0){
		if(angle < 180){
			return "left";
		}
		else return "right";
	}
	else{
		if(angle > 180){
			return "left";
		}
		else return "right";

	}
}
