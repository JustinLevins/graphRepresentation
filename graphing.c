#include <stdio.h>
#include <stdlib.h>

/*Short program to show how an input list of edges in the format (vx, vy) = edge
can be used to create an adjacency list representation of a graph in O(V + E) time.
This program takes an input .txt file with the aforementioned format:
(example below)

1 2
3 1
2 4

And outputs the graph's adjacency list representation in sorted order.
Compiled with GCC on Ubuntu 18.04
*/


typedef struct node{
	int vert;
	struct node* next;
}node;

typedef struct linkedList{
	struct node* head;	//head pointer for each list in array..best to think as a row
}linkedList;

typedef struct Graph{//will require a main graph sort of function to set each pointer in array to null
	int vertices;
	struct linkedList* adjList;
}Graph;

/*basically, just adds pointers to the array for each adjacent vertex. vertex-vertex relation describes exactly one edge.*/

void addEdge(Graph*, int, int);
node* createNode(int);
Graph* startGraph(int);
int max(char*);
void printAdjList(Graph*);
void freeList(Graph*);

int main(int argc, char**argv){

	if (argc != 2){
		printf("Error: Incorrect number of arguments! Exiting...\n");
		return -2;
	}

	FILE* fp = fopen(argv[1], "r+");
	if (fp == NULL){
		printf("Error reading from file. Exiting\n");
		return -1;
	}
	
	int numV = max(argv[1]); // number of vertices in the graph...will be size of "array of pointers"
	
	Graph* adj = startGraph(numV);
	int x, y;
	
	while (fscanf(fp, "%d %d", &x, &y) == 2){
		
		addEdge(adj, x, y);
		addEdge(adj, y, x);
		
	}

	printAdjList(adj);
	freeList(adj);
	return 0;
}

int max(char* file){

	int high = 1, comp = 1;
	FILE* fp = fopen(file, "r"); //null check?
	while (fscanf(fp, "%d", &comp) == 1){
		if (comp > high){
			high = comp;
		}
	}	
	return high;
}

void addEdge(Graph* existing, int source, int dest){ //iterating edges is theta(E)
	

	node* new = createNode(source);
	node* prev;
	node* temp;

	prev = existing->adjList[dest-1].head;
	temp = existing->adjList[dest-1].head->next;
	while (temp != NULL && source > temp->vert){
		prev = temp;
		temp = temp->next;

	}

	if (temp == NULL){
		prev->next = new;
	}

	else{
		new->next = temp;
		prev->next = new;
	}

}

node* createNode(int vertex){
	node* newNode = (node*) malloc(sizeof(node)); //node creation, followed by default assignment 
	newNode->vert = vertex;
	newNode->next = NULL;
	return newNode;
}

Graph* startGraph(int numVertices){
	Graph* graph = (Graph*) malloc(sizeof(Graph)); //fetching memory
	graph->adjList = malloc(sizeof(node) * numVertices * 4); //best to have a dynamic graph, hence the double pointer
	graph->vertices = numVertices;

	for (int i = 0; i < numVertices; i++){
		graph->adjList[i].head = createNode(i+1);
	}
	
	return graph;
}

void printAdjList(Graph* adjacencyList){ //n is numV
	// v: v2 v3 v4 #format
	for (int i = 0; i < adjacencyList->vertices; i++){
		printf("%d: ", adjacencyList->adjList[i].head->vert);
		node* traverse = adjacencyList->adjList[i].head->next;
		while (traverse){ //could print lots?
			printf("%d ", traverse->vert);
			traverse = traverse->next;
		}
		printf("\n");
	}
}

void freeList(Graph* graph){
	//frees the graph
    if(graph){
        if(graph->adjList){
            /*Free up the nodes*/
            for (int i = 0; i < graph->vertices; i++){
                node* ptr = graph->adjList[i].head;
                while (ptr){
                
                    node* temp = ptr;
                    ptr = ptr->next;
                    free(temp);
                }

            }
            free(graph->adjList);
        }
        free(graph);
    }
}

