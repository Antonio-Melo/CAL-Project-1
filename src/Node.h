#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Vertex {
	int id;
	double latitude_deg, longitude_deg, latitude_rad, longitude_rad;
public:
	Vertex(int id, double latitude_deg, double longitude_deg, double latitude_rad, double longitute_rad);
	void loadFromTxt(const char * path);
};


Vertex::Vertex(int id, double latitude_deg, double longitude_deg, double latitute_rad, double longitute_rad){
	this->id = id;
	this->latitude_deg = latitude_deg;
	this->latitude_rad = latitute_rad;
	this->longitude_deg = longitude_deg;
	this->longitude_rad = longitude_rad;
}

void Vertex::loadFromTxt(const char * path_node, const char * path_road){
	ifstream inFile;
	//Ler o ficheiro nos.txt
		inFile.open(path_node,std::fstream::in);

		if (!inFile) {
		    cerr << "Unable to open file datafile.txt";
		    exit(1);   // call system to stop
		}

		std::string   line;

		int idNo=0;
		int X_deg=0, X_rad = 0;
		int Y_deg=0, Y_rad = 0;

		while(getline(inFile, line))
		{
		    stringstream linestream(line);
		    string         data;

		    linestream >> idNo;

		    getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		    linestream >> X_deg;
		    getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		    linestream >> Y_deg;
		    getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		    linestream >> X_rad;
		    getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		    linestream >> Y_rad;
		    nodes.push_back(new Node(idNo, X_deg, Y_deg, X_rad, Y_rad));
		}

		inFile.close();


		//Ler o ficheiro arestas.txt
		inFile.open("arestas.txt");

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
			    roads.push_back(new Road(idRoad,nameRoad,is2Way));

			}

			inFile.close();
}
