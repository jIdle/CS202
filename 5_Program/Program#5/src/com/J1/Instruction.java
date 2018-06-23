/*
 * Kobe Davis
 * Prof. Fant
 * CS 202
 * 8 June 2017
 */

package com.J1;
import java.util.Scanner;

/**
 * Abstract Base class for Object Oriented Programming. Instruction is used as an umbrella over Shape, Content, and Extra sub classes.
 * Instruction will be used inside an array in toppingList. The purpose of Instruction is to be able to point to many different
 * aspects/parts of a pizza and be stored in a single data structure.
 */

abstract public class Instruction {

    protected Scanner read = null;      //allows user input
    protected double Price;             //price of ingredient
    protected boolean Allergens;        //whether the ingredient has allergens
    protected String Notes;             //extra instructions on making pizza

    Instruction(){      //default constructor
        this.read = new Scanner(System.in);
        this.Price = 0;
        this.Allergens = false;
        this.Notes = null;
    }
    Instruction(double Price, boolean Allergens, String Notes){     //constructor with args
        this.read = new Scanner(System.in);
        this.Price = Price;
        this.Allergens = Allergens;
        this.Notes = new String(Notes);
    }
    Instruction(Instruction toCopy){        //copy constructor
        this.read = new Scanner(System.in);
        this.Price = toCopy.Price;
        this.Allergens = toCopy.Allergens;
        this.Notes = new String(toCopy.Notes);
    }
    public void Prompt(){                   //prompt function uses the Scanner object to prompt the user to enter information for the Pizza
        System.out.println("Price: ");
        this.Price = this.read.nextDouble();
        System.out.println("Does it contain Allergens? (true or false): ");
        this.Allergens = this.read.nextBoolean();
        System.out.println("Extra instructions: ");
        this.Notes = this.read.next();
        this.read.nextLine();
    }
    abstract public boolean Equals(Instruction toCompare);   //abstract function, expected to be implemented in every sub class, Equals compares two Instructions and returns a boolean depending on if they are the same.
    abstract public double Display();                        //abstract function, expected to be implemented in every sub class, Display function displays all data members to console
    abstract public void Set(Instruction toCopy);            //abstract function, expected to be implemented in every sub class, simply a Setter function that receives an Instruction object to copy.
}
