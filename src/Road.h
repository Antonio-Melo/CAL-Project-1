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
	vector<Node *> nodes;
public:
	Road(string name,bool is);
	bool isIsTwoWay() const;
	void setIsTwoWay(bool isTwoWay);
	const string& getName() const;
	void setName(const string& name);
	void addNode(Node* n);
	const vector<Node*>& getNodes() const;
	void setNodes(const vector<Node*>& nodes);
};



#endif /* SRC_ROAD_H_ */
