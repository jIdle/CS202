/*
 * Kobe Davis
 * Prof. Fant
 * CS 202
 * 8 June 2017
 */

/**
 * Pizzeria class's purpose is to hold all the pizzas for a particular Pizzeria, in essense its purpose is to literally act as a Pizzeria.
 * As any BST does, Pizzeria can Insert pizzas, Retrieve pizzas, Remove pizzas, etc. It's a giant organizer for Pizzas via the assignment requirements.
 * Pizzeria is the inner bst in this assignment. This means that it is a bst that is technically resting on the nodes of a much larger bst.
 * Also, Pizzeria is a parent class to iNode. In this way whenever a node is created in the outer tree(pizzeriaTree), a pizzeria is automatically created.
 */

package com.J1;
import java.util.Scanner;

public class Pizzeria {

    protected Scanner Input;        //user input
    protected iNode Root;           //node that holds data specific to a Pizza
    protected String Name;          //name of this pizzeria

    Pizzeria(){     //default constructor
        this.Input = new Scanner(System.in);
        this.Root = null;
        System.out.println("\nEnter name of Pizzeria:");    //naming the pizzeria when it gets created
        this.Name = Input.next();
    }
    Pizzeria(Pizzeria toCopy){      //copy constructor
        Scanner Input = new Scanner(System.in);
        this.Root = Copy(toCopy.Root);          //calling copy method to copy one inner tree into this one
        this.Name = toCopy.Name;
    }

    //this method takes another Pizzeria(inner tree) and compares its name to this one
    public int Compare(Pizzeria toCompare){
        if(this.Name.compareTo(toCompare.Name) > 0){    //using string's compareto method
            return -1;   //toCompare is smaller
        }
        else if(this.Name.compareTo(toCompare.Name) < 0){
            return 1;   //toCompare is larger
        }
        return 0;       //toCompare is equal
    }
    ////this method takes a String and compares it to this one's name
    public int Compare(String toCompare){
        if(this.Name.compareTo(toCompare) > 0){     //using string's compareto method
            return -1;   //toCompare is smaller
        }
        else if(this.Name.compareTo(toCompare) < 0){
            return 1;   //toCompare is larger
        }
        return 0;       //toCompare is equal
    }

    //shortdisplay only displays the name of calling pizzeria(inner tree), nothing else
    public void shortDisplay(){
        System.out.println("\nPizzeria name: " + this.Name);
        System.out.println();
    }

    //longdisplay displays all of the pizzas in the calling pizzeria, this is a more detailed display
    public int longDisplay(){
        if(this.Root == null)       //can't display anything, empty
            return 0;
        return longDisplay(this.Root);
    }
    //recursive longdisplay
    private int longDisplay(iNode Root){
        if(Root == null)
            return 0;
        int temp = longDisplay(Root.getLeft()) + 1;     //first recursive call
        Root.Display();                                 //actual display method
        return temp + longDisplay(Root.getRight());     //second recursive call

    }

    //wrapper insert method that takes a list of pizza ingredients and hands it off to the recursive insert method
    public int Insert(toppingList toAdd){
        if(this.Root == null){              //pizzeria had no pizzas yet
            this.Root = new iNode(toAdd);   //use copy constructor to add pizza
            return 1;
        }
        return Insert(this.Root, toAdd);    //kicks off recursive process
    }
    //recursive insert method for pizzeria, inserts pizzas
    private int Insert(iNode Root, toppingList toAdd){
        if(Root.Compare(toAdd) == -1){          //deciding which way to go in bst
            if(Root.getLeft() == null){         //doing a look ahead b/c java makes pointers a pain in the ass
                iNode temp = new iNode(toAdd);
                Root.setLeft(temp);
                return 1;
            }
            else
                return Insert(Root.getLeft(), toAdd);   //recursive call because we didn't find the correct place to insert
        }
        else if(Root.Compare(toAdd) == 1){      //deciding which way to go in bst
            if(Root.getRight() == null){        //doing a look ahead b/c java makes pointers a pain in the ass
                iNode temp = new iNode(toAdd);
                Root.setRight(temp);
                return 1;
            }
            else
                return Insert(Root.getRight(), toAdd);  //recursive call because we didn't find the correct place to insert
        }
        return 0;
    }

    //wrapper method for recursive remove method. takes a String and attempts to find a match and remove it using the recursive methods
    public int Remove(String toRemove){
        if(this.Root == null)       //check if empty bst
            return 0;
        if(this.Root.Compare(toRemove) == 0) {      //check if data to remove is root node
            this.Root = Remove(this.Root);
            return 1;
        }
        return Remove(this.Root, toRemove);     //kick off recursive process
    }
    private int Remove(iNode Root, String toRemove){    //recursive method to locate where the specified node is. not remove it
        int Direction = Root.Compare(toRemove);
        if(Direction == -1){            //go left
            if(Root.getLeft() == null)      //look ahead to avoid nullpointerexception
                return 0;
            if(Root.getLeft().Compare(toRemove) == 0){      //checking for match
                    Root.setLeft(Remove(Root.getLeft()));       //calling the actual node removal method
                return 1;
            }
            else
                return Remove(Root.getLeft(), toRemove);
        }
        else if(Direction == 1){           //go right
            if(Root.getRight() == null)     //look ahead to avoid nullpointerexception
                return 0;
            if(Root.getRight().Compare(toRemove) == 0){     //checking for match
                Root.setRight(Remove(Root.getRight()));     //calling the actual node removal method
                return 1;
            }
            else
                return Remove(Root.getRight(), toRemove);
        }
        return 0;   
    }
    private iNode Remove(iNode Root){       //this method ACTUALLY removes the node, the one before located it
        if(Root.getLeft() == null && Root.getRight() == null){      //leaf node
            return null;
        }
        else if(Root.getLeft() != null && Root.getRight() == null){     //has a right child
            return Root.getRight();
        }
        else if(Root.getLeft() == null && Root.getRight() != null){     //has a left child
            return Root.getLeft();
        }
        else{                       //has both children, have to find IOS for replacement
            Integer toggle = 0;     //a switch to let the IOS method know that it needs to set the IOS to null on the way out
            iNode IOS;              //temp node to hold IOS
            if(Root.getRight().getLeft() == null){      //case: the IOS is the immediate right child 
                IOS = Root.getRight();
                Root.setRight(null);
            }
            else                                        //case: the IOS is somewhere down the left path of the immediate right child
                IOS = IOS(Root, toggle);                //call IOS method to handle finding and returning it
            IOS.setRight(Root.getRight());              //set children and return for replacement
            IOS.setLeft(Root.getLeft());
            return IOS;
        }
    }
    private iNode IOS(iNode Root, Integer toggle){      //IOS method just finds the node-set-for-removal's inorder successor so the bst doesn't fail
        if(Root.getLeft() == null){     //IOS found
            return Root;
        }
        iNode retVal = IOS(Root.getLeft(), toggle);     //recursive call
        if(toggle == 0) {                               //remembering to set IOS position to null and replacing with right child
            retVal.setLeft(retVal.getLeft().getRight());
            toggle = 1;
        }
        return retVal;
    }

    //wrapper retrieve method receives a String and attempts to find a match in the inner bst by using a recursive method
    public toppingList Retrieve(String Name){ 
        if(this.Root == null)                   //is bst empty?
            return null;
        return Retrieve(this.Root, Name);       //kick off recursive process
    }
    private toppingList Retrieve(iNode Root, String Name){  //recursive retrieve method
        if(Root == null)    //base case
            return null;
        int Direction = Root.Compare(Name);     //deciding whether to go left or right depending on the toppingList Compare methods return val
        if(Direction == -1){                    //go left child path
            return Retrieve(Root.getLeft(), Name);  //recursive call
        }
        else if(Direction == 1){                //go right child path
            return Retrieve(Root.getRight(), Name); //recursive call
        }
        return new toppingList(Root);       //match found
    }

    //removeAll method simply sets root data member to null to deallocate the entire inner bst
    public void removeAll(){
        this.Root = null;
    }

    //copy method is called in copy constructor to copy one pizzeria(inner bst) to another
    private iNode Copy(iNode Root){
        if(Root == null){       //base case
            return null;
        }
        iNode temp = new iNode(Root);       //creating new node
        temp.setLeft(Copy(Root.getLeft())); //setting its left child
        temp.setRight(Copy(Root.getRight()));   //setting its right child
        return temp;
    }

}




























