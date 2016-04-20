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

class Road {
private:
	string name;
	bool is_two_way;
	vector<int> nodesID;
public:
	Road(string name,bool is);
	bool isIsTwoWay() const;
	void setIsTwoWay(bool isTwoWay);
	const string& getName() const;
	void setName(const string& name);
	void addNodeID(int id);
	const vector<int> getNodesID() const;
	void setNodesID(const vector<int> nodesID);
};



#endif /* SRC_ROAD_H_ */
