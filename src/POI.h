/*
 * Poi.h
 *
 *  Created on: Apr 21, 2016
 *      Author: Antonio
 */

#ifndef SRC_POI_H_
#define SRC_POI_H_

#include "Node.h"

/**
 * enum used to represent a type of a Point of Interest
 */
enum POIType{POMPGAS,RESTAURANT,HOTEL,FAVORITE};

/**
 * Class that represents Point of Interest (Filling Station, Hotel, Restaurant and Favorite), stores node where it locates and POI type
 */
class POI {
	int  nodeID;
	POIType type;
public:
	/**
	 * POI constructor to generate points of interest
	 * @param int id that represents the id of Point of Interest
	 * @param POIType type that represents the type of Point of Interest
	 */
	POI(int id, POIType type);
	/**
	 * POI destructor
	 */
	virtual ~POI();
	/**
	 * Returns id of POI
	 * @return int with id of POI
	 */
	const int getNodeID() const;
	/**
	 * Returns type of POI
	 * @return POIType with type of POI
	 */
	const POIType getType() const;
	/**
	 * Returns a string that identifies POI type
	 * @return String F, H, R, O corresponding to the type of the POI
	 */
	const string toString() const;
};

#endif /* SRC_POI_H_ */
