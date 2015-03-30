#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>

#include "Sudoku.H"

#include "Cell.C"
#include "Group.C"

#include "Sudoku.C"

#include "puzzle.h"

//////////////////////////////////////////////////////////////////////
//                             MAIN
//////////////////////////////////////////////////////////////////////
int main( int argc, char* argv[] )
{
  int num = -1;

  
  std::cout << "Enter puzzle number (0-4):";
  std::cin >> num;

  if (num < 0 || num > 4 )
  {
    std::cout << "\nInvalid Puzzle Number\n";
    _exit( 1 );
  }
  Sudoku sudoku( iarr, num );

  sudoku.printPrettyCandBlankBoard();
  sudoku.printPrettyBlankBoard();
  sudoku.printPrettyCandBoard();
  sudoku.printPrettyBoard();
  sleep( 1 );

  bool done = false;

  while( !done )
  {
    done = true;
    bool cellChange   = true;
    bool groupChange  = true;

    while ( cellChange || groupChange )
    {
      cellChange  = sudoku.allCellFinalCheck();
      groupChange = sudoku.allGroupFinalCheck();

      if( cellChange )
      if( groupChange )
      if( cellChange || groupChange )
      {
        done = false;
      }
    }

    bool tier2 = true;
    while( tier2 )
    {
      tier2 = sudoku.findLinearBoxCandidates();
      if( tier2 )
      {
        done = false;
      }
    }
  }

  //sudoku.printPrettyBlankBoard();
  //sudoku.printPrettyCandBlankBoard();
  //sudoku.printPrettyCandBoard();
  //sudoku.printPrettyBoard();

  //sudoku.printPrettyBlank();
  //sudoku.printPrettyCandBoard();
}
