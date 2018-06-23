/* Kobe Davis
 * Prof. Fant
 * CS202
 * April 25, 2017
 *
 * Function definitions from the abstract_hierarchy header file will be held in this .cpp.
 */

//.cpp file which will be holding the function the communication, mail, facebook, email, and texting classes
//which are located inside the abstract_hierarchy header file.

#include "abstract_hierarchy.h"

using namespace std;

//default constructor for the comm class
comm::comm():to(NULL), from(NULL), message(NULL)
{
}

//destructor for comm class
comm::~comm()
{
    if(to)
    {
        delete [] to;
        to = NULL;
    }
    if(from)
    {
        delete [] from;
        from = NULL;
    }
    if(message)
    {
        delete [] message;
        message = NULL;
    }
}

//default constructor for mail class
mail::mail():PO_box(0), stamp_cost(0)
{
}

//destructor for mail class
mail::~mail()
{
}

//send function for mail class will show the user who they are able to send an email to out of the bst of contact
//information, then it will prompt them for the necessary information which will then be sent and stored.
int mail::send(tree & contacts)
{
    char user_entry[1000];
    cout << "Contact information concerning postage:" << endl;
    if(!contacts.display(4))//who can be messaged
    {
        return 0;
    }
    remove();//remove previous message and begin prompting
    cout << "\nEnter the mailing address of the person who are sending a text to: ";
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n'); cout << endl;
    to = new char[strlen(user_entry) + 1]; strcpy(to, user_entry);
    cout << "Enter your mailing address: ";
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n'); cout << endl;
    from = new char[strlen(user_entry) + 1]; strcpy(from, user_entry);
    cout << "Enter your message:" << endl;
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n');
    message = new char[strlen(user_entry) + 1]; strcpy(message, user_entry);
    cout << "Is this being sent to a P.O box?\n 1. Yes\n 0. No\n(Enter the corresponding number): ";
    cin >> PO_box; cin.ignore(100, '\n'); cout << endl;
    cout << "Enter cost of postage stamp: ";
    cin >> stamp_cost; cin.ignore(100, '\n'); cout << endl;
    return 1;
}

//mail class display function just couts all of its data members if they exist
int mail::display()
{
    if(message)//null check
    {
        cout << "Letter sent to: " << to << endl;
        cout << "P.O. box: ";
        if(PO_box)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
        cout << "From: " << from << endl;
        cout << "\nMessage:\n\n" << message << endl;
        cout << "Stamp Cost: " << stamp_cost << endl;
        return 1;
    }
    else//nothing previous message exists
    {
        cout << "Postal Service: No letters have been sent.\n" << endl;
    }
    return 0;
}

//remove function for the mail class removes the stored message/previous message
int mail::remove()
{
    if(message)//null check
    {
        delete [] message; message = NULL;
        delete [] to; to = NULL;
        delete [] from; from = NULL;
        PO_box = 0; stamp_cost = 0;
        cout << "Previous letter has been deleted!" << endl;
        return 1;
    }
    else//nothing to remove
    {
        cout << "Postal Service: There is no previous letter to delete, try sending one!\n" << endl;
    }
    return 0;
}

//faceboo class default constructor
facebook::facebook():thumbs_up(0), tag(NULL)
{
}

//facebook class destructor
facebook::~facebook()
{
    if(tag)
    {
        delete [] tag;
        tag = NULL;
    }
}

//send function for the facebook class prompts the user for the necessary information and then sends and
//stores the info
int facebook::send(tree & contacts)
{
    char user_entry[1000];
    cout << "Contact information concerning facebook:" << endl;
    if(!contacts.display(1))//show user who they can contact
    {
        return 0;
    }
    remove();//remove and begin prompting
    cout << "\nEnter the facebook username of the person who are sending a text to: ";
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n'); cout << endl;
    to = new char[strlen(user_entry) + 1]; strcpy(to, user_entry);
    cout << "Enter your facebook username: ";
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n'); cout << endl;
    from = new char[strlen(user_entry) + 1]; strcpy(from, user_entry);
    cout << "Enter your message:" << endl;
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n');
    message = new char[strlen(user_entry) + 1]; strcpy(message, user_entry);
    thumbs_up = 1;
    cout << "Who do you want to tag in this message?: ";
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n'); cout << endl;
    tag = new char[strlen(user_entry) + 1]; strcpy(tag, user_entry);
    return 1;
}

//facebook class display function just couts the data members
int facebook::display()
{
    if(message)//null check
    {
        cout << "Private message sent to: " << to << endl;
        cout << from << " said:\n\n" << message << endl;
        cout << tag << " was tagged in this message." << endl;
        if(thumbs_up)
            cout << "This message has been given a like!" << endl;
        return 1;
    }
    else//nothing to display
    {
        cout << "Facebook: No private messages have been made.\n" << endl;
    }
    return 0;
}

//facebook class remove function removes the current stored message
int facebook::remove()
{
    if(message)//null check
    {
        delete [] message; message = NULL;
        delete [] to; to = NULL;
        delete [] from; from = NULL;
        delete [] tag; tag = NULL;
        thumbs_up = 0;
    }
    else//nothing to remove
    {
        cout << "Facebook: No private message has been sent yet!\n" << endl;
    }
    return 0;
}

//email class default constructor
email::email():subject(NULL), CC(NULL), signature(NULL)
{
}

//email class destructor
email::~email()
{
    if(subject)
    {
        delete [] subject;
        subject = NULL;
    }
    if(CC)
    {
        delete [] CC;
        CC = NULL;
    }
    if(signature)
    {
        delete [] signature;
        signature = NULL;
    }
}

//email class send function prompts the user for the necessary information to send a message and then sends and
//stores the information
int email::send(tree & contacts)
{
    char user_entry[1000];
    cout << "Contact information concerning email." << endl;
    if(!contacts.display(3))//show the user who they can contact
    {
        return 0;
    }
    remove();//remove previous message and begin prompting user
    cout << "\nEnter the email address of the person who are sending a text to: ";
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n'); cout << endl;
    to = new char[strlen(user_entry) + 1]; strcpy(to, user_entry);
    cout << "Enter your email address: ";
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n'); cout << endl;
    from = new char[strlen(user_entry) + 1]; strcpy(from, user_entry);
    cout << "Enter your message:" << endl;
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n');
    message = new char[strlen(user_entry) + 1]; strcpy(message, user_entry);
    cout << "Enter subject for email: ";
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000,'\n'); cout << endl;
    subject = new char[strlen(user_entry) + 1]; strcpy(subject, user_entry);
    cout << "Who would you like to CC? (If no one just enter zero): ";
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n'); cout << endl;
    CC = new char[strlen(CC) + 1]; strcpy(CC, user_entry);
    cout << "Enter your email signature: ";
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n'); cout << endl;
    signature = new char[strlen(user_entry) + 1]; strcpy(signature, user_entry);
    return 1;
}

//email class display function just couts all the data members if the exist
int email::display()
{
    if(message)//null check
    {
        cout << "Email sent to: " << to << endl;
        cout << "From: " << from << endl;
        cout << "Subject: " << subject << endl;
        cout << "CC: " << CC << endl;
        cout << "\nBody:\n\n" << message << endl;
        cout << signature << endl;
        return 1;
    }
    else//nothing to display
    {
        cout << "Email: No email sent as of yet.\n" << endl;
    }
    return 0;
}

//email class remove function deletes the current stored messages
int email::remove()
{
    if(message)//do they exist so I can delete them?
    {
        delete [] message; message = NULL;
        delete [] to; to = NULL;
        delete [] from; from = NULL;
        delete [] CC; CC = NULL;
        delete [] signature; signature = NULL;
        return 1;
    }
    else//nothing to delete
    {
        cout << "Email: No email available to remove.\n" << endl;
    }
    return 0;
}

//default constructor for the texting class
texting::texting():emoji(NULL)
{
    group_text = new char*[5];
    for(int i = 0; i < 5; ++i)
    {
        group_text[i] = NULL;
    }
}

//destructor for the texting class
texting::~texting()
{
    if(emoji)
    {
        delete [] emoji;
        emoji = NULL;
    }
    if(group_text)//check null for group text array of  character arrays
    {
        for(int i = 0; i < 5; ++i)
        {
            if(group_text[i])//null check
            {
                delete [] group_text[i];//delete each array slot
                group_text[i] = NULL;
            }
        }
        delete [] group_text;
    }
}

//texting class send function prompts the user for the necessary data then sends and stores the data
int texting::send(tree & contacts)
{
    char user_entry[1000];
    cout << "Contact information concerning texting:" << endl;
    if(!contacts.display(2))//show user who they can contact
    {
        return 0;
    }
    remove();//delete previous message and begin prompting user
    cout << "\nEnter the number of the person who are sending a text to: ";
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n'); cout << endl;
    to = new char[strlen(user_entry) + 1]; strcpy(to, user_entry);
    cout << "Enter your number: ";
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n'); cout << endl;
    from = new char[strlen(user_entry) + 1]; strcpy(from, user_entry);
    cout << "Enter your message:" << endl;
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n');
    message = new char[strlen(user_entry) + 1]; strcpy(message, user_entry);
    cout << "Enter an emoticon you would like to send along with this message: ";
    cin.get(user_entry, 1000, '\n'); cin.ignore(1000, '\n'); cout << endl;
    emoji = new char[strlen(user_entry) + 1]; strcpy(emoji, user_entry);
    return 1;
}

//texting class display function just couts the data members
int texting::display()
{
    if(message)//null check
    {
        cout << "Sent to: " << to << endl; 
        cout << from << ": " << message << endl;
        cout << ":" << emoji << ":" << endl;
        for(int i = 0; i < 5; ++i)
        {
            cout << group_text[i] << " was part of this group text." << endl;
        }
        return 1;
    }
    else//no texts to display
    {
        cout << "Cell: No texts have been sent yet.\n" << endl;
    }
    return 0;
}

//texting class remove function will delete current stored message if it exists
int texting::remove()
{
    if(message)//null check
    {
        delete [] message; message = NULL;
        delete [] to; to = NULL;
        delete [] from; from = NULL;
        delete [] emoji; emoji = NULL;
        for(int i = 0; i < 5; ++i)
        {
            if(group_text[i])//delete character arrays inside group_text array
            {
                delete [] group_text[i]; group_text[i] = NULL;
            }
        }
        delete [] group_text; group_text = NULL;
    }
    else//no texts to delete
    {
        cout << "Cell: No text available to delete.\n" << endl;
    }
    return 0;
}
