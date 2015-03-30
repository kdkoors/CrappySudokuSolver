//--------------------------------------------------------------------

void
Cell::init( Group* r, Group* c, Group* b )
{
  row = r;
  col = c;
  box = b;
  for( int i=0; i<9; i++ )
  {
    candidate[i] = true;
  }
  solvedValue = 0;
}

//--------------------------------------------------------------------

void
Cell::setCellValue( int val )
{
  solvedValue = val;

  for( int i=0; i<9; i++ )
  {
    candidate[i] = false;
  }

  row->delGroupCandidate( val );
  col->delGroupCandidate( val );
  box->delGroupCandidate( val );
}

//--------------------------------------------------------------------

int
Cell::getCellValue()
{
  return solvedValue;
}
//--------------------------------------------------------------------

bool
Cell::isCellCandidate( int val )
{
  return candidate[val-1];
}

//--------------------------------------------------------------------

bool
Cell::delCellCandidate( int val )
{
  if( candidate[val-1] == false )
  {
    return( false );
  }
  else
  {
    candidate[val-1] = false;
    return( true );
  }
}

//--------------------------------------------------------------------

int
Cell::checkCellSolved()
{
  int candidateCount = 0;
  int solution = 0;

  for( int i=0; i<9; i++ )
  {
    if( candidate[i] == true )
    {
      solution = i+1;
      candidateCount++;
    }
  }
  if( candidateCount == 1 )
  {
    setCellValue( solution );
    return solution;
  }
  else
  {
    return 0;
  }
}

//--------------------------------------------------------------------

