/*
 * StreetMap.cpp
 *
 *  Created on: 19/04/2016
 *      Author: Telmo
 */

#include "StreetMap.h"
#include <map>

using namespace std;

StreetMap::StreetMap() {
	// TODO Auto-generated constructor stub

}

StreetMap::~StreetMap() {
	// TODO Auto-generated destructor stub
}

void StreetMap::loadFromTxt(const char *nodes_path, const char *roads_path, const char *subroads_path){
	ifstream inFile;
	//Ler os nodes
		inFile.open(nodes_path,std::fstream::in);

		if (!inFile) {
		    cerr << "Unable to open file datafile.txt";
		    exit(1);   // call system to stop
		}

		std::string   line;

		int idNode=0;
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
		    nodes.insert(pair<int,Node>(idNode,Node(X_deg, Y_deg, X_rad, Y_rad)));
		}

		inFile.close();


		//Ler as roads
		inFile.open(roads_path,std::fstream::in);

			if (!inFile) {
			    cerr << "Unable to open file datafile.txt";
			    exit(1);   // call system to stop
			}

			int idRoad = 0;
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
			    roads.insert(pair<int,Road>(idRoad,Road(nameRoad, is2Way)));

			}

			inFile.close();

			//Ler as subroads
			inFile.open(subroads_path,std::fstream::in);

				if (!inFile) {
				    cerr << "Unable to open file datafile.txt";
				    exit(1);   // call system to stop
				}


				int oNode = 0;
				int dNode = 0;

				while(getline(inFile, line))
				{
				    stringstream linestream(line);
				    string data;


				    linestream >> idRoad;

				    getline(linestream, data, ';');  // read up-to the first ; (discard ;).
				    linestream >> oNode;
				    getline(linestream, data,';'); //read name of road and discard ;
				    linestream >> dNode;
				    roads.find(idRoad)->second.addNode(&(nodes.find(idNode)->second));
				}

				inFile.close();

				map<int, Node>::iterator it = nodes.begin();
				map<int, Node>::iterator ite = nodes.end();

				while(it != ite){
					cout << it->first << "  " << it->second.getLatitudeDeg() << "  " << it->second.getLongitudeDeg()<< "  " << it->second.getLatitudeRad() << "  "<< it->second.getLongitudeRad() << "\n";
					it++;
				}

				map<int, Road>::iterator itr = roads.begin();
				map<int, Road>::iterator itre = roads.end();

				while(itr != itre){
					cout << itr->first << "  " << itr->second.getName() << "  "  << itr->second.isIsTwoWay() << "\n";
					itr++;
				}

}
