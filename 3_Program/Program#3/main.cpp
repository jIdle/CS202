/*
 * Kobe Davis
 * Prof. Fant
 * CS202
 * 5 May 2017
 */

//main file which will act the "client" or "user"

/*
 * The goal of this assignment is to experience operator overloading in an object oriented environment.
 * Also to create classes that support the copy constructor, destructor, and assignment operator when dynamic memory is involved.
 * The next purpose of this program is to create and apply the functionality of the overloaded operators.
 * This is supposed to be done using a data structure of: a linear linked list where each node has a bst that holds specified data.
 */

#include "list.h"
using namespace std;

int main()
{
    list my_list;
    list second;
    program * base = NULL; 
    int option = -1;
    int option2 = -1;
    char temp[100];
    bool temp1;

    //process directly below this is loading data from file using overloaded bitshift right operator with list
    cout << "\n\nLoading data..." << endl;
    ifstream in;
    in.open("program_data.txt");
    in >> my_list;
    in.close();
    cout << "Done loading data!\n" << endl;

    while(option != 0){//user interface
        cout << "\n 1. Use/Insert\n 2. Remove\n 3. Display All\n 4. Retrieve\n 5. Test Equality & Inequality Operators\n 6. Clear List\n 0. Quit\n(Enter corresponding number): "; //user options
        cin >> option; cin.ignore(100, '\n');   //user input

        //insert or use data
        if(option == 1)
        {
            cin >> my_list; cin.ignore(100, '\n');
        }
        else if(option == 2){
            //remove data specified by user
            cout << "Enter the name of the data you would like to remove." << endl;
            cin.get(temp, 100, '\n'); cin.ignore(100, '\n');
            my_list -= temp;
        }
        else if(option == 3)//display entire list that user has created thus far
            cout << my_list << endl;
        else if(option == 4){
            //retrieve data specified by user
            cout << "Enter the name of the data you would like to retrieve." << endl;
            cin.get(temp, 100, '\n'); cin.ignore(100, '\n');
            my_list.retrieve(base, temp);
            if(base){
                base->display();
                delete base;
                base = NULL;
            }
        }
        else if(option == 5){
            //allow user to create a second list for which they can test the relational and equality operators against using the current list
            while(option2 != 0){
                //user interface
                cout << "\n\nAll of the following options will now be in reference to a new list or the new list in comparison to the initial list." << endl;
                cout << "Once finished creating second list, select Test[4] to begin comparisons between lists.\n" << endl;
                cout << " 1. Insert\n 2. Remove\n 3. Display All\n 4. Test\n 0. Go back\n(Enter corresponding number): ";   //user options
                cin >> option2; cin.ignore(100, '\n');  //user input
                //insert into second list
                if(option2 == 2)
                {
                    cin >> second; cin.ignore(100,'\n');
                }
                else if(option2 == 2){
                    //remove from second list
                    cout << "Enter the name of the data you would like to remove." << endl;
                    cin.get(temp, 100, '\n'); cin.ignore(100, '\n');
                    second -= temp;
                }
                else if(option2 == 3)//display entire second list
                    cout << second << endl;
                else if(option2 == 4){
                    //test all relational and equality operators between lists
                    temp1 = my_list == second;
                    cout << "\nFirst List == Second List: " << temp1 << endl;
                    temp1 = my_list != second;
                    cout << "\nFirst List != Second List: " << temp1 << endl;
                    temp1 = my_list < second;
                    cout << "\nFirst List < Second List: " << temp1 << endl;
                    temp1 = my_list > second;
                    cout << "\nFirst List > Second List: " << temp1 << endl;
                    temp1 = my_list <= second;
                    cout << "\nFirst List <= Second List: " << temp1 << endl;
                    temp1 = my_list >= second;
                    cout << "\nFirst List >= Second List: " << temp1 << endl << endl;
                }
                else if(option2 == 0)//user chooses to go back to previous menu
                    cout << "Returning to previous menu." << endl;
                else//valid option was not chosen
                    cout << "Please enter a valid option." << endl;
            }
            option2 = -1;
        }
        else if(option == 6){
            //clear entire list
            my_list.remove_all();
            cout << "List has been cleared." << endl;
        }
        else if(option == 0)//quit program
            cout << "Program will now quit." << endl;
        else//valid option was not chosen
            cout << "Please enter a valid option." << endl;
    }
    return 0;
}
