#include <iostream>
#include <iomanip>
#include "StreetMap.h"
#include "Node.h"
#include "Road.h"
#include "Graph.h"
#include "graphviewer.h"
#include "dirent.h"
#include <vector>

using namespace std;

int main(){
	DIR *dir;
	struct dirent *ent;
	string map_folder;
	vector<string> maps;

	cout << "Welcome to easy pilot!" << endl;
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

	for (int i = 0; i < maps.size(); i++){
		cout << i << ": " << maps[i] << endl;
	}

	system("CLS");

	cout << "Loading Map" << endl;

	//StreetMap* streetmap = new StreetMap();
	/*streetmap->loadFromTxt("maps/" + map_folder + "/nodes.txt",
			"maps/" + map_folder + "roads.txt",
	//		"maps/" + map_folder + "subroads.txt");*/
	//streetmap->loadFromTxt("nodes.txt","roads.txt","subroads.txt");
	//streetmap->draw();
	char temp;
	cin >> temp;

	return 0;
}
