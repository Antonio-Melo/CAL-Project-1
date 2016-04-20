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

int main(){
	DIR *dir;
	struct dirent *ent;
	string map_folder;
	vector<string> maps;
	char sel;

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
	StreetMap* streetmap = new StreetMap("maps/" + map_folder);

	//Generating Graph/ Writing & Drawing
	streetmap->generateGraph();
	streetmap->write();
	streetmap->draw();
	string road1 = "y", road2 = "t";
	//getline(cin,road1);
	//getline(cin,road2);

	streetmap->addItinerary(56,road1);
	streetmap->addItinerary(2,road2);
	//cout << streetmap->getItinerary()[0].nodeID << streetmap->getItinerary()[0].name;
	//cout << streetmap->getItinerary()[1].nodeID << streetmap->getItinerary()[1].name;

	streetmap->calculateItinerary();

	//cout << streetmap->getNodeID(road1);
	cin >> sel;


	return 0;
}
