# 1.4 Neumann boundary conditions
The code is stored in "Neumann boundary conditions.cpp" file.
The Windows executable file is "Neumann boundary conditions.exe".
First, there is the determination of the critical radius via bisection method and then
output it, together with the critical mass and volume of Dirichlet case and Neumann
case, and the used radius.
Thus, in order to calculate the neutron density function we have first determined,
again by bisection method, the values of k and alpha, relevant in the equation of
neutron density solution.
So, we have calculated the neutron density function in very near space-time points,
storing the values in the "n.txt" file; then, one can plot it with 
MATLAB opening "plot n(t,r).mlx" file and using the same directory of "n.txt" file.
Moreover, we have extended the graph to virtual negative radius points, in order to
have a better outlook of the neutron density behaviour, by storing the corresponding 
values in the "nt.txt" file; the "plot n(t,r) tot.mlx" file can be opened by MATLAB
and, using the same directory of "nt.txt" file, one can see the plot of the neutron
density function, with negative radii included.
Finally, we have also calculated the initial distribution function, whose values are
stored in "nin.txt" file and opening "plot n(0,r).mlx" with MATLAB, and ensuring that
it is been using the same directory of "nin.txt" file, one can see its graph.
For simplicity, the relevant used functions are putted (and so defined) outside the
main.
