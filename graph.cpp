//=================================
// Aryah Rao, Lam Do, Phuong Le
// graph.cpp
// April 2024
// This file implements the templated Graph Class.
//=================================

#include "graph.h"

//========================================================
// Constructor
// Initialize Graph
// Parameters: 
//      keys - Vector of keys
//      data - Vector of data
//      edges - Adjacency vectors of keys
// Pre-condition: 
// Post-condition: 
// Return: 
//========================================================
template <typename K, typename D>
            Graph<K, D>::Graph      (vector<K> keys, vector<D> data, vector<vector<K>> edges)
{
    // Create vertices and store them in the vertices map
    for (int i = 0; i < keys.size(); i++) {
        Vertex v; 
        v.key = keys[i];
        v.data = data[i];
        v.distance = -1;
        v.parent = -1;
        v.visited = false;
        v.discoveryTime = int();
        v.finishTime = int();
        v.dfsParent = -1;
        v.dfsVisited = false;
        vertices[keys[i]] = v;
    }

    // Build the adjacency list using the edges
    for (int i = 0; i < keys.size(); i++) {
        vector<Vertex*> neighbors;  // Initialize adjacency list
        for (int j = 0; j < edges[i].size(); j++) {
            neighbors.push_back(&vertices[edges[i][j]]);
        }
        adjList[keys[i]] = neighbors;   // Map adjacency list to vertex key
    }

    // Call DFS
    dfs();
}

//========================================================
// get
// Return a pointer to the vertex corresponding to key k
// Parameters: 
//      k - Key of vertex
// Pre-condition: 
// Post-condition: 
// Return: Pointer to the vertex corresponding to key k
//========================================================
template <typename K, typename D>
typename    Graph<K, D>::Vertex*     Graph<K, D>::get        (K key) 
{
    // Find key in dictionary
    if (vertices.find(key) != vertices.end()) {
        return &vertices[key];  // Return pointer if found
    }
    return nullptr;     // Else return NULL
}

//========================================================
// reachable
// Indidate if vertex with key v is reachable from vertex with key u
// Parameters: 
//      u - Key of starting vertex
//      v - Key of destination vertex
// Pre-condition: 
// Post-condition: 
// Return: Boolean indicating if vertex with key v is reachable from vertex with key u
//========================================================
template <typename K, typename D>
bool        Graph<K, D>::reachable   (K u, K v)
{
    Vertex* vertX = get(v);         // Get vertex

    // If key s does not exist, exit
    if (vertX == nullptr) {
        return false;
    }

    // BFS has already been performed with u as the source
    if (bfsSource == u) {
        return vertX->distance != -1;   // Return if reachable from u
    }
    // BFS has not been performed or the source is different
    else {
        bfs(u);
        return vertX->distance != -1;   // Return if reachable from u
    }
}

//========================================================
// bfs
// Execute breadth-first search with source vertex with key s
// Parameters: 
//      s - Key of source vertex
// Pre-condition: 
// Post-condition: 
// Return: None
//========================================================
template <typename K, typename D>
void        Graph<K, D>::bfs         (K s) 
{
    // bfs already performed with key s
    if (bfsSource == s) {
        return;
    }

    // Get pointer
    Vertex* vertS = get(s);

    // If key s does not exist, exit
    if (vertS == nullptr) {
        return;
    }

    // Reset all values in the vertices
    for (auto& pair : vertices) {
        pair.second.visited = false;
        pair.second.distance = -1;
        pair.second.parent = -1;
    }

    // Update attributes of source s
    vertS->visited = true;
    vertS->distance = 0;
    vertS->parent = -1;        // I have problems with this, 
                                // if we use K() to represent NULL, what if
                                // there are vertices with key s? //i don't think this is possible (phuong)
                                // How do we tell the difference?

    // Initialize empty queue and enqueue s
    queue<K> Q;
    Q.push(s);

    while (!Q.empty()){
        // Dequeue and store in u
        K u = Q.front();
        Vertex* vertU = get(u);
        Q.pop(); 

        for (int i = 0; i < adjList[u].size(); i++) {
            Vertex* neighbor = adjList[u][i];
            
            // Update attributes of vertices adjacent to u
            if (!neighbor->visited) {
                neighbor->visited = true;
                neighbor->distance = vertU->distance + 1;
                neighbor->parent = u;
                Q.push(neighbor->key);
            }
        }
    }

    // Update last called source of BFS
    bfsSource = s;
}

//========================================================
// print_path
// Print the shortest path from vertex with key u to vertex with key v
// Parameters: 
//      u - Key of starting vertex
//      v - Key of destination vertex
// Pre-condition: 
// Post-condition: 
// Return: None
//========================================================
template<typename K, typename D>
void        Graph<K, D>::print_path  (K u, K v) 
{
    
}

//========================================================
// edge_class
// Return string representation of edge from vertex with key u to vertex with key v
// Parameters: 
//      u - Key of starting vertex
//      v - Key of destination vertex
// Pre-condition: 
// Post-condition: 
// Return: string representation of edge from vertex with key u to vertex with key v
//========================================================
template<typename K, typename D>
string      Graph<K, D>::edge_class     (K u, K v)
{
    // Call DFS?
    // dfs()

    // Get vertices
    Vertex* vertU = get(u);
    Vertex* vertV = get(v);

    // Check if v is the DFS parent of u
    if (vertU->dfsParent == vertV->key) {
        return "tree edge";
    }

    // Check if u is visited before v and v is visited before u is finished
    if (vertU->discoveryTime < vertV->discoveryTime && vertV->finishTime < vertU->finishTime) {
        return "forward edge";
    }

    // Check if v is visited before u and u is visited before v is finished
    if (vertV->discoveryTime < vertU->discoveryTime && vertU->finishTime < vertV->finishTime) {
        return "back edge";
    }

    // Check if v is finished before u is visited or u is finished before v is visited
    if (vertV->finishTime < vertU->discoveryTime || vertU->finishTime < vertV->discoveryTime) {
        return "cross edge";
    }

    // Else, there is no edge between u and v
    return "no edge";
}     

//========================================================
// bfs_tree
// Print the bfs tree with source vertex with key s
// Parameters: 
//      s - Key of source vertex
// Pre-condition: 
// Post-condition: 
// Return: None
//========================================================
template<typename K, typename D>
void        Graph<K, D>::bfs_tree       (K s) 
{
    //clear bst tree in case bfs has been called before
    if (bfsSource != K())
    {
        for (auto& pair : vertices)
        {
            Vertex* v = &pair.second;
            v->distance = -1;
            v->visited = false;
            v->parent = K ();
        }
    }

    //start to create bfs by assigning the source and get the src vertex
    bfsSource = s;
    Vertex* src = get(s);

    if(!src)
    {
        cout << "source not found" << endl;
        return;
    }

    //initiate the queue
    queue <Vertex*> Q;

    //change the source attribute as needed
    src->visited = true;
    src->distance = 0;
    src->parent = K();

    //string stream for printing the tree
    stringstream stream;

    //add the source key into the stream
    stream << s;

    //add the adj list of src to the queue Q while changing the attributes as needed
    for (Vertex* v : adjList[s])
    {
        if (!v->visited)
        {
            v->visited = true;
            v->parent = s;
            v->distance = 1;
            Q.push(v);
        }
    }

    //level to track each line of the tree
    int level = 0;

    //do bfs as usual while adding and printing string stream
    while (!Q.empty())
    {
        //take the current vertex
        Vertex* u = Q.front();
        Q.pop();

        //check if the current vertex belong to the current level or the next level
        if (u->distance != level) //change in distance means we are now looking at vertex at a new level
        {
            level++;
            cout << stream.str() << endl; //before starting a new line of the tree we print out the last finsihed one
            stream.str("");
            stream << u->key;
        }
        else //if current level just add a space to separate this vertex key with the previous one
        {
            stream << " " << u->key;
        }

        //chenking adjacent vertex to add to the queue
        for (Vertex* v : adjList[u->key])
        {
            if (!v->visited)
            {
                v->visited = true;
                v->parent = u->key;
                v->distance = u->distance + 1;
                Q.push(v);
            }
        }
    }

    //cout the last level of the tree
    cout << stream.str();


}

//========================================================
// dfs_helper
// Perform depth-first search (DFS) starting from vertex v
// Parameters: 
//      v - Key of source vertex
// Pre-condition: 
// Post-condition: 
// Return: None
//========================================================
template<typename K, typename D>
void        Graph<K, D>::dfs_helper       (K v) 
{
    Vertex* vertV = get(v);

    // Update v (current vertex)
    vertV->dfsVisited = true;
    time++;
    vertV->discoveryTime = time;

    // Visit all unvisited neighbors of the current vertex
    for (size_t i = 0; i < adjList[vertV->key].size(); i++) {
        Vertex* neighbor = adjList[vertV->key][i];
        if (!neighbor->dfsVisited) {
            neighbor->dfsParent = vertV->key;
            dfs_helper(neighbor->key);
        }
    }

    // Update finish time
    time++;
    vertV->finishTime = time;
}

//========================================================
// dfs
// Perform depth-first search (DFS) on the entire graph
// Parameters: 
// Pre-condition: 
// Post-condition: 
// Return: None
//========================================================
template<typename K, typename D>
void        Graph<K, D>::dfs       () 
{
    time = 0; // Reset the global time variable

    // Perform DFS on all unvisited vertices
    for (auto& pair : vertices) {
        if (!pair.second.dfsVisited) {
            dfs_helper(pair.first);
        }
    }
}