# 1.3 Cylindrical case
The code is stored in "3D Cylindrical case.cpp" file.
The Windows executable file is "3D Cylindrical case.exe".
First, there is the determination of the first ten zeros of the Bessel function, using
the bisection method, which is explained in the relative documentation. The zeros are
stored in the "zeros.txt" file.
After that, the code calculate the critical radius and the critical lenght and then
output them and the chosen radius.
Moreover, it calculate and output the critical mass and the ratio between the critical
masses (or volumes) of a cylindrical core and a spherical core.
Then, we have calculated the coefficients of the neutron density function, starting
from an initial distribution satisfying Dirichlet boundary conditions: so we calculate
directly the values of the coefficients, since the integration can be made exactly,
and they are stored in the text file "a.txt".
Thus, we have calculated the neutron density function in very near space points and
at a fixed time, storing the values in the "n.txt" file; then, one can plot it with 
MATLAB opening "plot n(z,r).mlx" file and using the same directory of "n.txt" file.
Finally, we have extended the graph to virtual negative radius points, in order to
have a better outlook of the neutron density behaviour, by storing the corresponding 
values in the "nt.txt" file; the "plot n(z,r) tot.mlx" file can be opened by MATLAB
and, using the same directory of "nt.txt" file, one can see the plot of the neutron
density function, with negative radii included.
For simplicity, the relevant used functions are putted (and so defined) outside the
main.
