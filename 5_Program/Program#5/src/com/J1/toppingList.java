/*
 * Kobe Davis
 * Prof. Fant
 * CS 202
 * 8 June 2017
 */

package com.J1;
import java.util.Random;
import java.util.Scanner;

/*
 * toppingList class isn't just a container for the array of base references, it manages:
 * 1. Organization of pizza details
 * 2. Insertion of pizza details
 * 3. Removal of pizza details
 * 4. Comparison of pizza details
 * And onwards, toppingList is extremely useful. It doesn't stop at that though, because we have a class encasing the array of base references,
 * we are able to have toppingList be a base class of the Node. This means that each node can be node and not have to worry about wrapper
 * functions to deal with the data, but instead has full access to toppingList functionality when it needs it.
 */

public class toppingList {

    protected Instruction[] Details;       //array of base class references]
    protected String Name;
    protected int ID;                       //just a number used to tell one order apart from another
    protected int Top;                      //keeps track of the number of items in the array

    toppingList(){      //default constructor
        Scanner Input = new Scanner(System.in);
        System.out.println("\nGive a name to this Pizza:");
        this.Name = Input.next();
        Random temp = new Random();     //Random object used to randomize the order ID
        this.Details = new Instruction[5];      //allocate the base reference array to size 5
        this.ID = temp.nextInt(100000); //set order id
        this.Top = 0;
    }

    toppingList(toppingList toAssign){      //copy constructor
        this.Name = toAssign.Name;
        this.ID = toAssign.ID;              //copy over data members
        this.Top = toAssign.Top;
        this.Details = new Instruction[5];

        for(int i = 0; i < 5; ++i){         //copy the base reference array
            if(toAssign.Details[i] == null)
                this.Details[i] = null;
            else{
                if(toAssign.Details[i] instanceof Shape) {      //the three next if statements are essentially RTTI
                    Shape temp = (Shape) toAssign.Details[i];   //downcast
                    this.Details[i] = new Shape(temp);          //copy data
                }
                if(toAssign.Details[i] instanceof Content) {
                    Content temp = (Content) toAssign.Details[i];
                    this.Details[i] = new Content(temp);
                }
                if(toAssign.Details[i] instanceof Extra) {
                    Extra temp = (Extra) toAssign.Details[i];
                    this.Details[i] = new Extra(temp);
                }
            }
        }
    }

    public boolean Equals(toppingList toCompare){       //compares the order ID's between two toppingLists
        return (this.ID == toCompare.ID);
    }
    public boolean Equals(int toCompare){
        //compares the order ID's between a toppingList and an integer
        return (this.ID == toCompare);
    }

    public int Compare(toppingList toCompare){
        if(this.Name.compareTo(toCompare.Name) > 0){
           return -1;   //toCompare is smaller
        }
        else if(this.Name.compareTo(toCompare.Name) < 0){
            return 1;   //toCompare is larger
        }
        return 0;       //toCompare is equal
    }

    public int Compare(String toCompare){
        if(this.Name.compareTo(toCompare) > 0){
            return -1;   //toCompare is smaller
        }
        else if(this.Name.compareTo(toCompare) < 0){
            return 1;   //toCompare is larger
        }
        return 0;       //toCompare is equal
    }

    public void Copy(toppingList toAssign){     //copy function receives a toppingList as an argument to copy. Almost identical to the copy constructor.
        this.Name = toAssign.Name;
        this.ID = toAssign.ID;
        this.Top = toAssign.Top;
        this.Details = new Instruction[5];

        for(int i = 0; i < 5; ++i){
            if(toAssign.Details[i] == null)
                this.Details[i] = null;
            else{
                if(toAssign.Details[i] instanceof Shape) {      //RTTI, kind of, with new cool instanceof syntax, just like copy constructor
                    Shape temp = (Shape) toAssign.Details[i];
                    this.Details[i] = new Shape(temp);
                }
                if(toAssign.Details[i] instanceof Content) {
                    Content temp = (Content) toAssign.Details[i];
                    this.Details[i] = new Content(temp);
                }
                if(toAssign.Details[i] instanceof Extra) {
                    Extra temp = (Extra) toAssign.Details[i];
                    this.Details[i] = new Extra(temp);
                }
            }
        }
    }

    public void Display(){              //displays all data in toppingList, which means the ID and the individual data in the array slots
        if(this.Details == null)
            return;
        double totalPrice = 0;          //temp variable used for calculating the total price of all the pizza ingredients
        System.out.println("\nPizza name: " + this.Name);
        System.out.println("Order ID: " + this.ID);     //display order number/ID
        System.out.println();
        for(int i = 0; i < 5; ++i) {            //display the base class references / call the display functions in those classes
            if (this.Details[i] != null)
                totalPrice += this.Details[i].Display();
        }
        System.out.println("Total Price:  $" + totalPrice);     //display total price
        System.out.println("\n");
    }

    public boolean Remove(int userOption){      //remove a specified ingredient in the array of base class references, could be for user mistake
        int Index = userOption - 1;
        if(Index < 0 || Index > 4 || this.Details[Index] == null)       //stops the user from entering an invalid choice for removal
            return false;
        this.Details[Index] = null;     //if nothing is entered for the specific ingredient
        return true;
    }

    public boolean Insert(Instruction toAdd){       //Insert function returns a boolean to convery success and failure, it also receives an Instruction obj (base class reference) to add to the array
        if(this.Top == 5)                           //Pizza might be filled with toppings, nothing more can be inserted
            return false;
        if(toAdd instanceof Shape) {                //check for valid downcast
            Shape temp = (Shape) toAdd;
            this.Details[Top] = new Shape(temp);    //add to array
        }
        if(toAdd instanceof Content) {              //check for valid downcast
            Content temp = (Content) toAdd;
            this.Details[Top] = new Content(temp);  //add to array
        }
        if(toAdd instanceof Extra) {                //check for valid downcast
            Extra temp = (Extra) toAdd;
            this.Details[Top] = new Extra(temp);    //add to array
        }
        ++this.Top;     //increment the top of the array
        return true;
    }
}





















