/*
 * NOTE TO GRADER:      INITIALLY COMPILED ON INTELLI J
 *                      Unsure of how this affects file read-in functionality on other IDEs.
 *
 * Kobe Davis
 * Prof. Fant
 * CS 202
 * 2 June 2017
 *
 * The purpose of this assignment is to experience implementation of personal, Object Oriented solutions in
 * Java for a Pizza ordering program. The goal is to create the Object Oriented section of programming separate from
 * the data structure. The data structures we are expected to create are:
 * 1. An array of base class pointers.
 * 2. A Doubly Linked List of those arrays.
 *
 */

package com.J1;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        Instruction sh;     //temp base class reference for storing shape of pizza
        Instruction co;     //temp base class reference for storing content of pizza
        Instruction ex;     //temp base class reference for storing toppings of pizza
        toppingList Order;  //class that acts as a manager/organizer for array of base class references
        Scanner Input = new Scanner(System.in);     //allows user to input to program
        int userOption = -1;        //integer used to store user input
        int userOption2 = -1;       //integer used to store user input
        DLL List = new DLL();       //doubly linked list object
        List.Load();                //creates the randomized combo pizza from text files

        //the following loop creates the "user interface"
        while(userOption != 0){
            System.out.println("\n\nWhat would you like to do?\n 1. Create Pizza\n 2. Display Order History\n 3. Retrieve Order\n 4. Cancel Order(Remove)\n 5. Delete Order History\n 0. Quit\n(Enter corresponding number): ");
            userOption = Input.nextInt();
            if(userOption == 1){            //user chooses to create a pizza
                System.out.println("\n\n");
                Order = new toppingList();
                sh = new Shape();
                sh.Prompt();            //create shape of pizza
                Order.Insert(sh);       //add to array of pizza ingredients/details
                co = new Content();
                co.Prompt();            //create content of pizza
                Order.Insert(co);       //add to array of pizza ingredients/details
                ex = new Extra();
                ex.Prompt();            //create topping for pizza
                Order.Insert(ex);       //add to array of pizza ingredients/details
                for(int i = 0; i < 2; ++i){     //user has the option to add two more toppings to the pizza
                    System.out.println("\nYou can add " + (2-i) + " more toppings to your Pizza.\n 1. Add more\n 2. Order Pizza\n(Enter corresponding number): ");
                    userOption2 = Input.nextInt();
                    if(userOption2 == 2)
                        break;
                    ex = new Extra();
                    ex.Prompt();            //user adds another topping
                    Order.Insert(ex);       //add to array of pizza ingredients/details
                }
                if(List.Insert(Order) == 0)     //check for failure/success
                    System.out.println("\nDLL Insert failed in main.");
                else
                    System.out.println("\nOrder has been made. Thank you.");

            }
            else if(userOption == 2){           //user chooses to display pizzas ordered already
                List.Display();
            }
            else if(userOption == 3){           //user chooses to retrieve a specific order from history
                Order = new toppingList();
                System.out.println("\nEnter the ID of the order you would like to retrieve: ");
                userOption2 = Input.nextInt();
                if(List.Retrieve(Order, userOption2) == 0)      //check for failure/success
                    System.out.println("\nOrder was not found.");
                else {
                    System.out.println("\nOrder was found:\n");
                    Order.Display();        //display what was found to user
                }
            }
            else if(userOption == 4){           //user chooses to cancel a specified order
                System.out.println("\nEnter the ID of the order you would like to cancel: ");
                userOption2 = Input.nextInt();
                if(List.Remove(userOption2) == 0)       //check for failure/success
                    System.out.println("\nOrder was not found.");
                else
                    System.out.println("\nOrder has been cancelled(removed).");
            }
            else if(userOption == 5){           //user chooses to remove all order history, for whatever reason
                List.removeAll();
                System.out.println("\nOrder history has been cleared.");
            }
            else if(userOption == 0){           //user chooses to quit program
                System.out.println("\nProgram will quit now.");
            }
            else            //user chose to not actually follow the instructions given to him/her
                System.out.println("\nPlease enter a valid option.");
            userOption2 = -1;
        }
    }
}
