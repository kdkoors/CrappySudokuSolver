class Cell;

class Group
{
  public:
    Group();

    // Used during initialization to populate group
    //
    void addCell( Cell* aCell );

    // Used to remove candidates from group's cells once
    // a cell has a final solution
    //
    void delGroupCandidate( int val );

    // Checks for a single instance of a candidate amoung
    // group's cells
    //
    bool checkGroupSolved();
    bool checkGroupSolved( int val );

    Cell* cell[9];

  protected:

    //Keep track of candidate counts for this group
    int candCount[9];

    //Just for initialization
    //
    int cellIndex;
};

