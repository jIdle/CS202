/*
 * Kobe Davis
 * Prof. Fant
 * CS 202
 * 8 June 2017
 */

package com.J1;

/**
 * Extra class defines the overall toppings of the pizza, that means this excludes sections such as the outer part of the pizza and the inside of it.
 * Extra class is a sub class of the Instruction abstract base class.
 */

public class Extra extends Instruction {

    private int Density;        //how much of this topping do you want on the pizza?
    private String Topping;     //What kind of topping is it?
    private boolean Vegetarian; //Is it vegeatarian?

    Extra(){        //default constructor
        this.Density = 0;
        this.Topping = null;
        this.Vegetarian = false;
    }
    Extra(double Price, boolean Allergens, String Notes, int Density, String Topping, boolean Vegetarian){      //constructor with args
        super(Price, Allergens, Notes);
        this.Density = Density;
        this.Topping = new String(Topping);
        this.Vegetarian = Vegetarian;
    }
    Extra(Extra toCopy){        //copy constructor
        super(toCopy);
        this.Density = toCopy.Density;
        this.Topping = new String(toCopy.Topping);
        this.Vegetarian = false;
    }
    public void Prompt(){       //prompt function uses the Scanner object in Instruction to prompt the user to enter information for the Pizza
        System.out.println("Enter information about the topping: \n\n");
        super.Prompt();
        System.out.println("Enter any topping: ");
        this.Topping = new String(this.read.next());
        this.read.nextLine();
        System.out.println("Density:\n 1. Heavy\n 2. Standard\n 3. Light\n(Enter corresponding number): ");
        this.Density = this.read.nextInt();
        System.out.println("Is it vegetarian? (true or false): ");
        this.Vegetarian = this.read.nextBoolean();
        System.out.println("\n");
    }
    @Override   //function was implemented as abstract in super class
    public boolean Equals(Instruction toCompare){           //compares an Instruction reference to the calling Instruction reference
        if(toCompare == null)
            return false;
        Extra temp = (Extra) toCompare;         //downcast for valid comparison
        if(this.Price != temp.Price || this.Allergens != temp.Allergens || !this.Notes.equals(temp.Notes) || this.Density != temp.Density || !this.Topping.equals(temp.Topping) || this.Vegetarian != Vegetarian)
            return false;
        return true;
    }
    @Override   //function was implemented as abstract in super class
    public double Display(){        //display function souts all data members
        System.out.println("Toppings on Pizza:");
        System.out.println("\tAllergens: " + this.Allergens);
        System.out.println("\tNotes: " + this.Notes);
        System.out.println("\tDensity: " + this.Density);
        System.out.println("\tTopping: " + this.Topping);
        System.out.println("\tVegetarian: " + this.Vegetarian);
        System.out.println();
        return this.Price;
    }
    @Override   //function was implemented as abstract in super class
    public void Set(Instruction toCopy){           //setter function, sets data of calling Instruction reference to the data of handed-in Instruction reference
        Extra temp = (Extra) toCopy;            //downcast for valid assignment
        this.Price = temp.Price;
        this.Allergens = temp.Allergens;
        this.Notes = new String(temp.Notes);
        this.Density = temp.Density;
        this.Topping = new String(temp.Topping);
        this.Vegetarian = temp.Vegetarian;
    }
}
