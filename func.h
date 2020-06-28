#ifndef _FUNC
#define _FUNC

/* Includes */
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>

/* Namespace */
//using std::map;
//using std::ostream;
//using std::vector;
//using std::string;
using namespace std;

/* Defines */
#define UNINITIALIZED -100


class func {
public:	
	virtual ~func();
//operator<<
	virtual void print(ostream& os) const = 0; 		

 protected:  
	int maxVal_; //maximum of all inputs
	int minVal_; //minimum of all inputs
	map<int,int> fmap_; //holds inputs and corresponding outputs
    void plot(ostream& os) const ; //plot fmap_
};

ostream& operator<<(ostream& os, const func& rhs);	// Not friend because print method is public

#endif

