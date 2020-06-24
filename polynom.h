#ifndef POLYNOM_H
#define POLYNOM_H

#include "func.h"

using namespace std;


class polynom : public func {
 public:
 
  void printcoefs(ostream&)  const ;

  protected:

  int n_; //order of the polynom
  int* coefs_; //coefficients 
};



#endif // POLYNOM_H
 
