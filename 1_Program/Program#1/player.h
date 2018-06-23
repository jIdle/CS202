//Kobe Davis
//Prof. Fant
//CS202
//April 24, 2017
//This file is a header file. It will hold the class definition for Player, Location, Name, Node, and Player_List.

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

//The location class will be the base class for the player class and the vertex class.
//In this way both player and vertices will have locations that can be communicated
//and understood.
class location
{
    public:
        //default constructor
        location();
        //constructor with args to define location object on creation
        location(int index_to_add, char * name_to_add);
        //location destructor
        ~location();
        //getter for v_index data member
        int get_location();
        //getter for vname data member
        char * vname();
        //setter for when handed sufficient and appropriate data members
        void set_location(int index_to_add, char * name_to_add);
        //setter for when a location is needed to be copied
        void set_location(location & to_add);
        //display function for location's data members
        void display();

    protected:
        //v_index data member keeps track of the array index a vertex is in.
        //because player derives from location, player knows the array index of the
        //vertex they stand on.
        int v_index;
        //v_name data member is an arbitrary name to help the player remember which
        //checkpoint they stand on.
        char * v_name;
};

//name class currently only contains name, but was made with the intention of
//having all information/data related to representing an individual player inside
//it. the name class is contained within the player class.
class name
{
    public:
        //default constructor
        name();
        //constructor with args
        name(char * to_add);
        //copy constructer
        name(const name & to_copy);
        //destructor
        ~name();
        //setter for player_name data member
        void set_name(char * to_add);
        //getter for player_name data member
        char * get_name();
        //function that display player_name data member
        void display();

    private:
        //the name of the player added to the game
        char * player_name;
};

//player class will be what ties to together all the attributes of a person playing the game.
//this class ties together the friends list, name, location, team, etc.
//player has a containing relationship with the name class and player_list class.
//player has an inherited relationship with the location class.
class player: public location
{
    public:
        //default constructor
        player();
        //constructor wit hargs for data members
        player(name * new_name, class player_list & new_friends, int player_team, int start_index, char * start_name);
        //copy constructor
        player(const player & to_copy);
        //destructor
        ~player();
        //displays all pertinent info concerning the player
        void display_info();
        //displays only the name of the player
        void display_name();
        //displays a players list of friends using the friends data member which is a player_list class type
        void view_friends();
        //compare_name receives a char * and returns either a 0 or 1 depending on if the name matches the name of the receiving player
        int compare_name(char * name_to_compare);
    private:
        //name_info data member is a name class, it contains all data pertinent to the user's identity
        name * name_info;
        //friends data member is a player_list class, it contains the players that are on the players team.
        class player_list * friends;
        //team data member is just an identifier for the players team.
        int team;
};

//node class will be used in the Linear Linked List of Arrays data structure containing player data types.
//in this program, this is how players are stored and organized for later access.
//each node contains a pointer to a player pointer, in this way, an array of player pointers can be created for adding players to the game.
//the nodes are just a piece of the data structure, the entire thing will be controlled by the player_list class.
class node
{
    public:
        //default constructor
        node();
        //destructor
        ~node();
        //getter for next node
        node *& to_next();
        //getter for players stored in the array player_array which is a data member below
        player **& to_array();
        //setter for next node if more players need to be added to the list
        void set_next(node * add_next); 

    private:
        //player_array data member will be used to store players/objects/pointers/data.
        player ** player_array;
        //pointer to the next node in line
        node * next;
};

//player_list class will be used to control the functionalities of the Linear Linked List of Arrays.
//It contains functions that display data, retrieve data, add data, etc. Normal data structures stuff.
//this class has an important role in the program because it manages all of the players that will be in
//the game, and it is also how anything else gains access to players if necessary. 
class player_list
{
    public:
        //default constructor
        player_list();
        //copy constructor
        player_list(const player_list & new_list);
        //destructor
        ~player_list();
        //this functions takes a player object by reference and adds it to the LLL of Arrays
        //This function works very similarly to the push function in a stack. If there isn't a list, this function will create one. It will also manage creating new nodes.
        void add_player(player & to_add);
        //This function returns a pointer by reference to a player class. The purpose of this function is to mediate the actual game turn-taking process.
        //This function can be called and the player handed back to whatever temporary player object will be the next player to take their turn.
        player *& turn_marker();
        //wrapper function for the recursive retrieve function below.
        player & retrieve_player(char * name_to_search);
        //recursive retrieve function, returns a player by reference and receives a node pointer and a character pointer to search for inside the list of players it manages.
        player & retrieve_player(node * head, char * name_to_search);
        //wrapper function for the recursive display function below
        void display();
        //recursive display function, traverses LLL and iterates through each array to display all data on players stored.
        void display(node * head);
        //wrapper function for team specific recursive display below
        void display_side(int team);
        //recursive team display function, takes a team identifier as an argument which helps the function decide which team to display.
        void display_side(node * head, int team);
        //this function was made solely for the purpose aiding another functions logic
        //all it does is increment an integer value 
        void increment();
    private:
        //marker is used to keep track of whos turn it should be.
        //whenever a player takes a turn, it increments to move onto the next player
        int marker;
        //similar to the stack adt, top_index is used to keep track of the most recently added player to the list of players in the LLL of Arrays
        int top_index;
        //array size is a variable which remains static once the program has begun. it keeps track of the size of the arrays created inside each node for holding player pointers.
        int array_size;
        //used alongside marker, node_marker keeps track of which node the currently playing player is being stored on.
        //this is useful because often times there may be more than 5 players and switching nodes becomes necessary for all players to have turns.
        node * node_marker;
        //node pointer to head of the LLL of Arrays
        node * head;
};
