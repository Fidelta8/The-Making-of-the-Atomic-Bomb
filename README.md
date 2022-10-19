# 2 The effect of a Tamper
The code is stored in "Tamper Effect.cpp" file.
The Windows executable file is "Tamper Effect.exe".
First, after having set the various constants, there is the determination of the 
critical radius via bisection method.
Then, there is the output of the new critical mass of the bomb which is sorrounded by
a tamper, specifying the radius of the core and of the tamper and the entire mass of
the bomb (core+tamper).
Moreover, in order to try to graph the behaviour of the core critical mass as function
of the tamper additive mass, we have explicitated the tamper radius as function of 
core radius (which is a double-valued function), and then the tamper mass as function 
of the core mass, and we have calculated such function in very near space points,
considering only the minus-valued function because the other case leads to a undesired 
negative masses and, moreover, we have started from a point after the asymptot that
the tamper radius function has when taken the minus.
The values of this calculation are stored in the "mass.txt" text file in order to 
allow the user which open "plot(m_tamp, m_core).mlx" file with MATLAB, ensuring
that the same directory of "mass.txt" file is opened in it, to plot the relevant 
dependence of the tamper mass to critical core mass (and viceversa), that one
with the decreasing values of the critical mass when the tamper mass is 
increasing.
For simplicity, the relevant used functions are putted (and so defined) outside the
main.
