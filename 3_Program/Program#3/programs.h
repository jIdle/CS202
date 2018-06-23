/*
 * Kobe Davis
 * Prof. Fant
 * CS202
 * 5 May 2017
 */

//header file for hierarchical classes 

#include <iostream>
#include <cstring>
#include <fstream>

/*
 * The classes program, website, social_app, and game_app are part of a hierarchy. Program is the abstract base
 * class and website, social_app, and game_app are the derived classes. The purpose of these derived classes is
 * to store history related data on some program usage. In case the names weren't self-explanatory, the website
 * class is specialized to hold data on websites specifically, the social_app class is specialized to hold data
 * on application that are primarily used for socializing, and the game_app class is specialized to hold data on
 * applicaitons that are primarily used for playing video games. These will be stored in a binary search tree
 * data structure after being upcasted so any type can be stored.
 */

//program will hold general information about the application that was used
class program
{
    public:
        program();//constructor
        program(double dur, double freq, char * nam, char * dat, char * act);//constructor with args
        program(const program & to_copy);//copy constructor
        virtual program & operator = (const program & to_assign) = 0;//assignment operator
        virtual ~program(); //destructor
        virtual void display() = 0;//pure virtual display function
        virtual void clear() = 0;//pure virtual clear function
        int compare_name(const program & to_compare);//compare name data member with another program
        int compare_name(const char * to_compare);//compare name data member with a cstring
        int compare_frequency(double to_compare) const;//compare frequency data member with another double
        double get_frequency() const;//getter for frequency data member
        void incr();//increments the frequency data member
    protected:
        double duration;//how long was app used
        double frequency;//how often is it used
        char * name;//what is the app's name
        char * date;//when was it used last
        char * actions;//what actions were taken on last use
};

//derived from the program class, website will hold three extra data members that pertain to website usage
class website: public program
{
    public:
        website();//default constructor
        website(char * add, char * sub, char * bro, double dur, double freq, char * nam, char * dat, char * act);//constructor with args
        website(const website & to_copy);//copy constructor
        program & operator = (const program & to_assign);//assignment operator
        ~website();//destructor
        void display();//function displays data members
        void clear();//function clears data members
    private:
        char * address;//website address
        char * sub_address;//any child addresses of main address
        char * browser;//browser used when website was accessed
};

//derived from program class, social_app will hold two extra data members that pertain to social application usage
class social_app: public program
{
    public:
        social_app();//default constructor
        social_app(char * to, char * from, double dur, double freq, char * nam, char * dat, char * act);//constructor with args
        social_app(const social_app & to_copy);//copy constructor
        program & operator = (const program & to_assign);//assignment operator
        ~social_app();//destructor
        void display();//displays data members
        void clear();//clears data members
    private:
        char * sent_to;//who was a message sent to?
        char * sent_from;//who was the message sent from?
};

//derived from program class, game_app will hold three extra data members that pertain to game application usage
class game_app: public program
{
    public:
        game_app();//default constructor
        game_app(int ach, int gain, int cur, double dur, double freq, char * nam, char * dat, char * act);//constructor with args
        game_app(const game_app & to_copy);//copy constructor
        program & operator = (const program & to_assign);//assignment operator
        ~game_app();//destructor
        void display();//displays data members
        void clear();//clears data members
    private:
        int achievement;//how many achievements does user have in this game
        int levels_gained;//how many levels were gained in this session
        int current_level;//what is user's current level
};
