/*
 * Poi.h
 *
 *  Created on: Apr 21, 2016
 *      Author: Antonio
 */

#ifndef SRC_POI_H_
#define SRC_POI_H_

#include "Node.h"

enum poiType{POMPGAS,RESTAURANT,HOTEL};

class Poi {
	Node n;
	poiType type;
public:
	Poi(Node n,poiType type);
	virtual ~Poi();
	const Node getNode() const;
	const poiType getType() const;
};

#endif /* SRC_POI_H_ */
