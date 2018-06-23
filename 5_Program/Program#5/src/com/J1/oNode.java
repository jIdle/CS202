/*
 * Kobe Davis
 * Prof. Fant
 * CS 202
 * 8 June 2017
 */

/**
 * oNode is the node used to hold data in the outer bst(pizzeriaTree). oNode holds this data by extending Pizzeria(inner tree).
 * This means that for each oNode, there is also another inner bst(Pizzeria).
 */

package com.J1;

public class oNode extends Pizzeria {

    private oNode Left;     //left child node
    private oNode Right;    //right child node

    oNode(){    //default constructor
        this.Left = null;
        this.Right = null;
        this.Name = null;
    }
    oNode(Pizzeria toCopy){     //constructor with args but actually kinda copy constructor b/c pizzeria is actually and oNode
        super(toCopy);          //calling super class copy constructor
        this.Left = null;
        this.Right = null;
        this.Name = toCopy.Name;
    }
    oNode(oNode toCopy){        //copy constructor
        super(toCopy);          //calling super class copy constructor
        this.Left = null;
        this.Right = null;
        this.Name = toCopy.Name;
    }

    public oNode getLeft(){
        return this.Left;
    }       //getter for left child node
    public oNode getRight(){
        return this.Right;
    }       //getter for right child node
    public void setLeft(oNode toAssign){
        this.Left = toAssign;
    }       //setter for left child node
    public void setRight(oNode toAssign){
        this.Right = toAssign;
    }       //setter for right child node
}
