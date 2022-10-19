
#include <iostream>
#include <cmath>

#include <fstream>

using namespace std;

//declaring functions
double f(double x, double y, double z);

int main()
{
	//declaring variables and constants
	double n;
	double const eta = 1.8958 * pow(10, 8);  //[1/s]
	double const mi = 2.3446 * pow(10, 5);  //[m^2/s]
	double PI = 4 * atan(1);  //Pi
	double const rho = 18710;  //[kg/m^3]
	double Lcrit = PI * sqrt(3 * mi / eta);
	double Mcrit = rho * pow(Lcrit, 3);  //critical mass
	double const L = 0.192;
	cout << "Critical lenght: " << Lcrit * 100 << " cm" << endl;
	cout << "Critical Mass: " << Mcrit << " kg" << endl;
	cout << "Used lenght: " << L * 100 << " cm" << endl;
	const int mp = 4;  //max value of p used
	const int mq = 4;  //max value of q used
	const int mk = 4;  //max value of k used
	double a[mp * mq* mk + 1];  //building the array containing coefficient values
	

	//determination of a(p,q) coefficients
	ofstream acoeff("a.txt"); //output data in a txt file
	for (int p = 1; p <= mp; p++) {
		for (int q = 1; q <= mq; q++) {
			for (int k = 1; k <= mk; k++) {
				int b = (p - 1) * mq * mk + (q - 1) * mk + k;
				a[b] = -512 * (pow(-1, q) - pow(-1, q + k) - 1 + pow(-1, k) + pow(-1, p) - pow(-1, p + k) - pow(-1, p + q) + pow(-1, p + q + k)) / (pow(p, 3) * pow(q, 3) * pow(k, 3) * pow(PI, 9));
				acoeff << p << " " << q << " " << k << " " << a[b] << endl;
			}
			
		}
	}


	//neutron density function
	ofstream ndensity("n.txt"); //output data in a txt file
	double r = 0.001;    //incrementator x
	double s = 0.001;    //incrementator y
	double l = 10;    //incrementator z
	double o = pow(10, -5);     //incrementator t
	for (double x = 0; x < L; x += r) {
		for (double y = 0; y < L; y += s) {
			for (double z = 0; z < L; z += l) {
				for (double t = 0; t < 2 * pow(10, -5); t += o) {
					n = 0;
					for (int p = 1; p <= mp; p++) {
						for (int q = 1; q <= mq; q++) {
							for (int k = 1; k <= mk; k++) {
								int b = (p - 1) * mq * mk + (q - 1) * mk + k;
								n = n + a[b] * exp((eta - mi * (pow(p, 2) + pow(q, 2) + pow(k, 2)) * pow(PI, 2) * (1 / pow(L, 2))) * t) * sin(p * PI * x / L) * sin(q * PI * y / L) * sin(k * PI * z / L);

							}
						}
					}
					ndensity << x << " " << y << " " << z << " " << t << " " << n << endl;
				}

			}
		}

	}

	//neutron density at a fixed time and fixed z
	ofstream nfixedt("nfix.txt"); //output data in a txt file

	for (double x = 0; x < L; x += r) {
		for (double y = 0; y < L; y += s) {
			n = 0;
			double const t = 2 * pow(10, -5);
			double const z = L/2;
			for (int p = 1; p <= mp; p++) {
				for (int q = 1; q <= mq; q++) {
					for (int k = 1; k <= mk; k++) {
						int b = (p - 1) * mq * mk + (q - 1) * mk + k;
						n = n + a[b] * exp((eta - mi * (pow(p, 2) + pow(q, 2) + pow(k, 2)) * pow(PI, 2) * (1 / pow(L, 2))) * t) * sin(p * PI * x / L) * sin(q * PI * y / L) * sin(k * PI * z / L);
					}
				}
			}
			nfixedt << x << " " << y << " " << n << endl;

		}

	}

	system("pause");


}
//defining functions
double f(double x, double y, double z) {  //immettere qui la funzione desiderata
	double g;
	double const L = 0.192;
	g = 8 * x * y * z * (pow(L, -3)) * (1 - x / L) * (1 - y / L) * (1 - z / L);
	return g;
}
