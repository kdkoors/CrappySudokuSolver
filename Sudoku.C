#include "../TxtGrafx.H"

Sudoku::Sudoku( int initArray[][9][9], int num )
{
  int b = 0;

  for( int r=0; r<9; r++ )
  {
    for( int c=0; c<9; c++ )
    {
      b = calculateBoxIndex( r, c );

      row[r].addCell( &(cell[r][c]) );
      col[c].addCell( &(cell[r][c]) );
      box[b].addCell( &(cell[r][c]) );

      cell[r][c].init( &row[r], &col[c], &box[b] );
    }
  }

  init( initArray[num] );
}

void
Sudoku::init( int valArray[][9] )
{
  for( int r=0; r<9; r++ )
  {
    for( int c=0; c<9; c++ )
    {
      if( valArray[r][c] != 0 )
      {
        cell[r][c].setCellValue( valArray[r][c] );
      }
    }
  }
}

int
Sudoku::calculateBoxIndex( int r, int c )
{
  int b = 0;

  if( c >= 6 )
  {
    b = 2;
  }
  else if( c >= 3 )
  {
    b = 1;
  }

  if( r >= 6 )
  {
    b += 6;
  }
  else if( r >= 3 )
  {
    b +=3;
  }

  return b;
}

Cell&
Sudoku::getCell( int r, int c )
{
    return cell[r][c];
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////TIER ONE////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool
Sudoku::allCellFinalCheck( bool debug )
{
  bool retVal = false;
  for( int r=0; r<9; r++ )
  {
    for( int c=0; c<9; c++ )
    {
      int val = 0;
      val = cell[r][c].checkCellSolved( );
      if( val != 0 )
      {
        cell[r][c].getRow()->delGroupCandidate( val );
        cell[r][c].getCol()->delGroupCandidate( val );
        cell[r][c].getBox()->delGroupCandidate( val );
        retVal = true;
        printPrettyCandBoard();
        printPrettyBoard();
        //std::cout << "Cell ";
        sleep( 1 );
      }
    }
  }
  return( retVal );
}

bool
Sudoku::allGroupFinalCheck( bool debug )
{
  bool retVal = false;
  for( int i=0; i<9; i++ )
  {
    if( row[i].checkGroupSolved() ||
        col[i].checkGroupSolved() ||
        box[i].checkGroupSolved() )
    {
      retVal = true;
      printPrettyCandBoard();
      printPrettyBoard();
      //std::cout << "Group";
      sleep( 1 );
    }

  }
  return( retVal );
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////TIER TWO////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool
Sudoku::findLinearBoxCandidates()
{
  bool retVal = false;
  //Go through each box and look for candiates in single row or col
  //so that they can be eliminated from the row/col in neighboring
  //boxes

  //Fist find the linear candidates with boxes.
  //
  for(int b=0; b<9; b++ )
  {
    for(int v=1; v<=9; v++ )
    {
      int candCount =  0;
      Group* rGrp = NULL;
      Group* cGrp = NULL;
      bool notLinear = false;
      bool candidateFound = false;

      for(int c=0; c<9; c++ )
      {
        if( notLinear )
        {
          break;
        }
        else if( box[b].cell[c]->isCellCandidate( v ) )
        {
          candidateFound = true;
          candCount++;
          switch( candCount )
          {
            case 1:
              //found our first candidate cell
              //save col and row information for comparison
              //
              rGrp = box[b].cell[c]->getRow();
              cGrp = box[b].cell[c]->getCol();
              break;

            case 2:
              //establish direction or non-linearity
              if( box[b].cell[c]->getRow() == rGrp )
              {
                cGrp = NULL;
              }
              else if( box[b].cell[c]->getCol() == cGrp )
              {
                rGrp = NULL;
              }
              else
              {
                notLinear = true;
              }
              break;

            case 3:
              //if there is a third candidate then make sure it
              //is line with the previous two
              if( box[b].cell[c]->getRow() != rGrp &&
                  box[b].cell[c]->getCol() != cGrp )
              {
                notLinear = true;
              }
              break;

            default:
              notLinear = true;
          }
        }
      }
      //have gone through the cells in the box looking for current
      //candidate.  If it's linear then remove candidates in the row/col
      //cells that are outside the current box
      if( !notLinear && candidateFound ) //love the double negatives
      {
        Group* rowcol = NULL;
        if( cGrp != NULL )
        {
          rowcol = cGrp;
        }
        else if( rGrp != NULL )
        {
          rowcol = rGrp;
        }
        
        for( int c=0; c<9; c++ )
        {
          if( rowcol->cell[c]->getBox() != &(box[b]) )
          {
            if( rowcol->cell[c]->delCellCandidate( v ) )
            {
              retVal = true;
              printPrettyCandBoard();
              printPrettyBoard();
              //std::cout << "Tier2";
              sleep( 1 );
            }
          }
        }
      }
    }
  }
  return( retVal );
}

/*void
Sudoku::findFullCandidates()
{
  //if for any n cells in a group there exist only n candidates then
  //those candidates must be exclusive to those cells and can be elminated
  //from all other cells in the group

  for( int g=0; g<9; g++ )
  {
    for(int i=2; i<5; i++ )
    {
      findFullCandidates( box[g], i );
      findFullCandidates( col[g], i );
      findFullCandidates( row[g], i );
    }
  }
}
*/
/*bool
Sudoku::findFullCandidates( Group& grp, int depth )
{
  bool candGroupMap[9][9]= {false};
  int  candGoupCount[9] = {0};

  // go through the group and accumulate data on    
  for( int cand=0; cand<9; cand++ )
  {
    for( int c=0; c<9; c++ )
    {
      if( grp.cell[c]->isCellCandidate[cand] )
      {
        candGroupCount[cand] += 1;
        candGroupMap[c][cand] = true;
      }
    }
  }

  depthCandidates[depth];
  for( int depthCount=0; depthCount<depth; depthCount++ )
  {
    for( int cand=0; cand<9; cand++ )
    {
      if( candGroupCount[cand] == depth )
      {
          //another number has the same number of candidate cells in 
          //the group.  Check to see if those cells match ours
      }
    }
  }
}
*/

//////////////////////////////////////////////////////////////////////////
//////////////////////////PRINTERS////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void
Sudoku::printPrettyCandBlankBoard()
{
  std::cout << "\e[H" << "\e[2J";
  std::cout << NRM_MAG_FG << xddx;
  for( int i=0; i<3; i++ )
  {
    std::cout << xxdd << xxdd << xxdd << xxdd << xxdd << xsdd  
              << xxdd << xxdd << xxdd << xxdd << xxdd << xsdd 
              << xxdd << xxdd << xxdd << xxdd << xxdd << xddd;
  }
  std::cout << "\e[D" << xdxd << std::endl;

  for( int h=0; h<3; h++ )
  {
    for( int i=0; i<3; i++ )
    {
      for( int j=0; j<3; j++ )
      {
        std::cout << ddxx << "     " << ssxx << "     " << ssxx << "     ";
        std::cout << ddxx << "     " << ssxx << "     " << ssxx << "     ";
        std::cout << ddxx << "     " << ssxx << "     " << ssxx << "     ";
        std::cout << ddxx << std::endl;
      }
      std::cout << ddsx;
      for( int j=0; j<3; j++ )
      {
        std::cout << xxss << xxss << xxss << xxss << xxss << ssss 
                  << xxss << xxss << xxss << xxss << xxss << ssss 
                  << xxss << xxss << xxss << xxss << xxss << ddss; 
      }
      std::cout << "\e[D" << ddxs << std::endl;
    }
    std::cout << "\e[A" << dddx;
    for( int i=0; i<3; i++ )
    {
      std::cout << xxdd << xxdd << xxdd << xxdd << xxdd << ssdd 
                << xxdd << xxdd << xxdd << xxdd << xxdd << ssdd 
                << xxdd << xxdd << xxdd << xxdd << xxdd << dddd;
    }
    std::cout << "\e[D" << ddxd << std::endl;
  }

  std::cout << "\e[A" << dxdx;
  for( int i=0; i<3; i++ )
  {
    std::cout << xxdd << xxdd << xxdd << xxdd << xxdd << sxdd 
              << xxdd << xxdd << xxdd << xxdd << xxdd << sxdd 
              << xxdd << xxdd << xxdd << xxdd << xxdd << dxdd;
  }
  std::cout << "\e[D" << dxxd << std::endl;
}


void
Sudoku::printPrettyBlankBoard()
{
  //std::cout << "\e[H" << "\e[2J";
  std::cout << NRM_MAG_FG << xddx;
  for( int i=0; i<3; i++ )
  {
    std::cout << xxdd << xxdd << xxdd << xsdd  
              << xxdd << xxdd << xxdd << xsdd 
              << xxdd << xxdd << xxdd << xddd;
  }
  std::cout << "\e[D" << xdxd << std::endl;
  for( int h=0; h<3; h++ )
  {
    for( int i=0; i<3; i++ )
    {
      for( int j=0; j<3; j++ )
      {
        std::cout << ddxx << "   " << ssxx << "   " << ssxx << "   ";
      }
      std::cout << ddxx << std::endl << ddsx;

      for( int j=0; j<3; j++ )
      {
        std::cout << xxss << xxss << xxss << ssss 
                  << xxss << xxss << xxss << ssss 
                  << xxss << xxss << xxss << ddss; 
      }
      std::cout << "\e[D" << ddxs << std::endl;
    }
    std::cout << "\e[A" << dddx;
    for( int i=0; i<3; i++ )
    {
      std::cout << xxdd << xxdd << xxdd << ssdd 
                << xxdd << xxdd << xxdd << ssdd 
                << xxdd << xxdd << xxdd << dddd; 
    }
    std::cout << "\e[D" << ddxd << std::endl;
  }

  std::cout << "\e[A" << dxdx;
  for( int i=0; i<3; i++ )
  {
    std::cout << xxdd << xxdd << xxdd << sxdd 
              << xxdd << xxdd << xxdd << sxdd 
              << xxdd << xxdd << xxdd << dxdd; 
   }
  std::cout << "\e[D" << dxxd << std::endl;
}

void
Sudoku::printPrettyBlank()
{
  printPrettyCandBlankBoard();
  printPrettyBlankBoard();
}

void
Sudoku::printPrettyCandBoard()
{
  std::cout << "\e[H";
  std::cout << BRT_YLW_FG;
  for(int r=0; r<9; r++ )
  {
    for( int c=0; c<9; c++ )
    {
      int x = c*6 + 3;
      int y = r*4 + 2;
      printf( "\e[%d;%dH", y, x );
      //std::cout << "x";

      for( int v=0; v<9; v++ )
      {
        int xOffset = x + v%3;
        int yOffset = y + v/3;
        printf( "\e[%d;%dH", yOffset, xOffset );
        if( cell[r][c].isCellCandidate( v+1 ) )
        {
          std::cout << v+1; 
        }
        else
        {
          std::cout << " ";
        }
      }
    }
  }
  std::cout << "\e[3E\e[2C";
}

void
Sudoku::printPrettyBoard()
{
  std::cout << BRT_YLW_FG;
  for(int r=0; r<9; r++ )
  {
    for( int c=0; c<9; c++ )
    {
      int value = cell[r][c].getCellValue();

      if( value < 1 )
      {
        std::cout << " ";
      }
      else
      {
        std::cout << value;
      }
      std::cout << "\e[3C";
    }
    std::cout << "\e[2E\e[2C";
  }
  std::cout << RESET << "\e[2B\n";
}

