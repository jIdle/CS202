//Kobe Davis
//Prof. Fant
//CS202
//April 24, 2017
//This file will hold the functions the the graph class in graph.h file.

#include "graph.h"

using namespace std;

//default constructor for the vertex class
vertex::vertex():edgelist(3), head(NULL)
{
}

//destructor for the vertex class
vertex::~vertex()
{
    head = NULL;
    edgelist = 0;
}

//getter for head of edge list for the vertex class
edge *& vertex::to_head()
{
    return head;
}

//setter for head of egde list for vertex class
void vertex::set_head(edge * add_head)
{
    head = add_head;
}

//getter for array index of any particular vertex
int vertex::to_index()
{
    return v_index;
}

//default constructor for edge class
edge::edge():adjacent(NULL), next(NULL)
{
}

//destructor for edge class
edge::~edge()
{
    adjacent = NULL;
    next = NULL;
}

//getter for vertex pointer adjacent in edge class
vertex *& edge::to_adjacent()
{
    return adjacent;
}

//getter for edge pointer next in edge class
edge *& edge::to_next()
{
    return next;
}

//setter for vertex pointer adjacent in edge class
//receives a vertex pointer as arg
void edge::set_adjacent(vertex * add_adjacent)
{
    adjacent = add_adjacent;
}

//setter for edge pointer next in edge class
//receives an edge pointer as arg
void edge::set_next(edge * add_next)
{
    next = add_next;
}

//default constructor for graph class
graph::graph():array_size(0), adjacency_list(NULL)
{
    generate_graph();//the random generation of the maze/graph happens within this function, because it is the first thing that must be done it is called inside the constructor.
}

//destructor for the graph class
graph::~graph()
{
    array_size = 0;
    //deallocate vertex array

    edge * current = NULL;
    edge * temp = NULL;
    for(int i = 0; i < array_size; ++i)
    {
        current = adjacency_list[i].to_head();
        temp = current->to_next();
        while(current)
        {
            delete current;
            if(temp)
            {
                current = temp;
                temp = temp->to_next();
            }
            else
            {
                current = NULL;
                temp = NULL;
            }
        }
    }
    delete [] adjacency_list;
}

//getter for the vertex array size
int graph::get_size()
{
    return array_size;
}

//generate graph function returns nothing and receives no arguments. the purpose of this function is to allocate memory for an array of vertices
//and then connect them randomly with edges. the only randomness that happens is the connection of edges to vertices. the vertices themselves
//are rather static once the memory for them is allocated. to accomplish the random generation an insert edge function was created to receive two
//integers as arguments. these two integers represent the indices of the vertices that will be connected by an edge. these two integers are randomized
//using the rand function
void graph::generate_graph()
{
   srand(time(0));//seed for randomness 
   array_size = rand() % 16 + 5;//randomly sizing the array of vertices
   int edge_to = 0;//defining an integer to be later used in connecting vertices
   int count = 65;//for use concerning ASCII values a few lines down

   adjacency_list = new vertex[array_size];//allocating memory for the vertices
   for(int i = 0; i < array_size; ++i)//setting data in the vertices
   {
       char v_name = count;//setting name
       adjacency_list[i].set_location(i, &v_name);//calling set location function because a vertex IS a location through inheritance
       ++count;//increment the counter to get newer ASCII values
   }
   for(int i = 0; i < 12; ++i)//iterate random process lots of time to make sure vertices are properly connected
   {
       for(int j = 0; j < array_size; ++j)//iteration must not try to access unavailable index, array_size keeps that in check
       {
           edge_to = rand() % (array_size + 1);//choose random vertex
           if(duplicate_check(adjacency_list[j].to_head(), edge_to))//check if duplicate connections will be made
           {
               if(j != edge_to && adjacency_list[j].edgelist != 0 && adjacency_list[edge_to].edgelist != 0)//check if edge list is already maxed out at 3 connections
               {
                   insert_edge(j, edge_to);//all requirement have been met, connect both vertices to each other.
                   insert_edge(edge_to, j);
               }
           }
       }
   }
}

//this function receives two indices as args which are used to connect two vertices together by an edge
void graph::insert_edge(int edge_from, int edge_to)
{
    --adjacency_list[edge_from].edgelist;//decrement the count for edges in the specified vertices edgelist
    edge * new_edge = new edge;//allocate memory for new edge
    new_edge->set_next(adjacency_list[edge_from].to_head());//link up edge list
    adjacency_list[edge_from].set_head(new_edge);//set head of edgelist to be updated with new node
    new_edge->set_adjacent(&adjacency_list[edge_to]);//set the connecting vertex 
}

//display_adjacent function receives an integer for an arg which is used to identify the vertex of which the edgelist will be displayed
void graph::display_adjacent(int index)
{
    if(index >= array_size)//is the given index invalid
    {
        cout << "Error: Arg larger than array size." << endl;
        return;
    }
    edge * current = adjacency_list[index].to_head();//create easy to use edge pointer
    while(current)//loop through edgelist
    {
        cout << "Checkpoint " << current->to_adjacent()->to_index() << endl;//display checkpoint information
        current = current->to_next();//go to next edge
    }
}

//getter for vertices held within the vertex array inside the graph class
//arg is the integer for the index specifying which vertex to return
vertex & graph::to_vertex(int index)
{
    return adjacency_list[index];
}

//the check_valid function returns an integer which signifies whether or not the connection between two vertices is a valid connection
//the function takes two arguments which are integers, they represent the indices of the two vertices
int graph::check_valid(int from, int destination)
{
    int return_value = 0;//value to return will be changed throughout the function
    edge * current = adjacency_list[from].to_head();//setting head of edgelist to convenient edge list
    while(current)//loop through edgelist to check if valid connection
    { 
        if(destination == current->to_adjacent()->to_index())//check if valid
        {
            return_value = 1;
        }
        current = current->to_next();//traverse edgelist
    }
    return return_value;
}

//this function returns an int to signify whether or not the combination of vertex connection has already happened
//the head of a vertices edgelist is handed in as an argument which is then used to traverse the edgelist and compare each to the specified vertex
int graph::duplicate_check(edge * current, int to_check)
{
    if(!current)//if we reach the end of the list
    {
        return 1;
    }
    if(current->to_adjacent()->to_index() == to_check)//if a duplicate is found
    {
        return 0;
    }
    return duplicate_check(current->to_next(), to_check);//recursive call to continue through edgelist checking for duplicates
}
