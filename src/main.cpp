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

using namespace std;

StreetMap *streetmap;


void seeItinerary() {
	string option;
	streetmap->calculateItinerary(true, true);
	streetmap->drawItinerary();
	//streetmap->printItinerary();
	//while(!cin.get());
}

void addItineraryPoint() {
	string option = "";
	while (option != "1" && option != "2" && option != "3" && option != "4" && option != "0"){
		cout << "1->Node ID;  2->Road;  3->Road Intersection;  4->POI;  0->Back;" << endl;
		getline(cin, option);
	}

	int id;
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
			//cout << i << ": " << streetmap->getPois()[i].getName();
		}
		getline(cin,poi);
		streetmap->addItinerary(id, poi); //falta funcao get nodeID by POI name
	}
}

void removeItineraryPoint() {
	int index = -1;
	cout << "Insert index to remove from itinerary: " << endl;
	cin >> index;
	cin.ignore();
	if(!(streetmap->removeItinerary(index)))
		cout << "Point was not removed because index inserted is out of range." << endl;

}


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
	streetmap->draw();

	string selected = "";

	while (selected != "0"){

		if (streetmap->getItinerary().size() != 0){
			cout << "_______________________________________" << endl;
			cout << "| #| Descriptor                  | Node|" << endl;
			cout << "|________________________________|_____|" << endl;
			for(unsigned int i = 0; i < streetmap->getItinerary().size(); i++){
				cout << "|" << setw(2) << i << "|" << setw(20) << streetmap->getItinerary()[i].name << "|" << setw(4) << streetmap->getItinerary()[i].nodeID << "|" << endl;
			}
		} else {
			cout << "Itinerary is empty." << endl;
		}

		//Print menu
		cout << "_______________________________________"  << endl;
		cout << "|                                      |" << endl;
		cout << "|              Easy Pilot              |" << endl;
		cout << "|                                      |" << endl;
		cout << "|   1. Calculate best way              |" << endl;
		cout << "|   2. Add to Itinerary                |" << endl;
		cout << "|   3. Remove from itinerary           |" << endl;
		cout << "|   0. Exit                            |" << endl;
		cout << "|                                      |" << endl;
		cout << "|______________________________________|" << endl << endl;

		getline(cin,selected);
		if (selected == "1"){
			if(streetmap->getItinerary().size() >= 0){
				seeItinerary();
			} else {
				cout << "Itinerary must have at least 2 points." << endl;
			}
		} else if (selected == "2"){
			addItineraryPoint();
		} else if (selected == "3"){
			removeItineraryPoint();
		} else if (selected != "0"){
			cout << "Insert valid option!" << endl;
		}
		//Generating Graph/ Writing & Drawing
		//streetmap->write();
		//streetmap->draw();
		//string road1 = "y", road2 = "t";
		//getline(cin,road1);
		//getline(cin,road2);

		//cout << streetmap->getItinerary()[0].nodeID << streetmap->getItinerary()[0].name;
		//cout << streetmap->getItinerary()[1].nodeID << streetmap->getItinerary()[1].name;

		//streetmap->calculateItinerary();

		//cout << streetmap->getNodeID(road1);

	}


	return 0;
}
