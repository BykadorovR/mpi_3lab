#ifndef BYKADOROV_ROMAN_LINE_H
#define BYKADOROV_ROMAN_LINE_H
#include "point.h"

class line {
 public:
     line();
     line(const point &l, const point &r);
     line(const line&);
     bool isLeft(const point &point);
     bool isRight(const point &point);
     double distanceToPoint(const point &point) const;
     point l_, r_;
 private:
     double a, b, c;
};
#endif // BYKADOROV_ROMAN_LINE_H