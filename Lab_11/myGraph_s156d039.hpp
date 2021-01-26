#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include <sstream>
#include <tuple>
#include <climits>

using namespace std;

class myGraph
{
        int num_v;
        int ** cost;
        int * dist;
        int * parent;
        bool * known;
        vector <string> data;
        list <int> * adjList;
        void DFShelper(int v, bool visit[]);

    public:
        myGraph(char* filename);
        void addEdge(int u, int v);
        void BFS(int s);
        void DFS(int s);
        void print();
        void print2();
        int minimumDist(int dist[], bool known[]);
        void dijkstra(int src);
        void printPath(int i);
        int computePathCost(int i);
};

myGraph::myGraph(char* filename)
{
    ifstream inFile(filename);
    if (inFile.is_open())
    {
        string line;
        while( getline(inFile,line) )
        {
            stringstream ss(line);

            string val;
            while( getline(ss,val,',') )
            {
                 data.push_back(val);
            }
        }
    }
    int c = data.size() - 3;
    num_v = stoi(data[c]);
    cost = new int*[num_v+1];
    for(int i = 0; i <= num_v; ++i)
        cost[i] = new int[num_v+1];
    for(int i = 0; i <= num_v; i++)
    {
        for(int j = 0; j <= num_v; j++)
        {
            cost[i][j] = -1;
        }
    }
    adjList = new list<int>[num_v+1];

    for(int i = 0; i < data.size(); i+=3)
    {
        if(stoi(data[i]) <= num_v)
            addEdge(stoi(data[i]), stoi(data[i+1]));
            cost[stoi(data[i])][stoi(data[i+1])] = stoi(data[i+2]);
    }
}

void myGraph::addEdge(int u, int v) 
{ 
    adjList[u].push_back(v);
}

void myGraph::print()
{
    for(int i = 0; i <= num_v; i++)
    {
        cout << i << ": ";
        for(list<int>::iterator it = adjList[i].begin(); it != adjList[i].end(); it++)
            cout << *it << ' ';
        cout << endl;
    }
}
void myGraph::print2()
{
    for(int i = 0; i <= num_v; i++)
    {
        cout << i << ": ";
        for(int j = 0; j < num_v; j++)
        {
            if(cost[i][j] != -1)
            {
                cout << cost[i][j] << ' ';
            }
        }
        cout << endl;
    }
}

int myGraph::minimumDist(int dist[], bool known[]) 
{
	int min=INT_MAX, index;
              
	for(int i=0; i <= num_v; i++) 
	{
		if(known[i]==false && dist[i]<=min)      
		{
			min=dist[i];
			index=i;
		}
	}
	return index;
}

void myGraph::dijkstra(int src)
{
    dist = new int[num_v];
    known = new bool[num_v];
    parent = new int[num_v];
    for(int i = 0; i <= num_v; i++)
	{
        parent[src] = -1;
		dist[i] = INT_MAX;
		known[i] = false;	
	}

    dist[src] = 0;

    for(int i = 0; i <= num_v; i++)                           
	{
		int min = minimumDist(dist, known); 
		known[min] = true;
		for(int i = 0; i <= num_v; i++)                  
		{
			if(!known[i] && cost[min][i] != -1 && dist[min]!=INT_MAX && dist[min]+cost[min][i]<dist[i])
            {
                parent[i] = min;
				dist[i]=dist[min]+cost[min][i];
            }
		}
	}
}

void myGraph::printPath(int i) 
{ 
    if (parent[i] == -1)
    { 
        cout << i << ' '; 
        return;
    }
  
    printPath(parent[i]); 
  
    cout << i << ' '; 
}

int myGraph::computePathCost(int i) 
{ 
    int ret = 0;
    ret = (int)(dist[i]);
    return ret;
} 

void myGraph::DFShelper(int v, bool visit[])
{
    visit[v] = true; 
    cout << v << endl; 
  
    list<int>::iterator i; 
    for (i = adjList[v].begin(); i != adjList[v].end(); ++i) 
        if (!visit[*i]) 
            DFShelper(*i, visit);
}

void myGraph::DFS(int s) 
{ 
    bool *visit = new bool[num_v]; 
    for (int i = 0; i < num_v; i++) 
        visit[i] = false; 
  
    DFShelper(s, visit); 
}

void myGraph::BFS(int s) 
{  
    bool *visit = new bool[num_v]; 
    for(int i = 0; i < num_v; i++) 
        visit[i] = false; 
  
    list<int> q; 
  
    visit[s] = true; 
    q.push_back(s); 

    list<int>::iterator i; 
  
    while(!q.empty()) 
    { 
        s = q.front(); 
        cout << s << endl; 
        q.pop_front(); 
  
        for (i = adjList[s].begin(); i != adjList[s].end(); ++i) 
        { 
            if (!visit[*i]) 
            { 
                visit[*i] = true; 
                q.push_back(*i); 
            } 
        } 
    } 
} 