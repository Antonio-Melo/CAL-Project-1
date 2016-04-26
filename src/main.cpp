#include <iostream>
#include <iomanip>
#include "StreetMap.h"
#include "Node.h"
#include "Road.h"
#include "Graph.h"
#include "graphviewer.h"
#include "dirent.h"
#include <vector>
#include <algorithm>
#include "POI.h"

using namespace std;

StreetMap *streetmap;

/**
 * Interface to select itinerary mode (distance or time, with or without tolls)
 * Shows itinerary graphically
 */
void seeItinerary() {
	string option = "A";
	bool dist,tolls;
	cout << "Best way by time or distance?(T/D)" << endl;
	while (option != "D" && option != "T"){
	getline(cin, option);
	if(option == "D")
		dist = true;
	else if(option == "T")
		dist = false;
	}
	cout << "Do you want to avoid tolls?(Y/N)"<< endl;
	while (option != "Y" && option != "N"){
		getline(cin, option);
	if(option == "Y")
		tolls = false;
	else if(option == "N")
		tolls = true;
	}
	if(streetmap->calculateItinerary(dist, tolls)){
		streetmap->printItinerary();
		streetmap->drawItinerary();
	} else {
		cout << "There is no way to travel your itinerary..." << endl;
	}
}

/**
 * Adds point to itinerary
 * A new point can be added by giving its ID, road name, roads intersections or POI
 */
void addItineraryPoint() {
	string option = "";
	while (option != "1" && option != "2" && option != "3" && option != "4" && option != "0"){
		cout << "1->Node ID;  2->Road;  3->Road Intersection;  4->POI;  0->Back;" << endl;
		getline(cin, option);
	}

	int id = -1;
	if (option == "1"){
		cout << "Node ID:" << endl;
		cin >> id;
		cin.ignore();
		if (id < streetmap->getNodes().size()){
			stringstream tmp;
			tmp << id;
			streetmap->addItinerary(id, tmp.str());
		} else {
			cout << "Point was not added because ID inserted is out of range." << endl;
			return;
		}
	} else if (option == "2"){
		string road1;
		cout << "Road:" << endl;
		getline(cin, road1);
		id = streetmap->getNodeID(road1);
		if (id != -1){
			streetmap->addItinerary(id, road1);
		} else {
			cout << "Point was not added because road inserted was not found." << endl;
			return;
		}
	} else if (option == "3"){
		string road1;
		string road2;
		cout << "Road 1:" << endl;
		getline(cin, road1);

		cout << "Road 2:" << endl;
		getline(cin, road2);
		id = streetmap->getNodeID(road1,road2);
		if (id != -1){
			streetmap->addItinerary(id, road1 + "|" + road2);
		} else {
			cout << "Point was not added because roads inserted don't intersect." << endl;
			return;
		}

	} else if (option == "4"){
		string poi;
		cout << "POI:" << endl;
		for (int i = 0; i < streetmap->getPois().size(); i++){
			cout << setw(3) << i << ": " << streetmap->getPois()[i].getNodeID() << "  " << streetmap->getPois()[i].toString() << endl;
		}
		if (streetmap->getItinerary().size() >= 1){
			cout << "  F: Closest Filling Station" << endl;
			cout << "  H: Closest Hotel" << endl;
			cout << "  R: Closest Restaurant" << endl;
		}
		getline(cin,poi);
		if (streetmap->getItinerary().size() >= 1){
			if (poi == "F"){
				id = streetmap->closestPOIs(POMPGAS);
			} else if (poi == "H"){
				id = streetmap->closestPOIs(HOTEL);
			} else if (poi == "R"){
				id = streetmap->closestPOIs(RESTAURANT);
			}
		}

		if (id == -1){
			int index;
			istringstream(poi) >> index;

			if (index < 0 || index > streetmap->getPois().size() - 1){
				cout << "Point was not added because POI inserted is out of range." << endl;
				return;
			}

			id = streetmap->getPois()[index].getNodeID();
			poi = streetmap->getPois()[index].toString();

		}

		streetmap->addItinerary(id, poi); //falta funcao get nodeID by POI name
	}
}

/**
 * Removes point from current itinerary by giving index
 */
void removeItineraryPoint() {
	int index = -1;
	cout << "Insert index to remove from itinerary: " << endl;
	cin >> index;
	cin.ignore();
	if(!(streetmap->removeItinerary(index)))
		cout << "Point was not removed because index inserted is out of range." << endl;

}

/**
 * Insert new POI into map
 */
void insertPoi(GraphViewer* gv){
	int id;
	bool found= false;

	while (!found){
		cout << "Node(id) of Point of Interest?"<< endl;
		cin >> id;
		cin.ignore();
		if (id < streetmap->getNodes().size() && id >=0 ) {
			stringstream tmp;
			tmp << id;
			streetmap->addItinerary(id, tmp.str());
			found = true;
		} else {
			cout << "Point was not added because ID inserted is out of range."
					<< endl;
			return;
		}
	}
	POI p = POI(id,FAVORITE);

	streetmap->insertPOI(p,gv);

}

/**
 * Point of entry to the program
 * Interface to select map
 * Load map
 * Calculate best way to travel the itinerary
 * Add new pooint to the itinerary
 * Remove point from the itinerary
 */
int main(){
	DIR *dir;
	struct dirent *ent;
	string map_folder;
	vector<string> maps;
	cout << "_________________________________________________________________________________"  <<endl;
	cout << "|                                                                                |"  <<endl;
	cout << "|Easy Pilot CAL 2015/2016                                                        |" << endl;
	cout << "|Welcome!                                                                        |" << endl;
	cout << "|This is a simple 'GPS' that allows you to find the best way to your destination!|" << endl;
	cout << "|(Please note that this doesn't track your current location.)                    |" << endl;
	cout << "|By: António Melo & Jorge Vale & Telmo Barros                                    |" <<endl;
	cout << "|________________________________________________________________________________|" << endl << endl;
	cout << "First of all enter the map you want to load (list of maps):" << endl;

	if ((dir = opendir ("maps")) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL) {
			if (ent->d_type == DT_DIR)
				if((strcmp(ent->d_name,".") != 0) && (strcmp(ent->d_name,"..") != 0))
					maps.push_back(ent->d_name);
		}
		closedir (dir);
	} else {
		/* could not open directory */
		perror ("");
		cout << "Your maps folder looks corrupted, fix it and try again" << endl;
		return EXIT_FAILURE;
	}

	for (unsigned int i = 0; i < maps.size(); i++){
		cout << i << ": " << maps[i] << endl;
	}

	while (find(maps.begin(), maps.end(), map_folder) == maps.end()){
		getline(cin,map_folder);
	}

	//system("CLS");

	cout << "Loading Map" << endl << endl;

	//Creating a StreetMap based on the input
	streetmap = new StreetMap("maps/" + map_folder);

	//streetmap->write();
	GraphViewer* gv =streetmap->draw();

	string selected = "";

	while (selected != "0"){

		if (streetmap->getItinerary().size() != 0){
			cout << " _______________________________________" << endl;
			cout << "| #| Descriptor                   | Node|" << endl;
			cout << "|__|______________________________|_____|" << endl;
			for(unsigned int i = 0; i < streetmap->getItinerary().size(); i++){
				cout << "|" << setw(2) << i << "|" << setw(30) << streetmap->getItinerary()[i].name << "|" << setw(5) << streetmap->getItinerary()[i].nodeID << "|" << endl;
			}
		} else {
			cout << "Itinerary is empty." << endl;
		}

		//Print menu
		cout << "|_______________________________________|"  << endl;
		cout << "|                                       |" << endl;
		cout << "|              Easy Pilot               |" << endl;
		cout << "|                                       |" << endl;
		cout << "|   1. Calculate best way               |" << endl;
		cout << "|   2. Add to Itinerary                 |" << endl;
		cout << "|   3. Remove from itinerary            |" << endl;
		cout << "|   4. Insert Point of Interest         |" << endl;
		cout << "|   0. Exit                             |" << endl;
		cout << "|                                       |" << endl;
		cout << "|_______________________________________|" << endl << endl;

		getline(cin,selected);
		if (selected == "1"){
			if(streetmap->getItinerary().size() >= 2){
				seeItinerary();
			} else {
				cout << "Itinerary must have at least 2 points." << endl;
			}
		} else if (selected == "2"){
			addItineraryPoint();
		} else if (selected == "3"){
			removeItineraryPoint();
		} else if (selected == "4"){
			insertPoi(gv);
		} else if (selected != "0"){
			cout << "Insert valid option!" << endl;
		}

	}


	return 0;
}
