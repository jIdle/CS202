/* Kobe Davis
 * Prof. Fant
 * CS202
 * April 25, 2017
 */

//header file which will be holding the class definitions for communication, mail, facebook, email, and texting
//classes. these classes will be in a hierarchical relationship where communication is the abstract base class.
//the purpose of this hierarchy is to make use of dynamic binding through pure virtual function.
//the classes: mail, facebook, email, and texting will be upcasted to a comm class pointer inside of a
//circular linked list.

#include "BST.h"

//this is the abstract base class in the overall hierarchy. it will contain the pure virtual function for use
//by the derived classes
class comm
{
    public:
        //default constructor
        comm();
        //virtual destructor so correct derived class destructor is called
        virtual ~comm();
        //pure virtual send function which takes a bst by reference as an argument to know who can be contacted,
        //and returns an int to convey success and failure. it is virtual so that the derived classes can have
        //their own, independent version of sending messages to contacts.
        virtual int send(tree & contacts) = 0;
        //pure virtual display function will, in general, be used to display data members to the client. int is
        //returned to convey success and failure.
        virtual int display() = 0;
        //pure virtual remove function will, in general, be used to clear out data being used by the current 
        //communication method. int is returned to convey success and failure
        virtual int remove() = 0;
    protected:
        char * to;//represents who the message is being sent to
        char * from;//represents who the message is coming from
        char * message;//represents the body of the message
};

//derived class from comm class, will represent postal communication method.
class mail: public comm
{
    public:
        //constructor
        mail();
        //destructor
        ~mail();
        //send function which takes a tree class by reference as an argument and returns an int to convey
        //success and failure. this function allows for the user to send messages to those held in the bst 
        //"contacts"
        int send(tree & contacts);
        //display function will display data members, returns an int to convey success and failure.
        int display();
        //remove function will clear data members, returns an int to convey success and failure.
        int remove();
    private:
        int PO_box;//tells the user whether or not the letter was sent to a P.O. box
        int stamp_cost;//tells the user how much the stamp cost
};

//derived class from comm class, will represent facebook communication method.
class facebook: public comm
{
    public:
        //default constructor
        facebook();
        //destructor
        ~facebook();
        //send function allows user to send a message to those in the bst that is handed in as arg
        int send(tree & contacts);
        //displays thumbs_up and tag data members along with those in base class
        int display();
        //resets or clears thumbs_up and tag data members
        int remove();
    private:
        int thumbs_up;//has the message been "liked"
        char * tag;//who was tagged in the message
};

//derived class from the comm class, will represent email communication method.
class email: public comm
{
    public:
        //default constructor
        email();
        //destructor
        ~email();
        //send function allows user to send an email to those in the bst that is handed in as arg
        int send(tree & contacts);
        //displays subject, CC, signature, and base class data members
        int display();
        //resets or clears subject, CC, signature, and base class data members
        int remove();
    private:
        char * subject;//subject of email
        char * CC;//who to CC on the email
        char * signature;//what is the signature at end of email
};

//derived class from the comm class, will represent texting communication method.
class texting: public comm
{
    public:
        //default constructor
        texting();
        //destructor
        ~texting();
        //send function allows user to send a text to those in the bst that is handed in as arg
        int send(tree & contacts);
        //displays emoji and group text array of character arrays data members
        int display();
        //resets or clears emoji, group text array, and base class data members
        int remove();
    private:
        char * emoji;//add an emoji to the text
        char ** group_text;//other peopel the user might want to send the text to.
};
