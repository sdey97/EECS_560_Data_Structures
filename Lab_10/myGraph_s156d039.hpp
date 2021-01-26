#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class myGraph
{
        int num_v;
        vector <string> data;
        list <int> * adjList;
        void DFShelper(int v, bool visit[]);

    public:
        myGraph(char* filename);
        void addEdge(int u, int v);
        void BFS(int s);
        void DFS(int s);
        void print();
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
    int c = data.size() - 2;
    num_v = stoi(data[c]);
    adjList = new list<int>[num_v+1];

    for(int i = 0; i < data.size(); i+=2)
    {
        if(stoi(data[i]) <= num_v)
            addEdge(stoi(data[i]), stoi(data[i+1]));
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