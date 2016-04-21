/*
 * Poi.h
 *
 *  Created on: Apr 21, 2016
 *      Author: Antonio
 */

#ifndef SRC_POI_H_
#define SRC_POI_H_

#include "Node.h"

enum POIType{POMPGAS,RESTAURANT,HOTEL,FAVORITE};

class POI {
	int  nodeID;
	POIType type;
public:
	POI(int id, POIType type);
	virtual ~POI();
	const int getNodeID() const;
	const POIType getType() const;
};

#endif /* SRC_POI_H_ */
