/*
 * StreetMap.cpp
 *
 *  Created on: 19/04/2016
 *      Author: Telmo
 */

#include "StreetMap.h"

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
		int X_deg=0, X_rad = 0;
		int Y_deg=0, Y_rad = 0;

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
		    nodes.insert(pair<int,Node>::(idNodenew Node(X_deg, Y_deg, X_rad, Y_rad)));
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
			    getline(linestream, nameRoad,';'); //read name of road and discard ;
			    linestream >> is2Way;
			    roads.insert(pair<int,Road>(idRoad,new Road(nameRoad, is2Way)));

			}

			inFile.close();

			//Ler as subroads
			inFile.open(subroads_path,std::fstream::in);

				if (!inFile) {
				    cerr << "Unable to open file datafile.txt";
				    exit(1);   // call system to stop
				}

				int idRoad = 0;
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
				    roads.find(idRoad)->second.addNode(nodes.find(idNode)->second);
				}

				inFile.close();
}
