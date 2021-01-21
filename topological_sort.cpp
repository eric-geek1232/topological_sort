/*By Eric 19-01-2021 -topological sort- */
#include <iostream>

using namespace std;
 
#define CONVERT_INT_TO_CHAR(integer) (char(integer))

class Graph
{
	private:
		int **adjacencyMatrix;
		int *inDegrees;
		int nVertices;
			
		int findStart();
		void decreaseInDegree(int vertex);
		void calculateInDegree();
		
	public:
		Graph();
		Graph(int nVertices);
		void sort();
		void setGraph();
		void showInDegree();
		void showGraph();
		bool isEmpty();	
};

Graph::Graph()
{
	nVertices = 0; 
}

Graph::Graph(int nVertices)
{
	this->nVertices = nVertices;
	
	adjacencyMatrix = new int*[nVertices];
	inDegrees = new int[nVertices];
	
	for (int col = 0; col < nVertices; col++) {
		adjacencyMatrix[col] = new int [nVertices];
	}
}

void Graph::setGraph()
{	
	char noPath;
	
	cout<< "\n\n\t Adding Distances...\n"<< endl;
	
	for (int row = 0; row < nVertices; row++) {
		for (int col = 0; col < nVertices; col++) {
			char destine = CONVERT_INT_TO_CHAR(col + 65);
			char origin = CONVERT_INT_TO_CHAR(row + 65);
			
			if (origin == destine) {
				adjacencyMatrix[row][col] = 0;
				continue;
			}
			
			cout<< "\n Is there any route "<< origin<< " TO "<< destine<< "? [s/n]: ";
			cin>> noPath;
			
			// SET INDEGREE
			if (noPath == 'n' || noPath == 'N') {
				adjacencyMatrix[row][col] = 0;
			} else{
				adjacencyMatrix[row][col] = 1;	
			}
		}
	}
	
	cout<< endl;
}

void Graph::showGraph() 
{
	cout<< "\n\n\t\tShowing Adjacency Matrix...\n"<< endl;
	
	// PRINT COLUMNS
	for	(int col = 0; col < nVertices; col++) {
		cout<< "\t("<< CONVERT_INT_TO_CHAR(col + 65)<< ")";
	}
	
	cout<< "\n"<< endl;
	
	for (int row = 0; row < nVertices; row++) {
		// PRINT ROWS
		cout<< " ("<< CONVERT_INT_TO_CHAR(row + 65)<< ")\t";
		
		// PRINT CONTENT 
		for (int col = 0; col < nVertices; col++) {
			cout<< " "<< adjacencyMatrix[row][col]<< "\t";	
		}
		
		cout<< "\n"<< endl;
	}
}

void Graph::calculateInDegree()
{
	for (int col = 0; col < nVertices; col++) {
		// CLEAN INDEGREE BEFORE
		inDegrees[col] = 0; 
		
		for (int row = 0; row < nVertices; row++) {
			if(adjacencyMatrix[row][col] == 1){
				inDegrees[col]++;	
			}
		}
	}
}

void Graph::showInDegree() 
{
	calculateInDegree();
	
	cout<< "\n\t\tShowing Indegrees...\n"<< endl;
	for (int i = 0; i < nVertices; i++) {
		cout<< "\n ("<< CONVERT_INT_TO_CHAR(i + 65)<< ")-|-Grade: "<< inDegrees[i]<< endl;
	}
}

int Graph::findStart()
{
	int i = 0;
	
	while (i < nVertices && inDegrees[i] != 0) {
		i++;
	}
	
	if (i != nVertices) {
		return i;
	} else {
		return -1;
	}
}

void Graph::decreaseInDegree(int vertex)
{
	inDegrees[vertex] = -1;
	
	for (int i = 0; i < nVertices; i++) {
		if (adjacencyMatrix[vertex][i] == 1) {
			inDegrees[i]--;
		}
	}
}

void Graph::sort()
{
	int node;
	
	cout<< "\n\n [Info]-sort: ";
	do {
		node = findStart();
		
		if (node != -1) {
			cout<< " ("<< CONVERT_INT_TO_CHAR(node + 65)<< ")-->";
			
			decreaseInDegree(node); 
		}
		
	} while (node != -1);
	
	cout<< "\n"<< endl;
}

bool Graph::isEmpty() 
{
	return nVertices == 0 ? true : false;
}

int main()
{
	Graph *graph = new Graph();
	int option;
	int nVertices;
	
	do {
		cout<< "\t TOPOLOGICAL SORT\n"<< endl;
		cout<< "\t.::MENU::.\n"<< endl;
		cout<< " [1] Create Graph"<< endl;
		cout<< " [2] Sort"<< endl;
		cout<< " [3] Exit"<< endl;
		cout<< "\n Choose: ";
		cin>>option;
		
		switch(option) {
			case 1:
				delete graph;
				
				cout<< "\n\n Type the number of vertices ";
				cin>> nVertices;
				
				graph = new Graph(nVertices);
				
				graph->setGraph();
				break;
				
			case 2:
				if (!graph->isEmpty()) {
					graph->showGraph();	
					graph->showInDegree();
					graph->sort();
				} else {
					cout<< "\n\n [Warning]-there's no a graph\n"<< endl;
				}
				break;
				
			case 3:
				cout<< "\n\n\t**Big thanks for using this program**\n"<< endl;
				break;
				
			default:
				cout<< "\n\n\tWrong option... try again!\n"<< endl;
		}
		
		system("pause");
		system("cls");
	} while (option != 3);
	
	return 0;
}
