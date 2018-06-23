/* Kobe Davis
 * Prof. Fant
 * CS202
 * April 25, 2017
 *
 * Function definitions from the BST header file will be held in this .cpp.
 */

#include "BST.h"

using namespace std;

//default constructor for bst_node class
bst_node::bst_node():left(NULL), right(NULL), person(NULL)
{
    person = new contact_folder*[5];//setting array of cotnact_folder inside node
    for(int i = 0; i < 5; ++i)
    {
        person[i] = NULL;
    }
}

//destructor for bst_node class
bst_node::~bst_node()
{
    left = NULL;
    right = NULL;
    if(person)
    {
        for(int i = 0; i < 5; ++i)
        {
            if(person[i])
            {
                delete person[i];
                person[i] = NULL;
            }
        }
        delete [] person;
        person = NULL;
    }
}

//setter for contact_folder data member inside of bst_node class
int bst_node::set_person(contact_folder & to_add)
{
    for(int i = 0; i < 5; ++i)
    {
        if(!person[i])//search for first null space
        {
           person[i] = new contact_folder(to_add);
           return 1;
        }
    }
    return 0;
}

//wrapper function to the contact_folder compare function from the contact_folder array data member
//held inside the bst_node class
int bst_node::compare(contact_folder & to_compare)
{
    return person[0]->compare(to_compare);
}

//match function from the bst_node class, determines if the contact_folder handed in has a matching ID
//data member
int bst_node::match(contact_folder *& copy_to)
{
    for(int i = 0; i < 5; ++i)//loop through all contact_folders held inside the array in bst_node class
    {
        if(person[i])//null check
        {
            if(person[i]->compare(*copy_to) == 2)//checking if ID matches
            {
                copy_to = new contact_folder(*person[i]);//deep copy
                return 1;
            }
        }
    }
    return 0;
}

//this function will search for a match to the to_remove arg and delete it if found inside the array of 
//contact_folders in bst_node class
int bst_node::remove(contact_folder * to_remove)
{
    for(int i = 0; i < 5; ++i)//loop through entire array
    {
        if(person[i] && person[i]->compare(*to_remove) == 2)//null check and ID matching check
        {
            delete person[i];
            person[i] = NULL;
            return 1;
        }
    }
    return 0;
}

//wrapper function for the contacT_folder display function 
int bst_node::display(int comm)
{
    for(int i = 0; i < 5; ++i)//loop through entire array of contact_folder
    {
        if(person[i])//null check
        {
            if(!person[i]->display(comm))//calling contact_folder display function
            {
                cout << "contact_folder display function return 0" << endl; 
                return 0;
            }
        }
    }
    return 1;
}

//bst_class function, checks how many contact_folders are currently held inside of the array data member
int bst_node::how_many()
{
    int count = 0;
    for(int i = 0; i < 5; ++i)//loop through entire array
    {
        if(person[i])//null check
        {
            ++count;
        }
    }
    return count;
}

//bst_node class getter for the left child node
bst_node *& bst_node::to_left()
{
    return left;
}

//bst_node class getter for the right child node
bst_node *& bst_node::to_right()
{
    return right;
}

//bst_class setter for the left child node
void bst_node::connect_left(bst_node * connection)
{
    left = connection;
}

//bst_class setter for the right child node
void bst_node::connect_right(bst_node * connection)
{
    right = connection;
}

//default constructor for the tree class
tree::tree():root(NULL)
{
}

//destructor for the tree class
tree::~tree()
{
    if(!remove_all(root))//remove_all function is called which deletes entire tree
    {
        cout << "Attempt to delete tree was unsuccesful." << endl;
    }
}

//tree class function extra info will prompt the user to set the "extra" data held inside the specified contact
//folder before inserting it into the binary search tree. setting them is not a requirement though
void tree::extra_info(contact_folder & person)
{ 
    int user_option = 0;//temporary variable to store user input
    char username[100];//temporary variable to store user input 
    cout << "Would you like to add a facebook for this person?\n 1. Y\n 2. N\n(Enter corresponding number):";
    cin >> user_option; cin.ignore(100, '\n'); cout << endl;
    if(user_option == 1)//ask user for facebook info
    {
        cout << "Enter facebook username: "; cin.get(username, 100, '\n'); cin.ignore(100, '\n'); cout << endl;
        if(!person.add_facebook(username))
            cout << "Could not add facebook user info." << endl;
    }
    cout << "Would you like to add an email for this person?\n 1. Y\n 2. N\n(Enter corresponding number):";
    cin >> user_option; cin.ignore(100, '\n'); cout << endl;
    if(user_option == 1)//ask user for email info
    {
        cout << "Enter email address: "; cin.get(username, 100, '\n'); cin.ignore(100, '\n'); cout << endl;
        if(!person.add_email(username))
            cout << "Could not add email user info." << endl;
    }
    cout << "Would you like to add a cell for this person?\n 1. Y\n 2. N\n(Enter corresponding number):";
    cin >> user_option; cin.ignore(100, '\n'); cout << endl;
    if(user_option == 1)//ask user for cell phone info
    {
        cout << "Enter cell number: "; cin >> user_option; cin.ignore(100, '\n'); cout << endl;
        if(!person.add_cell(user_option))
            cout << "Could not add cell user info." << endl;
    }
    cout << "Would you like to add a mailing address for this person?\n 1. Y\n 2. N\n(Enter corresponding number):";
    cin >> user_option; cin.ignore(100, '\n'); cout << endl;
    if(user_option == 1)//ask user for postage info
    {
        cout << "Enter postal address: "; cin.get(username, 100, '\n'); cin.ignore(100, '\n'); cout << endl;
        if(!person.add_postal(username))
            cout << "Could not add mailing user info." << endl;
    }
}

//wrapper function for recursive insert function held inside the tree class
int tree::insert(contact_folder & person)
{
    extra_info(person);//askign user to set "extra info"
    return insert(root, person);//kicks off recursive function
}

//recursive insert function held inside tree class. takes a contact_folder by reference as an arg, finds where
//it should be placed. if there is no node where it should be placed, then one is created along with the 
//contained contact_folder which undergoes a deep copy. If there is a node where it should be placed, then the
//contact has the same name as somebody else and will be placed inside the node's array of contact_folders.
int tree::insert(bst_node *& root, contact_folder & person)
{
    if(!root)//if where the cotnact should be placed has no pre-existing node
    {
        root = new bst_node;//deep copy stuff
        root->set_person(person);
        root->connect_left(NULL);
        root->connect_right(NULL);
        return 1;
    }
    int direction = root->compare(person);//recursive call
    if(!direction)//if match is found and node already exists
    {
        root->set_person(person);
        return 1;
    }
    else if(direction == -1)//if handed in contact is less than the current one
    {
        return insert(root->to_left(), person);//recursive call going left
    }
    else if(direction)//if handed in contact is greater than the current one
    {
        return insert(root->to_right(), person);//recursive call going right
    }
    cout << "Insert function failed to reach any case." << endl;
    return 0;
}

//wrapper function for the recursive display function
int tree::display(int comm)
{
    if(!root)//if tree hasn't been created yet
    {
        return 0;
    }
    display(root, comm);//kicks off recursive process
    return 1;
}

//recursive display function inside tree class. goes through the tree calling the node's display functions
void tree::display(bst_node * root, int comm)
{
    if(!root)//if we recurse too far
    {
        return;
    }
    display(root->to_left(), comm);//recursive call going left
    if(!root->display(comm))
    {
        cout << "node display function returned a 0" << endl;
    }
    display(root->to_right(), comm);//recursive call going right
    return;
}

//wrapper function for the recursive removal function
int tree::remove(contact_folder * person)
{
    if(!root)//check if tree exists in first place
    {
        return 0;
    }
    return remove(root, person);
}

//inorder successor is used to make sure that removing a node in a bst doesn't royally mess up everything
bst_node * tree::inorder_successor(bst_node *& root)
{
    if(!root->to_left())//found the inorder successor
    {
        //move the IOS to the actuall site of removal
        bst_node * temp = root;
        root = root->to_right();
        return temp;//return IOS
    }
    return inorder_successor(root->to_left());//recursive call to find the inorder successor
}

//recursive removal function held inside tree class, takes a contact_folder as an argument as searches
//for a match to it inside the bst, once found the matching data will be deleted
int tree::remove(bst_node *& root, contact_folder * person)
{
    if(!root)//if data is not found
    {
        return 0;
    }
    int direction = root->compare(*person);//determining which direction to go using node comparison function
    if(direction == -1)//go left child node
    {
        return remove(root->to_left(), person);
    }
    if(direction == 1)//go right child node
    {
        return remove(root->to_right(), person);
    }
    if(!direction || direction == 2)//match is found
    {
        if(root->how_many() == 1)//determine how to remove the node
        {
            if(!root->to_left() && !root->to_right())
            {
                delete root;
                root = NULL;
            }
            else if(!root->to_left() && root->to_right())
            {
                bst_node * temp = root->to_right();
                delete root;
                root = temp;
            }
            else if(root->to_left() && !root->to_right())
            {
                bst_node * temp = root->to_left();
                delete root;
                root = temp;
            }
            else if(root->to_left() && root->to_right())//remove by finding IOS
            {
                bst_node * temp = inorder_successor(root->to_right());
                temp->to_left() = root->to_left();
                temp->to_right() = root->to_right();
                delete root;
                root = temp;
            }
        }
        else//dont remove node, just data inside the array
        {
            if(!root->remove(person))
            {
                cout << "root's remove function returned a 0" << endl;
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

//wrapper function for the recursive retrieve function
int tree::retrieve(contact_folder *& person)
{
    if(!root)//no tree exists
    {
        return 0;
    }
    return retrieve(root, person);//kicks of recursive retrieve process
}

//recursive retrieve fucntion held inside the tree class, takes a contact_folder as an argument and searches
//for a match within the bst. when a match is found, the argument handed in will have the matching node's data
//copied into it so that the client can use that data
int tree::retrieve(bst_node *& root, contact_folder *& person)
{
    if(!root)//specified contact is not found
    {
        return 0;
    }
    int direction = root->compare(*person);//determine which direction to do in bst using node compare function
    if(!direction || direction == 2)
    {
        if(!root->match(person))//if the data isn't found inside the node
        {
            delete person;
            person = NULL;
            return 0;
        }
        return 1;
    }
    else if(direction == -1)//go to left child node
    {
        return retrieve(root->to_left(), person);
    }
    else if(direction)//go to right child node
    {
        return retrieve(root->to_right(), person);
    }
    return 0;
}

//recursive removal all function held inside the tree class, this function is called from the destructor when
//the bst is ending/being removed.
int tree::remove_all(bst_node *& root)
{
    if(!root)//recursed too far
    {
        return 0;
    }
    int success = remove_all(root->to_left()) + remove_all(root->to_right());//recursive call

    delete root;//deleting nodes
    root = NULL;
    ++success;//counting how many nodes are deleted.
    return success;
}
