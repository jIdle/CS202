/*
 * Kobe Davis
 * Prof. Fant
 * CS 202
 * 2 June 2017
 */

package com.J1;

/**
 * Shape class defines the overall shape of the pizza, that means this excludes sections such as the inner part of the pizza and what's on top of it.
 * Shape class is a sub class of the Instruction abstract base class.
 */

public class Shape extends Instruction {

    private int Size;           //how big the pizza is
    private String Method;      //How should it be cooked
    private String Crust;       //what is the consistency and density of the crust

    Shape(){    //default constructor
        this.Size = 0;
        this.Method = null;
        this.Crust = null;
    }
    Shape(double Price, boolean Allergens, String Notes, int Size, String Method, String Crust){    //cosntructor with args
        super(Price, Allergens, Notes);
        this.Size = Size;
        this.Method = new String(Method);
        this.Crust = new String(Crust);
    }
    Shape(Shape toCopy){    //copy constructor
        super(toCopy);
        this.Size = toCopy.Size;
        this.Method = new String(toCopy.Method);
        this.Crust = new String(toCopy.Crust);
    }
    public void Prompt(){       //prompt function uses the Scanner object in Instruction to prompt the user to enter information for the Pizza
        System.out.println("Enter information about the crust/cooking style of the pizza: \n\n");
        super.Prompt();
        System.out.println("Pizza size:\n 1. Small\n 2. Medium\n 3. Large\n(Enter corresponding number): ");
        this.Size = this.read.nextInt();
        System.out.println("Style: Standard, Handmade-Pan, or Brooklyn?: ");
        this.Method = new String(this.read.next());
        this.read.nextLine();
        System.out.println("Crust: Standard, Thin & Crunchy, or Gluten Free?: ");
        this.Crust = new String(this.read.next());
        this.read.nextLine();
        System.out.println("\n");
    }
    @Override   //function was implemented as abstract in super class
    public boolean Equals(Instruction toCompare){   //compares an Instruction reference to the calling Instruction reference
        if(toCompare == null)
            return false;
        Shape temp = (Shape) toCompare;     //downcast for valid comparison
        if(this.Price != temp.Price || this.Allergens != temp.Allergens || !this.Notes.equals(temp.Notes) || this.Size != temp.Size || !this.Method.equals(temp.Method) || !this.Crust.equals(temp.Crust))
           return false;
        return true;
    }
    @Override   //function was implemented as abstract in super class
    public double Display(){        //display function souts all data members
        System.out.println("Body of Pizza:");
        System.out.println("\tAllergens: " + this.Allergens);
        System.out.println("\tNotes: " + this.Notes);
        System.out.println("\tSize: " + this.Size);
        System.out.println("\tMethod: " + this.Method);
        System.out.println("\tCrust: " + this.Crust);
        System.out.println("\n");
        return this.Price;
    }
    @Override   //function was implemented as abstract in super class
    public void Set(Instruction toCopy){    //setter function, sets data of calling Instruction reference to the data of handed-in Instruction reference
        Shape temp = (Shape) toCopy;        //downcast for valid assignment
        this.Price = temp.Price;
        this.Allergens = temp.Allergens;
        this.Notes = new String(temp.Notes);
        this.Size = temp.Size;
        this.Method = new String(temp.Method);
        this.Crust = new String(temp.Crust);
    }
}
