# 1.1.1 One-Dimensional Cartesian case
The code is stored in "1D Cartesian case.cpp" file.
The Windows executable file is "1D Cartesian case.exe".
First, the code calculate the critical lenght and then output it and the chosen 
lenght, being sure that the used lenght is bigger than the critical one.
Then, we have calculated the coefficients of the neutron density function, starting
from an initial Gaussian distribution and using, as numerical integration, the 
trapezoidal method; the values of the coefficients are stored in the text file "a.txt".
Thus, we have calculated the neutron density function in very near space-time points, 
in order to graph it: storing the values of the neutron density function with the 
corresponding space and time point values in the "n.txt" file, one can use MATLAB to 
open "plot n(t,x).mlx" and, opening the directory where is "n.txt" file, he will receive 
the desired graph.
Finally, we have calculated the differences between the initial distribution function,
the Gaussian and the calculated one at time t=0, and stored them, whith the 
corresponding space values, in the "err.txt" file; therefore, open "Error.mlx" in 
MATLAB, after inserting the directory of the err.txt file, the user receives the
graph in which it is described the behaviour of the difference between the two 
initial distribution functions.
For simplicity, the relevant used functions are putted (and so defined) outside the
main.
