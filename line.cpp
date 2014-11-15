#include "line.h"
#include <cmath>
#include <iostream>

// (y1-y2)*x + (x2-x1)*y + (x1*y2 - x2*y1) = 0
line::line(const point &l,const point &r) {
    a = r.getY() - l.getY();
    b = l.getX() - r.getX();
    c = r.getX()*l.getY() - l.getX()*r.getY();
}

double line::distanceToPoint(const point &point) const {
    return fabs(a*point.getX() + b*point.getY() + c)/sqrt((double)a*a + b*b);
}
int line::checkRelativePointAndLine(const point &point) const {
    int relative = a*point.getX() + b*point.getY() + c;
    std::cout<<relative<<" relative ";
    if (relative < 0) std::cout<<" Higher (Left) "<<std::endl;
    if (relative > 0) std::cout<<" Lower (Right) "<<std::endl;
    return relative;
}

