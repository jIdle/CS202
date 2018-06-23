/*
 * Kobe Davis
 * Prof. Fant
 * CS 202
 * 8 June 2017
 */

/**
 * iNode is the node contained inside the inner tree(Pizzeria). Its purpose is to hold data related to specific pizzas.
 * iNode extends toppingList, so whenever an iNode is created, a list for poizza ingredients is created.
 */

package com.J1;

public class iNode extends toppingList {

    private iNode Left;     //left child node
    private iNode Right;    //right child node

    iNode(){    //default constructor
        this.Left = null;
        this.Right = null;
    }
    iNode(toppingList toCopy){  //constructor with args, kind of copy constructor thought b/c toppingList is actually an iNode
        super(toCopy);          //calling copy constructor of super class toppingList
        this.Left = null;
        this.Right = null;
    }
    iNode(iNode toCopy){    //copy constructor
        super(toCopy);      //calling super class copy constructor
        this.Left = null;
        this.Right = null;
    }
    public iNode getLeft(){
        return this.Left;
    }       //getter for left child node
    public iNode getRight(){
        return this.Right;
    }      //getter for right child node
    public void setLeft(iNode toAssign){
        this.Left = toAssign;
    }   //setter for left child node
    public void setRight(iNode toAssign){
        this.Right = toAssign;
    }   //setter for right child node
}
