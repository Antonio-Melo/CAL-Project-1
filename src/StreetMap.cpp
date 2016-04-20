/*
 * StreetMap.cpp
 *
 *  Created on: 19/04/2016
 *      Author: Telmo
 */

#include "StreetMap.h"
//#include <map>
#include <cmath>

using namespace std;

StreetMap::StreetMap(string path_1, string path_2, string path_3) {
	loadFromTxt(path_1.c_str(), path_2.c_str(), path_3.c_str());
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
	gv->defineEdgeColor("black");
	//gv->setEdgeCurved(false);

	map<int, Node>::iterator it = nodes.begin();
	map<int, Node>::iterator ite = nodes.end();

	while(it != ite){
		pixelY = ((it->second.getLatitudeDeg() - 41.17946) / (41.19294 - 41.17946)) * (600 - 0);
		pixelX = ((it->second.getLongitudeDeg() - -8.633804)/ (-8.627743 - -8.633804))*(600);
		gv->addNode(it->first,pixelX, -pixelY);
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
			kkk++;
		}
		itr++;
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
		for(int i = 0; i < itr->second.getNodesID().size(); i++){
			cout << itr->second.getNodesID()[i] << "  ";
		}
		cout << "\n";
		itr++;
	}
}
