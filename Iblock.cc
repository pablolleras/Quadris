#include "Iblock.h"
#include <iostream>
Iblock::Iblock(Board *board)
{
   //sets fields
   this->board = board;
   //array which holds coordinates of block's pieces
   Iblock::pieces = new Cell*[SIZE];
   lost = false;
   position = 0;//state of block
   //sets intitial position of block when it spawns
   for (int count = 0; count < SIZE; count++)
   {
      pieces[count] = this->board->theBoard[BUFFERROWS][count];
      
      if(pieces[count]->occupied) lost = true;

   } 
   //draws the block if the space is not occupied
   if (!lost)
      for (int count = 0; count < SIZE; count++)
      {
         pieces[count]->occupied = true;
         pieces[count]->type = 'I';
      }
}
Iblock::~Iblock()
{
   for (int i = 0; i < SIZE; i++)
   {
      pieces[i]->occupied = false;
      pieces[i]->type = ' ';
   }
}
//redraws the block's position
void Iblock::redraw()
{
   //iterates through cell and draws piece on board
   for(int count = 0; count < SIZE; count++)
   {
      pieces[count]->occupied = true;
      pieces[count]->type = 'I';
   }
}
//erases old position of block
void Iblock::erase(int row, int col)
{
   int graphicsMultiplier = 25;
   int yBuffer = 50;
   this->board->window->fillRectangle(col*graphicsMultiplier + 1 , row*graphicsMultiplier + yBuffer + 1 , graphicsMultiplier - 3 , graphicsMultiplier- 3, 1);
}
//shifts block one to the left, if possible
void Iblock::left()
{
   int row;
   int col;
   //iterates through block's current position and de-occupieds space
   for(int count = 0; count < SIZE; count++)
   {
      pieces[count]->occupied = false;
   }
   //checks if piece goes off board, leaves it in its place
   for(int count = 0; count < SIZE; count++)
   {
      col = pieces[count]->col;
      
      if (col - 1 < 0)
      {
         //if piece is off board, don't move it
         for (int count = 0; count < SIZE; count++)
         {
            pieces[count]->occupied = true;
            return;
         }
      }
   }
   //checks for collision on the left
   for(int count = 0; count < SIZE; count++)
   {
      row = pieces[count]->row;
      col = pieces[count]->col;
      Cell *temp = this->board->theBoard[row][col-1];
      if (temp->occupied) return;

   }
   //shifts all pieces of block one to the left
   for(int count = 0; count < SIZE; count++)
   {
      row = pieces[count]->row;
      col = pieces[count]->col;      
      this->erase(row,col);
      pieces[count]->type = ' ';
      pieces[count] = this->board->theBoard[row][col - 1];      
   }  
   this->redraw();
}
//shifts block one to the right, if possible
void Iblock::right()
{
   int row;
   int col;
   //iterates through block's current position and de-occupieds space
   for(int count = 0; count < SIZE; count++)
   {
      pieces[count]->occupied = false;
   }
   //checks if piece goes off board, leaves it in its place
   for(int count = 0; count < SIZE; count++)
   {
      col = pieces[count]->col;
      if (col + 1 >= NUMCOLS)
      {
         //if piece is off board, don't move it
         for (int count = 0; count < SIZE; count++)
         {
            pieces[count]->occupied = true;
            return;
         }
      }
   }
   //checks for collision on the right
   for(int count = 0; count < SIZE; count++)
   {
      row = pieces[count]->row;
      col = pieces[count]->col;
      Cell *temp = this->board->theBoard[row][col+1];
      if (temp->occupied) return;

   }
   //shifts all pieces of block one to the right
   for(int count = 0; count < SIZE; count++)
   {
      row = pieces[count]->row;
      col = pieces[count]->col;      
      this->erase(row,col);
      pieces[count]->type = ' ';
      pieces[count] = this->board->theBoard[row][col + 1];      
   }  
   this->redraw();
}
//shifts block down, if possible
void Iblock::down()
{
   int row;
   int col;
   //iterates through block's current position and de-occupieds space
   for(int count = 0; count < SIZE; count++)
   {
      pieces[count]->occupied = false;
   }
   //checks if piece goes off board, leaves it in its place
   for(int count = 0; count < SIZE; count++)
   {
      row = pieces[count]->row;
      //if piece is off board, don't move it
      if (row + 1 >= NUMROWS)
      {
         for (int count = 0; count < SIZE; count++)
         {
            pieces[count]->occupied = true;
            return;
         }
      }
   }
   //checks for collision on the bottom
   for(int count = 0; count < SIZE; count++)
   {
      row = pieces[count]->row;
      col = pieces[count]->col;
      Cell *temp = this->board->theBoard[row + 1][col];
      if (temp->occupied) return;

   }
   //shifts all pieces of block down
   for(int count = 0; count < SIZE; count++)
   {
      row = pieces[count]->row;
      col = pieces[count]->col;      
      this->erase(row,col);
      pieces[count]->type = ' ';
      pieces[count] = this->board->theBoard[row + 1][col];      
   }  
   this->redraw();
}
//moves current block down to the bottom of the board, ends turn
void Iblock::drop()
{
   //calls the down function until the piece reaches the bottom of the board
   for(int count = 0; count < NUMROWS; count++)
   {
      (*this).down();
   }
   //redraw piece if you did not lose
   if(!lost) this->redraw();
   //end the turn
   (*Iblock::board).endTurn();
}
//rotates piece clockwise, if possible
void Iblock::rotateCW()
{
   int row;
   int col;
   //checks if rotation is posible
   bool possible = true;
   //checks for the piece's current state, and shifts it accordingly. I has 2 states ( |, _ )
   if (position == 0)
   {
      //iterates through the pieces of the block and makes them "ghost" pieces
      //such that collision can be detected
      for (int i = 0; i < SIZE; i++)
      {
         pieces[i]->occupied=false;
         pieces[i]->type = ' ';
         row = pieces[i]->row;
         col = pieces[i]->col;
         //if the piece is off the board or hits another block in the process of rotation, abort rotation
         if (row-i < 0 || col-i < 0 || this->board->theBoard[row-i][col-i]->occupied)
         {            
            possible = false;//sets flag
         }
         
      }
      //if rotation is possible, shift all cells accordingly
      if (possible)
      {
         position++;
         //iterate through array of pieces and give each its new coordinates
         for (int i = 0; i < SIZE; i++)
         {
            //de-occupy previous location
            pieces[i]->occupied=false;
            pieces[i]->type = ' ';
            //get row and column coordinates
            row = pieces[i]->row;
            col = pieces[i]->col;
            //erase piece
            erase(row,col);
            //give piece new coordinates
            pieces[i] = this->board->theBoard[row-i][col-i];
         }
      }
   }
   //second position (from | to _)
   else 
   {
      //iterates through the pieces of the block and makes them "ghost" pieces
      //such that collision can be detected
      for (int i = 0; i < SIZE; i++)
      {
         pieces[i]->occupied=false;
         pieces[i]->type=' ';
         row = pieces[i]->row;
         col = pieces[i]->col;
         //if the piece is off the board or hits another block in the process of rotation, abort rotation
         if (row+i >= NUMROWS || col+i >= NUMCOLS || this->board->theBoard[row+i][col+i]->occupied) possible = false;
      }
      //if rotation is possible, shift all cells accordingly
      if (possible)
      {
         position--;
         //iterate through array of pieces and give each its new coordinates
         for (int i = 0; i < SIZE; i++)
         {
            //de-occupy previous location
            pieces[i]->occupied=false;
            pieces[i]->type = ' ';
            //get row and column coordinates
            row = pieces[i]->row;
            col = pieces[i]->col;
            //erase piece
            erase(row,col);
            //give piece new coordinates
            pieces[i] = this->board->theBoard[row+i][col+i];
         }
      }
   }
   this->redraw();
}
//rotates clockwise 3 times normally. in the specific case of I block, both directions of rotation
//result in the same outcome, and as such counterclockwise simply calls clockwise;
void Iblock::rotateCC()
{
   rotateCW();
}
