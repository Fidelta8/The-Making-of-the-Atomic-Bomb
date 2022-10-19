#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>

using namespace std;

double f(double x);
int main()
{
    double as, b, e, d,inf, sup;  //declaring variables
    e = 0.00000001;  //tolerance/precision
    const int m = 11;  //array dimension (how many zeros we want/expect?
    double zeros[m];  //if a function has more than one zeros, they can be stored in an array
    ofstream roots("zeros.txt");
    inf = 0;  //notice that this extremum is excluded from analysis: indeed, 0 is not found as root by the algorithm but it could be found if a negative value (like -e) is chosen instead of 0
    sup = 1;  //the size of the interval can be chosen at own will: smaller it is, and less probability of losing some zeros
    as = inf;  //inferior extremum
    b = sup;  //superior extremum
    for (int q = 1; q < m; q++) {
        auto start = chrono::steady_clock::now();  //this set a "time"-variable with the current time (taken from the system)
        while (b - as > e) {  //the while ends when the two extrema are very near (in relationship with the tolerance), i.e. when the root is found

           

            d = (as + b) / 2;  //bisection operation
            if (f(d) * f(as) < 0) {  //the zero lies in the first half of the chosen interval
                b = d;  //restricting the interval
            }
            if (f(d) * f(b) < 0) {  //the zero lies in the second half of the chosen interval
                as = d;  //restricting the interval
            }
            
            auto end = chrono::steady_clock::now();  //another "time"-variable
          
            //there is the possibility that there is no zero in the chosen interval, so the while loop would continue without limits
            //thus, since a root is found relatively early, one can state that if the loop duration is too long, then the interval of analysis can be changed
    
            if (chrono::duration_cast<chrono::nanoseconds>(end - start).count() > pow(10,8)) { //the value inside the condition counts the difference in time (in nanoseconds) between two "time"-variables
                as = inf + 1;
                b = sup + 1;  //the if condition is satisfied, so probably there is no root in the previous interval, so we displace it
                inf = inf + 1;  
                sup = sup + 1;  //we conveniently displace also the initializers
                start = chrono::steady_clock::now();  //restart the time count from this point
            }
           

        }
        zeros[q] = as;  //while is ended, so a zero is found and stored in the array
        
            cout << zeros[q] << endl;  //output of the zero
            roots << q << " " << zeros[q] << endl;
            
            as = as + e;  //next interval, simply just after the found zero
            b = sup;  //maybe there can be another zero in the "successful" interval, so let's analyse the remaining part
        
    
    }
    double PI = 4 * atan(1);  //Pi
    double err[m];  //we can compare the calculated zeros with the exact zeros (if the function analyzed has well-known/algebraic roots)
    for (int q = 1; q < m; q++) {
        err[q] = zeros[q] - q * PI;  //in the case of a sin function, the zeros are multiple of Pi
        cout << err[q] << endl;  //output the difference of the two kinds of zeros (which becomes smaller when the tolerance becomes smaller)
    }

    system("pause");

}

 double f( double x) {   //function whose zeros we want to know: we choose the sin function, which has more than one well-known zeros
   double fun;
    fun = sin(x);
    return fun;
}
