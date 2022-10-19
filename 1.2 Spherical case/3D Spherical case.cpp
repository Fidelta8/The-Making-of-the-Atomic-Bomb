

#include <iostream>
#include <cmath>

#include <fstream>

using namespace std;

//declaring functions
  double f(double r);

int main()
{
	//declaring variables and constants
	double n;
	double const eta = 1.8958 * pow(10, 8);  //[1/s]
	double const mi = 2.3446 * pow(10, 5);  //[m^2/s]
	double const rho = 18710;  //[kg/m^3]
	double PI = 4 * atan(1);  //Pi
	double rcrit = PI * sqrt(mi / eta); //L must be bigger than Lcrit to have explosion
	double const r1 = 0.115;  //[m]
	double Vc = pow(sqrt(3) * rcrit, 3);  //Volume of a Cubic bomb
	double Vs = 4 * PI * pow(rcrit, 3) / 3;  //Volume of a Spherical bomb
	cout << "Critical radius: " << rcrit * 100 << " cm" << endl;
	cout << "Critical mass: " << rho * Vs << " kg" << endl;
	cout << "Ratio between cube and sphere Volumes: " << Vc / Vs << endl;
	cout << "Used lenght: " << r1 * 100 << " cm" << endl;
	const int m = 31;
	double a[m];
	double aex[m];
	double const h = 0.00001;


	//determination of a(p) coefficients
	ofstream acoeff("aex.txt"); //exact values
	ofstream aa("aapp.txt"); //approx values
	ofstream aerr("aerr.txt");  //error between the two values
	for (int p = 1; p < m; p++) {
		a[p] = 0; //integration technique
		for (double i = 0; i <= r1; i += h) {
			a[p] = a[p] + (2 / r1) * h * 0.5 * ((i+h) * f(i + h) * sin((p * PI * (i + h) / r1)) + i* f(i) * sin((p * PI * i / r1)));

		}
		aex[p] = 12 * r1 * pow(-1, 1 + p) / (pow(p, 3) * pow(PI, 3));
		acoeff << p << " , " << aex[p] << endl;
		aa << p << " , " << a[p] << endl;
		aerr << p << " , " << a[p]-aex[p] << endl;
		

	}
	
	
	//neutron density function
	ofstream ndensity("n.txt"); //output data in a txt file
	double s = 0.001;    //incrementator r
	double o = pow(10, -8);     //incrementator t
	for (double r = 0.0001; r < r1; r += s) {   //starting point cannot be 0
		for (double t = 0; t < pow(10, -5); t += o) { //the explosion occurs sooner than Cartesian case
			n = 0;
			for (int p = 1; p < m; p++) {
				n = n + aex[p] * exp((eta - mi * pow(p, 2) * pow(PI, 2) * (1 / pow(r1, 2))) * t) * sin(p * PI * r / r1)/r;

			}
			ndensity << r << " " << t << " " << n << endl;
		}


	}

	//neutron density function with also negative radius values
	ofstream ndensitytot("ntot.txt"); //output data in a txt file
	 
	for (double r = -r1; r < r1 && r!=0; r += s) {   //starting point cannot be 0
		for (double t = 0; t < pow(10, -5); t += o) { //the explosion occurs sooner than Cartesian case
			n = 0;
			for (int p = 1; p < m; p++) {
				n = n + aex[p] * exp((eta - mi * pow(p, 2) * pow(PI, 2) * (1 / pow(r1, 2))) * t) * sin(p * PI * r / r1) / r;

			}
			ndensitytot << r << " " << t << " " << n << endl;
		}


	}

	system("pause");

}
//defining functions
double f(double r) {  
	double g;
	double const r1 = 0.115;
	g = 1 - pow(r / r1, 2);
	return g;
}

