/*
 * Kobe Davis
 * Prof. Fant
 * CS 202
 * 8 June 2017
 */

/**
 * pizzeriaTree is the outer bst in this assignment. This means that within pizzeriaTree there are nodes(oNode) that hold data
 * by extending it. oNodes are a sub class of the inner bst(Pizzeria), this means that for each node that the outer bst has,
 * there is one inner bst(Pizzeria). Each Pizzeria is a bst(inner one) that has many nodes(iNode) which extend data. iNode holds
 * the data of each individual pizza by being a sub class of toppingList. For each iNode, a toppingList is created.
 */

package com.J1;

public class pizzeriaTree {

    private oNode Root;     //root node of outer bst

    pizzeriaTree(){     //default constructor
        this.Root = null;
    }
    pizzeriaTree(pizzeriaTree toCopy){      //copy constructor
        this.Root = Copy(toCopy.Root);
    }
    public int Display(){       //wrapper for recursive display function
        if(Root == null)
            return 0;
        return Display(this.Root);
    }
    private int Display(oNode Root){    //recursive display function
        if(Root == null)
            return 0;
        int temp = Display(Root.getLeft()) + 1;     //recursive call
        Root.shortDisplay();                        //displaying pizzeria names
        return temp + Display(Root.getRight());     //recursive call and return
    }

    //displayAll not only displays the names of the pizzerias but also all of their pizzas, this is a pretty lengthy display
    public int displayAll(){    //wrapper function for recursive display
        if(Root == null)
            return 0;
        return displayAll(this.Root);       //kicks off recursion
    }
    private int displayAll(oNode Root){     //recursive display
        if(Root == null)
            return 0;
        int temp = Display(Root.getLeft()) + 1;     //recursive call
        Root.longDisplay();
        return temp + Display(Root.getRight());     //recursive call
    }

    public int Insert(Pizzeria toAdd){ //wrapper insert function for recursive insert below
        if(this.Root == null){          //empty bst?
            this.Root = new oNode(toAdd);
            return 1;
        }
        return Insert(this.Root, toAdd);       //kick off recursion
    }
    private int Insert(oNode Root, Pizzeria toAdd){     //recursive insert
        if(Root.Compare(toAdd) == -1){      //go left
            if(Root.getLeft() == null){     //check for nullpointerexception
                oNode temp = new oNode(toAdd);
                Root.setLeft(temp);
                return 1;
            }
            else
                return Insert(Root.getLeft(), toAdd);   //recursive call
        }
        else if(Root.Compare(toAdd) == 1){      //go right
            if(Root.getRight() == null){       //check for nullpointerexception
                oNode temp = new oNode(toAdd);
                Root.setRight(temp);
                return 1;
            }
            else
                return Insert(Root.getRight(), toAdd);      //recursive call
        }
        return 0;
    }

    //wrapper method for recursive remove method. takes a String and attempts to find a match and remove it using the recursive methods
    public int Remove(String toRemove){
        if(this.Root == null)        //check if empty bst
            return 0;
        if(this.Root.Compare(toRemove) == 0) {      //check if data to remove is root node
            this.Root = Remove(this.Root);
            return 1;
        }
        return Remove(this.Root, toRemove);     //kick off recursive process
    }
    private int Remove(oNode Root, String toRemove){    //recursive method to locate where the specified node is. not remove it
        int Direction = Root.Compare(toRemove);
        if(Direction == -1){                    //go left
            if(Root.getLeft() == null)          //look ahead to avoid nullpointerexception
                return 0;
            if(Root.getLeft().Compare(toRemove) == 0){      //checking for match
                Root.setLeft(Remove(Root.getLeft()));       //calling the actual node removal method
                return 1;
            }
            else
                return Remove(Root.getLeft(), toRemove);
        }
        else if(Direction == 1){                    //go right
            if(Root.getRight() == null)             //look ahead to avoid nullpointerexception
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
    private oNode Remove(oNode Root){           //this method ACTUALLY removes the node, the one before located it
        if(Root.getLeft() == null && Root.getRight() == null){  //leaf node
            return null;
        }
        else if(Root.getLeft() != null && Root.getRight() == null){     //has a right child
            return Root.getRight();
        }
        else if(Root.getLeft() == null && Root.getRight() != null){     //has a left child
            return Root.getLeft();
        }
        else{                               //has both children, have to find IOS for replacement
            Integer toggle = 0;             //a switch to let the IOS method know that it needs to set the IOS to null on the way out
            oNode IOS;                      //temp node to hold IOS
            if(Root.getRight().getLeft() == null){      //case: the IOS is the immediate right child
                IOS = Root.getRight();
                Root.setRight(null);
            }
            else
                IOS = IOS(Root, toggle);        //case: the IOS is somewhere down the left path of the immediate right child
            IOS.setRight(Root.getRight());      //call IOS method to handle finding and returning it
            IOS.setLeft(Root.getLeft());        //set children and return for replacement
            return IOS;
        }
    }
    private oNode IOS(oNode Root, Integer toggle){  //IOS method just finds the node-set-for-removal's inorder successor so the bst doesn't fail
        if(Root.getLeft() == null){         //IOS found
            return Root;
        }
        oNode retVal = IOS(Root.getLeft(), toggle);     //recursive call
        if(toggle == 0) {                            //remembering to set IOS position to null and replacing with right child
            retVal.setLeft(retVal.getLeft().getRight());
            toggle = 1;
        }
        return retVal;
    }
    //wrapper retrieve method receives a String and attempts to find a match in the inner bst by using a recursive method
    public Pizzeria Retrieve(String Name){
        if(this.Root == null)           //is bst empty?
            return null;
        return Retrieve(this.Root, Name);       //kick off recursive process
    }
    private Pizzeria Retrieve(oNode Root, String Name){     //recursive retrieve method
        if(Root == null)                //base case
            return null;
        int Direction = Root.Compare(Name);         //deciding whether to go left or right depending on the toppingList Compare methods return val
        if(Direction == -1){                    //go left child path
            return Retrieve(Root.getLeft(), Name);      //recursive call
        }
        else if(Direction == 1){                //go right child path
            return Retrieve(Root.getRight(), Name);     //recursive call
        }
        return Root;        //match found
    }

    //removeAll method simply sets root data member to null to deallocate the entire inner bst
    public void removeAll(){
        this.Root = null;
    }

    //copy method is called in copy constructor to copy one pizzeria(inner bst) to another
    private oNode Copy(oNode Root){
        if(Root == null){   //base case
            return null;
        }
        oNode temp = new oNode(Root);       //creating new node
        temp.setLeft(Copy(Root.getLeft())); //setting its left child
        temp.setRight(Copy(Root.getRight()));   //setting its right child
        return temp;
    }

}
