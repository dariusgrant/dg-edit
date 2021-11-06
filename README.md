# dg-edit: A simple text editor using C++ and FLTK.

## Minimum Requirements (earlier versions might work, but are untested)

* gcc >= 11.1.0 
* FLTK >= 1.3.7
* CMake >= 3.21

## Building

0.  Install Dependencies
    * Ensure that you have CMake and git installed and accessible from a shell.
1.  Open a shell which provides git and clone the repository with:
    '''git clone https://github.com/dariusgrant/dg-edit.git'''
2.  Go to the newly cloned dg-edit directory.
3.  Create a new directory named '''build''' and change the current directory to the newly created folder.
4.  Create a build environment with CMake
    '''cmake -S ../ -B ./'''
5.  Either open the generated project with an IDE or launch the build process with '''cmake --build .'''.

## Running

* To create a new file, run '''./dg-edit'''.
* To load an existing file, run '''./dg-edit <filename>'''.
