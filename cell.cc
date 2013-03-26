#include "cell.h"


Cell::Cell(int row, int col)
{  
   //sets initial values of cell
   this->row = row;
   this->col = col;
   Cell::type = ' ';
   Cell::occupied = false;   
}

Cell::~Cell()
{
   
}
