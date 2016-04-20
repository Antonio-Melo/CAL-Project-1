/*
 * Road.cpp
 *
 *  Created on: Apr 19, 2016
 *      Author: amelo
 */

#include "Road.h"

Road::Road(string name, bool is) {
	this->name = name;
	is_two_way = is;
}

bool Road::isIsTwoWay() const {
	return is_two_way;
}

void Road::setIsTwoWay(bool isTwoWay) {
	is_two_way = isTwoWay;
}

const string& Road::getName() const {
	return name;
}

const vector<unsigned long int> Road::getNodesID() const {
	return nodesID;
}

void Road::setNodesID(const vector<unsigned long int> nodesID) {
	this->nodesID = nodesID;
}

void Road::setName(const string& name) {
	this->name = name;
}

void Road::addNodeID(unsigned long int id){
	nodesID.push_back(id);
}
