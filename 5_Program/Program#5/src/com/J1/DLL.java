/*
 * Kobe Davis
 * Prof. Fant
 * CS 202
 * 2 June 2017
 */

package com.J1;

import java.io.File;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;
import java.util.Vector;

/**
 * The DLL class is the Doubly Linked List data structure. This class will manage the functionality of the list
 * (e.g. insert, remove, retrieve, etc.) and will manage the nodes holding the specified data.
 */

public class DLL {

    private dNode Head;     //beginning of list
    private dNode Tail;     //end of list

    DLL(){      //default constructor
        this.Head = null;
        this.Tail = null;
    }

    public void Display(){      //display function goes through list displaying data held in nodes
        if(this.Head == null){
            System.out.println("\nNothing to display.\n");      //list is empty so far
            return;
        }
        dNode Current = this.Head;
        while(Current != null){         //display data
            System.out.println("------------------------------------------------------------------------");
            Current.Display();
            Current = Current.getNext();
        }
    }

    public int Retrieve(toppingList copyTo, int ID){        //receives a container for storing what it finds and an integer to locate the correct order
        dNode Current = this.Head;                          //returns an integer to convey success and failure
        while(Current != null){         //search list of nodes/data
            if(Current.Equals(ID)) {    //if match is found
                copyTo.Copy(Current);   //then copy data to argument container
                return 1;
            }
            Current = Current.getNext();
        }
        return 0;
    }

    public int Remove(int ID){          //receives an integer to locate the correct order and remove it from list, returns an int to convey success and failure
        dNode Current = this.Head;
        while(Current != null){         //search through list for correct order
            if(Current.Equals(ID)){     //compare handed in ID
                if(this.Head == Current)                //everything below this is just linking up the list so no holes appear
                    this.Head = this.Head.getNext();
                if(Current.getPrevious() != null)
                    Current.getPrevious().setNext(Current.getNext());
                if(Current.getNext() != null)
                    Current.getNext().setPrevious(Current.getPrevious());
                Current = null;
                return 1;
            }
            Current = Current.getNext();
        }
        return 0;
    }

    public int Insert(toppingList toAdd){       //receives a toppingList class(organizer/manager for array of base class references) to add to the doubly linked list.
        if(toAdd == null)
            return 0;
        if(this.Head == null){              //if list has not yet been created (meaning this would be the first item)
            this.Head = new dNode(toAdd);   //node's copy constructor handling all the complicated stuff
            this.Tail = Head;       //setting tail of the list too
            return 1;
        }
        dNode Current = this.Head;
        this.Head = new dNode(toAdd);   //adding to front of list, who wants to see their oldest order first???
        Current.setPrevious(this.Head); //patching up list
        this.Head.setNext(Current);
        return 1;
    }

    public void removeAll(){    //throws list to the garbage collector by setting front and end of list to null
        this.Head = null;
        this.Tail = null;
    }

    /*
    Disgustingly long function, although read from file function often turn out like this.
    The Load function's purpose is to take the three text files: shLib.txt, conLib.txt, and exLib.txt, and extract Pizza related information from them.
    Each file contains different information (shape info, content info, topping info), therefore to properly randomize a combo pizza
    we have to know which parts to randomize, namely the three above, separately. Information from each file is read into a Vector
    separately (this means three different Vectors, one for each type of data) which will then be used with the Random object to select a random
    index in the Vector to ultimately create a fully randomized and pre-made combo pizza. Depending on if the user wants it, it may be inserted
    int the DLL.
     */
    public void Load(){

        File readFrom;       boolean Vegetarian;            //temporary variables used to store user input, they're exactly the same as the data members found in object oriented programming
        Scanner Read = null; String Line = null;
        double Price;        boolean Allergens;
        String Notes;        int Size = 0;
        String Method;       String Crust;
        String Cheese;       String Sauce;
        int Density;         String Topping;

        Vector<Shape> Store1 = new Vector<>();          //Vectors used to conveniently store information read from text files
        Vector<Content> Store2 = new Vector<>();
        Vector<Extra> Store3 = new Vector<>();

        //below is a try catch block encompassing all of the functionality because the File object has this issue where an IOException is thrown if the file isn't found.
        try{
            for(int i = 0; i < 3; ++i) {        //repeat three time to hit each text file
                if(i == 0) {
                    readFrom = new File ("src/com/J1/shLib");       //specify text to be read from
                    Read = new Scanner (readFrom);      //method for file input to program
                    Read.useDelimiter(":");             //set delimiter in text file data
                    while(Read.hasNext()){              //read in information while there is still information
                        Price = Read.nextDouble();      //set temp data
                        Allergens = Read.nextBoolean();
                        Notes = Read.next();
                        Size = Read.nextInt();
                        Method = Read.next();
                        Crust = Read.next();
                        Shape temp = new Shape(Price, Allergens, Notes, Size, Method, Crust);   //insert temp data into a temp Shape object
                        Store1.add(temp);       //add Shape object to Vector
                        Read.nextLine();
                    }
                }
                else if(i == 1) {
                    readFrom = new File ("src/com/J1/conLib");      //specify text to be read from
                    Read = new Scanner (readFrom);      //method for file input to program
                    Read.useDelimiter(":");             //set delimiter in text file data
                    while(Read.hasNextLine()){          //read in information while there is still information
                        Price = Read.nextDouble();      //set temp data
                        Allergens = Read.nextBoolean();
                        Notes = Read.next();
                        Cheese = Read.next();
                        Sauce = Read.next();
                        Content temp = new Content(Price, Allergens, Notes, Cheese, Sauce);     //insert temp data into a temp Shape object
                        Store2.add(temp);       //add Shape object to Vector
                        Read.nextLine();
                    }
                }
                else if(i == 2) {
                    readFrom = new File ("src/com/J1/exLib");       //specify text to be read from
                    Read = new Scanner (readFrom);      //method for file input to program
                    Read.useDelimiter(":");             //set delimiter in text file data
                    while(Read.hasNext()){              //read in information while there is still information
                        Price = Read.nextDouble();      //set temp data
                        Allergens = Read.nextBoolean();
                        Notes = Read.next();
                        Density = Read.nextInt();
                        Topping = Read.next();
                        Vegetarian = Read.nextBoolean();
                        Extra temp = new Extra(Price, Allergens, Notes, Density, Topping, Vegetarian);  //insert temp data into a temp Shape object
                        Store3.add(temp);        //add Shape object to Vector
                        Read.nextLine();
                    }
                }
                Read.close();   //close the last used file
            }
        }
        catch(IOException temp){    //if one of the files happen to have an error when
            if(Read!= null)
                Read.close();
            temp.printStackTrace();
        }

        Read = new Scanner(System.in);      //allows user input to program
        Random Index = new Random();        //allows creation of random numbers
        toppingList Combo = new toppingList();      //create container for array of base references
        Combo.Insert(Store1.get(Index.nextInt(Store1.size())));     //insert random pizza shape into toppingList
        Combo.Insert(Store2.get(Index.nextInt(Store2.size())));     //insert random pizza content into toppingList
        Combo.Insert(Store3.get(Index.nextInt(Store3.size())));     //insert random pizza topping into toppingList
        System.out.println("COMBO OF THE DAY!!!");
        Combo.Display();                                //display the combo pizza that was just created
        System.out.println("\nDo you want to order this combo?\n 1. Yes\n 2. No\n(Enter corresponding number): ");
        int Option = Read.nextInt();        //allow user to choose whether to order combo pizza
        if(Option == 1) {
            if (Insert(Combo) == 0)         //user chose to order combo pizza, insert into DLL
                System.out.println("Insert failed in DLL load function.");
            else
                System.out.println("Pizza has been ordered!\nThank you!");
        }
    }
}
