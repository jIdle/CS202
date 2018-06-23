//Kobe Davis
//Prof. Fant
//CS202
//April 24, 2017
//This file will hold the functions for the node class

#include "player.h"

using namespace std;

//default constructor for node class
node::node():next(NULL)
{
}

//destructor for node class
node::~node()
{
    next = NULL;
}

//getter/setter for node's next pointer.
//although it is technically a getter, the point of it return the pointer by reference can also be to set it
node *& node::to_next()
{
    return next; 
}

//getter for the array of player pointers inside the node. 
//this function's purpose is to give access to the data structure through the node for the player_list class.
player **& node::to_array()
{
    return player_array;
}
