//Kobe Davis
//Prof. Fant
//CS202
//April 24, 2017
//This file will hold the functions for the player_list class.

#include "player.h"

using namespace std;

//default constructor for player_list class
player_list::player_list():marker(0), top_index(0), array_size(5), node_marker(NULL), head(NULL)
{
    head = new node;//initializing head
    head->to_array() = new player*[array_size];//initializing player list
}

//copy constructor for player_list class
player_list::player_list(const player_list & new_list):marker(0), top_index(0), node_marker(NULL)
{
    array_size = new_list.array_size;
    head = new_list.head; 
}

//destructor for play_list class
player_list::~player_list()
{
    node_marker = NULL;
    node * current = NULL;

    while(head)
    {
        current = head->to_next();
        for(int i = 0; i < array_size; ++i)
        {
            if(head->to_array()[i])
            {
                delete head->to_array()[i];
                head->to_array()[i] = NULL;
            }
        }
        delete [] head->to_array();
        delete head;
        head = current;
    }
}

//add player function for player list class
//this function is very similar to the push function for a stack adt
//adds a new player each time it is used to the top of the array, when the array is filled an new node is created with an emtpy array
void player_list::add_player(player & to_add)
{
    if(top_index == array_size)//if the array is full and new node is created
    {
        top_index = 0;//resets the counter for number of people in the array
        node * temp = new node;//create new node
        temp->to_array() = new player*[array_size];//allocates memory for the array of player pointers
        temp->to_array()[top_index] = new player(to_add);//allocates memory for the person being added, uses the player copy constructor
        temp->to_next() = head;//connects the new node to the pre-existing list
        head = temp;//sets head to the front of the list again
        ++top_index;//increments the player counter
    }
    else//array isn't full so just allocate memory for the new player in the free array slot and increment the player counter
    {
        head->to_array()[top_index] = new player(to_add);
        ++top_index;
    }
}

//wrapper function for the recursive retrieve player function. receives a char * as an arg and returns a player by reference.
player & player_list::retrieve_player(char * name_to_search)
{
    return retrieve_player(head, name_to_search);//calls recursive function
}

//recursive retrieve function which attempts to match a given name to one in the list of players
//if the name match is found then the player is return by reference.
player & player_list::retrieve_player(node * head, char * name_to_search)
{
    if(!head)//if end of list is reached
    {
        throw invalid_argument("Specified player not found.");//no player can be returned, exception thrown
    }

    for(int i = 0; i < array_size; ++i)//iteration through the array
    {
        if(head->to_array()[i])//check if array slot actually exists
        {
            if(head->to_array()[i]->compare_name(name_to_search))//check if the name matches the player being viewed
            {
                return *head->to_array()[i];//all requirements were met and player is returned
            }
        }
    }
    return retrieve_player(head->to_next(), name_to_search);//recursive call which initiates the same process but for the next node
}

//turn_marker function keeps track of whos turn it is for the maze game and returns the player whos turn it is by reference
player *& player_list::turn_marker()
{
    if(!node_marker)//if we've traverse to the end of the list of players
    {
        node_marker = head;//reset to the beginning and turns start over
        marker = 0;//marker is an integer that keeps track of which index should be called in each array inside the LLL of of Arrays of Players.
        return turn_marker();//recursive call to make use of turn marker function now that we have reset the turns
    }
    else if(marker == array_size)//if the last player to have a turn was indexed at the end of an array
    {
        node_marker = node_marker->to_next();//move onto the next node 
        marker = 0;//start at the beginning of the array for the next node
        return turn_marker();//recursive call to make use of turn marker function now that we have reset the turns
    }
    else if(!node_marker->to_array()[marker])//this case takes care of the occurence of an empty array slot, if an array is not filled, that means the player pointers will be null
    {
        node_marker = head;//reset to the beginning because an empty array slot implies we have reached the end of the list of players
        marker = 0;//start at the beginning of the array for the head node
        return turn_marker();//recursive call to make use of turn marker function now that we have reset the turns.
    }
    else//lastly, if all cases have been taken care, we are likely just somewhere in the middle of an array, in which case we just return the player that marker specifies.
    {
        return node_marker->to_array()[marker]; 
    }
}

//increment function is used to increment the marker data member, that's it.
//the reason for this was that it was difficult to place inside the turn_marker function because of its recursiveness
//often times marker would be incremented in the wrong order or multiple times which caused problems.
void player_list::increment()
{
    ++marker;
}

//wrapper function for the recursive display function in player_lsit class
void player_list::display()
{
    cout << "\nActive players:\n" << endl;
    display(head);//call to recursive function
    cout << "\n\n" << endl;
}

//recursive display function. this function recurses through the LLL of Arrays of Players displaying all player info
void player_list::display(node * head)
{
    if(!head)//if we hit end of the list
    {
        return;
    }
    for(int i = 0; i < array_size; ++i)//iterate through array
    {
        if(head->to_array()[i])//if the array slot exists
        {
            head->to_array()[i]->display_info();//call the player display function
            cout << endl;
        }
    }
    display(head->to_next());//recursive call to traverse to next node
}

//wrapper function for the recursive display_side functing in player_list class
//receives a team indentifier to that the appropriate players will be displayed
void player_list::display_side(int team)
{
    display_side(head, team);//recursive call
}

//recursive display_side function will use the team id (integer) received to only display players on the same team.
void player_list::display_side(node * head, int team)
{
    if(!head)//if we hit the end of the list
    {
        return;
    }
    for(int i = 0; i < array_size; ++i)//iterates through array of players
    {
        if(head->to_array()[i])//if the array slot exists
        {
            if((i%2) == team)//categorizes team members
            {
                head->to_array()[i]->display_info();//calls player display function
                cout << endl;
            }
        }
    }
    display_side(head->to_next(), team);//recursive call to travers to the next node
}
