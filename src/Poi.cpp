/*
 * Poi.cpp
 *
 *  Created on: Apr 21, 2016
 *      Author: Antonio
 */

#include "Poi.h"

Poi::Poi(int idNode,poiType type) {
	this->idNode = idNode;
	this->type = type;
}

Poi::~Poi() {
	// TODO Auto-generated destructor stub
}

const Node Poi::getNode() const{
	return idNode;
}

const poiType Poi::getType() const{
		return type;
}

