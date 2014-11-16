#include "geometryOfHulls.h"
#include <iostream>
#include <algorithm>

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
	for (int i=0; i<h.size(); i++) {
		    double distance = topLine.distanceToPoint(vertex[h[i]]);
            if (distance > maxDistance) {
            	maxDistance = distance;
            	numberOfTop = h[i];
            }
	}
	return numberOfTop;
}

void GeometryOfHulls::quickHull(const std::vector<point> &vertex, std::vector<int> &hull) {
	 if (vertex.size() < 3)
        return;
    std::vector<int> lr(2);
	lr = getSideElems(vertex);
	std::cout<<std::endl<<lr[0]<<" LEFT "<<std::endl;
	std::cout<<lr[1]<<" RIGHT "<<std::endl;
	line topLine = line(vertex[lr[0]], vertex[lr[1]]);
	//Выше (левее)
	std::vector<int> h1;
	//Ниже (правее)
	std::vector<int> h2;
	for (int i=0; i<vertex.size(); ++i) {
		if (i!=lr[0] && i!=lr[1]) {
		    if (topLine.isLeft(vertex[i])) {
		    	h1.push_back(i);
		    }
		    if (topLine.isRight(vertex[i])) {
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
	int topPos = h[0];
	line topLine = line(vertex[leftPos], vertex[topPos]);
	double maxDist = lr.distanceToPoint(vertex[topPos]);
	for (int i=1; i<h.size(); i++) {
		if (h[i] != leftPos && h[i] != rightPos) {
			double curDist = lr.distanceToPoint(vertex[h[i]]);
			if (equal(maxDist, curDist)) {
				if (topLine.isLeft(vertex[h[i]])) {
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
    getPointsLeftByLine(vertex,h,LT,leftPos, topPos, S11);
    quickHull(vertex, hull, leftPos,topPos, S11);
    std::vector<int> S12;
    line TR = line(vertex[topPos],vertex[rightPos]);
    // формируем множество точек, находящихся слева от прямой TR
    getPointsLeftByLine(vertex, h,TR, topPos, rightPos ,S12);
    quickHull(vertex, hull, topPos, rightPos, S12);

}

bool GeometryOfHulls::less (double left, double right) {
	return !equal(left,right) && left<right;
}


double GeometryOfHulls::fabs(double left) {
    if (left<0)
        return -left;
    return left;
}

const double eps = 1e-8;
bool GeometryOfHulls::equal(double left, double right) {
    return fabs(left-right) <= eps;
}

void GeometryOfHulls::getPointsLeftByLine(const std::vector<point> &vertex, const std::vector<int> &h,
    line &line, int topPos, int lrPos, std::vector<int> &leftSetPoints) {
	for (int i=0; i<h.size(); i++)
    {
    	if (h[i] != topPos && h[i] != lrPos) {
	        if (line.isLeft(vertex[h[i]])) {
	            leftSetPoints.push_back(h[i]);
            }
        }
    }
}

bool GeometryOfHulls::nesting(const std::vector<point> &vertex1, const std::vector<point> &vertex2,
     	const std::vector<int> &h1, const std::vector<int> &h2){
	int start, end;
	bool isLeft = false;
	for (int j=0; j<h2.size(); j++) {
	    for (int i=0; i<h1.size(); i++) {
	    if (i==h1.size()-1) {
            start = h1[i];
            end = h1[0];
	    }
	    else {
	    	start = h1[i];
            end = h1[i+1];
	    }
	    line neighbourLine = line(vertex1[start], vertex1[end]);
	    std::cout<<vertex1[start].getX()<<" XS "<<vertex1[start].getY()<<" YS "<<std::endl;
	    std::cout<<vertex1[end].getX()<<" XE "<<vertex1[end].getY()<<" YE "<<std::endl;
	    if (neighbourLine.isLeft(vertex2[j])) {
	        std::cout<<" Is Left"<<std::endl;
	        isLeft = true;
	    }
	    else std::cout<<" Is Right"<<std::endl;
        }
        if (!isLeft)
        return true;
        isLeft = false;
    }
    return false;


}

bool GeometryOfHulls::intersection(const std::vector<point> &vertex1, const std::vector<point> &vertex2,
     	const std::vector<int> &h1, const std::vector<int> &h2) {
	/*if (intersection(point(1,0), point(1,1), point(1,1.1), point(0,1)))
		std::cout<<"POPAL";
	*/
	int start1, end1, start2, end2;
	for (int j=0; j<h2.size(); j++) {
		if (j==h2.size()-1) {
                start2 = h2[j];
                end2 = h2[0];
	        }
	    else {
	    	    start2 = h2[j];
                end2 = h2[j+1];
	        }
	    for (int i=0; i<h1.size(); i++) {
	    	if (i==h1.size()-1) {
                start1 = h1[i];
                end1 = h1[0];
	        }
	    else {
	    	    start1 = h1[i];
                end1 = h1[i+1];
	        }
	        //std::cout<<vertex1[start1].getX()<<vertex1[start1].getY()<<vertex1[end1].getX()<<vertex1[end1].getY()<<std::endl;
	        //std::cout<<vertex2[start2].getX()<<vertex2[start2].getY()<<vertex2[end2].getX()<<vertex2[end2].getY()<<std::endl;
	        if (intersection(vertex1[start1], vertex1[end1], vertex2[start2], vertex2[end2]))
	        	return true;

	    }
	}
	return false;
}

bool GeometryOfHulls::intersection(point p1, point q1, point p2, point q2) {
   // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4) {
    	std::cout<<"general";
        return true;
    }


    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
 }

int GeometryOfHulls::orientation(point p, point q, point r)
{
    double val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
              (q.getX() - p.getX()) * (r.getY() - q.getY());

    if (val < 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

bool GeometryOfHulls::onSegment(point p, point q, point r)
{
    if ((q.getX() - std::max(p.getX(), r.getX())) <= eps  && (q.getX()-std::min(p.getX(), r.getX())>= eps) &&
        (q.getY() -std::max(p.getY(), r.getY())<=eps ) && (q.getY() -std::min(p.getY(), r.getY())) >= eps )
       return true;

    return false;
}