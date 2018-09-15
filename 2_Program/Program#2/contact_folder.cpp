/* Kobe Davis
 * Prof. Fant
 * CS202
 * April 25, 2017
 *
 * Function definitions from the contact_folder header file will be held in this .cpp.
 */

#include "contact_folder.h"

using namespace std;

//default constructor for contact_folder class
contact_folder::contact_folder():username(NULL), ID(0), mailing_address(NULL), facebook_name(NULL),
    email_address(NULL), phone_number(NULL)
{
}

//constructor with args for the contact_folder class
contact_folder::contact_folder(char * user_to_add, int ID_to_add)
{
    username = new char[strlen(user_to_add) + 1];
    strcpy(username, user_to_add);
    ID = ID_to_add;
    mailing_address = NULL;
    facebook_name = NULL;
    email_address = NULL;
    phone_number = NULL;
}

//copy constructor for the contact_folder class
contact_folder::contact_folder(const contact_folder & to_copy)
{
    username = new char[strlen(to_copy.username)];//deep copy
    strcpy(username, to_copy.username);
    ID = to_copy.ID;
    if(to_copy.mailing_address)//make sure something was handed in
    {
        mailing_address = new char*[5];//array of character arrays
        for(int i = 0; i < 5; ++i)
        {
            mailing_address[i] = NULL;
            if(to_copy.mailing_address[i])//deep copy
            {
                mailing_address[i] = new char[strlen(to_copy.mailing_address[i]) + 1];
                strcpy(mailing_address[i], to_copy.mailing_address[i]);
            }
        }
    }
    if(to_copy.facebook_name)//make sure something was handed in
    {
        facebook_name = new char*[5];//array of character arrays
        for(int i = 0; i < 5; ++i)
        {
            facebook_name[i] = NULL;
            if(to_copy.facebook_name[i])//deep copy
            {
                facebook_name[i] = new char[strlen(to_copy.facebook_name[i]) + 1];
                strcpy(facebook_name[i], to_copy.facebook_name[i]);
            }
        }
    }
    if(to_copy.email_address)//make sure something was handed in
    {
        email_address = new char*[5];//array of character arrays
        for(int i = 0; i < 5; ++i)
        {
            email_address[i] = NULL;
            if(to_copy.email_address[i])//deep copy
            {
                email_address[i] = new char[strlen(to_copy.email_address[i]) + 1];
                strcpy(email_address[i], to_copy.email_address[i]);
            }
        }
    }
    if(to_copy.phone_number)//make sure something was handed in
    {
        phone_number = new int[5];//array of ints
        for(int i = 0; i < 5; ++i)
        {
            phone_number[i] = 0;
            if(to_copy.phone_number[i] != 0)
            {
                phone_number[i] = to_copy.phone_number[i];//shallow copy
            }
        }
    }
}

//destructor for contact_folder class
contact_folder::~contact_folder()
{
    if(username)//null check
    {
        delete [] username;
    }
    ID = 0;
    if(mailing_address)//null check
    {
        for(int i = 0; i < 5; ++i)//delete entire array
        {
            if(mailing_address[i])
            {
                delete [] mailing_address[i];
                mailing_address[i] = NULL;
            }
        }
        delete [] mailing_address;
        mailing_address = NULL;
    }
    if(facebook_name)//null check
    {
        for(int i = 0; i < 5; ++i)//delete entire array
        {
            if(facebook_name[i])
            {
                delete [] facebook_name[i];
                facebook_name[i] = NULL;
            }
        }
        delete [] facebook_name;
        facebook_name = NULL;
    }
    if(email_address)//null check
    {
        for(int i = 0; i < 5; ++i)//delete entire array
        {
            if(email_address[i])
            {
                delete [] email_address[i];
                email_address[i] = NULL;
            }
        }
        delete [] email_address;
        email_address = NULL;
    }
    if(phone_number)//null check
    {
        delete [] phone_number;
        phone_number = NULL;
    }
}

//comparison function from contact_folder class
int contact_folder::compare(contact_folder & to_compare)
{
    if(strcmp(to_compare.username, username) < 0)//if the arg handed in is less than the current one
        return -1;

    else if(strcmp(to_compare.username, username) > 0)//if the arg handed in is greater than the current one
        return 1;

    else
    {
        if(to_compare.ID == ID)//if the ID also happens to match
        {
            return 2;//returns special number letting receiver know
        }
        return 0;//otherwise just let the receiver know that a match was found, but not an ID match.
    }
}

//setter for facebook data member in contact_folder class
int contact_folder::add_facebook(char * to_add)
{
    if(!facebook_name)//null check, if triggers, create the entire array of character arrays also
    {
        facebook_name = new char*[5];
        facebook_name[0] = new char[strlen(to_add) + 1];
        strcpy(facebook_name[0], to_add);
        return 1;
    }
    else//if it has already been created just work inside the array of character arrays
    {
        for(int i = 0; i < 5; ++i)
        {
            if(!facebook_name[i])//null check
            {
                facebook_name[i] = new char[strlen(to_add) + 1];//deep copy
                strcpy(facebook_name[i], to_add);
                return 1;
            }
        }
    }
    return 0;
}

//setter for mailing address data member in contact_folder class
int contact_folder::add_postal(char * to_add)
{
    if(!mailing_address)//null check, if triggers, create the entire array of character arrays also
    {
        mailing_address = new char*[5];
        mailing_address[0] = new char[strlen(to_add) + 1];
        strcpy(mailing_address[0], to_add);
        return 1;
    }
    else//if it has already been created just work inside the array of character arrays
    {
        for(int i = 0; i < 5; ++i)
        {
            if(!mailing_address[i])//null check
            {
                mailing_address[i] = new char[strlen(to_add) + 1];
                strcpy(mailing_address[i], to_add);
                return 1;
            }
        }
    }
    return 0;
}

//setter for email_address data member inside the contact_folder class
int contact_folder::add_email(char * to_add)
{
    if(!email_address)//null check, if triggers, create entire array of character arrays
    {
        email_address = new char*[5];
        email_address[0] = new char[strlen(to_add) + 1];
        strcpy(email_address[0], to_add);
        return 1;
    }
    else//if it has already been created then just add inside of it into one the character arrays
    {
        for(int i = 0; i < 5; ++i)
        {
            if(!email_address[i])//null check
            {
                email_address[i] = new char[strlen(to_add) + 1];
                strcpy(email_address[i], to_add);
                return 1;
            }
        }
    }
    return 0;
}

//setter for phone_number data member inside the contact_folder class
int contact_folder::add_cell(int to_add)
{
    if(!phone_number)//null check, if it triggers create the entire array of integers
    {
        phone_number = new int[5];
        phone_number[0] = to_add;
        return 1;
    }
    else//if the entire array has already been created, then just focus on adding into one of the ints.
    {
        for(int i = 0; i < 5; ++i)
        {
            if(!phone_number[i])//null check
            {
                phone_number[i] = to_add;
                return 1;
            }
        }
    }
    return 0;
}

//display function from the contact_folder class, this function will takes an integer
//and with it, decide which data members to display. The username and ID will always be displayed though.
int contact_folder::display(int comm)
{
    if(username){//null check
        cout << "\nUsername: " << username << endl;
        cout << "ID: " << ID << endl;//display username and ID of the specified user
        if(comm == 1){//if the data to be displayed is facebook data
            if(facebook_name){
                int count = 0;
                for(int i = 0; i < 5; ++i){
                    if(facebook_name[i]){//looping through facebok data to display it
                        ++count;
                        cout << "Account #" << count << ": " << facebook_name[i] << endl;
                    }
                }
            }
            else//if no facebook data is found
                cout << "No facebook account." << endl;
        }
        else if(comm == 2){//if the data to be displayed is cell phone data
            if(phone_number){//null check
                cout << "Cell phone: " << *phone_number << endl;
            }
        }
        else if(comm == 3){//if the data to be displayed is email data
            if(email_address){//null check
                int count = 0;
                for(int i = 0; i < 5; ++i){//loop through all emails and display
                    if(email_address[i]){
                        ++count;
                        cout << "Email #" << count << ": " << email_address[i] << endl;
                    }
                }
            }
            else//no email data was found
                cout << "No email address." << endl;
        }
        else if(comm == 4){//if the data to be displayed is postage data
            if(mailing_address){//null check
                int count = 0;
                for(int i = 0; i < 5; ++i){//loop through all mailing address data and display
                    if(mailing_address[i]){
                        ++count;
                        cout << "Mailing Address #" << count << ": " << mailing_address[i] << endl;
                    }
                }
            }
            else//no mailing address data was found
                cout << "No mailing address." << endl;
        }
        cout << endl;
        return 1;
    }
    return 0;
}

//display all function from the contact_folder class, this function takes no arguments and returns and int
//depending on whether there is data to be displayed or not. it just displayes everything
int contact_folder::display_all()
{
    if(username){//null check
        cout << "\nUsername: " << username << endl;
        cout << "ID: " << ID << endl;
    }
    else
        return 0;

    if(phone_number){//null check
        for(int i = 0; i < 5; ++i){
            if(phone_number[i])//loop through all phone numbers
                cout << (i+1) << ". Phone number: " << phone_number[i] << endl;
        }
    }
    else
        cout << "Phone number has not been set." << endl;

    if(mailing_address){//null check
        for(int i = 0; i < 5; ++i){//loop through all mailing addresses
            if(mailing_address[i])
                cout << (i+1) << ". Mailing address: " << mailing_address[i] << endl;
        }
    }
    else
        cout << "Mailing address has not been set." << endl;

    if(facebook_name){//null check
        for(int i = 0; i < 5; ++i){//loop through all facebook usernames
            if(facebook_name[i])
                cout << (i+1) << ". Facebook: " << facebook_name[i] << endl;
        }
    }
    else
        cout << "Facebook has not been set." << endl;

    if(email_address){//null check
        for(int i = 0; i < 5; ++i){//loop through all email addresses
            if(email_address[i])
                cout << (i+1) << ". Email address: " << email_address[i] << endl;
        }
    }
    else
        cout << "Email address has not been set." << endl;
    return 1;
}
