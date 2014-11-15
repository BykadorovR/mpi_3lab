#ifndef BYKADOROV_ROMAN_LINE_H
#define BYKADOROV_ROMAN_LINE_H
#include "point.h"

class line {
public:
 line();
 line(const point &l, const point &r);
 line(const line&);
 int checkRelativePointAndLine(const point &point) const;
 double distanceToPoint(const point &point) const;
 private:
 int a, b, c;
};
#endif // BYKADOROV_ROMAN_LINE_H