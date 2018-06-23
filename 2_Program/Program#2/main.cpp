/* Kobe Davis
 * Prof. Fant
 * CS202
 * April 25, 2017
 */

//main file for program #2
//The purpose of this program is to experience dynamic binding through the use of pure virtual function and abstract base classes in a hierarchy.
//This will be accomplished by creating a program that will allow a user to cycle through different means of communication. This program
//in particular will include the forms of communication: Facebook, Texting, Email, and Mail. An abstract base class pointer will be held
//inside each node in a Circular Linked List which will be used for upcasting derived classes. In this way, many different class types can
//be stored in one data structure.

#include "CLL.h"

using namespace std;

int main()
{
    tree contacts;//this binary search tree will be used as the address book or contact book for who the user can send messages to.
    contact_folder * person;//the contact folder is what stores all of one person's contact information together in one place.
    clist app_list;//this circular linked list will be used to hold all of the user's different communication methods
    comm * base_ptr = NULL;//this comm pointer will be used to allow the user to interface with their communication method
    char temp[100]; int temp2 = 0;//temporary variables used for user input
    int temp_ID = 0; int temp3 = 0;
    int first_switch = 0;

    while(temp2 != 8)//until the user decides to quit
    {
        //prompting user for choices
        cout << "\nWhat would you like to do with your methods of communication?" << endl;
        cout << " 1. Create Communication Method\n 2. Display All\n 3. Remove All\n 4. View Current Communication Method\n 5. Switch to Next Communication Method\n 6. Add Contact\n 7. Delete Contact\n 8. Quit\n(Enter corresponding number): ";
        cin >> temp2; cin.ignore(100,'\n');cout << endl;
        if(temp2 == 1)//if user chooses to create a comm method
        {
            if(!app_list.insert())//call cll insert function
                cout << "Insert was not succesful." << endl;
            if(first_switch == 0)
            {
                if(!app_list.next_comm(base_ptr))//switch user to this eln they've just created
                    cout << "Could not switch to current device." << endl;
                first_switch = 1;
            }
        }
        if(temp2 == 2)//if the user chooses to display all of their eln
        {
            if(!app_list.display_all())//call cll display all function
                cout << "There is nothing to display." << endl;
        }
        if(temp2 == 3)//if the user decides to remove all of their created eln
        {
            if(!app_list.remove_all())//call cll remove all function
                cout << "There is nothing to remove." << endl;
            else
                cout << "List of communication methods successfully removed." << endl;
            base_ptr = NULL; first_switch = 0;
        }
        if(temp2 == 4)//if the user decides to view the eln they are currently using
        {
            while(temp3 != 4)//prompt user with new menu until they decide to go back to last one
            {
                cout << "What would you like to do with this communication method?" << endl;
                cout << " 1. Send Message\n 2. Read Last Message\n 3. Remove Last Message\n 4. Go Back\n(Enter corresponding number): ";
                cin >> temp3; cin.ignore(100, '\n'); cout << endl;
                if(temp3 == 1)//if user decides to send a messages from their eln
                {
                    if(base_ptr)//null check
                    {
                        if(!base_ptr->send(contacts))//call comm pointer send function
                            cout << "\nNo contacts to send message to.\n" << endl;
                    }
                    else
                        cout << "No communication method has been created yet!\n" << endl;
                }
                if(temp3 == 2)//if user decides to view last message sent
                {
                    if(base_ptr)
                        base_ptr->display();//call comm pointer display function
                    else
                        cout << "No communication method has been created yet!\n" << endl;
                }
                if(temp3 == 3)//if the user decides to remove the last message sent
                {
                    if(base_ptr)//null check
                        base_ptr->remove();//call comm pointer remove function
                    else
                        cout << "No communication method has been created yet!\n" << endl;
                }
                if(temp3 == 4)//if the user decides to go back to the previous menu
                    cout << "Returning to previous menu." << endl;
            }
            temp3 = 0;
        }
        if(temp2 == 5)//if the user decides to switch to the next eln in line
        {
            app_list.next_comm(base_ptr);//call cll next_comm function which will switch eln
            cout << "Switched to the next device." << endl;
        }
        if(temp2 == 6)//if user decides to add a new contact to the address/contact book
        {
            cout << "Enter person's name: ";//prompting user
            cin.get(temp, 100, '\n'); cin.ignore(100, '\n'); cout << endl;
            person = new contact_folder(temp, temp_ID);
            ++temp_ID;
            if(!contacts.insert(*person))//call tree class insert function
                cout << "Could not add contact." << endl;
            delete person; person = NULL;
        }
        if(temp2 == 7)//if the user decides to delete a particular contact from the address/contact book
        {
            if(contacts.display(0))//call tree class display function
            {
                cout << "\nEnter the name and ID of the person you would like to remove (ID may not always be necessary):" << endl;//prompt user for the person that should be removed
                cout << "Enter name: "; cin.get(temp, 100, '\n'); cin.ignore(100, '\n');
                cout << "Enter ID: "; cin >> temp3; cin.ignore(100, '\n');

                person = new contact_folder(temp, temp2);
                if(!contacts.remove(person))//call tree class remove function
                    cout << "Contact does not exist." << endl;
                delete person; person = NULL;
                temp3 = 0;
            }
            else
                cout << "There are no contacts to remove." << endl;
        }
    }
        cout << "Program will quit." << endl;//user opted to quit program

        //Below this is proof the the Binary Search Tree retrieve function is fully functional, simply by removing the comment formatting it will work.
        //It just isn't needed in this program design, nor is it implemented in any useful way besides just randomly wanting to look at someone. 
        //Although it does actually work and it has been fully tested.

    //cout << "\nEnter the name and ID of the person you would like to view:" << endl;
    //cout << "Enter name: "; cin.get(temp, 100, '\n'); cin.ignore(100, '\n');
    //cout << "Enter ID: "; cin >> temp2; cin.ignore(100, '\n');

    //person = new contact_folder(temp, temp2);
    //if(!contacts.retrieve(person))
    //{
    //    cout << "retrieve function returned 0" << endl;
    //}
    //else if(person->display_all())
    //{
    //    delete person; person = NULL;
    //}
    //else
    //    cout << "display function returned a 0" << endl;

    //if(!contacts.display())
    //{
    //    cout << "display function returned a 0 in main" << endl;
    //}

    return 0;
}
