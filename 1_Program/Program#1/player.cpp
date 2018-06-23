//Kobe Davis
//Prof. Fant
//CS202
//April 24, 2017
//.cpp file for player.h header file
//This file will hold functions for the Player class, Location class, and Name class.

#include "player.h"

using namespace std;

//location class's default constructor
location::location():v_index(-1), v_name(NULL)
{
}

//location class's constructor with args
location::location(int index_to_add, char * name_to_add):v_index(index_to_add)
{
    v_name = new char[strlen(name_to_add) + 1];//deep copy of name: v_name
    strcpy(v_name, name_to_add);
}

//location destructor
location::~location()
{
    if(v_name)
    {
        delete [] v_name;//deleting v_name if it exists
    }
}

//getter for location data member v_index
int location::get_location()
{
    return v_index;
}

//getter for location data member v_name
char * location::vname()
{
    return v_name;
}

//setter for locations data members, returns nothing and receives an integer and a character pointer
void location::set_location(int index_to_add, char * name_to_add)
{
    v_index = index_to_add;
    v_name = new char[strlen(name_to_add) + 1];//deep copy of name v_name
    strcpy(v_name, name_to_add);
}

//setter for location class which resembles a copy constructor
//this function takes a location object by reference
void location::set_location(location & to_add)
{
    v_index = to_add.v_index;
    if(v_name)
    {
        delete [] v_name;//if a name already exists for a particular location, delete it
        v_name = NULL;
    }
    v_name = new char[strlen(to_add.v_name) + 1];//deep copy of name v_name
    strcpy(v_name, to_add.v_name);
}

//default constructor for player class
player::player():name_info(NULL), friends(NULL), team(0)
{
}

//constructor with args for player class, receives all of player class's data members
player::player(name * new_name, player_list & new_friends, int player_team, int start_index, char * start_name):
    location(start_index, start_name)//initialization list kickstarting player's base class location's constructor with args
{
    team = player_team;
    name_info = new name(*new_name);//deep copy using name class's copy constructor
    friends = &new_friends;//setting player's data member "friends" which is a player_list pointer to point to the address of a new list
}

//player class's copy constructor
player::player(const player & to_copy):location(to_copy.v_index, to_copy.v_name)//initialization list kickstarting base class location's constructor with args
{
    team = to_copy.team;//setting team
    name_info = new name(*to_copy.name_info);//deep copy using name class's copy constructor
    friends = to_copy.friends;//setting player's data member "friends" which is a player_list pointer to point to the address of a new list.
}

//destructor for player class
player::~player()
{
    if(name_info)
    {
        delete name_info;
    }
}

//display function for player class that acts as a wrapper function for the display function of the name pointer that player contains.
void player::display_name()
{
    name_info->display();//calling name pointers display function to display the specified players info pertaining to their identity
}

//compare_name function returns an int if the name handed in matches the receiving player's name
int player::compare_name(char * name_to_compare)
{
    if(strcmp(name_to_compare, name_info->get_name()) == 0)//comparing the two character arrays
    {
        return 1;//they match
    }
    else
    {
        return 0;//they don't match
    }
}

//this display function inside the player class display all information about the player, not just anything specific
void player::display_info()
{
    name_info->display();//calling name's display function
    cout << "Player's vertex index is: " << v_index << endl;//displaying players vertex index in the vertex array in the graph class
    cout << "Players vertex name is: " << v_name << endl;//displaying the name of the vertex that the player is on
}

//display function in player class that takes the players team identifier (integer) and displays only people that are on the same team.
void player::view_friends()
{
    friends->display_side(team);//calling function display_side from player_list class
}

//default constructor for name class
name::name():player_name(NULL)
{
}

//copy constructor for name class
name::name(const name & to_copy)
{
    player_name = new char[strlen(to_copy.player_name) + 1];
    strcpy(player_name, to_copy.player_name);
}

//constructor with args for the name class
name::name(char * to_add):player_name(NULL)
{
    player_name = new char[strlen(to_add) + 1];
    strcpy(player_name, to_add);
}

//destructor for the name class
name::~name()
{
    if(player_name)
    {
        delete [] player_name;
    }
}

//getter for the char * data type player_name inside name class
char * name::get_name()
{
    return player_name;
}

//display function for the name class, will not display name if the pointer is null
void name::display()
{
    if(player_name)//pointer exists
    {
        cout << "Name: " << player_name << endl;
    }
    else//pointer is null
    {
        cout << "Name not set." << endl;
    }
}
