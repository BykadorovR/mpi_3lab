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
	std::vector<int> lr (2);
	lr[0] = leftPos;
	lr[1] = rightPos;
	return lr;
}

int GeometryOfHulls::getTopElement(const std::vector<point> &vertex, const std::vector<int> &h,
	    const line &topLine) {
    double maxDistance = 0;
    int numberOfTop = 0;
    //std::cout<<h.size()<<" SIZE";
	for (int i=0; i<h.size(); i++) {
		    double distance = topLine.distanceToPoint(vertex[h[i]]);
            if (distance > maxDistance) {
            	maxDistance = distance;
            	numberOfTop = h[i];
            }
	}
	//std::cout<<vertex[numberOfTop].getX()<<" X "<<vertex[numberOfTop].getY()<<" Y"<<std::endl;
	return numberOfTop;
}

void GeometryOfHulls::quickHull(const std::vector<point> &vertex, std::vector<int> &hull) {
	 if (vertex.size() < 3)
        return;
    std::vector<int> lr(2);
	lr = getSideElems(vertex);
	//cout<<endl<<lr[0]<<" LEFT "<<endl;
	//cout<<lr[1]<<" RIGHT "<<endl;
	line topLine = line(vertex[lr[0]], vertex[lr[1]]);
	//Выше (левее)
	std::vector<int> h1;
	//Ниже (правее)
	std::vector<int> h2;
	for (int i=0; i<vertex.size(); ++i) {
	//	cout<<i<<" i "<<lr[0]<<" lr[0] "<<endl;
	//	cout<<i<<" i "<<lr[1]<<" lr[1] "<<endl;
		if (i!=lr[0] && i!=lr[1]) {
		    if (topLine.checkRelativePointAndLine(vertex[i]) > 0) {
		    	h1.push_back(i);
		    }
		    if (topLine.checkRelativePointAndLine(vertex[i]) < 0) {
		        h2.push_back(i);
		    }
		}
    }

    quickHull(vertex, hull, lr[0], lr[1], h1);
    quickHull(vertex, hull, lr[1], lr[0], h2);
}

void GeometryOfHulls::quickHull(const std::vector<point> &vertex, std::vector<int> &hull,
     int leftPos, int rightPos, const std::vector<int> &h) {
	if (h.size()==0) {
		hull.push_back(rightPos);
		return;
	}

	line lr(vertex[leftPos],vertex[rightPos]);
	//Предпологаем, что 1 точка самая высокая (точка отсчета)
	int topPos = h[0];
	line topLine = line(vertex[leftPos], vertex[topPos]);
	double maxDist = lr.distanceToPoint(vertex[topPos]);
	for (int i=1; i<h.size(); ++i) {
		if (h[i] != leftPos && h[i] != rightPos) {
			double curDist = lr.distanceToPoint(vertex[i]);
			if (equal(maxDist, curDist)) {
				if (topLine.checkRelativePointAndLine(vertex[h[i]]) > 0) {
					topPos = h[i];
					topLine = line(vertex[leftPos], vertex[topPos]);
				}
			}
			if (less(maxDist, curDist)) {
				maxDist = curDist;
				topPos = h[i];
				topLine = line(vertex[leftPos], vertex[topPos]);
			}
		}
	}

	std::vector<int> S11;
    line LT = line(vertex[leftPos],vertex[topPos]);
    // формируем множество точек, находящихся слева от прямой LT
    getPointsLeftByLine(vertex,h,LT,S11);
    quickHull(vertex, hull, leftPos,topPos, S11);

    std::vector<int> S12;
    line TR = line(vertex[topPos],vertex[rightPos]);
    // формируем множество точек, находящихся слева от прямой TR
    getPointsLeftByLine(vertex, h,TR,S12);
    quickHull(vertex, hull, topPos, rightPos, S12);
}

bool GeometryOfHulls::less (double left, double right) {
	if (left<right) return true;
	else return false;
}


double GeometryOfHulls::fabs(double left)
{
    if (left<0)
        return -left;
    return left;
}

const double eps = 1e-8;
bool GeometryOfHulls::equal(double left, double right)
{
    return fabs(left-right) <= eps;
}

void GeometryOfHulls::getPointsLeftByLine(const std::vector<point> &vertex, const std::vector<int> &h,
    line &line, std::vector<int> &leftSetPoints)
{
    for (int i=0; i<h.size(); ++i)
    {
        if (line.checkRelativePointAndLine(vertex[h[i]])>0)
            leftSetPoints.push_back(h[i]);
    }
}