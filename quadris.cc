#include <iostream>
#include <sstream>
#include <string>
#include "Oblock.h"
#include "Lblock.h"
#include "Jblock.h"
#include "Iblock.h"
#include "Tblock.h"
#include "Sblock.h"
#include "Zblock.h"
#include "zero.h"
#include "one.h"
#include "two.h"
#include "three.h"
#include "window.h"

using namespace std;

bool textOnly = false;
//given a window and a board, draws the graphical representation of the board within the window
void drawBoard(Xwindow *window, Board *board)
{
   int gridWidth = 10;//number of rows
   int gridHeight = 18;//number of columns
   //streams to cast ints to string
   stringstream level;  
   stringstream score;
   stringstream hiScore;
   
   window->fillRectangle(0, 0, 250, 500, 1);//set background
   window->fillRectangle(0, 0, 250, 50, 1);//set score section
   //write titles for score
   window->drawString(5, 15, "Level: ", 0);
   window->drawString(5, 30, "Score: ", 0);
   window->drawString(5, 45, "Hi Score: ", 0);
   
   //set starting level
   level << board->currentLevel;
   window->drawString(60, 15, level.str(),0);
   //set starting score
   score << board->currentScore;
   window->drawString(60, 30, score.str(),0);
   //set starting hi score
   hiScore << board->hiScore;
   window->drawString(80, 45, hiScore.str(),0);
   
   //iterates through window to draw grid
   for(int count = 0; count <= gridWidth; count++)
      window->fillRectangle(25*count, 50, 1, 500, 0);
   for(int count = 0; count < gridHeight; count++)
      window->fillRectangle(0, 50+(25*count), 250, 1, 0);
}


//assigns a color to each block type
int blockColor(char blockType)
{   
   if (blockType == 'I') return 2; 
   else if (blockType == 'J') return 3;
   else if (blockType == 'L') return 4;
   else if (blockType == 'T') return 5;
   else if (blockType == 'O') return 6;
   else if (blockType == 'S') return 7;
   else if (blockType == 'Z') return 8;
   else return 1;
}

//draws the upcoming block in the "next" window
void previewNext(Xwindow *window, Board *board)
{
   char nextBlock = board->next;
   int bevel = 1; //decorative bevel
   int graphicsMultiplier = 25;//each block (in window) is 25 pixels wide & tall, so multiplies coordinates
   //the following 7 cases draw the "next" block given the type
   //each rectangle fill has different constants added to each field for aesthetic purposes
   if (nextBlock == 'I') 
   {               
     int color = blockColor(nextBlock);     
     window->fillRectangle(graphicsMultiplier * 1 + bevel, graphicsMultiplier * 3 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 2 + bevel, graphicsMultiplier * 3 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 3 + bevel, graphicsMultiplier * 3 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 4 + bevel, graphicsMultiplier * 3 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
   }
   else if (nextBlock == 'J')
   {
     int color = blockColor(nextBlock);     
     window->fillRectangle(graphicsMultiplier * 1 + bevel, graphicsMultiplier * 3 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 1 + bevel, graphicsMultiplier * 4 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 2 + bevel, graphicsMultiplier * 4 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 3 + bevel, graphicsMultiplier * 4 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
   }
   else if (nextBlock == 'L') 
   {
     int color = blockColor(nextBlock);     
     window->fillRectangle(graphicsMultiplier * 1 + bevel, graphicsMultiplier * 4 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 2 + bevel, graphicsMultiplier * 4 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 3 + bevel, graphicsMultiplier * 4 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 3 + bevel, graphicsMultiplier * 3 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
   }
   else if (nextBlock == 'T')  
   {
     int color = blockColor(nextBlock);     
     window->fillRectangle(graphicsMultiplier * 1 + bevel, graphicsMultiplier * 3 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 2 + bevel, graphicsMultiplier * 3 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 3 + bevel, graphicsMultiplier * 3 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 2 + bevel, graphicsMultiplier * 4 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
   }
   else if (nextBlock == 'O')  
   {
     int color = blockColor(nextBlock); 
     window->fillRectangle(graphicsMultiplier * 1 + bevel, graphicsMultiplier * 3 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 2 + bevel, graphicsMultiplier * 3 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 1 + bevel, graphicsMultiplier * 4 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 2 + bevel, graphicsMultiplier * 4 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
   }
   else if (nextBlock == 'S') 
   {
     int color = blockColor(nextBlock);     
     window->fillRectangle(graphicsMultiplier * 1 + bevel, graphicsMultiplier * 4 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 2 + bevel, graphicsMultiplier * 4 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 2 + bevel, graphicsMultiplier * 3 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 3 + bevel, graphicsMultiplier * 3 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
   }
   else if (nextBlock == 'Z') 
   {
     int color = blockColor(nextBlock);     
     window->fillRectangle(graphicsMultiplier * 1 + bevel, graphicsMultiplier * 3 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 2 + bevel, graphicsMultiplier * 3 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 2 + bevel, graphicsMultiplier * 4 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     window->fillRectangle(graphicsMultiplier * 3 + bevel, graphicsMultiplier * 4 + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
   }
}
//iterates through grid and erases the previous "next" block
void eraseNext(Xwindow *window, Board *board)
{
   int previewGrid = 4;//size of small grid
   int graphicsMultiplier = 25;
   //iterate through grid
   for(int row = 1; row<= previewGrid; row++)
   {
      for(int col = 1; col <= previewGrid; col++)
      {
         window->fillRectangle(col*graphicsMultiplier + 1 , row*graphicsMultiplier + 1 , graphicsMultiplier - 3 , graphicsMultiplier- 3, 1);//cover with black/"erase"
      }
   }
   
}
//sets the preview window's design and draws first upcoming block
void drawNext(Xwindow *window, Board *board)
{
   window->fillRectangle(0, 0, 150, 150, 1);//set background
   window->drawString(5, 15, "Next:",0);
   for(int count = 1; count <= 5; count++)
   {
      window->fillRectangle(25*count, 25, 1, 100, 0);
      window->fillRectangle(25, 25*count, 100, 1, 0);
   }
   previewNext(window, board);
}

//draws the block currently being played, given the yBuffer for the score section and graphics multiplier for window size
void drawCurrent(Xwindow *window, int graphicsMultiplier, int yBuffer, Block *currBlock)
{
   //iterate through grid and fill corresponding pieces with colored blocks
   for (int count = 0; count < SIZE; count++)
   {
     //row and column coordinates
     int row = currBlock->pieces[count]->row * graphicsMultiplier + yBuffer;
     int col = currBlock->pieces[count]->col * graphicsMultiplier;
     
     char blockType = currBlock->pieces[count]->type;
     int bevel = 1;//decorative bevel
     int color = blockColor(blockType);//gets corresponding block color
     //draws the block
     window->fillRectangle(col + bevel , row + bevel, graphicsMultiplier - 4*bevel, graphicsMultiplier - 4*bevel, color);
     
   }
}
//main takes in command line arguments
int main(int argc, char* argv[])
{
   Xwindow *window = new Xwindow(250, 500);//main playing area
   Xwindow *nextWindow = new Xwindow(150, 150);//preview block window
   //covers cases for command line arguments
   if(argc > 3)
   {
      cerr<<"Invalid Number of Arguments"<<endl;      
   }
   else if(argc == 2)
   {
      if(argv[1] != "text")
      {
         textOnly = true;
      }
   }
   else if(argc == 3)
   {
      if(argv[1] != "-seed")
      {
         int s;
         istringstream ( argv[2] ) >> s;//casts string to int
         Board *board = new Board(window,s);//passes seed to board
      }      
   }
  
   
   int graphicsMultiplier = 25;//block pixel size
   int yBuffer = 50;//buffer area for score
   Board *board = new Board(window);//creates playing board
   Block *currBlock = board->current;//currently played block
   string line = "";
   string buffer = "";
   string commands[] = {"left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup", "leveldown", "restart"};//possible commands
   int numCommands = 9;
   size_t found;//index of string where letter is found (for autocomplete)
   int commandsFound = 0;
   string command = "";
   int mult;//command multiplier
   int count;   
   
   cout << (*board) << endl;//prints board
   
   
   
   drawBoard(window, board);//draws playing area    
   drawNext(nextWindow, board);//draws preview area
   drawCurrent(window, graphicsMultiplier, yBuffer, currBlock);//draws currently played block

   //gets commands until eof
   while (getline(cin, line))
   {
      count = mult = 0;
      
      //checks if user input has a number as first character
      while (line[0]-'0' < 10 && line[0]-'0' >= 0)
      {
         count++;
         mult = (mult * 10) + line[0] - '0';//covers multi digit cases
         ostringstream oss;
         //removes first character of string
         for (int i = 1; i < line.length(); i++) oss << line[i];
            line = oss.str();
      }
      //default "1" multiplier
      if (count == 0) mult = 1;
         
      commandsFound = 0; 
      command = "Command Not Found";//default command
      //iterates through array of commands to see if user input is a substring of any of them
      for( int count = 0; count < numCommands; count++)
      {                 
         found = commands[count].find(line);//gets the index in string where substring was found
         //if the substring was found at position 0 (start of word) increase number of commands which have been matched
         if(found!=string::npos &&  int(found) == 0)
         {
            commandsFound++;
            command = commands[count];//set command to the one which was found
         }
      }
      //if multiple matches are found, command is ambiguous
      if(commandsFound > 1)
         command = "Command is Ambiguous";         
      
      //calls each corresponding function according to command, and runs it as many times as the specified multiplier, if anys
      if (command == "left") for (int i = 0; i < mult; i++) (*currBlock).left();
      else if (command == "right") for (int i = 0; i < mult; i++) (*currBlock).right();
      else if (command == "down") for (int i = 0; i < mult; i++) (*currBlock).down();
      else if (command == "clockwise") for (int i = 0; i < mult; i++) (*currBlock).rotateCW();
      else if (command == "counterclockwise") for (int i = 0; i < mult; i++) (*currBlock).rotateCC();
      else if (command == "drop") for (int i = 0; i < mult; i++) (*board).dropCurrent();
      else if (command == "levelup") for (int i = 0; i < mult; i++) (*board).levelUp();
      else if (command == "leveldown") for (int i = 0; i < mult; i++) (*board).levelDown();
      else if (command == "restart") for (int i = 0; i < mult; i++) (*board).reset();
      else cerr << command << endl << endl;
      cout << (*board) << endl;//redraw board
      //drawCurrent(window, graphicsMultiplier, yBuffer, currBlock);
      currBlock = board->current;//points at new current block
      drawCurrent(window, graphicsMultiplier, yBuffer, currBlock);//redraws current block
      //draws upcoming block
      eraseNext(nextWindow, board);
      previewNext(nextWindow, board);
   }
 
   //clears memory when program ends
   delete board;
   delete window;
   delete nextWindow;
}
