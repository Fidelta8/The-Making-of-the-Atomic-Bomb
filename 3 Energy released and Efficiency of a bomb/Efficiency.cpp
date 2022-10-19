

#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>


#include <fstream>

using namespace std;

//declaring functions
double f(double r);


int main()
{
	//declaring variables and constants
	double n;
	double const eta = 1.8958 * pow(10, 8);
	double const mi = 2.3446 * pow(10, 5);
	double const lambdat = 3.6 * pow(10, -2);
	double PI = 4 * atan(1);
	//founding rcritical value via bisection method
	double c = 0.00000000001;  //tolerance
	double inf = 0;
	double sup = 0.1;
	double as = inf;
	double b = sup;
	double d;

	auto start = chrono::steady_clock::now();
	while (b - as > c) {


		d = (as + b) / 2;
		if (f(d) * f(as) < 0) {
			b = d;
		}
		if (f(d) * f(b) < 0) {
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
	}  //end of bisection algorithm
	
	double rcrit = as;
	double rDir = PI * sqrt(mi / eta);
	double VDir = 4 * PI * pow(rDir, 3) / 3;
	double Vcrit = 4 * PI * pow(rcrit, 3) / 3;
	
	cout << "Critical radius: " << rcrit * 100 << " cm" << endl;
	//Hitherto is the Neumann case copied


	//First, we determine the efficiency as a function of C>1 critical masses used
	//determination of k and alpha
	ofstream eff("eff.txt");
	for (double C = 1; C < 3.2; C += 0.1) {
		double r1 = cbrt(C) * rcrit;
		//determination of k and alpha via bisection method
		c = 0.00001;  //tolerance
		inf = 0;
		sup = 1;
		as = inf;
		b = sup;
		start = chrono::steady_clock::now();
		while (b - as > c) {


			d = (as + b) / 2;
			if ((-1 + r1 * d / (tan(r1 * d)) + 3 * r1 / (2 * lambdat)) * (-1 + r1 * as / (tan(r1 * as)) + 3 * r1 / (2 * lambdat)) < 0) {
				b = d;
			}
			if ((-1 + r1 * d / (tan(r1 * d)) + 3 * r1 / (2 * lambdat)) * (-1 + r1 * b / (tan(r1 * b)) + 3 * r1 / (2 * lambdat)) < 0) {
				as = d;
			}
			auto end = chrono::steady_clock::now();
			if (chrono::duration_cast<chrono::nanoseconds>(end - start).count() > pow(10, 7)) {
				as = inf + 1;
				b = sup + 1;
				inf = inf + 1;
				sup = sup + 1;
				start = chrono::steady_clock::now();
			}


		}  //end of bisection algorithm
		double k = as;
		double alpha = mi * pow(k, 2) - eta;
		double const tau = 8.6347 * pow(10, -9);
		double Alpha = alpha * tau;


		double deltar = (sqrt(C) - cbrt(C)) * rcrit;
		double const rho0 = 18710;
		double rhoraverage = (1 + cbrt(C)) * rho0 * rcrit / 2;
		double gamma = double(1) / 3;
		double const Ef = 180 * 1.60218 * pow(10, -13); //MeV to J
		double const Avogadro = 6.022 * pow(10, 23);
		double const Atomicweight = 235.04;
		double nuclei = rho0 * Avogadro * pow(10, 3) / Atomicweight;
		double efficiency = (deltar * pow(Alpha, 2) * rhoraverage) / (3 * gamma * nuclei * pow(tau, 2) * Ef);
		eff << C << " " << efficiency << endl; 
	}
	//Second, we will concentrate to a particular value of C
	double const C = 1.5;
	double r1 = cbrt(C) * rcrit;
	//determination of k and alpha via bisection method
	c = 0.00001;  //tolerance
	inf = 0;
	sup = 1;
	as = inf;
	b = sup;
	start = chrono::steady_clock::now();
	while (b - as > c) {


		d = (as + b) / 2;
		if ((-1 + r1 * d / (tan(r1 * d)) + 3 * r1 / (2 * lambdat)) * (-1 + r1 * as / (tan(r1 * as)) + 3 * r1 / (2 * lambdat)) < 0) {
			b = d;
		}
		if ((-1 + r1 * d / (tan(r1 * d)) + 3 * r1 / (2 * lambdat)) * (-1 + r1 * b / (tan(r1 * b)) + 3 * r1 / (2 * lambdat)) < 0) {
			as = d;
		}
		auto end = chrono::steady_clock::now();
		if (chrono::duration_cast<chrono::nanoseconds>(end - start).count() > pow(10, 7)) {
			as = inf + 1;
			b = sup + 1;
			inf = inf + 1;
			sup = sup + 1;
			start = chrono::steady_clock::now();
		}


	}  //end of bisection algorithm
	double k = as;
	double alpha = mi * pow(k, 2) - eta;
	double const tau = 8.6347 * pow(10, -9);
	double Alpha = alpha * tau;

	double deltar = (sqrt(C) - cbrt(C)) * rcrit;
	double const rho0 = 18710;
	double rhoraverage = (1 + cbrt(C)) * rho0 * rcrit / 2;
	double gamma = double(1) / 3;
	double const Ef = 180 * 1.60218 * pow(10, -13); //MeV to J
	double const Avogadro = 6.022 * pow(10, 23);
	double const Atomicweight = 235.04;
	double nuclei = rho0 * Avogadro * pow(10, 3) / Atomicweight;
	double Y = (deltar * pow(Alpha, 2) * rhoraverage * (4 * PI * pow(sqrt(C) * rcrit, 3) / 3)) / (3 * gamma * pow(tau, 2));
	cout << "Energy released up to second criticality (Yield) in Joule: " << Y << " J" << endl;
	cout << "Energy released up to second criticality (Yield) in kiloton: " << Y/(4.184*pow(10,12)) << " kt" << endl;
	double efficiency = (deltar * pow(Alpha, 2) * rhoraverage) / (3 * gamma * nuclei * pow(tau, 2) * Ef);
	cout << "Efficiency: " << efficiency * 100 << " %" << endl;
	double N0 = 1/(4*PI*pow(r1,3)/3);
	double tfiss =- (tau / Alpha) * log(-Alpha * nuclei / N0);
	double tseccrit =- (tau / Alpha) * log((-deltar * pow(Alpha, 3) * rhoraverage) / (3 * gamma * pow(tau, 2) * Ef * N0));
	cout << "Fission time: " << tfiss * pow(10, 6) << " micros" << endl;
	cout << "Second criticality time: " << tseccrit * pow(10, 6) << " micros" << endl;
	double Pin =- gamma * N0 * Ef / Alpha;
	double Pfin = pow(Alpha, 2) * deltar * rhoraverage / (3 * pow(tau, 2));
	cout << "Initial pressure: " << Pin << " Pa" << endl;
	cout << "Final pressure: " << Pfin << " Pa" << endl;
	double const L= 16093.4;
	double const rhoair = 0.6;
	double Vair = 4 * PI * pow(L, 3) /3;
	double h = 1.83;
	cout << "Fermi's calculation: " << 9.81 * rhoair * Vair * pow(2.5, 2) / (8 * h * 4.184 * pow(10, 12)) << " kt" << endl;
	ofstream Values("Values.txt");
	Values << "Quantity" << " , " << "Physical meaning" << " , " << "Value" << " Unit" << endl << "rcrit" << " , " << "Critical radius" << " , " << rcrit << " m" << endl << "ri" << " , " << "Initial radius" << " , " << cbrt(C) * rcrit << " m" << endl << "rseccrit" << " , " << "Radius at crit. shutdown" << " , " << sqrt(C) * rcrit << " m" << endl << "deltar" << " , " << "Expansion radius" << " , " << deltar << " m" << endl << "eff" << " , " << "Efficiency" << " , " << efficiency << " %" << endl << "Pfin" << " , " << "Pressure at crit. shutdown" << " , " << Pfin << " Pa" << endl << "Y" << " , " << "Yield (Energy released at crit. shutdown)" << " , " << Y / (4.184 * pow(10, 12)) << " kt" << endl << "tfiss" << " , " << "Time needed to fission all nuclei" << " , " << tfiss << " s" << endl << "tseccrit" << " , " << "Time to crit. shutdown" << " , " << tseccrit << " s" << endl << "Yf" << " , " << "Hypothetical Yield (Fermi)" << " , " << 9.81 * rhoair * Vair * pow(2.5, 2) / (8 * 1.83 * 4.184 * pow(10, 12)) << " kt" << endl;

	system("pause");

}
//defining functions
double f(double r) {  
	double g;
	double const eta = 1.8958 * pow(10, 8);
	double const mi = 2.3446 * pow(10, 5);
	double const lambdat = 3.6 * pow(10, -2);
	g = -1 + r * sqrt(eta / mi) / (tan(r * sqrt(eta / mi))) + 3 * r / (2 * lambdat);
	return g;
}




