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

void Road::addNodeID(int id){
	nodesID.push_back(id);
}

bool Road::isIsTwoWay() const {
	return is_two_way;
}

const string& Road::getName() const {
	return name;
}

const string Road::getType()const{
	return type;
}

const vector<int> Road::getNodesID() const {
	return nodesID;
}

void Road::setIsTwoWay(bool isTwoWay) {
	is_two_way = isTwoWay;
}


void Road::setNodesID(const vector<int> nodesID) {
	this->nodesID = nodesID;
}

void Road::setName(const string& name) {
	this->name = name;
}


