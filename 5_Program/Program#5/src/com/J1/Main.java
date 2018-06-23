/*
 * Kobe Davis
 * Prof. Fant
 * CS 202
 * 8 June 2017
 */

/**
 *The purpose of this assignment is to experience implementation of personal Object Oriented solutions in
 * Java for a Pizza ordering and Pizzeria organizing program. The goal is to create the Object Oriented
 * section of programming separate from the data structure. The data structures we are expected to create are:
 * 1. An array of base class pointers.
 * 2. A Binary Search Tree of Binary Search Trees
 */

package com.J1;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        Instruction sh;     //temp base class reference for storing shape of pizza
        Instruction co;     //temp base class reference for storing content of pizza
        Instruction ex;     //temp base class reference for storing toppings of pizza
        toppingList Order;  //class that acts as a manager/organizer for array of base class references
        DLL List = new DLL();       //doubly linked list object
        Scanner Input = new Scanner(System.in);     //allows user to input to program
        Pizzeria iTree;
        pizzeriaTree oTree = new pizzeriaTree();
        int userOption = -1;        //integer used to store user input
        int userOption2 = -1;       //integer used to store user input
        int userOption3 = -1;       //integer used to store user input

        //the following loop creates the "user interface"
        while(userOption != 0)
        {
            userOption = -1;        //making sure user input doesn't mess up a loop
            userOption2 = -1;
            userOption3 = -1;

            System.out.println("\n\nWhat would you like to do?\n 1. Create Pizzeria\n 2. Display Pizzerias\n 3. Retrieve Specific Pizzeria\n 4. Remove Pizzeria\n 5. Remove All Pizzerias\n 0. Quit\n(Enter corresponding number): ");
            userOption = Input.nextInt();
            if(userOption == 1)     //user chooses to create pizzeria
            {
                iTree = new Pizzeria();
                if(oTree.Insert(iTree) == 0)
                    System.out.println("\noTree Insert returned 0 in main.");
            }
            else if(userOption == 2)        //user chooses to display pizzerias
            {
                if(oTree.Display() == 0)
                    System.out.println("\noTree Display returned 0 in main.");
            }
            else if(userOption == 3)        //user chooses to retrieve/work with a specific pizzeria
            {
                System.out.println("\nEnter the name of the Pizzeria you would like to view:");
                String temp = Input.next();
                iTree = oTree.Retrieve(temp);
                if(iTree == null)
                    System.out.println("\noTree Retrieve returned null in main.");
                else
                    while(userOption3 != 0){
                        System.out.println("\n\nWhat would you like to do with this Pizzeria?\n 1. Create Pizza\n 2. Display Pizzas\n 3. Retrieve Pizza\n 4. Remove Pizza\n 5. Remove All Pizzas\n 0. Go back\n(Enter corresponding number): ");
                        userOption3 = Input.nextInt();
                        if(userOption3 == 1){            //user chooses to create a pizza
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
                                System.out.println("\nYou can add " + (2-i) + " more toppings to your Pizza.\n 1. Add more\n 2. Finish creating pizza\n(Enter corresponding number): ");
                                userOption2 = Input.nextInt();
                                if(userOption2 == 2)
                                    break;
                                ex = new Extra();
                                ex.Prompt();            //user adds another topping
                                Order.Insert(ex);       //add to array of pizza ingredients/details
                            }
                            if(iTree.Insert(Order) == 0)     //check for failure/success
                                System.out.println("\niTree Insert failed in main.");
                            else
                                System.out.println("\nPizza has been created");

                        }
                        else if(userOption3 == 2){           //user chooses to display pizzas ordered already
                            iTree.longDisplay();
                        }
                        else if(userOption3 == 3){           //user chooses to retrieve a specific order from history
                            System.out.println("\nEnter the name of the Pizza you would like to retrieve: ");
                            String t = Input.next();
                            Order = iTree.Retrieve(t);
                            if(Order == null)      //check for failure/success
                                System.out.println("\nPizza was not found.");
                            else {
                                System.out.println("\nPizza was found:\n");
                                Order.Display();        //display what was found to user
                            }
                        }
                        else if(userOption3 == 4){           //user chooses to cancel a specified order
                            System.out.println("\nEnter the name of the Pizza you would like to remove: ");
                            String ui = Input.next();
                            if(iTree.Remove(ui) == 0)       //check for failure/success
                                System.out.println("\nPizza was not found.");
                            else
                                System.out.println("\nPizza has been removed.");
                        }
                        else if(userOption3 == 5){           //user chooses to remove all order history, for whatever reason
                            iTree.removeAll();
                            System.out.println("\nPizzas have been cleared.");
                        }
                        else if(userOption3 == 0){           //user chooses to quit program
                            System.out.println("\nReturning to previous menu.");
                        }
                        else            //user chose to not actually follow the instructions given to him/her
                            System.out.println("\nPlease enter a valid option.");
                    }
            }
            else if(userOption == 4)    //user chooses to remove a specific pizzeria
            {
                System.out.println("\nEnter the name of the Pizzeria you would like to remove:");
                String temp = Input.next();
                if(oTree.Remove(temp) == 0)
                    System.out.println("\noTree Remove returned 0 in main.");
            }
            else if(userOption == 5)        //user chooses to remove all pizzerias
            {
                System.out.println("\nDeleting ALL Pizzerias");
                oTree.removeAll();
            }
            else if(userOption == 0)        //user chooses to exit program
            {
                System.out.println("\nExiting program.");
            }
            else        //user didn't follow instructions
                System.out.println("\nPlease enter a valid option.");
        }
    }
}
