# CrappySudokuSolver
Really crappy implmentation of a Sudoku solver in C++

So this thing is terrible. Written in the middle
of the night during mission support.
It contains
a terrible circular reference between the Cell and
Group classes.  And the build process is, uh, unique.
You will notice that the "main" source file, sudo.C
does the #includes of not the header files but the C
source files themselves.  This is all due to the 
funky circular reference.

Anyway, if you have an even remotely recent copy of the
GNU C++ compliler it should build with a simple
'g++ -I . sudo.C'

I promise to make it better at some point.  

