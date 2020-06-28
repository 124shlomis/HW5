
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
polynom::polynom(const polynom& PolyToCopy):func(PolyToCopy), n_(PolyToCopy.n_) {
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
        *FreeCoefficient = 0;
        *FreeCoefficient = this->coefs_[0] * MultiPoly.coefs_[0];
        polynom ProdPoly(0,FreeCoefficient);
        delete FreeCoefficient; // free memory after using
        return ProdPoly;
    } else { // case order is greater than zero.
        int MultiOrder = n_+MultiPoly.n_;
        int* coefs =new int[MultiOrder+1];
        for (int i=0; i<MultiOrder+1; i++){ // initialize coefs
            coefs[i]=0;
        }
        polynom ProdPoly(MultiOrder,coefs);
        delete [] coefs; // free memory after using
        for (int i=0; i < n_+1; i++){
            for (int j=0; j< MultiPoly.n_+1 ; j++){
                ProdPoly.coefs_[i+j] += coefs_[i]*MultiPoly.coefs_[j];
            }
        }
        return ProdPoly;
    }
}

// Derivative
polynom polynom::Derivative() const {
    if (n_ == 0 ){
        int* FreeCoefficient = new int;
        *FreeCoefficient = 0;
        polynom DerPoly(0,FreeCoefficient);
        delete FreeCoefficient; // free memory after using
        return DerPoly;
    } else {
        int* coefs = new int[n_];
        for (int i=1; i<n_+1 ; i++){ // start from x^1
            coefs[i-1] = i * coefs_[i] ;
        }
        polynom DerPoly(n_-1,coefs);
        delete [] coefs; // free memory after using
        return DerPoly;
    }
}


// Integral
polynom polynom::Integral() const{
    /* allocating new memory for new coefs */
    int* coefs = new int[n_+1];
    coefs[0] = 0; // need to print 'C' instead !!
    for (int i=0; i<n_+1 ; i++){ // start from x^1
        coefs[i+1] = coefs_[i] / (i+1);
    }
    polynom IntPoly(n_+1,coefs);
    delete [] coefs; // free memory after using
    return IntPoly;
}

// print
void polynom::print(ostream& os) const {
    printcoefs(os);
    os << endl;
    os << "Derivative: ";
    polynom d = Derivative();
    d.printcoefs(os);
    os << endl;
    os << "Integral: ";
    polynom i = Integral();
    i.printcoefs(os);
    os << "+C" << endl;
    if (!fmap_.empty()) {
        plot(os);
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



int main() {
	//Test 1:
	cout << "Test 1:" << endl;
	int a[2] = { 1, 3 };
	func* p1 = new polynom(1, a);
	cout << "p1 is: "<< *p1 << endl;
	//delete p1;
	int b[2] = { 1, 3 };
	func* p2 = new polynom(1, b);
	//cout << "p2 is: " << *p2 << endl;
	func* p3 = new polynom(*(polynom*)p1 + *(polynom*)p2);
	//cout << "after +: " << *p3 << endl;
	func* p4 = new polynom(*(polynom*)p2 - *(polynom*)p1);
	//cout << "after -: " << *p4 << endl;
	func* p5 = new polynom(*(polynom*)p1 * *(polynom*)p2);
	//cout << "after *: " << *p5 << endl;
	//auto* poly_p1 = (polynom*)p1;
	//poly_p1->Derivative();
	//cout << "p1 after Derivative: " << *p1 << endl;
	//auto* poly_p2 = (polynom*)p2;
	//poly_p2->Integral();
	//cout << "p2 after Integral: " << *p2 << endl;
	delete p1;
	delete p2;
	delete p3;
	delete p4;
	delete p5;
    /*
	//Test 2:
	cout << "Test 2:" << endl;
	int x[4] = { 1, 3, -6, -12 };
	p1 = new polynom(3, x);
	cout << "p1 is: "<< *p1 << endl;
	int y[4] = { 1, -3, 6, 12 };
	p2 = new polynom(3, y);
	cout << "p2 is: " << *p2 << endl;
	p3 = new polynom(*(polynom*)p1 + *(polynom*)p2);
	cout << "after +: " << *p3 << endl;
	p4 = new polynom(*(polynom*)p2 - *(polynom*)p1);
	cout << "after -: " << *p4 << endl;
	p5 = new polynom(*(polynom*)p1 * *(polynom*)p2);
	cout << "after *: " << *p5 << endl;
	poly_p1 = (polynom*)p1;
	poly_p1->Derivative();
	cout << "p1 after Derivative: " << *p1 << endl;
	poly_p2 = (polynom*)p2;
	poly_p2->Integral();
	cout << "p2 after Integral: " << *p2 << endl;
	delete p1;
	delete p2;
	delete p3;
	delete p4;
	delete p5;
     */
}
