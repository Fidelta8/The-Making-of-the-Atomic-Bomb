# *Bisection method
The code is stored in "Bisection method.cpp" file.
The Windows executable file is "Bisection method.exe".
After declaring variables, we set a tolerance/precison we want to obtain from our 
research of the roots and an array size, in which we can store the found values.
The extrema are initialized to some desidered value, so the interval of the analysis
can be chosen at will. 
The algorithm is simple: until the two extrema are different for a very small value, 
set by the tolerance, the cycle "while" will try to find a root in the chosen interval;
to do this, it considers the point in the middle of the interval and substitutes at 
once the values of the extrema with this and check which one of the two substitutions
allows to take the product of the function at the two new extrema negative. So it 
restricts the interval in correspondence of this eventuality and continue until
the interval is very narrow, so pratically founding the zero. Notice that more narrow
is the initial interval, more accurate the algorithm is because it may happen that, if
the interval is too large, the product of functions can be positive nevertheless the
presence of a zero in that interval; moreover, it is possible that, if it is too large, 
there are two roots and the algorithm will outcome only one.  
It may happen that the algorithm will not give any result in that interval, 
so there is an implementation that allows to displace by a certain phase the interval 
in order to find the roots elsewhere. To this aim, because if there is a root in the
interval the algorithm will found it very "soon" (it does not last more than one tenth
of second for sure), there is a countation of the time that allows to displace the 
interval whether the finding lasts too much.
Once found, all the zero are printed and stored in the "zeros.txt" file.
Moreover, one can check the error that the roots-finding with bisection method has
compared to the exact value of the roots, if these are analytical.
In our case, we have chosen the simple sine function and, of course, the error values 
depend on our initial choice of the tolerance.

