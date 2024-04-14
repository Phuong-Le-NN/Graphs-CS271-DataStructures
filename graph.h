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

using namespace std;

template <typename K, typename D>
class Graph {
private:
    struct Vertex
    {
        K       key;
        D       data;
        int     distance;
        K       predecessor;
    };

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