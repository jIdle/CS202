/* Kobe Davis
 * Prof. Fant
 * CS202
 * April 25, 2017
 *
 * Function definitions from the CLL header file will be held in this .cpp.
 */


#include "CLL.h"

using namespace std;

//default constructor for the node class
node::node():next(NULL), base_ptr(NULL)
{
}

//destructor for the node class
node::~node()
{
    next = NULL;
    if(base_ptr)
    {
        delete base_ptr;
        base_ptr = NULL;
    }
}

//getter for the next node in node class
node *& node::to_next()
{
    return next;
}

//getter for the comm pointer data member in node class
comm *& node::to_base()
{
    return base_ptr;
}

//display function wrapper in node class which calls comm pointer display function
int node::display()
{
    return base_ptr->display();
}

//wrapper function in node class which calls remove function from the comm pointer data member
int node::clear()
{
    return base_ptr->remove();
}

//clist class default constructor
clist::clist():rear(NULL)
{
}

//clist class destructor
clist::~clist()
{
    if(!remove_all())//calling remove all function to delete cll
    {
        cout << "Attempt to delete CLL was unsuccesful." << endl;
    }
}

//wrapper function for recursive insert function in clist class
int clist::insert()
{
    int success = 0;
    if(!rear)//if the cll hasn't even been created yet
    {
        success = insert(rear);
        rear->to_next() = rear;
    }
    else//if it has been created already
    {
        node * head = rear->to_next();
        rear->to_next() = NULL;
        success = insert(head);//recursive call
        rear->to_next() = head;
    }
    return success;
}

//recursive insert function in clist class
int clist::insert(node *& head)
{
    if(!head)//reach end of the cll
    {
        head = new node;
        if(!assign_app(head->to_base()))//calling assign_app function to allow user to choose which method
        {                               //method of communication they would like to create
            delete head; head = NULL;
            cout << "assign function returned a zero." << endl;
            return 0;
        }
        rear = head;//updating rear
        return 1;
    }
    return insert(head->to_next());//recursive call
}

//wrapper function for the recursive next_comm function in clist class
int clist::next_comm(comm *& base_ptr)
{
    if(!rear)//if cll doesn't actually exist yet
    {
        cout << "Create a form of communication first!" << endl;
        return 0;
    }
    if(!base_ptr)//if the argument handed in is null
    {
        base_ptr = rear->to_next()->to_base();//give it a value (head of list)
        return 1;
    }
    return next_comm(rear->to_next(), base_ptr);//find next communication in line after the handed comm
}

//recursive next_comm function in clist class, this function will use the comm pointer argument
//and compare it to every comm pointer in the cll until it finds a match, when it does it will set the
//comm pointer handed in by argument to the next comm pointer so that the user will then be able
//to use the next communication method in line.
int clist::next_comm(node *& head, comm *& base_ptr)
{
    if(base_ptr == head->to_base())//match is found between arg and current comm
    {
        base_ptr = head->to_next()->to_base();//set arg comm pointer to next in line
        return 1;
    }
    return next_comm(head->to_next(), base_ptr);//recursive call
}

//remove function in clist class that remove the "head" node and linkes the cll up using the "previous" node.
int clist::remove(node *& head, node *& previous)
{
    if(!head)//if the node handed by arg is null
    {
        return 0;
    }
    if(head == rear)//if the node to remove happens to be the rear also
    {
        previous->to_next() = head->to_next();
        rear = previous;//update rear first
        delete head; head = NULL;
        return 1;
    }
    previous->to_next() = head->to_next();//link up list before removing
    delete head; head = NULL;
    return 1;
}

//assign app function in clist class is what does the upcasting
int clist::assign_app(comm *& base_ptr)
{
    int user_option = 0;
    cout << "What communication method would you like to create?" << endl;
    cout << " 1. Facebook\n 2. Texting\n 3. Email\n 4. Mail\n(Enter the corresponding number): ";
    cin >> user_option; cin.ignore(100, '\n');

    do//do whille loop to ensure user actually makes a valid choice
    {
        if(user_option == 1)
            base_ptr = new facebook;//upcast facebook class to abstract base class pointer
        else if(user_option == 2)
            base_ptr = new texting;//upcast texting class to abstract base class pointer
        else if(user_option == 3)
            base_ptr = new email;//upcast email class to abstract base class pointer
        else if(user_option == 4)
            base_ptr = new mail;//upcast mail class to abstract base class pointer
        else
            cout << "Please choose one of the specified options." << endl;
    }while(user_option < 1 || user_option > 4);
    return 1;
}

//wrapper function for the recursive display function in clist class
int clist::display_all()
{
    if(!rear)//if the cll doesn't exist
    {
        return 0;
    }
    node * head = rear->to_next();//break cll so it becomes a lll
    rear->to_next() = NULL;
    int success = display_all(head);//kicks off recursive process
    rear->to_next() = head;
    return success;
}

//recursive display all function for the clist class. displays all data in the cll by calling the nodes
//wrapper display function at each recursion
int clist::display_all(node * head)
{
    if(!head)//if we hit the end of the list
    {
        return 0;
    }
    if(!head->display())//call display function of node
    {
        //cout << "node display function return 0 in clist display all." << endl;
    }
    return display_all(head->to_next()) + 1;//recursive call
}

//wrapper function for the recursive remove all function in clist class.
int clist::remove_all()
{
    if(!rear)//if cll doesn't exist yet
    {
        return 0;
    }
    node * head = rear->to_next();//break cll so it becomes a lll
    rear->to_next() = NULL;
    return remove_all(head);//kicks off recursive process
}

//recursive remove all function in clist class, recurses to the end of the list, on returned will remove
//the nodes.
int clist::remove_all(node *& head)
{
    if(!head)//we hit the end of the list
    {
        return 0;
    }
    int remove_count = remove_all(head->to_next()) + 1;//recursive call
    delete head;//delete the node
    head = NULL;
    return remove_count;
}
