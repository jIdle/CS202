/*
 * Kobe Davis
 * Prof. Fant
 * CS 202
 * 2 June 2017
 */

package com.J1;

/**
 * Content class defines the overall Content of the pizza, that means this excludes sections such as the outer part of the pizza and what's on top of it.
 * Content class is a sub class of the Instruction abstract base class.
 */

public class Content extends Instruction{

        String Cheese;      //what kind of cheese
        String Sauce;       //what kind of sauce

    Content(){  //default constructor
        this.Cheese = null;
        this.Sauce = null;
    }
    Content(double Price, boolean Allergens, String Notes, String Cheese, String Sauce){    //constructor with args
        super(Price, Allergens, Notes);
        this.Cheese = new String(Cheese);
        this.Sauce = new String(Sauce);
    }
    Content(Content toCopy){    //copy constructor
        super(toCopy);
        this.Cheese = new String(toCopy.Cheese);
        this.Sauce = new String(toCopy.Sauce);
    }
    public void Prompt(){       //prompt function uses the Scanner object in Instruction to prompt the user to enter information for the Pizza
        System.out.println("Enter information about the cheese and sauce of the pizza: \n\n");
        super.Prompt();
        System.out.println("Cheese: Mozzarella, Provolone Blend, or Parmesan Blend?: ");
        this.Cheese = new String(this.read.next());
        this.read.nextLine();
        System.out.println("Sauce: Marinara, Garlic Parmesan, Tomato?: ");
        this.Sauce = new String(this.read.next());
        this.read.nextLine();
        System.out.println("\n");
    }
    @Override   //function was implemented as abstract in super class
    public boolean Equals(Instruction toCompare){           //compares an Instruction reference to the calling Instruction reference
        if(toCompare == null)
            return false;
        Content temp = (Content) toCompare;         //downcast for valid comparison
        if(this.Price != temp.Price || this.Allergens != temp.Allergens || !this.Notes.equals(temp.Notes) || !this.Cheese.equals(temp.Cheese) || !this.Sauce.equals(temp.Sauce))
            return false;
        return true;
    }
    @Override   //function was implemented as abstract in super class
    public double Display(){            //display function souts all data members
        System.out.println("Content of Pizza:");
        System.out.println("\tAllergens: " + this.Allergens);
        System.out.println("\tNotes: " + this.Notes);
        System.out.println("\tCheese: " + this.Cheese);
        System.out.println("\tSauce: " + this.Sauce);
        System.out.println("\n");
        return this.Price;
    }
    @Override   //function was implemented as abstract in super class
    public void Set(Instruction toCopy){    //setter function, sets data of calling Instruction reference to the data of handed-in Instruction reference 
        Content temp = (Content) toCopy;    //downcast for valid assignment
        this.Price = temp.Price;
        this.Allergens = temp.Allergens;
        this.Notes = new String(temp.Notes);
        this.Cheese = new String(temp.Cheese);
        this.Sauce = new String(temp.Sauce);
    }
}
