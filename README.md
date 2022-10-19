# The-Making-of-the-Atomic-Bomb
I discuss the neutron diffusion equation and, in particular, its applications in the
building of the Nuclear Weapons.
I consulted the paper of Graham Griffiths (2018), Neutron diffusion, 
URL https: //www.researchgate.net/publication/323035158 Neutron diffusion and the book
Reed, B. C. (2015), The Physics of the Manhattan project, Springer-Verlag, 
Berlin Heidelberg, 3rd Ed.
The paper is a .pdf file named "The Making of the Atomic Bomb.pdf", in which is written
the whole theory and are shown the results of the various calculations.
Every codes are written in C++.
Each of the folders contains a README file, which explain step-by-step what is made in
that context a .cpp file that can be compiled with any compilator (personally I have 
used Virtual Studio 2022) and a Windows executable file (.exe) which allows to a Windows 
user to run directly the code; moreover, the folders, which follow the order of the 
paper contents (except for the last one, which provides documentation of the used 
bisection method), are provided of data, directly streamed by the .exe file and most 
of them contain also a .mlx file, that can be opened with MATLAB, and selecting the 
directory where the relative file is located, it will furnish a plot.
The C++ libraries which are used in the whole project are 5:
-iostream, declares objects that control reading from and writing to the standard 
 streams. This include is often the only header you need to do input and output from 
 a C++ program;
-cmath, provides the most used mathematical functions;
-ctime, contains definitions of functions to get and manipulate date and time
 information;
-chrono, which elements deal with time. In particular, we use it to measure durations;
-fstream, allows to print in a file the desired quantities.
I often specify the functions needed outside the main.
Francesco De Stefano.
