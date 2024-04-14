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
    return true;
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
    return "";
}     

//========================================================
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