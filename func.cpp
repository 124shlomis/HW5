/* Includes */
#include "func.h"



void func::plot(ostream& os) const {

	vector<int> sortImage;
	//map<int, int>::iterator it;
	sortImage.clear();

	for (auto it = fmap_.begin(); it != fmap_.end(); ++it) {   //try their loop
		sortImage.push_back(it->second);
	}

	sort(sortImage.begin(), sortImage.end());
	reverse(sortImage.begin(), sortImage.end());

	for (auto it_im = sortImage.begin(); it_im != sortImage.end(); ++it_im) {
		if (it_im != sortImage.begin() && *it_im == *(it_im - 1)) { //remove repeated
			it_im = sortImage.erase(it_im) - 1;
		}
	}

	for (auto it_im = sortImage.begin();
		it_im != sortImage.end(); ++it_im) {
		int x_anchor = minVal_;
		if (*it_im < -9)
			os << *it_im;
		else
			if ((*it_im < 0) || (*it_im > 9))
				os << " " << *it_im;
			else
				os << "  " << *it_im;


		for (auto it_dom = fmap_.begin();  // passing on the first polynom
			it_dom != fmap_.end(); ++it_dom) { //print (x,y)
			if (it_dom->second == *it_im) {
				int x = it_dom->first;
				int spaces = x - x_anchor;
				int i = 0;
				while (i < spaces) {
					os << "   ";
					i++;
				}
				os << "*  ";
				x_anchor = x + 1;
			}

		}

		os << endl;
		if ((it_im + 1) != sortImage.end()) { //print empty lines
			int lines = *it_im - *(it_im + 1) - 1;
			int i = 1;

			while (i < lines + 1) {
				if (*it_im - i < -9)
					os << *it_im - i;
				else
					if ((*it_im - i < 0) || (*it_im - i > 9))
						os << " " << *it_im - i;
					else
						os << "  " << *it_im - i;
				cout << endl;
				i++;

			}
		}

	}//for sortImage

	//print x axis

	bool flag = fmap_.empty();
	if (flag == false)
	{
		cout << " ";
		for (auto i = minVal_; i < maxVal_ + 1; i++)
		{
			if (i < 0) os << " " << i;
			else
			{
				if (i == maxVal_ && i == 0) break;
				os << "  " << i;
			}
		}
		os << endl;
	}
}





ostream& operator<<(ostream& os, const func& rhs) {
	rhs.print(os); 			// The right print method will be invoked.
	return os;
}


// virtual d'tor
func::~func() {}




