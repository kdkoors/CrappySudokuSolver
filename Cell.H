class Cell
{
  public:
    Cell(){}

    void
    init( Group*, Group*, Group* );

    void
    setCellValue( int val );

    int
    getCellValue();

    bool
    isCellCandidate( int val );

    // returns cell solution, if found
    bool
    delCellCandidate( int val );

    int
    checkCellSolved();

    Group* getRow(){ return( row ); }
    Group* getCol(){ return( col ); }
    Group* getBox(){ return( box ); }

  protected:

    Group* row;
    Group* col;
    Group* box;

    int solvedValue;
    bool candidate[9];

};

