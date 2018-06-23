/* Kobe Davis
 * Prof. Fant
 * CS202
 * April 25, 2017
 *
 * Header file for the circular linked linked data structure.
 */

#include "abstract_hierarchy.h"

//The node class will be used inside of a circular linked list. Each node will hold a pointer to
//an abstract base class which will be holding some class object that has been upcasted to the base class.
class node
{
    public:
        //default constructor
        node();
        //destructor
        ~node();
        //getter for next node
        node *& to_next();
        //getter for comm pointer base_ptr
        comm *& to_base();
        //wrapper function for comm class display function
        int display();
        //wrapper function for comm class remove function
        int clear();
    private:
        node * next; //pointer to next node in CLL
        comm * base_ptr;//pointer to comm class which is the abstract base class of different communications
};

//Circular Linked List data structure is created/works by this class. The class has functions to insert, remove, display, retrieve, display all, and remove all. It will be used to hold different methods of communication
//in a list so that the user can switch through these different comms easily.
class clist
{
    public:
        //default constructor
        clist();
        //destructor
        ~clist();
        //wrapper for recursive insert function
        int insert();
        //next_comm takes a comm pointer by reference and recurses through the CLL until it finds the
        //communication method that comes after the argument and changes the argument to point to the next one.
        //In this way the user can now look at different comms one right after the other.
        int next_comm(comm *& base_ptr);
        //This function is sort of a wrapper function, it recurses through the CLL calling each node's display
        //function
        int display_all();
        //wrapper function for the recursive remove all function
        int remove_all();
    private:
        node * rear;//rear node which points to the front of the CLL
        //recursive insert function takes a comm pointer argument and places it inside the CLL. returns an int to
        //convey success and fialure.
        int insert(node *& head);
        //recursive function which is called by the wrapper above.
        int next_comm(node *& head, comm *& base_ptr);
        //assign_app function allows the user to choose which kind of communication method they want to create.
        //this function takes a comm pointer by reference as an argument which is modified inside the function.
        //an in is returned to convey success and failure
        int assign_app(comm *& base_ptr);
        //recursive remove function called by the wrapper function above. this function takes a node and the node
        //previous to it and removes the node while linking up the list with the previous one. returns an int
        //to convey success and failure.
        int remove(node *& head, node *& previous);
        //recursive display all function called by the wrapper above. function takes a node pointer as an arg
        //to recurse through the CLL and call the node's display functions
        int display_all(node * head);
        //recursive remove all function which is called in the destructor. int is returned to convey success
        //and failure.
        int remove_all(node *& head);
};
