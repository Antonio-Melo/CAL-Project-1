/*
 * Road.h
 *
 *  Created on: Apr 19, 2016
 *      Author: amelo
 */

#ifndef SRC_ROAD_H_
#define SRC_ROAD_H_

#include <string>
#include "Node.h"

using namespace std;

enum roadType{HIGHWAY,NATIONAL,ROUTE};

class Road {
private:
	string name;
	bool is_two_way;
	roadType type;//HIGHWAY or NATIONAL or ROUTE
	vector<int> nodesID;
	double price;
public:
	Road(string name,bool is,roadType type);
	void addNodeID(int id);
	bool isIsTwoWay() const;
	const string& getName() const;
	const vector<int> getNodesID() const;
	const roadType getType()const;
	const double getPrice() const;
	void setName(const string& name);
	void setIsTwoWay(bool isTwoWay);
	void setNodesID(const vector<int> nodesID);
};



#endif /* SRC_ROAD_H_ */
