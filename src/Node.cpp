/*
 * Nope.cpp
 *
 *  Created on: Apr 19, 2016
 *      Author: Jorge
 */

#include "Node.h"

using namespace std;

Node::Node(int id, double latitude_deg, double longitude_deg, double latitute_rad, double longitute_rad){
	this->id = id;
	this->latitude_deg = latitude_deg;
	this->latitude_rad = latitute_rad;
	this->longitude_deg = longitude_deg;
	this->longitude_rad = longitude_rad;
}

