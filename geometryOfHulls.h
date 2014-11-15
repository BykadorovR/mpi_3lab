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
private:
 bool less (double left, double right);
 bool equal(double left, double right);
 double fabs(double left);
 void getPointsLeftByLine(const std::vector<point> &vertex,  const std::vector<int> &h,
     line &line, std::vector<int> &leftSetPoints);
};

#endif // BYKADOROV_ROMAN_GEOMETRY_OF_HULLS_H