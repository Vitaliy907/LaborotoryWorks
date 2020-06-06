#include <iostream>
#include <climits>
#include <cmath>

using namespace std;

const double E = std::exp(1.0);


const double A = 0.7;
const double B = 1.2;

double XNow;
const double XBeg = 0.5;
const double XEnd = 1.5;
const double dX = 0.05;

double ZMin = DBL_MAX;
double ZMax = DBL_MIN;

int comp_acc = 3;

bool is_double_equal(double first, double second) {
	double diff;
	long int comp;
	diff = first - second;
	for (int i = 0; i != comp_acc; i++) {
		diff = diff * 10;
	}
	comp = diff;
	if (comp == 0)
		return true;
	else
		return false;
}

int main()
{
	double Z;
	
	XNow = XBeg;

	cout << endl << "First function:" << endl;

	while ((XNow < A or is_double_equal(XNow, A)) and (XNow < XEnd or is_double_equal(XNow, XEnd))){
		Z = abs(XNow);
		if (Z < ZMin) ZMin = Z;
		if (Z > ZMax) ZMax = Z;
		cout << "X: " << XNow << "\t" << "Z: " << Z << endl;
		XNow += dX;
	}

	cout << endl << "Second function: " << endl;

	while ((XNow < B) and (XNow < XEnd or is_double_equal(XNow, XEnd))){
		Z = abs(XNow) + cos(XNow);
		if (Z < ZMin) ZMin = Z;
		if (Z > ZMax) ZMax = Z;
		cout << "X: " << XNow << "\t" << "Z: " << Z << endl;
		XNow += dX;
	}

	cout << endl << "Third function:" << endl;

	while ( (XNow > B or is_double_equal(XNow, B)) and ( XNow < XEnd or is_double_equal(XNow, XEnd) )){
		Z = tan(XNow);
		if (Z < ZMin) ZMin = Z;
		if (Z > ZMax) ZMax = Z;
		cout << "X: " << XNow << "\t" << "Z: " << Z << endl;
		XNow += dX;
	}

	cout << endl << "ZMin: " << ZMin;
	cout << endl << "ZMax: " << ZMax;
	
}