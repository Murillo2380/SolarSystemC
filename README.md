#Summary
This was a project for Graphic Computation subject and now it is online to assist other students with any doubts they may have with OpenGL api.

#Instructions
Use the **Makefile** to compile the project by typing `make` into the command line prompt then run the file using the `space` executable file.

##Arguments
To run this arguments, type as follows on the command-line prompt: `./space <args>`. Instead of **<args>**, choose one or more of the arguments listed below. Default values can be found on **spacedef.h** file.

**Note:** this project does not follow the Unix command-line patterns, instead the argument's name is an abreviation of what the command does.

* **-ep** Displays the path of the planes.
* **-ns** Disables the stars.
* **-dpf=<double_value>** Days per frame. Higher values means faster simulation (the planets will move faster).
* **-ss=<double_value>** Size scale. Higher number means bigger planets.
* **-ds=<double_value>** Distance scale. Higher number means bigger distance between the planets.

##Commands
Commands listed below, use capital letters to move faster.
* Horizontal move: w, a, s, d.
* Vertical move: e, q. 
* Look around: click and drag the mouse to the direction you want to look. This feature needs improvements.

#Known bugs
* The planets do not spin around itself.
* Gravity not implemented as was supposed to be (removed).

#Acknowledgements
The **star.c** file was used to inspire the author of this project on how to create the moving "space dust" you see in this project.

#Author's note
Comments are in Portuguese-BR, some parts of the code are not commented since this code was not intented to be distributed, it was just a homework. The purpose of this repo is to assist others and not to teach how to create a solar system using C language (improvements in comments should not be expected).



