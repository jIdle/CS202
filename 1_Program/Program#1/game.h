//Kobe Davis
//Prof. Fant
//CS202
//April 24, 2017
//This file will be the header file for the game class.

#include "graph.h"

//game class will be the overarching class which mediates communication between the graph and player_list class.
//it will also direct and operate the flow and organization of the actual game.
class game
{
    public:
        //default constructor
        game();
        //destructor
        ~game();
        //the setup function will use both the graph and player_list data members below to begin creating the maze and adding players to play the maze game.
        void setup();
        //the play function will organize and manage the players' turn taking and actions during each turn. this function also uses the below data members
        //to make the game fully operational.
        void play();

    private:
        //graph datatype maze will be what represents the maze the players will play on. maze contains a vertex array and an adjacency list alongside it
        //construct this maze. the graph is randomly generated, and by that I mean the connection between the vertices are randomly placed.
        graph maze;
        //this player_list datatype will be what holds all of the players added to game, and also is what actually adds the players to the game.
        player_list group;
        //temporary name pointer used in the creation of players in the beginning
        name * name_to_add;
        //temporary player pointer used in the creation of players in the beginning.
        player * temp_player;
};
