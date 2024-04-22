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
#include <queue>
#include <unordered_map>

using namespace std;

template <typename D, typename K>
class Graph {
private:
    struct Vertex {
        // Overall attributes
        D data;                 // Data associated with the vertex
        K key;                  // Key of the vertex

        // Attributes for BFS
        int distance;           // Distance from the source vertex during BFS
        Vertex* parent;         // Parent vertex key during BFS
        bool visited;           // Flag to mark if the vertex has been visited during BFS

        // Attributes for DFS
        int discoveryTime;      // Discovery time of the vertex during DFS
        int finishTime;         // Finish time of the vertex during DFS
        Vertex* dfsParent;      // Parent vertex key during DFS
        bool dfsVisited;        // Flag to mark if the vertex has been visited during DFS
    };

unordered_map<K, Vertex> vertices;                  // Dictionary: Keys -> Vertices
unordered_map<K, vector<Vertex*>> adjList;          // Dictionary: Keys -> List of Adjacent Vertices
vector<K> vertices_list;                            // List of vertex keys in the order they were added

Vertex*    bfsSource;                              // Variable to store the BFS source

int         time;                                   // Global time variable
void        dfs_helper      (K v);                  // Perform depth-first search (DFS) starting from vertex v
void        dfs             (void);                 // Perform depth-first search (DFS) on the entire graph

public:
            Graph           (vector<K> keys, vector<D> data, vector<vector<K>> edges);  // Constructor
Vertex*     get             (K key);          // Return a pointer to the vertex corresponding to key k
bool        reachable       (K u, K v);       // Indidate if v is reachable from u
void        bfs             (K s);            // Execute breadth-first search with source s
void        print_path      (K u, K v);       // Print the shortest path from u to v
string      edge_class      (K u, K v);       // Return the string representation of edge from u to v
void        bfs_tree        (K s);            // Print the bfs tree with source s
};

#include "graph.cpp"

#endif