/*
 * Kobe Davis
 * Prof. Fant
 * CS202
 * 5 May 2017
 */

//implementation file for the binary search tree data structure

#include "bst.h"
using namespace std;

//b_node default destructor
b_node::b_node():base(NULL), left(NULL), right(NULL)
{
}

//b_node class copy constructor
b_node::b_node(const program & to_copy):left(NULL), right(NULL)
{
    //In this copy constructor we aren't sure what to_copy to base.
    //To solve this we do downcasting with dynamic_cast
    const website * ws = dynamic_cast<const website*>(&to_copy);//downcasting program reference handed in
    if(ws)                                                      //setting it to website pointer ws
        base = new website(*ws);
    const social_app * sa = dynamic_cast<const social_app*>(&to_copy);
    if(sa)
        base = new social_app(*sa);
    const game_app * ga = dynamic_cast<const game_app*>(&to_copy);
    if(ga)
        base = new game_app(*ga);
}

//b_node class destructor
b_node::~b_node()
{
    if(base)
    {
        delete base;
        base = NULL;
    }
    left = NULL;
    right = NULL;
}

//b_node class getter of left b_node child
b_node *& b_node::to_left()
{
    return left;
}

//b_node class getter of right b_node child
b_node *& b_node::to_right()
{
    return right;
}

//b_node class program pointer getter
program & b_node::to_program()
{
    return *base;
}

//first variation of compare name function, it takes a program reference and hands it into its own program
//data member's compare name function
int b_node::compare_name(const program & to_compare)
{
    return base->compare_name(to_compare);
}

//second variation of compare name function, takes a char * and calls its own program data member's compare
//name function
int b_node::compare_name(const char * to_compare)
{
    return base->compare_name(to_compare);
}

//b_node display function is a wrapper function for program poitner data member
void b_node::display()
{
    base->display();//data member display function
}

//bst class default constructor
bst::bst():root(NULL)
{
}

//bst class copy constructor
bst::bst(const bst & to_copy)
{
    if(!full_copy(root, to_copy.root)) //full copy function copies the handed in binary search tree
        cout << "bst copy function in copy constructor failed." << endl;
}

//destructor for bst class
bst::~bst()
{
    remove_all(root);//remove all function removes entire search tree
}

//assignment operator for bst class
bst & bst::operator = (const bst & to_copy)
{
    if(this == &to_copy)//is this pointing to itself?
    {
        return *this;
    }
    if(this)//make sure this is reset and cleared before assigning stuff to it
    {
        if(!remove_all(root))//call remove all function to clear bst
            cout << "Nothing to clear in new bst." << endl;
    }
    if(!full_copy(root, to_copy.root))//after bst is cleared then copy to_copy into this
        cout << "bst copy function failed." << endl;
    return *this;
}

//wrapper insert function for bst class
int bst::insert(const program & to_insert)
{
    return insert(root, to_insert);//calling recursive insert function
}

//recursive insert function for bst class
//this function takes a program reference and inserts it in the appropriate place in the bst.
//The bst is organized alphabetically
int bst::insert(b_node *& root, const program & to_insert)
{
    if(!root)//base case went to far
    {
        root = new b_node(to_insert);//dynamic allocation of b_node using constructor with args for b_node
        return 1;
    }
    int direction = root->compare_name(to_insert);//using b_node's compare name wrapper function to determine
    if(direction == -1)                           //which direction the data should be inserted
    {
        return insert(root->to_left(), to_insert);
    }
    if(!direction)
    {
        cout << "Name already taken!" << endl;
    }
    return insert(root->to_right(), to_insert);
}

//bst class remove wrapper function
int bst::remove(const char * to_match)
{
    if(!root)
    {
        return 0;
    }
    return remove(root, to_match);//kick off recursive function
}

//recursive remove function for bst class, it takes a character pointer and traverse the bst looking for a match
int bst::remove(b_node *& root, const char * to_match)
{
    if(!root)//base case, went too far
    {
        return 0;
    }  
    int direction = root->compare_name(to_match);//determine which direction should be traversed
    if(direction == -1)
    {
        return remove(root->to_left(), to_match);
    }
    else if(direction == 1) 
    {
        return remove(root->to_right(), to_match);
    }
    else//match is found and removal process kicks off
    {
        if(!root->to_left() && !root->to_right())//leaf
        {
            delete root;
            root = NULL;
        }
        else if(!root->to_left() && root->to_right())//one child
        {
            b_node * temp = root->to_right();
            delete root;
            root = temp;
        }
        else if(root->to_left() && !root->to_right())//one child
        {
            b_node * temp = root->to_left();
            delete root;
            root = temp;
        }
        else if(root->to_left() && root->to_right())
        {
            b_node * temp = inorder_successor(root->to_right());//IOS is needed because two children
            temp->to_left() = root->to_left();
            temp->to_right() = root->to_right();
            delete root;
            root = temp;
        }
        return 1;
    }
    return 0;
}

//IOS function to aide in the removal process in bst class
b_node * bst::inorder_successor(b_node *& root)
{
    if(!root->to_left())//found IOS
    {
        b_node * temp = root; //succesfully replace IOS
        root = root->to_right();
        return temp;
    }
    return inorder_successor(root->to_left());//recursive process to find IOS
}

//wrapper retrieve function for bst class
int bst::retrieve(program *& copy_to, char * to_match)
{
    if(!root)
    {
        return 0;
    }
    return retrieve(root, copy_to, to_match);//kicking off recursive process / calling recursive removal
}

//recursive retrieve function for bst class
//takes a b_node to traverse tree, a program pointer to copy what it finds into it, and a char * to know what to search for.
int bst::retrieve(b_node *& root, program *& copy_to, char * to_match)
{
    if(!root)//base case, traverse too far
    {
        return 0;
    }
    int direction = root->compare_name(to_match);//in which direction should we traverse? Use argument to_match to determine this.
    if(direction == -1)
    {
        return retrieve(root->to_left(), copy_to, to_match);
    }
    if(direction == 1)
    {
        return retrieve(root->to_right(), copy_to, to_match);
    }
    //below this, we are assuming we have found a match for retrieval, next we need to downcast the data we found in the tree to determine what kind of data our argument copy_to should be allocated as.
    website * ws = dynamic_cast<website*>(&root->to_program());
    if(ws)
        copy_to = new website(*ws);
    social_app * sa = dynamic_cast<social_app*>(&root->to_program());
    if(sa)
        copy_to = new social_app(*sa);
    game_app * ga = dynamic_cast<game_app*>(&root->to_program());
    if(ga)
        copy_to = new game_app(*ga);
    return 1;
}

//display all wrapper function for bst class
int bst::display_all()
{
    if(!root)
    {
        return 0;
    }
    return display_all(root);//calls recursive display all function
}

//recursive display all function goes left to right (smallest to largest) displaying values to user.
int bst::display_all(b_node * root)
{
    if(!root)
    {
        return 0;
    }
    int success = 1;
    success += display_all(root->to_left());//recurse left
    root->display();//display value
    success += display_all(root->to_right());//recurse right
    return success;
}

//recursive remove all function, it de-allocates on return, bst class
int bst::remove_all(b_node *& root)
{
    if(!root)//base case, traverse too far
    {
        return 0;
    }
    int success = remove_all(root->to_left()) + remove_all(root->to_right()) + 1;//recursive call, traverse as far as possible
    delete root;//when on the way back from recursing
    root = NULL;
    return success;
}

//copy function for bst class, it takes a b_node from another different bst and copies the entire thing into the current one
int bst::full_copy(b_node *& root, b_node * source)
{
    if(!source)//tree that is being copied traversed too far
    {
        root = NULL;
        return 0;
    }
    int count = 0;
    root = new b_node(source->to_program());//allocate memory using the current tree node's constructor with args
    count = full_copy(root->to_left(), source->to_left()) + full_copy(root->to_right(), source->to_right()) + 1;//recursive call
    return count;
}

//compare_bst is part of bst class, it is similar to full copy in that it takes a node from another bst, but it goes through both trees comparing the values.
//This is done to check whether or not the trees are equal.
bool bst::compare_bst(b_node * root, b_node * to_compare) const
{
    if(!root && !to_compare)//if both trees end in the same spot
        return true;
    if(!root && to_compare)//if trees are different lengths
        return false;
    if(root && !to_compare)//if trees are different length
        return false;
    if(root->compare_name(to_compare->to_program()) != 0)//comparing the values held inside the b_nodes
        return false;
    if(!compare_bst(root->to_left(), to_compare->to_left()))//recursive call to the left child
        return false;
    if(!compare_bst(root->to_right(), to_compare->to_right()))//recursive call to the right child
        return false;
    return true;
}
