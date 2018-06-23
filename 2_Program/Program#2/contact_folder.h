/* Kobe Davis
 * Prof. Fant
 * CS202
 * April 25, 2017
 *
 * Header file for the contact_folder class.
 */

#include <iostream>
#include <cstring>

//This class will hold any and all information pertinent to what the communication classes might need.
class contact_folder
{
    public:
        //default constructor
        contact_folder();
        //constructor with args
        contact_folder(char * user_to_add, int ID_to_add);
        //copy constructor
        contact_folder(const contact_folder & to_copy);
        //destructor
        ~contact_folder();
        //compare function is used to help the BST which direction to go eat each node.
        //The usernames are compared inside of it and an integer is returned specify whether or not
        //a match was found, or which direction to go. A two can be returned if the ID of the individual
        //also matches. Comparisons are made against the contact_folder handed as an argument byu reference.
        int compare(contact_folder & to_compare);
        //setter for the facebook array of character arrays, integer is returned to convey success and failure.
        int add_facebook(char * to_add);
        //setter for the postage array of character arrays, integer is returned to convey success and failure.
        int add_postal(char * to_add);
        //setter for the email array of character arrays, integer is returned to convey succes and failure.
        int add_email(char * to_add);
        //setter for the array of cell phone numbers, integer is returned to convey success and failure.
        int add_cell(int to_add);
        //display function which allows only specific data members to be displayed depending on the integer
        //handed in the argument. integer is returned to convey success and failure.
        int display(int comm);
        //display all function will display all data members and return an int to convey success and failure.
        int display_all();
    private:
        char * username; //Usually the name of the person being stored
        int ID; //This ID is used for each user because there may be users with the same name.
        char ** mailing_address; //The below data members are self explanatory.
        char ** facebook_name;   //Pointers to pointers and pointers are used in case of many accounts/coms.
        char ** email_address;
        int * phone_number;
};
