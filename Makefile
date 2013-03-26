quadris : quadris.o board.o cell.o level.o zero.o one.o two.o three.o block.o Iblock.o Jblock.o Lblock.o Oblock.o Sblock.o Tblock.o Zblock.o window.o
	g++ quadris.o board.o cell.o level.o zero.o one.o two.o three.o block.o Iblock.o Jblock.o Lblock.o Oblock.o Sblock.o Tblock.o Zblock.o window.o PRNG.h -lX11 -o quadris

quadris.o : quadris.cc board.h zero.h one.h two.h three.h Iblock.h Jblock.h Lblock.h Oblock.h Sblock.h Tblock.h Zblock.h window.h
	g++ -c quadris.cc

window.o : window.cc window.h
	g++ -c window.cc
	
board.o : board.cc board.h
	g++ -c board.cc

cell.o : cell.cc cell.h
	g++ -c cell.cc

level.o : level.cc level.h
	g++ -c level.cc

zero.o : zero.cc zero.h
	g++ -c zero.cc

one.o : one.cc one.h
	g++ -c one.cc

two.o : two.cc two.h
	g++ -c two.cc

three.o : three.cc three.h
	g++ -c three.cc

block.o : block.cc block.h
	g++ -c block.cc

Iblock.o : Iblock.cc Iblock.h
	g++ -c Iblock.cc

Jblock.o : Jblock.cc Jblock.h
	g++ -c Jblock.cc

Lblock.o : Lblock.cc Lblock.h
	g++ -c Lblock.cc

Oblock.o : Oblock.cc Oblock.h
	g++ -c Oblock.cc

Sblock.o : Sblock.cc Sblock.h
	g++ -c Sblock.cc

Tblock.o : Tblock.cc Tblock.h
	g++ -c Tblock.cc

Zblock.o : Zblock.cc Zblock.h
	g++ -c Zblock.cc
