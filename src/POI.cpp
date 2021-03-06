#include "POI.h"

POI::POI(int id, POIType type) {
	this->nodeID = id;
	this->type = type;
}

POI::~POI() {
	// TODO Auto-generated destructor stub
}

const int POI::getNodeID() const{
	return nodeID;
}

const POIType POI::getType() const{
		return type;
}
const string POI::toString() const{
	switch(type){
	case POMPGAS:
		return "F";
	case RESTAURANT:
		return "R";
	case HOTEL:
		return "H";
	default:
		return "O";
	}
}
