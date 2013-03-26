#ifndef __OBLOCK_H__
#define __OBLOCK_H__
#include "block.h"

class Oblock: public Block
{
  public:
   Oblock(Board *board);
   ~Oblock();
   void erase(int row, int col);
   void redraw();
   void left();
   void right();
   void down();
   void drop();
   void rotateCW();
   void rotateCC();
};


#endif
