#include "polynom.h"

// Ctor
polynom::polynom(int order, const int* CoefsArr):func() {
    if (CoefsArr != nullptr){
        n_ = order; // set order
        /* cloning data */
        coefs_ = new int[order+1];
        for (int i=0; i < order+1 ; i++){
            coefs_[i] = CoefsArr[i];
        }
    }
}

// Copy Ctor

polynom::polynom(const polynom& PolyToCopy):func(PolyToCopy), n_(PolyToCopy.n_) { /*reminder*/
    int order = PolyToCopy.n_;
    coefs_ = new int[order+1];
    for (int i=0; i < order+1 ; i++) {
        coefs_[i] = PolyToCopy.coefs_[i];
    }
    fmap_ = PolyToCopy.fmap_;
}

polynom::~polynom() {
    delete[] coefs_;
}

/* Operators */
polynom& polynom::operator=(const polynom &poly) {
    if (this != &poly){
        n_ = poly.n_;
        delete [] coefs_;
        coefs_ = new int[poly.n_+1];
        for (int i=0; i<poly.n_+1; i++){
            coefs_[i]=poly.coefs_[i];
        }
    }
    return *this;
}

polynom polynom::operator+(const polynom& polynom1) const {
    if (n_ > polynom1.n_){
        polynom polynom2(n_,coefs_);
        for (int i=0; i<n_+1; i++){
            polynom2.coefs_[i] += polynom1.coefs_[i];
        }
        return polynom2;
    } else {
        polynom polynom2(polynom1.n_,polynom1.coefs_);
        for (int i=0; i<n_+1; i++){
            polynom2.coefs_[i] += coefs_[i];
        }
        return polynom2;
    }
}

polynom polynom::operator-(const polynom& polynom1) const {
    if (n_ > polynom1.n_){
        polynom polynom2(n_,coefs_);
        for (int i=0; i<n_+1; i++){
            polynom2.coefs_[i] += polynom1.coefs_[i];
        }
        return polynom2;
    } else {
        polynom polynom2(polynom1.n_,polynom1.coefs_);
        for (int i=0; i<n_+1; i++){
            polynom2.coefs_[i] += coefs_[i];
        }
        return polynom2;
    }
}




void polynom::printcoefs(ostream& os)  const {
  int allZero = 1;
  for (auto i = n_ ; i>=0; i--) {
    if (coefs_[i]>0) {
      allZero = 0;
      if(i!=n_){
	os << "+";
      }
      if (coefs_[i]!=1 || i==0){
	os << coefs_[i];
      }
      if(i>0) {
	os << "x";
	if (i>1) 
	  os << "^" << i ;
      }
    }
    else if(coefs_[i]<0) {
      allZero = 0;
      if (coefs_[i]!=-1 || i==0){
	os << coefs_[i];
      }
      else 
	os << "-";
      if(i>0) {
	os << "x";
	if (i>1) 
	  os << "^" << i ;
      }
    }
    else if(i==0 && allZero == 1){ //coefs_[i]==0
        os << "0";
	continue;
    }
  }
}
