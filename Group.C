Group::Group():
  cellIndex( 0 )
{
}

void
Group::delGroupCandidate( int val )
{
  for( int i=0; i<9; i++ )
  {
    cell[i]->delCellCandidate( val );
    candCount[val] = 0;
  }
}

bool
Group::checkGroupSolved()
{
  bool retVal = false;
  for(int v=1; v<=9; v++ )
  {
    if( checkGroupSolved( v ) )
    {
      retVal = true;
    }
  }
  return( retVal );
}

bool
Group::checkGroupSolved( int val )
{
  int candCount = 0;
  int cellIndex = 0;

  for( int c=0; c<9; c++ )
  {
    if( cell[c]->isCellCandidate( val ) )
    {
      candCount++;
      cellIndex = c;
    }
  }
  if( candCount == 1 )
  {
    cell[cellIndex]->setCellValue( val );
    return( true );
  }
  else
  {
    return( false );
  }
}

void
Group::addCell( Cell* aCell )
{
  cell[cellIndex++] = aCell;
}

