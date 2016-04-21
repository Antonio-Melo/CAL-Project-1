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

void addItineraryPoint() {
}

void removeItineraryPoint() {
	int index = -1;
	cout << "Insert index to remove from itinerary: " << endl;
	cin >> index;
	cin.ignore();
	if(!(streetmap->removeItinerary(index)))
		cout << "Point was not removed because index inserted is out of range." << endl;

}

void seeItinerary() {
	string sel;
	streetmap->addItinerary(56,"rua1");
	streetmap->addItinerary(2,"rua2");
	streetmap->calculateItinerary();
	streetmap->write();
	streetmap->draw();
	streetmap->drawItinerary();
	//streetmap->printItinerary();
	getline(cin,sel);
}

int main(){
	DIR *dir;
	struct dirent *ent;
	string map_folder;
	vector<string> maps;

	cout << "Welcome to Easy Pilot!" << endl;
	cout << "This is a simple 'GPS' that allows you to find the best way to your destination!" << endl;
	cout << "(Please note that this doesn't track your current location.)" << endl << endl;
	cout << "First of all enter the map you want to load (list of maps): " << endl;

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

	cout << "Loading Map" << endl;

	//Creating a StreetMap based on the input
	streetmap = new StreetMap("maps/" + map_folder);

	string selected = "";

	while (selected != "0"){

		if (streetmap->getItinerary().size() != 0){
			cout << "------------------------------" << endl;
			cout << "| #| Descriptor         |Node|" << endl;
			cout << "------------------------------" << endl;
			for(unsigned int i = 0; i < streetmap->getItinerary().size(); i++){
				cout << "|" << setw(2) << i << "|" << setw(20) << streetmap->getItinerary()[i].name << "|" << setw(4) << streetmap->getItinerary()[i].nodeID << "|" << endl;
			}
			cout << "------------------------------" << endl << endl;;
		} else {
			cout << "Itinerary is empty." << endl << endl;
		}

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
		} else {
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
