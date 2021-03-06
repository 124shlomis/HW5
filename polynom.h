#ifndef POLYNOM_H
#define POLYNOM_H

/* Includes */
#include "func.h"

/* Namespaces */
using namespace std;


class polynom : public func {

 public:

    polynom(int order, const int* arr);
    polynom(const polynom& PolyToCopy);
    ~polynom() override;
    polynom& operator=(const polynom& poly);
    polynom operator+(const polynom& polynom1) const;
    polynom operator-(const polynom& polynom1) const;
    polynom operator*(const polynom& polynom1) const;
    polynom Derivative() const;
    polynom Integral() const;
    void print(ostream& os) const override;
    void printcoefs(ostream&)  const ;

  protected:

  int n_; //order of the polynom
  int* coefs_{}; //coefficients
};

#endif // POLYNOM_H
 
