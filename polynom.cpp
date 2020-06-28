
/* Includes */
#include "polynom.h"

// C'tor
polynom::polynom(int order, const int* Coefs):func(),n_(order) {
    if (Coefs != nullptr){
        /* cloning data */
        coefs_ = new int[order+1];
        for (int i=0; i < order+1 ; i++){
            coefs_[i] = Coefs[i];
        }
    }
    else { // case CoefsArr == nullptr
        coefs_= nullptr;
    }
}

// Copy C'tor
polynom::polynom(const polynom& PolyToCopy):func(), n_(PolyToCopy.n_) {
    int OrderPolyCpy = PolyToCopy.n_;
    coefs_ = new int[OrderPolyCpy+1];
    for (int i=0; i < OrderPolyCpy+1 ; i++) { // cloning coefs.
        coefs_[i] = PolyToCopy.coefs_[i];
    }
    fmap_ = PolyToCopy.fmap_;
}

// D'tor
polynom::~polynom() {
    delete[] coefs_;
}

/* Operators */

polynom& polynom::operator=(const polynom &EqPoly) {
    if (this != &EqPoly){
        n_ = EqPoly.n_; // set new order;
        delete [] coefs_; // delete coefs and make new.
        coefs_ = new int[EqPoly.n_+1];
        for (int i=0; i<EqPoly.n_+1; i++){
            coefs_[i]=EqPoly.coefs_[i];
        }
    }
    return *this;
}

polynom polynom::operator+(const polynom& AddedPoly) const {
    if (n_ > AddedPoly.n_){ // case this.n_ greater than AddedPoly.n_
        polynom SumPoly(n_, coefs_); // construct new poly. initialize new poly with this coefs and order.
        for (int i=0 ; i < (AddedPoly.n_ + 1) ; i++){
            SumPoly.coefs_[i] += AddedPoly.coefs_[i]; // summing
        }
        return SumPoly;
    } else { // case AddedPoly.n_ greater than this.n_
        polynom SumPoly(AddedPoly.n_, AddedPoly.coefs_); // construct new poly. initialize new poly with AddedPoly coefs and order.
        for (int i=0 ; i< (n_+1) ; i++){
            SumPoly.coefs_[i] += coefs_[i]; // summing
        }
        return SumPoly;
    }
}

polynom polynom::operator-(const polynom& SubsPoly) const {
    if (n_ > SubsPoly.n_){ // case this.n_ greater than AddedPoly.n_
        polynom DiffPoly(n_,coefs_);  // construct new poly. initialize new poly with this coefs and order.
        for (int i=0 ; i < (SubsPoly.n_+1) ; i++){
            DiffPoly.coefs_[i] -= SubsPoly.coefs_[i]; // subtracting
        }
        return DiffPoly;
    } else { // case AddedPoly.n_ greater than this.n_
        polynom DiffPoly(SubsPoly.n_, SubsPoly.coefs_); // construct new poly. initialize new poly with SubsPoly coefs and order.
        for (int i=0 ; i < n_ + 1 ; i++){
            DiffPoly.coefs_[i] -= coefs_[i]; // subtracting
        }
        return DiffPoly;
    }
}

polynom polynom::operator*(const polynom &MultiPoly) const {
    if (n_ == 0 && MultiPoly.n_ == 0){ // case both order zero
        int* FreeCoefficient = new int;
        *FreeCoefficient = MultiPoly.coefs_[0] * coefs_[0];
        polynom ProdPoly(0,FreeCoefficient);
        delete FreeCoefficient; // free memory after using
        return ProdPoly;
    } else { // case order is greater than zero.
        int MultiOrder = n_+MultiPoly.n_+1;
        int* coefs =new int[MultiOrder];
        for (int i=0; i<MultiOrder; i++){ // initialize coefs
            coefs[i]=0;
        }
        polynom ProdPoly(MultiOrder,coefs);
        delete [] coefs; // free memory after using
        for (int i=0; i < MultiPoly.n_+1; i++){
            for (int j=0; j< n_+1 ; j++){
                ProdPoly.coefs_[i+j] = coefs_[i]*MultiPoly.coefs_[j];
            }
        }
        return ProdPoly;
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


