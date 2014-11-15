#include "geometryOfHulls.h"
#include <iostream>

std::vector<int> GeometryOfHulls::getSideElems(const std::vector<point> &vertex) {
	int rightPos = 0;
	int leftPos = 0;
	for (int i=1; i<vertex.size(); ++i) {
		if (less(vertex[i].getX(), vertex[leftPos].getX()))
			leftPos = i;
		else
			if (less(vertex[rightPos].getX(), vertex[i].getX()))
			    rightPos = i;
	}
	std::vector<int> LR (2);
	LR[0] = leftPos;
	LR[1] = rightPos;
	return LR;
}

int GeometryOfHulls::getTopElement(const std::vector<point> &vertex, const std::vector<int> &h,
	    const line &topLine) {
    double maxDistance = 0;
    int numberOfTop = 0;
    std::cout<<h.size()<<" SIZE";
	for (int i=0; i<h.size(); i++) {
		    double distance = topLine.distanceToPoint(vertex[h[i]]);
            if (distance > maxDistance) {
            	maxDistance = distance;
            	numberOfTop = h[i];
            }
	}
	std::cout<<vertex[numberOfTop].getX()<<" X "<<vertex[numberOfTop].getY()<<" Y"<<std::endl;
	return numberOfTop;
}

bool GeometryOfHulls::less (double left, double right) {
	if (left<right) return true;
	else return false;
}

