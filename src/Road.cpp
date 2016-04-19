/*
 * Road.cpp
 *
 *  Created on: Apr 19, 2016
 *      Author: amelo
 */

#include "Road.h"


Road::Road(int id,string name, bool is) {
	this->name = name;
	this->id = id;
	is_two_way = is;
}

