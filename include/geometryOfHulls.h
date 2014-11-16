#ifndef BYKADOROV_ROMAN_GEOMETRY_OF_HULLS_H
#define BYKADOROV_ROMAN_GEOMETRY_OF_HULLS_H
#include <vector>
#include "point.h"
#include "line.h"

class GeometryOfHulls {
 public:
     std::vector<int> getSideElems(const std::vector<point> &vertex);
     int getTopElement(const std::vector<point> &vertex, const std::vector<int> &h, const line &topLine);
     void quickHull(const std::vector<point> &vertex, std::vector<int> &hull,
     int leftPos, int rightPos, const std::vector<int> &h);
     void quickHull(const std::vector<point> &vertex, std::vector<int> &hull);
     bool nesting(const std::vector<point> &vertex1, const std::vector<point> &vertex2,
     	const std::vector<int> &h1, const std::vector<int> &h2);
     bool intersection(const std::vector<point> &vertex1, const std::vector<point> &vertex2,
     	const std::vector<int> &h1, const std::vector<int> &h2);

 private:
     double fabs(double left);
     bool less (double left, double right);
     bool equal(double left, double right);
     int orientation(point p, point q, point r);
     bool intersection(point p1, point q1, point p2, point q2);
     bool onSegment(point p, point q, point r);
     void getPointsLeftByLine(const std::vector<point> &vertex,  const std::vector<int> &h,
         line &line, int topPos, int lrPos, std::vector<int> &leftSetPoints);
};

#endif // BYKADOROV_ROMAN_GEOMETRY_OF_HULLS_H