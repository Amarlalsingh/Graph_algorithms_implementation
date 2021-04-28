/*
 - C++ class for introducing graphs & graph algorithms
 - for simplification, we have the following restrictions:
    - less than 100 nodes
    - no self edges
    - all graph description files will be weighted
    - all weights > 0

 - node order
    print out the nodes, on 1 line, in the order dictated by algorithm
 - spanning tree
    print out edges     start-end   in the order dictated by algorithm



Graph Description File format
  Number of Nodes
  Number of Edges
  Source  Destination  Weight     [ for each edge ]

*/


#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <queue>
using namespace std;

class graph
{
    public:
        graph();
        graph( int n );              // constructor, x is # of nodes
        graph( int n, int e );       // constructor, n is # of nodes
                                     //              e is # of edges
        void bfs(int x, int n, vector<bool>& Mark);   // breadth-first node order
        void bfssp(int x, int n, vector<bool>& Mark); // breadth-first spanning tree
        void dfs(int x, int n, vector<bool>& Mark);   // depth-first node order
        void dfssp(int x, int n, vector<bool>& Mark); // depth-first spanning tree
        void mprint(int n);          // print representation
        void fill( ifstream& file ); // fill graph from data file
        void clearMark(vector<bool>& Mark, int n); // Makes Mark all false
               // file is open;pay attention to read before & in
        void dstra(int x, int n, vector<bool>& Mark);
        void prim(int x, int n, vector<bool>& Mark);
        void krus(int x, int n, vector<bool>& Mark);
    private:
      int** matrix;
      int size;
};




graph::graph()
{}
graph::graph( int n )
{}
graph::graph( int n, int e )
{
  size = n*n;
  //auto = new int adj[n][n];
  matrix = new int*[n];
  for (int row = 0; row < n; row++)
  {
    matrix[row] = new int[n];
    for (int column = 0; column < n; column++)
    {
        matrix[row][column] = 0;
    }
  }
}


void graph::mprint(int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}


void graph::fill( ifstream& file )
{
  int src, dest;
  int weight = 0;
  while(!file.eof())
  {
        file >> src >> dest;// >> weight;
        if (weight > 0)
        {
          matrix[src-1][dest-1] = 1;//weight; // will = weight when weight is existing
          matrix[dest-1][src-1] = 1; //weight;
        }
        else
        {
          matrix[src-1][dest-1] = 1;
          matrix[dest-1][src-1] = 1;
        }
  }
  file.close();
}

void graph::dstra(int x, int n, vector<bool>& Mark);
{
/*
- Dijkstra - Single source shortest path - ask for starting node
- display the cost of trip to each node,
- indicating shorted path at end*special:
- each time you mark a node as final & update neighbors
    print the distance list. (done)
- I will ask you such as when 5 was finalized, what distance was shortest to 8 at that time
*/

int startNode=x ;  // The start node is node from where we calculate minimum distance


/*
cout<<"\n Enter the start node \n";
cin>>startNode;

// just uncomment this if we need to manually ask for starting node
*/


vector<int> dist(n+1); // to store the shortest distance from startNode

int MAX_DISTANCE = 1000000000; //I assumed the distances can fit the int datatype

for(int i=0;i<=n;i++) //setting all distance to the max_distance
    dist[i]= MAX_DISTANCE;

dist[startNode]=0; // as it is the source node from where we start

priority_queue<int> pq;

pq.push({0,startNode}); //pushing the startNode with distance 0

// priority queue sorts max value at top so I am using negative of distance
// so that the minimum distance by value i.e. |dist| is on the top
// by doing this there is no need of complex comparator for priority_queue

while(!pq.empty()){
    int u = q.top().second;
    q.pop();

    if(Mark[u]) continue; // if processed then continue;

    Mark[u]=1;
    // node u is finalized now so we will update the neighbours and
    // print dist list

    //updating neighbors
    for(int i=0;i<=n;i++){

        if(matrix[u][i]!=0){
            // there is an edge from u--->i
            int weight= matrix[u][i];

            if(dist[u] + weight < dist[i]){ //updating weight and pushing in priority_queue
                dist[i]=dist[u]+weight;
                pq.push({-dist[i],i});
            }
        }
    }

    //printing distance list
    cout<<" Node: "<<u<<" is finalized\n";
    cout<<"Printing the distance list\n";

    for(int i=1;i<=n;i++){
        cout<<i<<" has distance of "<<dist[i]<<endl;
    }
}

    cout<<"Printing final shortest distance\n";
    for(int i=1;i<=n;i++){
        cout<<i<<" has distance of "<<dist[i]<<endl;
    }

    // print shortest path for all nodes

    // query of node finalized and current shortest distance of other node




}

void graph::prim(int x, int n, vector<bool>& Mark);
{
/*
    Prim - Minimum spanning tree
 - list of edges used, in order selected
 - ( make start-end match the order, start is end in tree tree )
 - ask for starting location
 - tree cost for result should be reported
*/
}

void graph::krus(int x, int n, vector<bool>& Mark);
{
/*
 - Kruskal - Minimum spanning tree
 - list of edges used, in order selected
 - ( start-end should be listed so start is smaller )
 - tree cost for result should be reported
*/
}


void graph::dfs(int x, int n, vector<bool>& Mark)
{
  stack<int> s;
  s.push(x);
  while (!s.empty())
  {
    x = s.top();
    s.pop();
    if(!Mark[x])
    {
      cout << x+1 << " ";
      Mark[x] = true;
      for (int i = n; i >= 0; i--)
      {
        if (matrix[x][i] == 1 && !Mark[i])
        {
            s.push(i);
        }
      }
    }
  }
}



void graph::bfs(int x, int n, vector<bool>& Mark)
{
  queue<int> q;
  q.push(x);
  while (!q.empty())
  {
    x = q.front();
    q.pop();
    if(!Mark[x])
    {
      cout << x+1 << " ";
      Mark[x] = true;
      for (int i = 0; i <= n; i++)
      {
        if (matrix[x][i] == 1 && !Mark[i])
        {
            q.push(i);
        }
      }
    }
  }
}




void graph::bfssp(int x, int n, vector<bool>& Mark)
{
  queue<int> q;
  q.push(x);
  while (!q.empty())
  {
    x = q.front();
    q.pop();
    if(!Mark[x])
    {
      Mark[x] = true;
      for (int i = 0; i <= n; i++)
      {
        if (matrix[x][i] == 1 && !Mark[i])
        {
          cout << x+1 << "-" << i+1 << " ";
            q.push(i);
        }
      }
    }
  }
}



void graph::dfssp(int x, int n, vector<bool>& Mark)
{
  int cnt = 0;
  stack<int> s;
  s.push(x);
  while (!s.empty())
  {
    x = s.top();
    s.pop();
    if(!Mark[x])
    {
      Mark[x] = true;
      for (int i = n; i >= 0; i--)
      {
        if (matrix[x][i] == 1 && !Mark[i])
        {
          s.push(i);
        }
      }
      for (int j = 0; j <= n; j++)
      {
         if (matrix[x][j] == 1 && !Mark[j])
        {
          cout << x+1 << "-" << j+1<< " ";
        }
      }
    }
  }
}



void graph::clearMark(vector<bool>& Mark, int n) // Clear out the false statements for
  {                                       // other searches
    for(int i = 0; i < n; i++)
    {
      for(int j = 0; j < n; j++)
      {
        int x = matrix[i][j]; // Made it easier for me to understand
        Mark[x] = false;
      }
    }
  }

int main( int argc, char *argv[] )
{
    int size, numnode, numedge;
    int location;
    ifstream ifp;

    //checking to see if file was entered on command line
    if ( argc != 2 )
    {
        cout << "File was not entered\n";
        return 2;
    }

    ifp.open( argv[1] );

    // checking to see if file was opened successfully
    if( !ifp.is_open() )
    {
        cout << "File could not be opened\n";
        return 3;
    }

    // reading in number of nodes
    ifp >> numnode;
    // reading in number of edge
    ifp >> numedge;

    //create graph with an adjadceny matrix of
    // size = num of nodes x num of nodes
    // array can be bigger if needed so you can make it work
    graph g( numnode, numedge );

    //fill adjacency matrix
    g.fill( ifp );

    //print the matrix
    g.mprint(numnode);
    cout << endl << endl;


        //ask for starting location
        cout << "Enter the starting location: ";
        cin >> location;
        location = location - 1;

        vector<bool> Markdfs(numnode, false);
        vector<bool> Markdsp(numnode, false);
        vector<bool> Markbfs(numnode, false);
        vector<bool> Markbsp(numnode, false);
        vector<bool> Markdstra(numnode, false);
        vector<bool> Markprim(numnode, false);
        vector<bool> Markkrus(numnode, false);
        // calculate DFS
        cout << "DFS: ";
        g.dfs(location, numnode, Markdfs);
        cout << endl << endl;
        //g.clearMark(Mark, numnode);

        //calculate DFS-SP
        cout << "DFS Spanning Tree: ";
        g.dfssp(location, numnode, Markdsp);
        cout << endl << endl;
        //g.clearMark(Mark, numnode);

        //calculate BFS
        cout << "BFS: ";
        g.bfs(location, numnode, Markbfs);
        cout << endl << endl;
        //g.clearMark(Mark, numnode);

        //calculate BFS-SP
        cout << "BFS Spanning Tree: ";
        g.bfssp(location, numnode, Markbsp);
        cout << endl << endl;
        //g.clearMark(Mark, numnode);

        //calculate Dijkstra
        cout << "Dijkstra: ";
        g.dstra(location, numnode, Markdstra);
        cout << endl << endl;

        //calculate Prim
        cout << "Prim: ";
        g.prim(location, numnode, Markdprim);
        cout << endl << endl;

        //calculate Kruskal
        cout << "Kruskal ";
        g.krus(location, numnode, Markkrus);
        cout << endl << endl;

        return 0;
    }
