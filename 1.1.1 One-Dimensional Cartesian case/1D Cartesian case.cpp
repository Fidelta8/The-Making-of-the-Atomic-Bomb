

#include <iostream>
#include <cmath>

#include <fstream>

using namespace std;

//declaring functions
double f(double x);

 int main()
{
	//declaring variables and constants
	double n;
	double const eta = 1.8958 * pow(10, 8); //[1/s]
	double const mi = 2.3446 * pow(10, 5);  //[m^2/s]
	double PI = 4 * atan(1);  //Pi
	double Lcrit = PI * sqrt(mi / eta); //L must be bigger than Lcrit to have explosion
	cout << "Critical lenght: " << Lcrit * 100 << " cm" << endl;  //print the critical lenght
	double const L = 0.111;  //[m]
	cout << "Used lenght: " << L * 100 << " cm" << endl;  //print the used lenght L>Lcrit
	const int m = 33;  //array lenght
	double a[m]; //declaring the a coefficients as an array
	
	

	//determination of a(p) coefficients
	ofstream acoeff("a.txt"); //output data in a txt file
	for (int p = 1; p < m; p++) {
		a[p] = 0;  //integration technique (trapezoidal rule)
		double const h = 0.00005;  //increment used in the trapezoidal rule (precision)
		for (double i = 0; i <= L; i += h) {
			a[p] = a[p] + (2 / L) * h * 0.5 * (f(i + h) * sin((p * PI * (i + h) / L)) + f(i) * sin((p * PI * i / L)));

		}
		acoeff << p << " " << a[p] << endl; //values of the coefficients saved in a txt file

	}
	//neutron density function
	ofstream ndensity("n.txt"); //output data in a txt file
	double r = 0.001;    //x incrementator 
	double o =pow(10,-8);     //t incrementator 
	for (double x = 0; x < L; x += r) {
		for (double t = 0; t < 2*pow(10,-5); t += o) {
			n = 0;
			for (int p = 1; p < m; p++) {
				n = n + a[p] * exp((eta - mi * pow(p, 2) * pow(PI, 2) * (1 / pow(L, 2))) * t) * sin(p * PI * x / L);

			}
			ndensity << x << " " << t << " " << n << endl;  //we can plot these data 
		}


	}
	//difference between n(0,x) and f(x) in a txt file
	ofstream err("err.txt");
	r = 0.001;
	for (double x = 0; x < L; x += r) {
		n = 0;
		double const t = 0;
		for (int p = 1; p < m; p++) {
			n = n + a[p] * exp((eta - mi * pow(p, 2) * pow(PI, 2) * (1 / pow(L, 2))) * t) * sin(p * PI * x / L);
			
			err << x << " " << n-f(x) << endl;  
		}
		
	}

	system("pause");


}
//defining functions
double f(double x) {  //Gaussian distribution function
	double g;
	double const A = 1;
	double const lambda = 100;
	double const L = 0.111;
	g = A * exp(-4 * lambda * pow((x - 0.5 * L), 2) / pow(L, 2));
	return g;
}
