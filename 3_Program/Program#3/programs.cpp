/*
 * Kobe Davis
 * Prof. Fant
 * CS202
 * 5 May 2017
 */

//implementation file for the hierarchical classes

#include "programs.h"
using namespace std;

//default constructor for program class
program::program():duration(0), frequency(0), name(NULL), date(NULL), actions(NULL)
{
}

//constructor with args for program class
program::program(double dur, double freq, char * nam, char * dat, char * act):duration(dur), frequency(freq)
{
    name = new char[strlen(nam) + 1]; strcpy(name, nam);        //dynamically allocating data
    date = new char[strlen(dat) + 1]; strcpy(date, dat);
    actions = new char[strlen(act) + 1]; strcpy(actions, act);
}

//copy constructor for program class
program::program(const program & to_copy)
{
    duration = to_copy.duration;
    frequency = to_copy.frequency;
    name = new char[strlen(to_copy.name) + 1]; strcpy(name, to_copy.name);
    date = new char[strlen(to_copy.date) + 1]; strcpy(date, to_copy.date);
    actions = new char[strlen(to_copy.actions) + 1]; strcpy(actions, to_copy.actions);
}

//assignment operator for program class
program & program::operator = (const program & to_assign)
{
    if(this == &to_assign)//check if pointing to self
    {
        return *this;
    }
    if(this)//make sure it's empty
    {
        clear();
    }
    duration = to_assign.duration;      //assign variables
    frequency = to_assign.frequency;
    name = new char[strlen(to_assign.name) + 1]; strcpy(name, to_assign.name);
    date = new char[strlen(to_assign.date) + 1]; strcpy(date, to_assign.date);
    actions = new char[strlen(to_assign.actions) + 1]; strcpy(actions, to_assign.actions);
    return *this;
}

//destructor for program class
program::~program()
{
    if(name)
    {
        delete [] name;
        name = NULL;
    }
    if(date)
    {
        delete [] date;
        date = NULL;
    }
    if(actions)
    {
        delete [] actions;
        actions = NULL;
    }
}

//pure virtual display function, implementation specific to program
void program::display()
{
    //display variables
    cout << "-------------------------------------------------------------" << endl;
    cout << "Used for " << duration << " minutes." << endl;
    cout << "Used " << frequency << " time since arrival." << endl;
    cout << "Name: " << name << endl;
    cout << "Used on " << date << endl;
    cout << "Record of user's actions: " << actions << endl;
}

//program class function to clear out any pre-existing data
void program::clear()
{
    duration = 0;
    frequency = 0;
    if(name)
    {
        delete [] name; name = NULL;
    }
    if(date)
    {
        delete [] date; date = NULL;
    }
    if(actions)
    {
        delete [] actions; actions = NULL;
    }
}

//first variation of compare name function program class, it takes another program reference and uses
//strcmp function to compare the names
int program::compare_name(const program & to_compare)
{
    int direction = strcmp(to_compare.name, name);//using string compare function
    if(direction < 0)
        return -1;
    if(direction > 0)
        return 1;
    return 0;
}

//second variation of compare name function in program class, instead of taking a program reference it uses
//just a char * for comparison. 
int program::compare_name(const char * to_compare)
{
    int direction = strcmp(to_compare, name);//using string compare function
    if(direction < 0)
        return -1;
    if(direction > 0)
        return 1;
    return 0;
}

//frequency comparison function in program class, takes a double representing another frequency
//data member from elsewhere and compares magnitudes.
int program::compare_frequency(double to_compare) const
{
    if(to_compare < frequency)
        return -1;
    if(to_compare > frequency)
        return 1;
    return 0;
}

//frequency data member getter function
double program::get_frequency() const
{
    return frequency;
}

//incr is a member function from program class, all it does it increments the frequency data member
void program::incr()
{
    ++frequency;
}

//default constructor for website class
website::website():address(NULL), sub_address(NULL), browser(NULL)
{
}

//constructor with args for the website class
website::website(char* add, char* sub, char* bro, double dur, double freq, char* nam, char* dat, char* act):
    program(dur, freq, nam, dat, act) //calling base class constructor with args
{
    address = new char[strlen(add) + 1];        //dynamic allocation
    strcpy(address, add);
    sub_address = new char[strlen(sub) + 1];
    strcpy(sub_address, sub);
    browser = new char[strlen(bro) + 1];
    strcpy(browser, bro);
}

//copy constructor for website class
website::website(const website & to_copy):program(to_copy) //calling copy constructor for base class
{
    address = new char[strlen(to_copy.address) + 1];        //dynamic allocation
    strcpy(address, to_copy.address);
    sub_address = new char[strlen(to_copy.sub_address) + 1];
    strcpy(sub_address, to_copy.sub_address);
    browser = new char[strlen(to_copy.browser) + 1];
    strcpy(browser, to_copy.browser);
}

//assignment operator for website class, receives a program reference as an argument and returns one too.
program & website::operator = (const program & to_assign)
{
    if(this == &to_assign)  //checks if pointing to self
    {
        return *this;
    }
    if(this)    //makes sure is empty before changing
    {
        clear();
    }
    program::operator=(to_assign);//calling base class assignment operator
    const website & temp = dynamic_cast<const website&>(to_assign);//downcasting program reference handed in
    address = new char[strlen(temp.address) + 1];   //below this is dynamic allocation
    strcpy(address, temp.address);
    sub_address = new char[strlen(temp.sub_address) + 1];
    strcpy(sub_address, temp.sub_address);
    browser = new char[strlen(temp.browser) + 1];
    strcpy(browser, temp.browser);
    return *this;
}

//destructor for website class
website::~website()
{
    if(address)
    {
        delete [] address;
        address = NULL;
    }
    if(sub_address)
    {
        delete [] sub_address;
        sub_address = NULL;
    }
    if(browser)
    {
        delete [] browser;
        browser = NULL;
    }
}

//website class display function
void website::display()
{
    program::display();//calling base class display function with scope operator
    cout << "Website visited: " << address << endl;
    cout << "Website's sub-address visited: " << sub_address << endl;
    cout << "Browser used: " << browser << endl;
    cout << "-------------------------------------------------------------" << endl << endl;
}

//website class clear function gets rid of and resets pre-existing data in website object
void website::clear()
{
    program::clear();   //calling base class clear so no data it missed
    if(address)
    {
        delete [] address; address = NULL;
    }
    if(sub_address)
    {
        delete [] sub_address; sub_address = NULL;
    }
    if(browser)
    {
        delete [] browser; browser = NULL;
    }
}

//default constructor for social app class
social_app::social_app():sent_to(NULL), sent_from(NULL)
{
}

//constructor with args for social app class
social_app::social_app(char * to, char * from, double dur, double freq, char* nam, char* dat, char* act):
    program(dur, freq, nam, dat, act) //calling base class constructor with args
{
    sent_to = new char[strlen(to) + 1];     //dynamic allocation
    strcpy(sent_to, to);
    sent_from = new char[strlen(from) + 1];
    strcpy(sent_from, from);
}

//copy constructor for social app class
social_app::social_app(const social_app & to_copy):program(to_copy) //calling base class copy constructor
{
    sent_to = new char[strlen(to_copy.sent_to) + 1];    //dynamic allocation 
    strcpy(sent_to, to_copy.sent_to);
    sent_from = new char[strlen(to_copy.sent_from) + 1];
    strcpy(sent_from, to_copy.sent_from);
}

//assignment operator for social app class
program & social_app::operator = (const program & to_assign)
{
    if(this == &to_assign) //check if pointing to self
    {
        return *this;
    }
    if(this)//make sure this is cleared of pre-existing data
    {
        clear();
    }
    program::operator=(to_assign); //call base class assignment operator
    const social_app & temp = dynamic_cast<const social_app&>(to_assign);//downcast program reference handed in
    sent_to = new char[strlen(temp.sent_to) + 1];   //dynamic allocation below
    strcpy(sent_to, temp.sent_to);
    sent_from = new char[strlen(temp.sent_from) + 1];
    strcpy(sent_from, temp.sent_from);
    return *this;
}

//destructor for social app class
social_app::~social_app()
{
    if(sent_to)
    {
        delete [] sent_to;
        sent_to = NULL;
    }
    if(sent_from)
    {
        delete [] sent_from;
        sent_from = NULL;
    }
}

//display function for social app class
void social_app::display()
{
    program::display(); //calling base class display function
    cout << "Message sent from: " << sent_from << endl;
    cout << "Message sent to: " << sent_to << endl;
    cout << "-------------------------------------------------------------" << endl << endl;
}

//social app class clear function, this just reset or deletes pre-existing data 
void social_app::clear()
{
    program::clear();//calling base class clear function
    if(sent_to)
    {
        delete [] sent_to; sent_to = NULL;
    }
    if(sent_from)
    {
        delete [] sent_from; sent_from = NULL;
    }
}

//game_app class default constructor
game_app::game_app():achievement(0), levels_gained(0), current_level(0)
{
}

//game_app class constructor with args
game_app::game_app(int ach, int gain, int cur, double dur, double freq, char* nam, char* dat, char* act):
    program(dur, freq, nam, dat, act)//calling base class cosntructor with args
{
    achievement = ach;      //setting variables
    levels_gained = gain;
    current_level = cur;
}

//copy constructor for game_app class
game_app::game_app(const game_app & to_copy):program(to_copy) //calling copy constructor for base class
{
    achievement = to_copy.achievement;  //setting variables
    levels_gained = to_copy.levels_gained;
    current_level = to_copy.current_level;
}

//assignment operator for game_app class
program & game_app::operator = (const program & to_assign)
{
    if(this == &to_assign)//check if pointing to self
    {
        return *this;
    }
    if(this)//make sure to clear this before changing it
    {
        clear();
    }
    program::operator=(to_assign); //calling base class assignment operator
    const game_app & temp = dynamic_cast<const game_app&>(to_assign);//downcast program reference handed in
    achievement = temp.achievement;     //set variables
    levels_gained = temp.levels_gained;
    current_level = temp.current_level;
    return *this;
}

//game_app class destructor
game_app::~game_app()
{
}

//game_app class display function
void game_app::display()
{
    program::display();//calling base class display function
    cout << achievement << " achievements unlocked." << endl;
    cout << levels_gained << " levels gained during this session." << endl;
    cout << "Current level is: " << current_level << endl;
    cout << "-------------------------------------------------------------" << endl << endl;
}

//game_app class clear function
void game_app::clear()
{
    program::clear();//calling base class clear function
}
