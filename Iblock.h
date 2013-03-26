#ifndef __IBLOCK_H__
#define __IBLOCK_H__
#include "block.h"

class Iblock: public Block
{
  public:
   Iblock(Board *board);
   ~Iblock();
   void redraw();
   void erase(int row, int col);
   void left();
   void right();
   void down();
   void drop();
   void rotateCW();
   void rotateCC();
};


#endif
