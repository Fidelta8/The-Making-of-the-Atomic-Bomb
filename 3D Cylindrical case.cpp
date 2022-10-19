

#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>

#include <fstream>

using namespace std;

//declaring functions
double f(double r, double z);
double Bessel(double a, double x);

int main()
{
	//declaring variables and constants
	double n;
	double const eta = 1.8958 * pow(10, 8);  //[1/s]
	double const mi = 2.3446 * pow(10, 5);  //[m^2/s]
	double const rho = 18710;  //[kg/m^3]
	double PI = 4 * atan(1);  //Pi
	const int m = 11;  //dimension of arrays
	
	double Lcrit = PI * sqrt(3*mi / eta); 
	//determination of the first 10 zeros of the Bessel function
	ofstream zeros("zeros.txt"); //output Bessel zeros in a txt file
	double alpha[m];  //zeros are putted in an array
	double c = 0.000001;  //application of bisection method, documentation on the relative section
	double inf = 0;
	double sup = 1;
	double as = inf;
	double b = sup;		
	double d;
	for (int q = 1; q < m; q++) {  
		auto start = chrono::steady_clock::now();
		
		while (b - as > c) {

			d = (as + b) / 2;
			if (Bessel(0,d) * Bessel(0, as) < 0) {
				b = d;
			}
			if (Bessel(0, d) * Bessel(0, b) < 0) {
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
		}
		alpha[q] = as;
		zeros << q << " , " << alpha[q] << endl;
		as = as + c;
		b = sup;
	}  //end of bisection method and zeros research

	double rcrit = alpha[1] * sqrt(3 * mi / (2 * eta));
	double const r1 = 0.104;  //[m]
	double const L = 0.192;  //[m]
	double Vcyl = PI*pow(rcrit,2)*Lcrit;
	double Vsphere = 4 * PI * pow(PI*sqrt(mi/eta), 3) / 3;
	cout << "Critical lenght: " << Lcrit * 100 << " cm" << endl;
	cout << "Critical radius: " << rcrit * 100 << " cm" << endl;
	cout << "Critical mass: " << rho * Vcyl << " kg" << endl;
	cout << "Ratio between cylindrical and sphere Volumes: " << Vcyl / Vsphere << endl;
	cout << "Used lenght: " << L * 100 << " cm" << endl;
	cout << "Used radius: " << r1 * 100 << " cm" << endl;
	


	//determination of a(p) coefficients
	double a[m];
	ofstream acoeff("a.txt"); //output data in a txt file
	for (int q = 1; q < m; q++) {
		
		a[q] = 4 * (alpha[q] * Bessel(0, alpha[q]) + 2 * Bessel(1, alpha[q])) / (pow(Bessel(1, alpha[q]), 2) * pow(alpha[q], 3));
		acoeff << q << " , " << a[q] << endl;


	}
	
	//neutron density function at fixed time
	ofstream ndensity("n.txt"); //output data in a txt file
	double s = 0.003;    //incrementator r
	double o = 0.003;  //incrementator z
	double const t = pow(10, -5);
	for (double r = 0; r < r1; r += s) {   
		for (double z = 0; z < L; z += o) { 
			n = 0;
			for (int q = 1; q < m; q++) {
				n = n + a[q] * Bessel(0, (alpha[q] * r / r1)) * exp(((eta * pow(r1 * L, 2) - mi * (pow(alpha[q] * L, 2) + pow(PI * r1, 2))) * (1 / pow(r1 * L, 2))) * t) * sin(PI * z / L);


			}
			ndensity << r << " " << z << " " << n << endl;
		}
	}

	//neutron density function for also negative radius values
	double nt;
	ofstream ntot("nt.txt"); //output data in a txt file
	for (double r = -r1; r < r1 && r != r1; r += s) {   
		for (double z = 0; z < L; z += o) {
			n = 0;
			for (int q = 1; q < m; q++) {
				n = n + a[q] * Bessel(0, (alpha[q] * r / r1)) * exp(((eta * pow(r1 * L, 2) - mi * (pow(alpha[q] * L, 2) + pow(PI * r1, 2))) * (1 / pow(r1 * L, 2))) * t) * sin(PI * z / L);


			}
			ntot << r << " " << z << " " << n << endl;
		}
	}

	system("pause");

}
//defining functions
double f(double r, double z) {  
	double g;
	double const r1 = 0.104;
	double const L = 0.192;
	double PI = 4 * atan(1);
	g = (1 - pow(r / r1, 2))*sin(PI*z/L);
	return g;
}

//Bessel function of the first kind, order a
double Bessel(double a, double x) {
	double g;
	g = 0;
	for (int k = 0; k < 100; k++) {
		g =g + pow(-1, k) * pow(x / 2, 2 * k + a) / (tgamma(k +1) * tgamma(k + a + 1));
	}
	return g;
}

