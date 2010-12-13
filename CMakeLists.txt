CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(PhaedrusFPS)

# Add the libraries
ADD_SUBDIRECTORY(lib)

# Add all the source files, which also creates the phaedrusfps executable, linked against the libraries
ADD_SUBDIRECTORY(src)