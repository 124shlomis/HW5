#ifndef FUNC_H_
#define FUNC_H_

/* Includes */
#include <map>
#include <iostream>


/* Namespaces */
using namespace std;
using std::map;
using std::ostream;


class func {
 


 protected:
   
  
  int maxVal_; //maximum of all inputs
  int minVal_; //minimum of all inputs
  map<int,int> fmap_; //holds inputs and corresponding outputs
  void plot(ostream& os) const ; //plot fmap_
};


#endif // FUNC_H_
