#include <cmath>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActor.hpp"

/*
    Going further:  You can modify this class to contain more characteristics
    of the "actor" (anything that moves in your game) or to change how some of
    the functions work.
*/

Actor:: Actor()
{
    actorChar = int('A');
    location_x = MIN_SCREEN_X;
    location_y = MIN_SCREEN_Y;
    health = 100;
    put_actor();
}

Actor:: Actor(char initPlayerChar, int x0, int y0, int health0)
{
    change_char(initPlayerChar);
    location_x = MIN_SCREEN_X;
    location_y = MIN_SCREEN_Y;
    health = 0;
    update_health(health0);
    update_location(x0,y0);
}
    
int Actor:: get_x() const
{
    return location_x;
}
    
int Actor:: get_y() const
{
    return location_y;
}
    
string Actor:: get_location_string() const
{
    char buffer[80]={0};
    itoa(location_x,buffer,10);
    string formatted_location = "(" + string(buffer) + ",";
    itoa(location_y,buffer,10);
    formatted_location += string(buffer) + ")";
    return formatted_location;
}
    
void Actor:: change_char(char new_actor_char)
{
    actorChar = min(int('~'),max(int(new_actor_char),int(' ')));
}
    
int Actor:: get_health_int() const
{
    return health;
}
    
string Actor:: get_health_message() const
{
    char buffer[80]={0};
    itoa(health,buffer,10);
    return string(1,char(actorChar)) + " health: " + string(buffer);
}

void Actor:: update_health(int change_in_health)
{
    health = max(health + change_in_health, 0);  // force health to be positive
}

bool Actor:: can_move(int delta_x, int delta_y) const
{
    int new_x = location_x + delta_x;
    int new_y = location_y + delta_y;

    return new_x >= MIN_BOARD_X && new_x <= MAX_BOARD_X
        && new_y >= MIN_BOARD_Y && new_y <= MAX_BOARD_Y;
}

void Actor:: update_location(int delta_x, int delta_y)
{
    if (can_move(delta_x, delta_y))
    {
        terminal_clear_area(location_x, location_y, 1, 1);
        location_x += delta_x;
        location_y += delta_y;
        put_actor();
    }
}
    
void Actor:: put_actor() const
{
    terminal_put(location_x, location_y, actorChar);
    terminal_refresh();
}

