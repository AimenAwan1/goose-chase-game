//START: gooseEscapeGamePlay.cpp

#include <iostream>
#include <cmath>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActor.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

extern Console out;

//initialize board function
void initializeBoard(char map[row][columns])
{
	for (int count = 0; count < row; count++)
	{
		for (int index = 0; index < columns; index++)
		{
			map[count][index] = ' ';
		}
	}
}

//print board function
void printBoard(char map[row][columns])
{

    terminal_put(5, 10, WIN_CHAR);
    terminal_put(70, 5, JUMP_CHAR);
    terminal_put(7, 3, JUMP_CHAR);
	terminal_put(21, 10, JUMP_CHAR);
	terminal_put(21, 11, POOP_CHAR);
	terminal_put(60, 5, POOP_CHAR);
	terminal_put(5, 18, POOP_CHAR);
	terminal_put(66, 15, POWERUP_CHAR);
	
    for(int rows = 10; rows < 20; rows++)
	{
		terminal_put(rows, 10, WALL_CHAR);	
	}
}

bool captured(Actor const & player, Actor const & monster)
{
    return (player.get_x() == monster.get_x() 
         && player.get_y() == monster.get_y());
}

//function to move player
void movePlayer(int key, Actor & player, char map[row][columns])
{
    int yMove = 0, xMove = 0;
    if (key == TK_UP)
        yMove = -1;
    else if (key == TK_DOWN)
        yMove = 1;
    else if (key == TK_LEFT)
        xMove = -1;
    else if (key == TK_RIGHT)
        xMove = 1;
      
	// make the player jump 5 tiles power-up
	if(map[player.get_y()][player.get_x()] == JUMP_TILE)
	{
		yMove *= jumpTile;
		xMove *= jumpTile; 	
	}	

    if (player.can_move(xMove, yMove) 
      && map[player.get_y()][player.get_x()]!= SHALL_NOT_PASS)
        player.update_location(xMove, yMove);
}

//funtion to move monster
void moveGoose(Actor & monster, Actor & player, char map[row][columns])
{
	if(monster.get_x() > player.get_x())
		monster.update_location(-1, 0);
	else if(monster.get_x() < player.get_x())
		monster.update_location(1, 0);
		
	else if(monster.get_y() > player.get_y())
		monster.update_location(0, -1);
	else if(monster.get_y() < player.get_y())
		monster.update_location(0, 1);

	//reprint board if player or goose overide other tiles except for wall
	if(map[player.get_y()][player.get_x()] != SHALL_NOT_PASS)
		printBoard(map);
		
}

//function to increase or decrease player's health
bool changeHealth(Actor & player, char map[row][columns])
{
	if(map[player.get_y()][player.get_x()] == GOOSE_POOP)
	{
		player.update_health(-oneLife);
		return 1;
	}
		
	if(map[player.get_y()][player.get_x()] == POWER_UP)
	{
		player.update_health(oneLife);
		return 1;
	}	
	return 0;
}

//function to teleport goose away
void blowGoose(Actor & player, Actor & monster, char map[row][columns], 
			   int keyEntered)
{
	if(map[player.get_y()][player.get_x()] == CORNER && keyEntered == TK_SPACE)
	{
		if(player.get_x() == 0)
			monster.update_location(79 - monster.get_x(), 0);
		else if(player.get_x() == 79)	
			monster.update_location(-monster.get_x(), 0);	
	}		
}

//initialize player and goose to random location each game
void randLocation(int & playerX, int & playerY, int & gooseX, int & gooseY)
{
	do
	{
		playerX = rand() % 40 + 40; 
		playerY = rand() % 10;
		
		gooseX = rand() % 40 + 40;
		gooseY = rand() % 10 + 11;
	} 
	while(playerX == gooseX && playerY == gooseY);
}

//function to print out instructions or current health
void instructions(int keyEntered, Actor & player)
{
	if(keyEntered == TK_I)
	{
		out.writeLine("* power-up lets you jump 5 tiles");
		out.writeLine("# is goose poop and will make you lose 1/3 lives");
		out.writeLine("! will give you back a life");
		out.writeLine("If you are in a corner and click space the goose will "
					   "get teleported away");
	}	
	
	if (keyEntered == TK_H)
		out.writeLine(player.get_health_message());
}
		
//END: gooseEscapeGamePlay.cpp
