//Kobe Davis
//Prof. Fant
//CS202
//April 24, 2017
//This file be the "client" or "user". main.cpp file

#include "game.h"

using namespace std;

int main()
{
    game maze_game;//initializing game object
    maze_game.setup();//calling setup function to add players and create graph
    maze_game.play();//calling play function to begin the game, maze traversal, and player turns

    return 0;
}









