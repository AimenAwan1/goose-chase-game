//START: gooseEscapeMain.cpp

/* Aimen Awan and Joanna Deng*/

#include <BearLibTerminal.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActor.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

Console out;

int main()
{
	srand(time(0));
    terminal_open();
  	terminal_set(SETUP_MESSAGE);
	
	// initializing and declaring player and monster
	int playerX = 0; 
	int playerY = 0;
	int gooseX = 0;
	int gooseY = 0;
	
	randLocation(playerX, playerY, gooseX, gooseY);
		
	Actor player(PLAYER_CHAR, playerX , playerY, 100);
	Actor monster(MONSTER_CHAR, gooseX, gooseY, 100);
	
    char map[row][columns];
    initializeBoard(map);

	//initializing special tile locations
	for(int col = 10; col < 20; col++)
	{
		map[10][col] = SHALL_NOT_PASS;	
	}
	
	map[0][0] = CORNER;
	map[20][0] = CORNER;
	map[0][79] = CORNER;
	map[20][79] = CORNER;
		
	map[10][21] = JUMP_TILE;
	map[3][7] = JUMP_TILE;
	map[5][70] = JUMP_TILE;
	
	map[11][21] = GOOSE_POOP;
	map[5][60] = GOOSE_POOP;
	map[18][5] = GOOSE_POOP;
	
	map[15][66] = POWER_UP;
	
  	map[10][5]= WINNER;
  	
  	printBoard(map);
  	
    out.writeLine("Escape the Goose! " + monster.get_location_string());
	out.writeLine("Use the arrow keys to move, press I for instructions, and H "
				  "for health");
	out.writeLine("If the goose catches you, you lose!");
	out.writeLine("Be careful! Sometimes the goose can jump through walls!");

    int keyEntered = TK_A; 
    
    while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE 
          && !captured(player,monster) 
		  && map[player.get_y()][player.get_x()] != WINNER 
		  && player.get_health_int() != 1)
	{
	    keyEntered = terminal_read();

        if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
        {
    	    movePlayer(keyEntered,player, map);
    	    blowGoose(player,monster, map, keyEntered);
		    moveGoose(monster, player, map);
    	    if(changeHealth(player, map))	
				out.writeLine(player.get_health_message());			
			instructions(keyEntered, player);
        }
  	}

    if (keyEntered != TK_CLOSE)
    {
        out.writeLine("Game has ended");

		if (captured(player,monster))
			out.writeLine("The goose got you :(");
		
		else if(player.get_x() == 5 && player.get_y() == 10)
			out.writeLine("Congratulations, you won!");
			
		else if (player.get_health_int() == 1)
			out.writeLine("You died from E.coli from the goose poop :(");
						
        while (terminal_read() != TK_CLOSE);
   }
    terminal_close();
}

//END: gooseEscapeMain.cpp
