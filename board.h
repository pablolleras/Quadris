#ifndef __BOARD_H__
#define __BOARD_H__
#define NUMCOLS 10//board width
#define NUMROWS 18//board height
#include <iostream>
#include <sstream>
#include <string>
#include "cell.h"
#include "window.h"
#include "PRNG.h"

class Block;
class Level;

class Board
{
     
   Level *level;     //level object
   
  public:
   PRNG *random; 
   int currentLevel;//level indicator
   int hiScore;
   int currentScore;
   Cell ***theBoard;
   Xwindow *window;    
   Board(Xwindow *window);
   Board(Xwindow *window, int seed);
   Board();
   ~Board();
   Block *current;
   char next; // type of upcoming block
   int blockColor(char blockType);
   void erase(int row, int col);
   void redrawBoard(int row, int col, char blockType);
   void dropCurrent();
   void dropRows(int rowsCleared, int emptyRow);
   void calculateScore();
   void reset();
   void levelUp();
   void levelDown();
   void endTurn();
   
   friend std::ostream& ::operator<<(std::ostream &out, const Board &b);
};


#endif
