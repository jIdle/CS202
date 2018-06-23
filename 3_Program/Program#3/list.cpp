/*
 * Kobe Davis
 * Prof. Fant
 * CS202
 * 5 May 2017
 */

//implementation file for linear linked list data structure

#include "list.h"
using namespace std;

//default constructor for l_node class
l_node::l_node():next(NULL), frequency(0)
{
}

//constructor with args for l_node class
l_node::l_node(const program & to_add):next(NULL)
{
    frequency = to_add.get_frequency();
    insert(to_add);//calling insert function from parent class
}

//copy constructor for l_node class
l_node::l_node(const l_node & to_copy):bst(to_copy), next(NULL)//calling part copy constructor
{
    frequency = to_copy.frequency;
}

//destructor for l_node class
l_node::~l_node()
{
    next = NULL;
}

//getter for next node in l_node class
l_node *& l_node::to_next()
{
    return next;
}

//getter for root node held in parent class
b_node *& l_node::to_root()
{
    return root;
}

//getter for freequency data member
double & l_node::get_frequency()
{
    return frequency;
}

//default constructor for list class
list::list():head(NULL)
{
}

//copy constructor for list class
list::list(const list & to_copy)
{
    cout << full_copy(head, to_copy.head) << " nodes copied." << endl;//calling copy function
}

//destructor for list class
list::~list()
{
    if(!remove_all(head))//calling remove all function which de-allocates data in list
        //cout << "Failed to delete list." << endl;
    head = NULL;
}

//overloaded bitshift operator, it is used to accomodate for commnads such as cout << list which will function
//as a display all function. This function is a friend function of the list class and it receives an ostream
//object to accomplish cout stuff and it also receives a list class from which it will display data
ostream & operator << (ostream & out, const list & to_display)
{
    //ostream object is used to display to console and also call display all function from list
    out << "You have displayed " << to_display.display_all(to_display.head) << " search trees." << endl;
    return out;//maintaining stream
}

//recursive display all function for list class
int list::display_all(l_node * head) const
{
    if(!head)//base case, traverse too far
        return 0;
    if(!head->display_all())//calling the display all function for bst inside each node
        cout << "BST display all failed inside LLL display all." << endl;
    return display_all(head->to_next()) + 1; //recursive call
}

//overloaded bitshift operator, it is used to accomodate for commands such as cin >> list which will allow the
//user to input data to the list from the command prompt. This is accomplished receiving an istream object and
//list object by argument
istream & operator >> (istream & in, list & input_to)
{
    char name[100];        char date[100];          //temp variables to allow user to input data
    char actions[1000];    double frequency = 0;    //they correspond to the data members found within the
    char address[100];     char browser[100];       //program classes
    char sub_address[100]; char sent_from[100];
    char sent_to[100];     int levels_gained = 0;   
    int achievement = 0;   double duration = 0;   
    int current_level = 0; program * base = NULL;//this one is used for the retrieve function
    char match[100];       int option = 0; 

    cout << "\nEnter the data you would like to use, if the item is not found then you will create it: " << endl;
    in.get(match, 100, '\n'); in.ignore(100, '\n');//user search for pre-existing data
    if(input_to.retrieve(base, match)){//call retrieve function
        input_to -= match;//if found, will remove it from current position to place in higher frequency spot 
        base->incr();//if found, increment frequency of usage
        input_to += *base;//place back into list in correct spot according to updated frequency
        cout << "Data was located pre-existing in list, it's frequency of use will increment." << endl;
        return in;//maintain stream
    }
    cout << "\nSpecified data was not found, please input data: " << endl;
    cout << "What do you want to use?\n 1. Website\n 2. Social App (Facebook, Snapchat, etc.)\n 3. Gaming App (Pokemon GO, Emulator, etc.)\n 0. Quit\n(Enter corresponding number): ";
    do{//data was not found pre-existing in list, user will now input data
        in >> option; in.ignore(100,'\n'); cout << endl;  
        cout << "Enter program name: "; in.get(name,100,'\n'); in.ignore(100,'\n'); cout << endl;
        cout << "Enter date used: "; in.get(date,100,'\n'); in.ignore(100,'\n'); cout << endl;
        cout << "Enter description of actions: "; in.get(actions,1000,'\n'); in.ignore(100,'\n'); cout << endl;
        cout << "Enter minutes used: "; in >> duration; in.ignore(100,'\n'); cout << endl;
        cout << "Enter frequency of use (How many times in a day): "; in >> frequency; in.ignore(100,'\n'); cout << endl;

        if(option == 1){//user chooses to use website
            cout << "Enter website address: "; in.get(address,100,'\n'); in.ignore(100,'\n'); cout << endl;
            cout << "Enter sub-address visited: "; in.get(sub_address,100,'\n'); in.ignore(100,'\n'); cout << endl;
            cout << "Enter browser used: "; in.get(browser,100,'\n'); in.ignore(100,'\n'); cout << endl;
            base = new website(address, sub_address, browser, duration, frequency, name, date, actions); 
            //upcasting to base class pointer
        }
        else if(option == 2){//user decides to use a social app
            cout << "Enter who messages were sent to: "; in.get(sent_to,100,'\n'); in.ignore(100,'\n'); cout << endl;
            cout << "Enter your name or user name: "; in.get(sent_from,100,'\n'); in.ignore(100,'\n'); cout << endl;
            base = new social_app(sent_to, sent_from, duration, frequency, name, date, actions); 
            //upcasting to base class pointer
        }
        else if(option == 3){//user decides to use a game app
            cout << "Enter number of achievements unlocked: "; in >> achievement; in.ignore(100,'\n'); cout << endl;
            cout << "Enter current level: "; in >> current_level; in.ignore(100,'\n'); cout << endl;
            cout << "Enter levels gained during session: "; in >> levels_gained; in.ignore(100,'\n'); cout << endl;
            base = new game_app(achievement, levels_gained, current_level, duration, frequency, name, date, actions); 
            //upcasting to base class pointer
        }
        if(base){//if the user made a valid choice, we make sure to add their new data to list and delete pointer
            input_to += *base;//add to list
            delete base; base = NULL;//delete pointer
            cout << "Succesfuly added new data to list.\n(Press enter)." << endl;
            return in;//maintain stream
        }
        else if(option == 0){//user decided to go back
            cout << "Returning to previous menu.\n" << endl;
            return in;//maintain stream
        }
        else//user did not enter a supplied number
            cout << "Please enter a valid choice.\n" << endl;
    }while(option < 0 && option > 3);//restrictions for what user may enter
    return in;//maintain stream
}

//overloaded bitshift operator, this function is used for loading data from a file to the list data structure
//similar to the function above in arguments and returns, although there is no istream object, ifstream instead
ifstream & operator >> (ifstream & in, list & to_create)
{
    char type[100];        double duration = 0;     //temporary variables used to file input
    char name[100];        char date[100];
    char actions[1000];    double frequency = 0;
    char address[100];     char browser[100];
    char sub_address[100]; char sent_from[100];
    char sent_to[100];     int levels_gained = 0;   
    int achievement = 0;   program * base = NULL;//this variable is used for upcasting before input to list
    int current_level = 0;

    in.get(type, 100, ':'); in.ignore(100, ':');//checking eof
    while(!in.eof()){//continue drawing from file as long as we aren't at the end of the file
        if(!strcmp(type, "website")){//if the identifier in the file is "website"
            in >> duration; in.ignore(100, ':');
            in >> frequency; in.ignore(100, ':');
            in.get(name, 100, ':'); in.ignore(100, ':');
            in.get(date, 100, ':'); in.ignore(100, ':');
            in.get(actions, 1000, ':'); in.ignore(100, ':');
            in.get(address, 100, ':'); in.ignore(100, ':');
            in.get(sub_address, 100, ':'); in.ignore(100, ':');
            in.get(browser, 100, '\n'); in.ignore(100, '\n');
            base = new website(address, sub_address, browser, duration, frequency, name, date, actions); 
            to_create += *base;//upcast to temporary program pointer and insert to list
        }
        else if(!strcmp(type, "social_app")){//if the identifier in the file is "social_app"
            in >> duration; in.ignore(100, ':');
            in >> frequency; in.ignore(100, ':');
            in.get(name, 100, ':'); in.ignore(100, ':');
            in.get(date, 100, ':'); in.ignore(100, ':');
            in.get(actions, 1000, ':'); in.ignore(100, ':');
            in.get(sent_to, 100, ':'); in.ignore(100, ':');
            in.get(sent_from, 100, '\n'); in.ignore(100, '\n');
            base = new social_app(sent_to, sent_from, duration, frequency, name, date, actions); 
            to_create += *base;//upcast to temporary program pointer and insert to list
        }
        else if(!strcmp(type, "game_app")){//if the identifier in the file is "game_app"
            in >> duration; in.ignore(100, ':');
            in >> frequency; in.ignore(100, ':');
            in.get(name, 100, ':'); in.ignore(100, ':');
            in.get(date, 100, ':'); in.ignore(100, ':');
            in.get(actions, 100, ':'); in.ignore(100, ':');
            in >> achievement; in.ignore(100, ':');
            in >> levels_gained; in.ignore(100, ':');
            in >> current_level; in.ignore(100, '\n');
            base = new game_app(achievement, levels_gained, current_level, duration,frequency,name,date,actions);
            to_create += *base;//upcast to temporary program pointer and insert to list
        }
        else//identifier read from file was not one of the three above, probably due to spelling error
            cout << "Identifier not recognized." << endl;
        if(base){//if the identifier was recognized and an insert happened, delete the temp pointer
            delete base;
            base = NULL;
        }
        in.get(type, 100, ':'); in.ignore(100, ':');//because check for eof is before loop, we put this here
    }
    return in;//maintain stream
}

//assignment operator for list class, this function receives another list object and copies its contents into
//the current list, a list reference is returned to benefit chaining
list & list::operator = (const list & to_copy)
{
    if(this == &to_copy)//check if pointing to self
        return *this;
    if(this){           //check if there is pre-existing data in list to copy to
        if(!remove_all(head))//if there was, then remove everything in it
            cout << "Nothing to clear in new list." << endl;
    }
    //lastly, call the list class copy function to transfer all data from arg list to current list
    cout << full_copy(head, to_copy.head) << " search trees copied.\n" << endl;
    return *this;//return reference to self
}

//overloaded arithmetic operator in list class, returns a list by value to support chaining, takes a program reference as
//an argument to add to calling list
list list::operator + (const program & to_add) const
{
    list temp(*this);//create temporary list and call copy constructor on the calling list
    temp += to_add;//use arithmetic assignment operator to add program argument to temp list
    return temp;//return the temporary list by value
}

//overloaded arithmetic assignment operator in list class, receives a program reference with  which it will add to the list.
list & list::operator += (const program & to_add)
{
    if(!insert(head, to_add)){//call recursive insert function and hand in program argument
        cout << "LLL recursive insert failed." << endl;
    }
    return *this;//return reference to self
}

//recursive insert function in list class, returns an int to represent success and failure and receives an l_node
//pointer to traverse the linked list and a program reference to add to list
int list::insert(l_node *& head, const program & to_add)
{
    if(!head){//base case, traverse to end of list and found no place to insert
        head = new l_node(to_add);//insert at end of list, create new l_node calling constructor with arg
        return 1;
    }
    int direction = to_add.compare_frequency(head->get_frequency());//determine whether to traverse forward,
//traversed too far, create node behind current position and insert //add to current node's bst or create new
    if(direction == -1){                                            //new node behind itself                 
        l_node * temp = new l_node(to_add);                         
        temp->to_next() = head;
        head = temp;
        return 1;
    }
    else if(direction == 0){//add to current l_nodes's bst 
        head->insert(to_add);
        return 1;
    }
    return insert(head->to_next(), to_add);//traverse forward
}

//overloaded arithmatic operator in list class, returns a list by value to support chaining, receives a char *
//to use for matching in the list, if found, will remove matching data
list list::operator - (const char * match) const
{
    list temp(*this);//create temporary list using copy constructor on calling list
    temp -= match;//call overloaded arithmetic assignment operator to attempt to remove specified data
    return temp;//return temp list by value
}

//overloaded arithmetic assignment operator in list class, receives a char * to attempt to match data in calling
//list, if found, will remove
list & list::operator -= (const char * match)
{
    if(!remove(head, match))//current list's recursive remove function called, handed specified data(char*)
        cout << "No match was found for specified data." << endl;
    return *this;//return self by reference
}

//list class recursive remove function, receives an l_node to traverse the linked list and a char * to find
//data to be removed
int list::remove(l_node *& head, const char * match)
{
    if(!head)//base case, traversed too far
        return 0;
    if(head->remove(match) == 1){//attempt to remove in current bst, bst may or may not have it
        if(head->to_root() == NULL){//if after removal l_node's bst is empty, delete useless l_node
            l_node * temp = head->to_next();//link up linked list 
            delete head; head = temp;
        }
        return 1;//data was succesfully found an removed
    }
    return remove(head->to_next(), match);//recursive call
}

//overloaded equality operator in list class, receives a list object by reference and calls list class
//compare list function, returns a bool to convey whether list are equal
bool list::operator == (const list & to_compare) const
{
    if(compare_list(head, to_compare.head))//calling list class compare_list function, handing it to_compare
        return true;//depending on whether they are equal or not return a boolean
    return false;
}

//overloaded equality operator in list class, exactly the same as the one above, return values are swapped.
bool list::operator != (const list & to_compare) const
{
    if(compare_list(head, to_compare.head))
        return false;
    return true;
}

//recursive list comparison function in list class, this function will determine whether or not two list are 
//exactly the same. It makes use of the bst comparison function at each l_node to determine whether the bsts
//are also equal. the head node is usually the current list, and the to_compare node is usually the list that
//is being compared against
bool list::compare_list(l_node * head, l_node * to_compare) const
{
    if(!head && !to_compare)//both lists end in the same place, usually means lists are equal
        return true;
    if(!head && to_compare)//one list is shorter
        return false;
    if(!to_compare && head)//one list is shorter
        return false;
    if(!head->compare_bst(head->to_root(), to_compare->to_root()))//calling bst comparison function
        return false;
    if(!compare_list(head->to_next(), to_compare->to_next()))//recursive call
        return false;
    return true;
}

//overloaded relational operator in list class, compares to lists to determine which is greater/smaller
//a dedicated relational function inequalityXI is called in all of the overloaded relational operators
//to determine which is bigger/smaller
bool list::operator < (const list & to_compare) const
{
    if(inequalityXI(head, to_compare.head) == -1)//call dedicated relation function
        return true;
    return false;
}

//exactly the same as one above it except the if statement checks for the opposite return value
bool list::operator > (const list & to_compare) const
{
    if(inequalityXI(head, to_compare.head) == 1)//call dedicated relation function
        return true;
    return false;
}

//exactly the same as those above except two cases are check for to account for list equaling each other
bool list::operator <= (const list & to_compare) const
{
    int retval = inequalityXI(head, to_compare.head);//calling dedicated relational function
    if(retval == -1 || retval == 0)//check for equals and less than
        return true;
    return false;
}

//same as above, -1 is switched to 1 to check for opposite case
bool list::operator >= (const list & to_compare) const
{
    int retval = inequalityXI(head, to_compare.head);//calling dedicated relation function
    if(retval == 1 || retval == 0)//check for both cases
        return true;
    return false;
}

//recursive list comparison function in list class, it determines the length of a list relative to another
//(less than, greater than, equal to, etc.)
int list::inequalityXI(l_node * head, l_node * source) const
{
    if(!head && !source)//list are equal
        return 0;
    if(!head && source)//first list is shorter
        return -1;
    if(head && !source)//first list is greater
        return 1;
    return inequalityXI(head->to_next(), source->to_next());//recursive call
}

//list class copy function receives a head node from another list and traverse both copying source to head
//l_node copy constructor is used to kick off the process of copying everything 
int list::full_copy(l_node *& head, l_node * source)
{
    if(!source)//source list has reached its end
        return 0;
    head = new l_node(*source);//l_node copy constructor used to copy bst and stuff
    int count = full_copy(head->to_next(), source->to_next()) + 1;//recursive call
    return count;
}

//wrapper function in list class to kick off recursive retrieve function. Takes a program pointer to store the
//found data and a char * to match data against
int list::retrieve(program *& copy_to, char * match)
{
    return retrieve(head, copy_to, match);//kick off recursive process
}

//recursive retrieval function in list class, only thing different than one above is it takes an l_node pointer
//to traverse the list. This function calls the bst retrieve function at every l_node and hands it the program
//pointer and char * for matching
int list::retrieve(l_node *& head, program *& copy_to, char * match)
{
    if(!head)//base case, traversed too far
        return 0;
    if(head->retrieve(copy_to, match))//attempt to retrieve data from current bst
        return 1;
    return retrieve(head->to_next(), copy_to, match);//recursive call
}

//wrapper function for recursive remove all function in list class
void list::remove_all()
{
    for(int i = 0; i < 50; ++i)//clear screen, makes it prettier
        cout << "\n\n\n" << endl;
    remove_all(head);//recursive call
}

//recursive remove all function in lis class, takes an l_node pointer to traverse list
//de_allocation takes place on return
int list::remove_all(l_node *& head)
{
    if(!head)//base case, traverse to end of list
        return 0;
    int count = remove_all(head->to_next()) + 1;//recursive call
    delete head;//delete data on way back
    head = NULL;
    return count;
}
