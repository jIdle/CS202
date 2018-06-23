/*
 * Kobe Davis
 * Prof. Fant
 * CS 202
 * 2 June 2017
 */

package com.J1;

/**
 * dNode class is just node being used by the doubly linked list. The special part about it is that it is a sub class of toppingList.
 * This allows for the dNode class to not have to worry about using wrapper functions or being the middleman too much for the DLL class
 * and the data. dNode can just be a node, and when data access is necessary it can call the functions of toppingList to complete this
 * goal. On top of this, a node would never be without data, this works perfectly because whenever a dNode object is created we now
 * automatically have a toppingList also.
 */

public class dNode extends toppingList {

    private dNode Next;         //reference(pointer) to next node in doubly linked list
    private dNode Previous;     //reference(pointer) to previous node in doubly linked list

    dNode(){    //default constructor
        this.Next = null;
        this.Previous = null;
    }
    dNode(toppingList toCreate){    //constructor with args
        super(toCreate);    //call super class copy constructor to set data
        this.Next = null;
        this.Previous = null;
    }
    dNode(dNode toCopy){    //copy constructor
        super(toCopy);      //call super class copy constructor to set data (this works because a dNode is actually just a toppingList)
        this.Next = null;
        this.Previous = null;
    }
    public void setNext(dNode toSet){   //setter function for previous data member
        this.Next = toSet;
    }
    public void setPrevious(dNode toSet){   //setter function for next data member
        this.Previous = toSet;
    }
    public dNode getNext(){     //getter function for next data member
        return this.Next;
    }
    public dNode getPrevious(){     //getter function for previous data member
        return this.Previous;
    }
}
