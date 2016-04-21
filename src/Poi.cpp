/*
 * Poi.cpp
 *
 *  Created on: Apr 21, 2016
 *      Author: Antonio
 */

#include "Poi.h"

Poi::Poi(Node n,poiType type) {
	this->n = n;
	this->type = type;
}

Poi::~Poi() {
	// TODO Auto-generated destructor stub
}

const Node Poi::getNode() const{
	return n;
}

const poiType Poi::getType() const{
		return type;
}

