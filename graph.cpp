//=================================
// Aryah Rao, Lam Do, Phuong Le
// graph.cpp
// April 2024
// This file implements the templated Graph Class.
//=================================

#include "graph.h"
#include <map>

//========================================================
// Constructor
// Initialize Graph
// Parameters: 
//      keys - Vector of keys
//      data - Vector of data
//      edges - Adjacency vectors of keys
// Pre-condition: No key duplicate in keys
// Post-condition: Graph is constructed
// Return: None
//========================================================
template <typename D, typename K>
            Graph<D,K>::Graph      (vector<K> keys, vector<D> data, vector<vector<K>> edges)
{
    map <K, int> keyfreq;
    for ( int i = 0; i < keys.size(); i++)
    {
        if (keyfreq[keys[i]] == 0)
        {
            keyfreq[keys[i]] = 1;
        }
        else
        {   
            // cout << "Set of keys contains duplicate" << endl;
            return;
        }
    }
    // Create vertices and store them in the vertices map
    for (int i = 0; i < keys.size(); i++) {
        // Overall attributes
        Vertex v; 
        v.key = keys[i];
        v.data = data[i];

        // Update attributes for BFS
        v.distance = -1;
        v.parent = nullptr;
        v.visited = false;

        // Update attributes for DFS
        v.discoveryTime = int();
        v.finishTime = int();
        v.dfsParent = nullptr;
        v.dfsVisited = false;
        
        // Update unordered map vertices - Map keys with vertices
        vertices[keys[i]] = v;

        // Append the key to vertices_list
        vertices_list.push_back(keys[i]); 
    }

    // Update unordered map adjList - Map key with adjacency list of vertex pointers
    for (int i = 0; i < keys.size(); i++) {
        vector<Vertex*> neighbors;                          // Initialize individual adjacency list
        for (int j = 0; j < edges[i].size(); j++) {
            neighbors.push_back(&vertices[edges[i][j]]);
        }
        adjList[keys[i]] = neighbors;                       // Map adjacency list to vertex key
    }

    bfsSource = nullptr;

    // Call DFS
    dfs();
    bfsSource = nullptr;
}

//========================================================
// get
// Return a pointer to the vertex corresponding to key k
// Parameters: 
//      k - Key of vertex
// Pre-condition: Key k exists in graph
// Post-condition: None
// Return: Pointer to the vertex corresponding to key k
//========================================================
template <typename D, typename K>
typename    Graph<D,K>::Vertex*     Graph<D,K>::get        (K key) 
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
// Pre-condition: Vertex with key u and vertex with key v exists in graph
// Post-condition: None
// Return: Boolean indicating if vertex with key v is reachable from vertex with key u
//========================================================
template <typename D, typename K>
bool        Graph<D,K>::reachable   (K u, K v)
{
    Vertex* vertX = get(v);             // Get vertex

    // If key s does not exist, exit
    if (vertX == nullptr) {
        return false;
    }
    // BFS has not been performed or the source is different
    if (bfsSource != get(u)) {
        bfs(u);
    }
    return vertX->distance != -1;       // Return if reachable from u
}

//========================================================
// bfs
// Execute breadth-first search with source vertex with key s
// Parameters: 
//      s - Key of source vertex
// Pre-condition: Vertex with key s exists in graph
// Post-condition: Attributes (distance and parent) of vertices in the bfs tree are updated accordingly 
// Return: None
//========================================================
template <typename D, typename K>
void        Graph<D,K>::bfs         (K s) 
{
    // Get vertex pointer
    Vertex* vertS = get(s);

    // BFS already performed with key s, exit
    if (bfsSource == vertS) {
        return;
    }

    // Clear BFS tree in case BFS has been called before
    if (bfsSource != nullptr)
    {
        for (auto& pair : vertices)
        {
            Vertex* v = &pair.second;
            v->distance = -1;
            v->visited = false;
            v->parent = nullptr;
        }
    }

    // If key s does not exist, exit
    if (vertS == nullptr) {
        return;
    }

    // Update attributes of source s
    vertS->visited = true;
    vertS->distance = 0;
    vertS->parent = nullptr;

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
                neighbor->parent = vertU;
                Q.push(neighbor->key);
            }
        }
    }
    // Update last called source of BFS
    bfsSource = vertS;
}

//========================================================
// print_path
// Print the shortest path from vertex with key u to vertex with key v
// Parameters: 
//      u - Key of starting vertex
//      v - Key of destination vertex
// Pre-condition: Vertex with key u and key v exists in graph
// Post-condition: Prints the path from vertex with key u to vertex with key v if exists
// Return: None
//========================================================
template<typename D, typename K>
void        Graph<D,K>::print_path  (K u, K v) 
{
    // If key u or key v does not exist, exit
    if (get(u) == nullptr || get(v) == nullptr) {
        return;
    }

    // Check the source before calling bfs
    if (bfsSource != get(u)) {
        bfs(u);
    }

    // Get the vertex with key v to trace along the parents to get back to u
    Vertex* x = get(v)->parent;

    // Intitiate the stream to convert the keys on the path and print out later
    stringstream stream;

    // Put the last key in the path into the stream
    stream << v;
    string output = stream.str();

    // Trace the path backward from v to u
    while (x != nullptr && x->key != u)
    {
        stream.str("");
        stream << x->key;
        output = stream.str() + " -> " + output;
        x = x->parent;
    }

    // If v is reachable from u, x would not be null
    if (x != nullptr)
    {
        // Add last vertex key
        stream.str("");
        stream << x->key;
        output = stream.str() + " -> " + output;

        cout <<output;
    }
}

//========================================================
// edge_class
// Return string representation of edge from vertex with key u to vertex with key v
// Parameters: 
//      u - Key of starting vertex
//      v - Key of destination vertex
// Pre-condition: Vertex with key u and key v exists in graph and DFS is called on graph
// Post-condition: None
// Return: string representation of edge from vertex with key u to vertex with key v
//========================================================
template<typename D, typename K>
string      Graph<D,K>::edge_class     (K u, K v)
{
    // Get vertices
    Vertex* vertU = get(u);
    Vertex* vertV = get(v);

    // Check if non-existent
    if (vertU == nullptr ||  vertV == nullptr){
        return "no edge";
    }

    // Special case of same key
    if (u == v) {
            // Check if self-loops are stored in the adjacency list
            for (Vertex* adj : adjList[u]) {
                if (adj->key == u) {
                    return "back edge";
                }
            }
            return "no edge";
        }

    // Check if v is the DFS parent of u
    if (vertU->dfsParent == vertV || vertV->dfsParent == vertU) {
        return "tree edge";
    }

    // Check if u is visited before v and v is visited before u is finished
    if (vertU->discoveryTime < vertV->discoveryTime && vertV->finishTime < vertU->finishTime) {
        return "forward edge";
    }

    // Check if v is visited before u and u is visited before v is finished
    if (vertV->discoveryTime <= vertU->discoveryTime && vertU->finishTime <= vertV->finishTime) {
        return "back edge";
    }

    // Check if v is finished before u is visited or u is finished before v is visited
    if (vertV->discoveryTime < vertU->discoveryTime && vertU->finishTime > vertV->finishTime) {
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
// Pre-condition: Vertex with key s exists in graph
// Post-condition: Print BFS tree level by level
// Return: None
//========================================================
template<typename D, typename K>
void        Graph<D,K>::bfs_tree       (K s) 
{
    // Clear BFS tree in case BFS has been called before
    if (bfsSource != nullptr)
    {
        for (auto& pair : vertices)
        {
            Vertex* v = &pair.second;
            v->distance = -1;
            v->visited = false;
            v->parent = nullptr;
        }
    }

    // Start to create bfs by updating BFS source and get the src vertex
    Vertex* src = get(s);
    bfsSource = src;

    // If source not found, exit
    if(!src) {
        return;
    }

    // Initialize the queue
    queue <Vertex*> Q;

    // Change the source attribute as needed
    src->visited = true;
    src->distance = 0;
    src->parent = nullptr;

    // String stream for printing the tree
    stringstream stream;

    // Add the source key into the stream
    stream << s;

    // Add the adj list of src to the queue Q while changing the attributes as needed
    for (Vertex* v : adjList[s])
    {
        if (!v->visited)
        {
            v->visited = true;
            v->parent = src;
            v->distance = 1;
            Q.push(v);
        }
    }

    // Level to track each line of the tree
    int level = 0;

    // Execute BFS as usual while adding and printing string stream
    while (!Q.empty())
    {
        // Take the current vertex
        Vertex* u = Q.front();
        Q.pop();

        // Check if the current vertex belong to the current level or the next level
        if (u->distance != level) // Change in distance means we are now looking at vertex at a new level
        {
            level++;
            cout << stream.str() << endl; // Before starting a new line of the tree we print out the last finsihed one
            stream.str("");
            stream << u->key;
        }
        else // If current level just add a space to separate this vertex key with the previous one
        {
            stream << " " << u->key;
        }

        // Check adjacent vertex to add to the queue
        for (Vertex* v : adjList[u->key])
        {
            if (!v->visited)
            {
                v->visited = true;
                v->parent = u;
                v->distance = u->distance + 1;
                Q.push(v);
            }
        }
    }

    // Print the last level of the tree
    cout << stream.str();
}

//========================================================
// dfs_helper
// Perform depth-first search (DFS) starting from vertex v
// Parameters: 
//      v - Key of source vertex
// Pre-condition: Vertex with key v exists
// Post-condition: Update attributes (discovertyTime and finishTime) according to DFS starting from vertex v
// Return: None
//========================================================
template<typename D, typename K>
void        Graph<D,K>::dfs_helper       (K v) 
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
            neighbor->dfsParent = vertV;
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
// Parameters: None
// Pre-condition: None
// Post-condition: All attributes are updated according to DFS on the whole graph
// Return: None
//========================================================
template<typename D, typename K>
void        Graph<D,K>::dfs       () 
{
    time = 0; // Reset the global time variable

    // Perform DFS on all unvisited vertices
    for (int i = 0; i < vertices_list.size(); i++)
    {
        if (!vertices[vertices_list[i]].dfsVisited) {
            dfs_helper(vertices_list[i]);
        }
    }
}