/* Kobe Davis
 * Prof. Fant
 * CS202
 * April 25, 2017
 *
 * Header file for the binary search tree data structure.
 */

#include "contact_folder.h"

//bst_node is just a node for a bst besides some functions that all the tree class to access the contact_folder
//array inside the node. each node will hold an array of contact folders on the off chance that a person
//has the same name as another person, this way both people can be stored and found on the same node,
//just within the array.
class bst_node
{
    public:
        //default constructor
        bst_node();
        //destructor
        ~bst_node();
        //setter for the contact_folder array data member below
        int set_person(contact_folder & to_add);
        //compare is a wrapper function for the comparison function found in the contact_folder data members
        //the int return type and contact_folder argument are simply to satisfy the contact_folder compare func.
        int compare(contact_folder & to_compare);
        //match function takes a contact_folder pointer by reference as an argument and searches for a matching
        //contact_folder inside the contact_folder array datamember. If a match is found it sets the
        //contact_folder arg to the matching one but along with more data. returns an integer to convey success
        //and failure.
        int match(contact_folder *& copy_to);
        //remove function takes a contact_folder as an argument and tries to find on inside the contact_folder
        //array data member, if a match is found it will delete the discovered contact_folder. an integer is
        //returned to convey success and failure.
        int remove(contact_folder * to_remove);
        //display function is just a wrapper function for the contact_folders held inside the array datamember
        //below, the function also has the added that it loops through the array. the integer argument is used
        //to pass into the cotnact_folder display function.
        int display(int comm);
        //how many function is used to determine how many elements are filled (not NULL) inside the array of
        //contact_folders. an integer is returned to convey success and failure.
        int how_many();
        //getter for the left child node data member
        bst_node *& to_left();
        //getter for the right child node data member
        bst_node *& to_right();
        //setter for the left child node data member
        void connect_left(bst_node * connection);
        //setter for the right child node data member
        void connect_right(bst_node * connection);
    private:
        bst_node * left;//left child node in bst
        bst_node * right;//right child node in bst
        contact_folder ** person;//array of contact_folder which hold users with similar names
};

//tree class is used to create a binary search tree data structure, it has functionalities to, insert, remove,
//retrieve, and display data. It also has the added display all and remove all functions. this data structure
//will hold nodes that are holding arrays of user information in the form of the class contact_folder.
class tree
{
    public:
        //default constructor
        tree();
        //destructor
        ~tree();
        //extra info function takes a contact_folder by reference and prompts the user to set extra data
        //(e.g. facebook, texting, etc. stuff)
        void extra_info(contact_folder & person);
        //insert function takes a contact_folder as an argument and places it inside the bst. an integer is
        //returned to convey success and failure. this is the wrapper to the recursive
        int insert(contact_folder & person);
        //remove function takes a contact_folder as an argument and searches the bst for a match to which it will
        //then remove and connect up the bst. if there is more than one person inside the array where the match
        //is found then only that individual will be removed and not the entire node. integer is returned to
        //convey success and failure. this is the wrapper to the recursive
        int remove(contact_folder * person);
        //retrieve function takes a contact_folder as an argument and searches the bst for a match to which it
        //will then do a deep copy from the matching contact_folder to the handed in contact_folder. an integer
        //is returned to convey success and failure. this is the wrapper to the recursive
        int retrieve(contact_folder *& person);
        //wrapper function for the nodes display function. arg is just used to satisfy nodes arg requirement.
        int display(int comm);
    private:
        //recursive insert function which is called from the wrapper
        int insert(bst_node *& root, contact_folder & person);
        //inorder successor function is used inside the remove function to make sure the bst connects up.
        bst_node * inorder_successor(bst_node *& root);
        //recursive remove function which is called from the wrapper
        int remove(bst_node *& root, contact_folder * person);
        //recursive retrieve function which is called from the wrapper
        int retrieve(bst_node *& root, contact_folder *& person);
        //recursive display function which is called from the wrapper
        void display(bst_node * root, int comm);
        //recurrsive remove all function called from the destructor
        int remove_all(bst_node *& root);
        //root of the entire bst.
        bst_node * root;
};
