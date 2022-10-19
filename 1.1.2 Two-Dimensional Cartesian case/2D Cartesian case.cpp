

#include <iostream>
#include <cmath>

#include <fstream>

using namespace std;

//declaring functions
double f(double x, double y);

int main()
{
	//declaring variables and constants
	double n;
	double const eta = 1.8958 * pow(10, 8);  //[1/s]
	double const mi = 2.3446 * pow(10, 5);  //[m^2/s]
	double PI = 4 * atan(1);  //Pi
	double Lcrit = PI * sqrt(2*mi / eta); //L must be bigger than Lcrit to have explosion
	double const L = 0.157;
	cout << "Critical lenght: " << Lcrit * 100 << " cm" << endl;
	cout << "Used lenght: " << L * 100 << " cm" << endl;

	//determination of a(p,q) coefficients
	const int mp = 5;  //max value of p used
	const int mq = 5;  //max value of q used
	double a[mp*mq+1];  //putting a[p] coefficients in an array
		
	ofstream acoeff("a.txt"); //output data in a txt file
	for (int p = 1; p <= mp; p++) {
		for (int q = 1; q <= mq; q++) {
			 int b=(p-1)*mq+q;
			
			a[b] = 256 * (1 - pow(-1, q) - pow(-1, p) + pow(-1, p + q)) / (pow(p, 3) * pow(q, 3) * pow(PI, 6));
			acoeff << p << " " << q << " "<< a[b] << endl;
			
		}
	}
	

	//neutron density function
	ofstream ndensity("n.txt"); //output data in a txt file
	double r = 0.001;    //incrementatore x
	double s = 0.001;    //incrementatore y
	double o = pow(10, -6);     //incrementatore t
	for (double x = 0; x < L; x += r) {
		for (double y = 0; y < L; y += s) {
			for (double t = 0; t < 2 * pow(10, -5); t += o) {
				n = 0;
				for (int p = 1; p <= mp; p++) {
					for (int q = 1; q <= mq; q++) {
						int b = (p - 1) * mq + q;
						n = n + a[b] * exp((eta - mi * (pow(p, 2) + pow(q, 2)) * pow(PI, 2) * (1 / pow(L, 2))) * t) * sin(p * PI * x / L) * sin(q * PI * y / L);

					}
				}
				ndensity << x << " " << y << " " << t << " " << n << endl;
			}
		}

	}

	//neutron density function at a fixed time
	ofstream nfixedt("nfix.txt"); //output data in a txt file
	
	for (double x = 0; x < L; x += r) {
		for (double y = 0; y < L; y += s) {
			n = 0;
			double const t= 5*pow(10, -5);
			for (int p = 1; p <= mp; p++) {
				for (int q = 1; q <= mq; q++) {
					int b = (p - 1) * mq + q;
					n = n + a[b] * exp((eta - mi * (pow(p, 2) + pow(q, 2)) * pow(PI, 2) * (1 / pow(L, 2))) * t) * sin(p * PI * x / L) * sin(q * PI * y / L);
				}
			}
			nfixedt << x << " " << y << " " << n << endl;

		}

	}
	
	system("pause");

	
}
//defining functions
double f(double x, double y) {  
	double g;
	double const L = 0.157;
	g = 16*x*y*(pow(L,-2)) * (1-x/L)*(1-y/L);
	return g;
}

