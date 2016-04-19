/*
 * Road.h
 *
 *  Created on: Apr 19, 2016
 *      Author: amelo
 */

#ifndef SRC_ROAD_H_
#define SRC_ROAD_H_

#include <string>

using namespace std;

class Road {
private:
	string name;
	int id;
	bool is_two_way;
public:
	Road(string name,bool is);
	addNode(Node &n);
};



#endif /* SRC_ROAD_H_ */
