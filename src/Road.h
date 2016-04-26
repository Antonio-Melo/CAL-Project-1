/*
 * Road.h
 */

#ifndef SRC_ROAD_H_
#define SRC_ROAD_H_

#include <string>
#include "Node.h"

using namespace std;
/**
 * enum used to represent a type of a road
 */
enum roadType{HIGHWAY,NATIONAL,ROUTE};
/**
 * Class that represents a road, stores its name, type if it is two way or only one, price (not used) and the group of nodes that compose the road
 *
 */
class Road {
private:
	string name;
	bool is_two_way;
	roadType type;//HIGHWAY or NATIONAL or ROUTE
	vector<int> nodesID;
	double price;
public:
	/**
	 * Road constructor to generate roads
	 * @param string name that represents name of the road
	 * @param bool is that represents if the road is two ways or not
	 * @param roadType to represent the type of the road
	 */
	Road(string name,bool is,roadType type);
	/**
	 * Adds a id from a node to the vector
	 * @param id ID to be added
	 */
	void addNodeID(int id);
	/**
	 * Checks if the road is two ways
	 * @return if the road is two ways or not
	 */
	bool isIsTwoWay() const;
	/**
	 * Returns name of road
	 * @return string with the name of the road
	 */
	const string& getName() const;
	/**
	 * Returns nodes ID
	 * @return vector with all ID of the nodes in road
	 */
	const vector<int> getNodesID() const;
	/**
	 * Returns type of road
	 * @return string with the type of the road
	 */
	const roadType getType()const;
	/**
	 * Returns price of road
	 * @return double with the price of the road
	 */
	const double getPrice() const;
	/**
	 * Sets name to a road
	 * @param name new name to set
	 */
	void setName(const string& name);
	/**
	 * Sets if a road is two ways
	 * @param isTwoWay new is_two_way to set
	 */
	void setIsTwoWay(bool isTwoWay);
	/**
	 * Sets nodesID to a new vector
	 * @param nodesID New vector to set
	 */
	void setNodesID(const vector<int> nodesID);
};



#endif /* SRC_ROAD_H_ */
