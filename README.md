# 1.2 Spherical case
The code is stored in "3D Spherical case.cpp" file.
The Windows executable file is "3D Spherical case.exe".
First, the code calculate the critical radius and then output it and the chosen 
radius, being sure that the used radius is bigger than the critical one.
Moreover, it calculate and output the critical mass and the ratio between the critical
masses (or volumes) of a cubic core and a spherical core.
Then, we have calculated the coefficients of the neutron density function, starting
from an initial distribution satisfying Dirichlet boundary conditions: so we calculate
directly the values of the coefficients, since the integration can be made exactly,
and they are stored in the text file "aex.txt"; moreover, we have also calculated the 
coefficient using the numerical integration method of trapezoids, storing the results
in the text file "aapp.txt". Finally, we have compared the value of the coefficients
calculated in the two different ways, making the difference between them, and these
difference values are stored in the "aerr.txt" file.
Thus, we have calculated the neutron density function in very near space-time points, 
storing the values of the neutron density function with the corresponding space and
time point values in the "n.txt" file; then, one can plot it with MATLAB opening 
"plot n(t,r).mlx" file and using the same directory of "n.txt" file.
Finally, we have extended the graph to virtual negative radius points, in order to
have a better outlook of the neutron density behaviour, by storing the corresponding 
values in the "ntot.txt" file; the "plot n(t,r) tot.mlx" file can be opened by MATLAB and, 
using the same directory of "ntot.txt" file, one can see the plot of the neutron
density function, with negative radii included.
For simplicity, the relevant used functions are putted (and so defined) outside the
main.
