//Kobe Davis
//Prof. Fant
//CS202
//April 24, 2017
//This file will hold the functions for the game class in game.h.

#include "game.h"

using namespace std;

//default constructor for game class
game::game():name_to_add(NULL), temp_player(NULL)
{
}

//destructor for game class
game::~game()
{
}

//this function uses the player_list class to add players to the game before the game starts
void game::setup()
{
    char temp_name[100];//holds temporary name for creating player
    int user_input = 0;//for user to decide whether or not to add another player
    int count = 1;//count players
    int team = 1;//which team the player will be on
    char temp_start[5] = "A";//name of vertex

    while(user_input != 2)//each loop adds a player
    {
        cout << "Enter Player Name: "; 
        cin.get(temp_name, 100, '\n'); cin.ignore(100, '\n'); cout << endl; 
        name_to_add = new name(temp_name);//create a name
        temp_player = new player(name_to_add, group, team, 0, temp_start);//create player
        group.add_player(*temp_player);//add that player to the list

        delete name_to_add; name_to_add = NULL;
        delete temp_player; temp_player = NULL;
        group.display();//display active players
        ++count;//count number of players
 
        cout << "Add Player " << count << "?" << endl;
        cout << "1. Y" << endl; cout << "2. N" << endl;
        cout << "Enter the corresponding number: "; 
        cin >> user_input; cin.ignore(100, '\n'); cout << endl;//add another player?
        if(team == 1)
        {
            team = 0;
        }
        else
        {
            team = 1;
        }
    }
}

//play function manages players turns and their actions using the graph and player_list classes
void game::play()
{
    int winners = 0;//used if someone wins
    int user_input = 0;//allows the player to choose actions
    int temp_choice = 0;//allows the user to choose where to move in the maze
    int valid = 0;//checks the movements the player choose sis valid
    int winning_checkpoint = maze.get_size() - 1;//the winning checkpoint
 
    temp_player = group.turn_marker();//temp player which points to the address of an actual player
    temp_player->display_info();//display the player's information
    do//do while loop that lets players take turns
    {
        cout << "\n\n" << endl;
        cout << "1. View Paths\n2. Choose Path\n3. View Friends\n4. Choose Rewards\n5. Quit Game" << endl;//options to choose
        cin >> user_input; cin.ignore(100, '\n'); cout << endl << endl;
        if(user_input == 1)//if the player chooses to view paths
        { 
            maze.display_adjacent(temp_player->get_location());//display paths adjacent to the checkpoint the player is on
        }
        else if(user_input == 2)//if the player chooses to choose paths
        {
            while(valid == 0)//if choice prior was invalid keep asking
            {
                cout << "Which checkpoint would you like to move to?" << endl;
                cin >> temp_choice; cin.ignore(100, '\n'); cout << endl;//choose path
                valid = maze.check_valid(temp_player->get_location(), temp_choice);//check if choice is valid
                if(valid)//if the path is valid
                {
                    if(temp_choice != winning_checkpoint)//check if the checkpoint traveled to is the winning one
                    {
                        temp_player->set_location(temp_choice, maze.to_vertex(temp_choice).vname());//set new location
                        group.increment();//increment which player should be chosen
                        temp_player = group.turn_marker();//switch to the next player
                        cout << "\n\n" << endl;
                        temp_player->display_info();//display new player information
                    }
                    else
                    {
                        winners = 1;//if the player hits the winning checkpoint
                    }
                }
            }
            valid = 0;
        }
        else if(user_input == 3)//if player chooses view friends
        {
            temp_player->view_friends();//call the function to display the specified player's friends
        }
        else if(user_input == 4)//if the player chooses to choose rewards
        {
            //temp_player = group.turn_marker();
            //cout << "\n\n" << endl;
            //temp_player->display_info();
        }
        else if(user_input == 5)//if the user chooses to quit the game
        {
            cout << "The game will now exit." << endl;
        }
        else//user's option was not listed above
        {
            cout << "Invalid entry. Please choose from the options listed above." << endl;
        }
    }while(winners != 2 && user_input != 5 && winners == 0);

    if(winners == 1)//winning message for player
    {
        temp_player->display_name();
        cout << "Has won the game!" << endl;
    }
}
