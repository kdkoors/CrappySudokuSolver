#include "Group.H"
#include "Cell.H"

class Sudoku
{
  public:
    Sudoku( int initArray[][9][9], int num );
    
    Cell& getCell( int r, int c );

    void removeGroupValue( int r, int c, int val );

    void removeGroupValue( Cell* cell, int val );

    void printPrettyCandBlankBoard();
    void printPrettyBlankBoard();

    void printPrettyCandBoard();
    void printPrettyBoard();

    void printPrettyBlank();
    void printPretty();
    
    void printLine( int, char );


    //TIER 1
    //
    bool allCellFinalCheck( bool debug = false );

    bool allGroupFinalCheck( bool debug = false ); 


    //TIER 2
    //
    
    bool findLinearBoxCandidates();

    //void findFullCandidates();
    //bool findFullCandidates( Group& grp, int i );


  private:
    void init( int initArray[][9] );
    int calculateBoxIndex( int r, int c );

    Cell cell[9][9];

    Group row[9];
    Group col[9];
    Group box[9];

};

