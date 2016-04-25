/*
 * Nope.cpp
 *
 *  Created on: Apr 19, 2016
 *      Author: Jorge
 */

#include "Node.h"

using namespace std;

Node::Node(double latitude_deg, double longitude_deg, double latitute_rad, double longitude_rad){
	this->latitude_deg = latitude_deg;
	this->latitude_rad = latitute_rad;
	this->longitude_deg = longitude_deg;
	this->longitude_rad = longitude_rad;
}

double Node::getLatitudeDeg() const {
	return latitude_deg;
}

void Node::setLatitudeDeg(double latitudeDeg) {
	latitude_deg = latitudeDeg;
}

double Node::getLatitudeRad() const {
	return latitude_rad;
}

void Node::setLatitudeRad(double latitudeRad) {
	latitude_rad = latitudeRad;
}

double Node::getLongitudeDeg() const {
	return longitude_deg;
}

void Node::setLongitudeDeg(double longitudeDeg) {
	longitude_deg = longitudeDeg;
}

double Node::getLongitudeRad() const {
	return longitude_rad;
}

void Node::setLongitudeRad(double longitudeRad) {
	longitude_rad = longitudeRad;
}

vector<int> Node::getRoadsID(){
	return RoadsID;
}

void Node::addRoadsID(int id){
	RoadsID.push_back(id);
}
