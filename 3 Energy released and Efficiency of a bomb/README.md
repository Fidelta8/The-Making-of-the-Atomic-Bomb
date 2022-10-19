# 3 Energy released and Efficiency of a bomb
The code is stored in "Efficiency.cpp" file.
The Windows executable file is "Efficiency.exe".
The first part, concerning the determination of the critical radius, is literally 
copied from "Neumann boundary conditions.cpp" file.
Then we have considered the case in which C varies and the case of a fixed value:
in both cases, the values of k and alpha, are determined via the bisection method.
In the first case, the efficiency is calculated as function of C and the results of 
calculation are stored in the "eff.txt" file; in order to have a graph of how 
efficiency varies with the C value, the user can open "plot(C, Efficiency).mlx" 
with MATLAB, ensuring that the same directory of "eff.txt" file is selected.
In the second case, all relevant physical quantities are calculated setting C=1.5 
and stored in the "Values.txt" file.
The constant (and the variables) are defined throughout the entire code.
For simplicity, the relevant used functions are putted (and so defined) outside the
main.

