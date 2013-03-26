#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "cell.h"
#include "board.h"
#define SIZE 4 //number of pieces in a block
#define BUFFERROWS 3 //top three rows for rotation space

class Block
{
   
  public:
   bool lost;//losing flag
   //current block state. each piece has a different number of possible rotation states
   int position;
   Cell **pieces;//array of pieces
   Board *board;  
   Block();
   ~Block();
   virtual void redraw();
   virtual void left();
   virtual void right();
   virtual void down();
   virtual void drop();
   virtual void rotateCW();
   virtual void rotateCC();
};


#endif
