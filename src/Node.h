#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * Class that represents Node in a map, Points of a road or intersection between roads, stores latitude also roads ID that have it
 */
class Node {
	double latitude_deg, longitude_deg, latitude_rad, longitude_rad;
	vector<int> RoadsID;
public:
	/**
	 * Node constructor to generate nodes
	 * @param double latitude_deg that represents latitude of node in degrees
	 * @param double longitude_deg that represents longitude of node in degrees
	 * @param double latitude_rad that represents longitude of node in rad
	 * @param double longitute_rad that represents longitude of node in rad
	 */
	Node(double latitude_deg, double longitude_deg, double latitude_rad, double longitute_rad);
	/**
	 * Returns latitude in degrees
	 * @return double with the latitude in degrees
	 */
	double getLatitudeDeg() const;
	/**
	 * Sets latitude_deg
	 * @param latitudeDeg new latitude_deg to be added
	 */
	void setLatitudeDeg(double latitudeDeg);
	/**
	 * Returns latitude in rad
	 * @return double with the latitude in rad
	 */
	double getLatitudeRad() const;
	/**
	 * Sets latitude_rad
	 * @param latitudeRad new latitude_rad to be added
	 */
	void setLatitudeRad(double latitudeRad);
	/**
	 * Returns longitude in degrees
	 * @return double with the longitude in degrees
	 */
	double getLongitudeDeg() const;
	/**
	 * Sets longitude_deg
	 * @param longitudeDeg new longitude_deg to be added
	 */
	void setLongitudeDeg(double longitudeDeg);
	/**
	 * Returns longitude in rad
	 * @return double with the longitude in rad
	 */
	double getLongitudeRad() const;
	/**
	 * Sets longitude_rad
	 * @param longitudeRad new longitude_rad to be added
	 */
	void setLongitudeRad(double longitudeRad);


	vector<int> getRoadsID();

	void addRoadsID(int id);

};

#endif
