

#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>

#include <fstream>

using namespace std;

//declaring functions
double f(double r);
double w(double k);

int main()
{
	//declaring variables and constants
	double n;
	double const eta = 1.8958 * pow(10, 8);  //[1/s]
	double const mi = 2.3446 * pow(10, 5);  //[m^2/s]
	double const lambdat = 3.6 * pow(10, -2);  //[m]
	double const rho = 18710;  //[kg/m^3]
	double PI = 4 * atan(1);
	//founding rcritical value via bisection method (documentation on the relative section)
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

	}
	//as takes the value of the critical radius at the end of the while
	double rcrit = as;
	double rDir = PI*sqrt(mi/eta); 
	double const r1 = 0.085;
	double VDir = 4 * PI * pow(rDir, 3) / 3;
	double Vcrit = 4 * PI * pow(rcrit, 3) / 3;
	cout << "Critical Volume in Dirichlet case: " << VDir * 1000000 << endl;
	cout << "Critical Volume: " << Vcrit * 1000000 << " cmc" << endl;
	cout << "Critical radius: " << rcrit *100 << " cm" << endl;
	cout << "Critical Mass in Dirichlet case: " << rho * VDir << " kg" << endl;
	cout << "Critical Mass: " << rho * Vcrit << " kg" << endl;
	cout << "Used radius: " << r1 * 100 << " cm" << endl;
	


	//determination of k and alpha via bisection method
	c = 0.00001;
	inf = 0;
	sup = 1;
	as = inf;
	b = sup;
	start = chrono::steady_clock::now();
	while (b - as > c) {


		d = (as + b) / 2;
		if (w(d) * w(as) < 0) {
			b = d;                    
		}
		if (w(d) * w(b) < 0) {
			as = d;
		}
		auto end = chrono::steady_clock::now();
		if (chrono::duration_cast<chrono::nanoseconds>(end - start).count() > pow(10, 8)) {
			as = inf + 1;
			b = sup + 1;
			inf = inf + 1;
			sup = sup + 1;
			start = chrono::steady_clock::now();
		}

	} //end of bisection method
	double k = as;
	double alpha = mi * pow(k, 2) - eta;





	//neutron density function
	ofstream ndensity("n.txt"); //output data in a txt file
	double s = 0.0001;    //incrementator x
	double o = pow(10, -8);     //incrementator t
	for (double r = 0.0001; r < r1; r += s) {   //starting point cannot be 0
		for (double t = 0; t < 3*pow(10, -6); t += o) { //the explosion occurs sooner than Cartesian case
			n = (r1 / sin(k * r1)) * exp(-alpha * t) * sin(k * r) / r;
			ndensity << r << " " << t << " " << n << endl;
		}


	}

	//neutron density function
	double nt;
	ofstream ntot("nt.txt"); 
	for (double r = -r1; r < r1 && r != r1; r += s) {   
		for (double t = 0; t < 3 * pow(10, -6); t += o) { 
			n = (r1 / sin(k * r1)) * exp(-alpha * t) * sin(k * r) / r;
			ntot << r << " " << t << " " << n << endl;
		}
	}

	//neutron density at initial time, with all radius values
	double nin;
	ofstream ninit("nin.txt"); //output data in a txt file
	
	for (double r = -r1; r < r1 && r != r1; r += s) {   //starting point cannot be 0
		double const t = 0;
		n = (r1 / sin(k * r1)) * exp(-alpha * t) * sin(k * r) / r;
		ninit << r << " " << n << endl;
	}
		
	system("pause");

}
//defining functions
double f(double r) {  //to determine the critical radius
	double g;
	double const eta = 1.8958 * pow(10, 8);
	double const mi = 2.3446 * pow(10, 5);
	double const lambdat = 3.6 * pow(10, -2);
	g = -1 + r * sqrt(eta / mi) / (tan(r * sqrt(eta / mi))) + 3 * r / (2 * lambdat);
	return g;
}

double w(double k) {  //the inverse of f function, to determine k and so alpha
	double g;
	double const lambdat = 3.6 * pow(10, -2);
	double const r1 = 0.085;
	g = -1 + r1 * k / (tan(r1 * k)) + 3 * r1 / (2 * lambdat);
	return g;
}


