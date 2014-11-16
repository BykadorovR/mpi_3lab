#include "line.h"
#include "GeometryOfHulls.h"
#include <iostream>
#include <cmath>

// (y1-y2)*x + (x2-x1)*y + (x1*y2 - x2*y1) = 0
line::line(const point &l,const point &r) {
	l_ = l;
	r_ = r;
    a = r.getY() - l.getY();
    b = l.getX() - r.getX();
    c = r.getX()*l.getY() - l.getX()*r.getY();
}

double line::distanceToPoint(const point &point) const {
    return fabs(a*point.getX() + b*point.getY() + c)/sqrt((double)a*a + b*b);
}


bool line::isLeft(const point &point) {
    double left = a*point.getX() + b*point.getY() + c;
    std::cout<<left<<" Left "<<std::endl;
	//return ((point.getX()-l_.getX())*(point.getY()-r_.getY())-(point.getY()-l_.getY())*(point.getX()-r_.getX()))<0;
    return left < 0;
}

bool line::isRight(const point &point) {
	double right = a*point.getX() + b*point.getY() + c;
		//return ((point.getX()-l_.getX())*(point.getY()-r_.getY())-(point.getY()-l_.getY())*(point.getX()-r_.getX()))>0;
	return right > 0;
}

