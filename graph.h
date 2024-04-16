//=================================
// Aryah Rao, Lam Do, Phuong Le
// graph.h
// April 2024
// This file contains the class header for the templated Graph class.
//=================================

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

template <typename K, typename D>
class Graph {
private:
    struct Vertex {
        D data;         // Data associated with the vertex
        K key;          // Key of the vertex
        int distance;   // Distance from the source vertex during BFS
        K parent;       // Parent vertex key during BFS
        bool visited;   // Flag to mark if the vertex has been visited during BFS
    };

unordered_map<K, Vertex> vertices;                  // Dictionary: Keys -> Vertices
unordered_map<K, vector<Vertex*>> adjList;          // Dictionary: Keys -> List of Adjacent Vertices

public:
            Graph           (vector<K> keys, vector<D> data, vector<vector<K>> edges);  // Constructor
Vertex*     get             (K key) const;          // Return a pointer to the vertex corresponding to key k
bool        reachable       (K u, K v) const;       // Indidate if v is reachable from u
void        bfs             (K s);                  // Execute breadth-first search with source s
void        print_path      (K u, K v) const;       // Print the shortest path from u to v
string      edge_class      (K u, K v) const;       // Return the string representation of edge from u to v
void        bfs_tree        (K s) const;            // Print the bfs tree with source s
};

#include "graph.cpp"

#endif