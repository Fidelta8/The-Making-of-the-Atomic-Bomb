

#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>

#include <fstream>

using namespace std;

//declaring functions

double cr(double r);

int main()
{
	//declaring variables and constants
	double n;
	double const eta = 1.8958 * pow(10, 8);  //[1/s]
	double const mi = 2.3446 * pow(10, 5);  //[m^2/s]
	double const rhocore = 18710;  //[kg/m^3]
	double const rhotamp = 14800;  //[kg/m^3]
	double const Avogadro = 6.022 * pow(10, 23);  //[1/mol]
	double const Aweight_tamp = 195.84;  //[g/mol]
	double nucleid = pow(10, 3) * rhotamp * Avogadro / Aweight_tamp;  //[1/m^3]
	double const sigma = 6.587 * pow(10, -28);  //[m^2]
	double lambdat_tamp = 1 / (nucleid * sigma);  //[m]
	double const lambdat_core = 0.036;  //[m]
	double const lambdaf_core = 0.1689;  //[m]

	double const ni = 2.637;
	double d_core = sqrt(lambdat_core * lambdaf_core / (3 * (ni - 1)));  //[m]
	double PI = 4 * atan(1);
	//founding the value of the second criticality with the given rtamp, via bisection method
	double const rtamp = 0.117;  //used tamper lenght [m]
	double c = 0.00000000001;  //tolerance
	double inf = 0;
	double sup = 0.1;
	double as = inf;
	double b = sup;
	double d;	
	auto start = chrono::steady_clock::now();
	while (b - as > c) {


		d = (as + b) / 2;
		if (cr(d) * cr(as) < 0) {
			b = d;
		}
		if (cr(d) * cr(b) < 0) {
			as = d;
		}

		auto end = chrono::steady_clock::now();
		if (chrono::duration_cast<chrono::nanoseconds>(end - start).count() > pow(10, 8)) {
			as = inf + 0.1;
			b = sup + 0.1;
			inf = inf + 0.1;
			sup = sup + 0.1;
			start = chrono::steady_clock::now();
		}

	} // end of bisection algorithm
	double rnewcrit = as;
	double Vtamp = 4 * PI * pow(rnewcrit, 3) / 3;
	cout << "New critical mass for a spherical bomb with a total radius of " << 100 *  rtamp << " cm and a tamper with a mass of " << rhotamp * 4 * PI * (pow( rtamp, 3) - pow(rnewcrit, 3)) / 3 << " kg and a thickness of " <<100*(rtamp-rnewcrit)<<" cm is: " << rhocore * Vtamp << " kg" << endl;

	//Tamper mass as function of the critical mass
	ofstream mass("mass.txt"); //output data in a txt file
	double s = 0.000001;    //incrementator rcrit
	double rt;
	double j;
	double mcore;
	double mtamp;
	for (double r = 0.06; r < 0.14; r += s) {   //extremal values to avoid asymptot

		j = tan(r/d_core)*lambdat_tamp/(lambdat_core*r*(tan(r/d_core)-r/d_core))-1/r;
		rt = (-3 - sqrt(9 + 24 * lambdat_tamp * j)) / (6 * j); //choose -sqrt because it is decreasing function whereas +sqrt is increasing function
		mcore = rhocore * 4 * PI * pow(r, 3) / 3;
		mtamp = rhotamp * 4 * PI * (pow(rt, 3) - pow(r, 3)) / 3;
		
		if (mtamp >= 0) { //avoid negative masses
			mass << mcore << " " << mtamp << endl;

		}


	}


	system("pause");

	

}
//defining functions

double cr(double r) {  //this is the function whose zeros we want to determine
	double g;
	double const rtamp = 0.117;
	double const rhotamp = 14800;
	double const Avogadro = 6.022 * pow(10, 23);
	double const Aweight_tamp = 195.84;
	double nucleid = pow(10, 3) * rhotamp * Avogadro / Aweight_tamp;
	double const sigma = 6.587 * pow(10, -28);
	double lambdat_tamp = 1 / (nucleid * sigma);
	double const lambdat_core = 0.036;
	double const lambdaf_core = 0.1689;
	double const ni = 2.637;
	double d_core = sqrt(lambdat_core * lambdaf_core / (3 * (ni - 1)));
	g = (1 + (2 * r * lambdat_tamp / (3 * pow(rtamp, 2))) - (r / rtamp)) * (((r / d_core) / tan(r / d_core)) - 1) + lambdat_tamp / lambdat_core;
	return g;
}


