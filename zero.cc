#include "zero.h"

Zero::Zero(Board *board)
{
   //sets fields
   this->board = board;
   this->streamCount = 0;
}
Zero::~Zero()
{
}
char Zero::nextBlock()
{
   //uses ifstream to read from file
   std::string blockType = "";
   std::ifstream ifs("sequence.txt");
   //reads character from stream
   for (int i = 0; i <= streamCount; i++)
   {
      blockType = "";
      ifs>>blockType;
   }
   this->streamCount++;
   //calls for the creation of corresponding block given its type
   if (blockType == "I") return 'I'; //Iblock(this->board);
   else if (blockType == "J") return 'J';//Jblock(this->board);
   else if (blockType == "L") return 'L';//Lblock(this->board);
   else if (blockType == "T") return 'T';//Tblock(this->board);
   else if (blockType == "O") return 'O';//Oblock(this->board);
   else if (blockType == "S") return 'S';//Sblock(this->board);
   else if (blockType == "Z") return 'Z';//Zblock(this->board);

}
