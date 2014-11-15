#ifndef BYKADOROV_ROMAN_GEOMETRY_OF_HULLS_H
#define BYKADOROV_ROMAN_GEOMETRY_OF_HULLS_H
#include <vector>
#include "point.h"
#include "line.h"

class GeometryOfHulls {
public:
 std::vector<int> getSideElems(const std::vector<point> &vertex);
 int getTopElement(const std::vector<point> &vertex, const std::vector<int> &h, const line &topLine);
private:
 bool less (double left, double right);
};

#endif // BYKADOROV_ROMAN_GEOMETRY_OF_HULLS_H