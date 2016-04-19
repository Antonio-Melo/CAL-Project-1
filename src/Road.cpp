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

const vector<Node*>& Road::getNodes() const {
	return nodes;
}

void Road::setNodes(const vector<Node*>& nodes) {
	this->nodes = nodes;
}

void Road::setName(const string& name) {
	this->name = name;
}

void Road::addNode(Node* n){
	nodes.push_back(n);
}
