/*
 * Kobe Davis
 * Prof. Fant
 * CS202
 * 5 May 2017
 */

//header file for linear linked list data structure

#include "bst.h"
using namespace std;

/*
 * The list class creates a linear linked list, it organizes binary search trees by the contained data's
 * frequency of usage. The more often used applications will be closer to the front of the list, whereas the
 * less often used data will be closer to the end. This is supposed to represent a "locality of reference".
 * Alongside this, the list class contains all of the specified overloaded operators so that it can be used
 * conveniently with operators instead of calling unfamiliar functions.
 * The l_node class is just a node, although, l_node is a derived class from the bst class. This allows every
 * node to already contain a binary search tree, this also allows the l_node class to allocate data to the
 * bst through the copy constructor or constructor with args.
 */

class l_node: public bst
{
    public:
        l_node();//default constructor
        l_node(const program & to_add);//constructor with args
        l_node(const l_node & to_copy);//copy constructor
        ~l_node();//destructor
        l_node *& to_next();//getter for next node in linked list
        b_node *& to_root();//getter for root b_node in parent class
        double & get_frequency();//getter for frequency data member
    private:
        l_node * next;//next node in LLL
        double frequency;//used to help relevant functions determine where to insert and retrieve
};

class list
{
    public:
        list();//default constructor
        list(const list & to_copy);//copy constructor
        ~list();//destructor
        friend ostream& operator << (ostream &, const list & to_display); //display
        friend istream& operator >> (istream &, list &); //user insert
        friend ifstream& operator >> (ifstream & in, list &); //load function
        list & operator = (const list &); //assignment operator
        list operator + (const program &) const; //insert by pre-existing object
        list & operator += (const program & to_add); //same as above, just better
        list operator - (const char * match) const; //remove from list using pre-existing object
        list & operator -= (const char * match); //same as above, just better
        bool operator == (const list &) const; //is it the same?
        bool operator != (const list &) const; //is it not the same?
        bool operator < (const list &) const; //is it less than?
        bool operator > (const list &) const; //is it greater than?
        bool operator <= (const list &) const; //inclusive less than
        bool operator >= (const list &) const; //inclusive greater than
        int retrieve(program *& copy_to, char * match);//wrapper for recursive retrieve function
        void remove_all();//wrapper for recursive remove all function
    private:
        l_node * head;//head of linear linked list
        //all the functions below are recursive
        int insert(l_node *& head, const program & to_add);//inserts program into list
        int remove(l_node *& head, const char * match); //remove specified program from list
        int retrieve(l_node *& head, program *& copy_to, char * match);//retrieve specified program from list
        int display_all(l_node * head) const;//display all programs in data structure
        int full_copy(l_node *& head, l_node * source);//take another list and fully copy it
        bool compare_list(l_node * head, l_node * to_compare) const;//take another list and determine if equal
        int inequalityXI(l_node * head, l_node * source) const;//take another list and determine relative size
        int remove_all(l_node *& head);//remove all data in a list
};
