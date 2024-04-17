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
        v.parent = K();
        v.visited = false;
        v.bfsSource = K();
        v.discoveryTime = int();
        v.finishTime = int();
        v.dfsParent = K();
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
    dfs()
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
typename    Graph<K, D>::
Vertex*     Graph<K, D>::get        (K key) const
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
bool        Graph<K, D>::reachable   (K u, K v) const
{
    Vertex* vertX = get(v);         // Get vertex
    
    // BFS has already been performed with u as the source
    if (vertX->bfsSource == u) {
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
void        Graph<K, D>::print_path  (K u, K v) const
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
string      Graph<K, D>::edge_class     (K u, K v) const
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
void        Graph<K, D>::bfs_tree       (K s) const
{

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
void        Graph<K, D>::dfs_helper       (K v) const
{
    Vertex* vertV = get(v);

    // Update v (current vertex)
    vertV->dfsVisited = true;
    time++;
    vertV->discoveryTime = time;

    // Visit all unvisited neighbors of the current vertex
    for (int i = 0; i < adjList[vertV->key].size(); i++) {
        Vertex* neighbor = adjList[vertV->key][i];
        if (!neighbor->dfsVisited) {
            neighbor->dfsParent = vertV->key;
            dfs_helper(neighbor);
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
void        Graph<K, D>::dfs       () const
{
    time = 0;   // Reset the global time variable

    // Perform DFS on all unvisited vertices
    for (auto& pair : vertices) {
        if (!pair.second.dfsVisited) {
            dfs_visit(&pair.second);
        }
    }
}