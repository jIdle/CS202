//Kobe Davis
//Prof. Fant
//CS202
//April 24, 2017
//This will be the header file for the graph class, vertex class, and the edge class.

#include "player.h"

//vertex class is used a part of the graph data structure.
//each vertex will represent a "checkpoint" that players can move to each turn.
//the vertex class is a derived class from location. this is useful because vertices have loccations
//or at the least information about their whereabouts, such as the index inside the array of vertices 
//that a vertex might be in, or even a name so that players can more easily recognize which "checkpoints"
//they've been to before.
class vertex: public location
{
    public:
        //default constructor
        vertex();
        //destructor
        ~vertex();
        //getter for edge pointer head which returns by reference. the edges represent the paths to and from each vertex.
        class edge *& to_head();
        //getter for the vertices' index for the vertex array held inside the location base class
        int to_index();
        //setter for a "path" from this vertex. set_head function receives an edge pointer which will be used to connect two vertices together
        void set_head(edge * add_head); 
        //used to limit the number of paths from any particular vertex
        int edgelist;
    private:
        //pointer to the head of the edge list which contains the paths away from this vertex
        class edge * head;
};

//edge class represent that paths leading between vertices in this maze program. 
//when a player chooses to travel from one "checkpoint" to another, they are making use of the edge class because they were able to reach the next vertex succesfully
class edge
{
    public:
        //default constructor
        edge();
        //destructor
        ~edge();
        //getter for the adjacent vertex or, in other words, the vertex that is connecting the one that the player came from.
        vertex *& to_adjacent();
        //getter for the next edge in the edge list. this is used to traverse and edgelist either when displaying paths, searching for paths, or anything that involves the "next" edge in a list.
        edge *& to_next();
        //setter for the connecting vertex, set_adjacent receives a vertex pointer as an argument. this function will then connect the curren edge to the specified vertex
        void set_adjacent(vertex * add_adjacent); 
        //setter for the next edge in the edge list. receives an edge pointer to accomplish this goal.
        void set_next(edge * add_next); 

    private:
        //adjacent is a vertex pointer, it is used by the above functions to make connected to other vertices
        vertex * adjacent;
        //similar to the above datatype, this edge pointer is used to make connecting to other edges.
        edge * next;
};

//graph class is what manages the graph data structure as a whole. both vertex and edge class are made use of by functions in the class to succesfully create a working graph.
//one of the special goals of this class is to create a maze that is different every time it is created.
//this means that the maze is randomly generated. to accomplish this, the graph class uses the generate graph function.
class graph
{
    public:
        //default constructor
        graph();
        //destructor
        ~graph();
        //generate_graph function returns nothing and receives nothing. its primary purpose is to use the vertex pointer data member below to create a randomly generated maze.
        void generate_graph();
        //insert_edge function takes two integers which correspond to the indices of vertices. the function will takes those integers, search the vertex array for the vertices
        //in those specified indices, and then connect them using an edge datatype.
        void insert_edge(int edge_from, int edge_to);
        //display_adjacent function receives an integer which it uses to determine which vertex it should look at the adjacents of.
        //specifically, it uses that integer to search for the correct vertex in the vertex array and then traverse its edgelist displaying the name of the vertices
        //that each edge connects to.
        void display_adjacent(int index);
        //getter for the specified vertex. vertex is specified by the integer argument in this function. 
        //to_vertex takes this integer and searches the vertex array for the vertex in this index. when it is found, the vertex will be returned by reference.
        vertex & to_vertex(int index);
        //check_valid function's purpose is to decide whether or not the user is choosing to move down an available path. if the integer combination handed as an argument 
        //is found not to represent a connection between two vertices, then a 0 is returned. otherwise a 1 is returned.
        int check_valid(int from, int destination);
        //duplicate_check is used to aid the generate graph function in creating a graph that follows the rules specified in the assignment page.
        //specifically, this function ensures that no connections between vertices are made twice, which would be pointless in a maze.
        //this is accomplished receiving the head of an edge list and the vertex index that is attempting to connect. if this integer is already found in the edge list
        //the attemp is denied at connection and a 0 is returned, otherwise a 1 is returned.
        int duplicate_check(edge * current, int to_check);
        //getter function for the array size data member
        int get_size();
    private:
        //keeps track of the size of the array allocated for the vertices
        int array_size;
        //vertex pointer adjacency_list is used to create an array of vertices which are connected by LLL of edges.
        //this will represent the "maze" that the players will navigate through.
        vertex * adjacency_list;
};
