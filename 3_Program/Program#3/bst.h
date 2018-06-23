/*
 * Kobe Davis
 * Prof. Fant
 * CS202
 * 5 May 2017
 */

//header file for the binary search tree data structure

#include "programs.h"

/*
 * The class bst will be the binary search tree data structure that organizes the program data. It is also
 * a base or parent class to the l_node class in the list.h file. This is so that whenever a node is created
 * in the linear linked list data structure, a binary search tree is created along with it. This works perfectly
 * because in this assignment, a linked list node would not exist without data inside of it anyways. The only
 * way that data exists inside of it is through the use of a binary search tree.
 * The b_node class is just a node, much like the linked list node, but it has a left and right child, as well
 * as a program base pointer. The purpose of doing this is so we can upcast different types of data to this
 * pointer and have variety in one data structure.
 */

class b_node
{
    public:
        b_node();//default constructor
        b_node(const program & to_copy);//copy constructor
        ~b_node();//destructor
        b_node *& to_left();//left child getter
        b_node *& to_right();//right child getter
        program & to_program();//program base pointer getter
        int compare_name(const program & to_compare);//wrapper function for program class compare name function
        int compare_name(const char * to_compare);//wrapper function program class compare name function
        void display();//wrapper function for program class display function
    private:
        program * base;//base class pointer to hold either website, social_app, or game_app
        b_node * left;//pointer to left child
        b_node * right;//pointer to right child
};

class bst
{
    public:
        bst();//default constructor
        bst(const bst & to_copy);//copy constructor
        ~bst();//destructor
        bst & operator = (const bst & to_assign);//assignment operator
        int insert(const program & to_insert);//wrapper for recursive insert function
        int remove(const char * to_match);//wrapper for recursive remove function
        int retrieve(program *& copy_to, char * match);//wrapper for recursive retrieve function
        int display_all();//wrapper for recursive display all function
        bool compare_bst(b_node * root, b_node * to_compare) const;//compares two bsts, determines if equal
    protected:
        b_node * root;
        int insert(b_node *& root, const program & to_insert);//recursively inserts data
        int remove(b_node *& root, const char * to_match);//recursively removes specified data
        b_node * inorder_successor(b_node *& root);//finds and returns IOS to remove function
        int retrieve(b_node *& root, program *& copy_to, char * match);//recursively retrieves specified data
        int display_all(b_node * root);//recursively displays all data in bst
        int remove_all(b_node *& root);//recursively deallocates all data in tree
        int full_copy(b_node *& root, b_node * source);//recursively copies one bst into another
};
