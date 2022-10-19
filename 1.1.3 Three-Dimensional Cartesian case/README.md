# 1.1.3 Three-Dimensional Cartesian case
The code is stored in "3D Cartesian case.cpp" file.
The Windows executable file is "3D Cartesian case.exe".
First, the code calculate the critical lenght and then output it and the chosen 
lenght, being sure that the used lenght is bigger than the critical one.
Moreover, it calculate and output the critical mass.
Then, we have calculated the coefficients of the neutron density function, starting
from an initial distribution satisfying Dirichlet boundary conditions: so we calculate
directly the values of the coefficients, since the integration can be made exactly,
and they are stored in the text file "a.txt".
Thus, we have calculated the neutron density function in very near space-time points, 
storing the values of the neutron density function with the 
corresponding space and time point values in the "n.txt" file, and then we have also 
calculated the neutron density function at a fixed time t and fixed height z, storing 
the corresponding values at various space points in the "nfix.txt" file; 
hence, one can run the countour plot of this last function opening 
contourplot "n(x,y).mlx" on MATLAB, after having inserted the directory of "nfix.txt" file.
For simplicity, the relevant used functions are putted (and so defined) outside the
main.

