# Projet2020

## Compiling the project
To compile the project, a makefile is provided, and should work without any problems. This project is designed for Linux (tested on Debian), and might not work on other operating systems.

## Libraries
All the libraries used in this project (aside of the standard C librarie) are in the ./libs directory
If the compilation isn't working, consider extracting the corresponding archive, and then performing the following commands:

```
cd ./libs/thelibyouwanttoinstall
make
su root
make install
```

or installing the librarie from the package manager (might not be the correct version though)
