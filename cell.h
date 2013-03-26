#ifndef __CELL_H__
#define __CELL_H__

class Cell
{
 public:
  int row;
  int col;
  char type;//content of cell
  bool occupied;
  Cell(int row, int col);
  ~Cell();
};


#endif
