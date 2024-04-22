//=================================
// Aryah Rao, Lam Do, Phuong Le
// Based on test_graph.example.cpp written by Dr. Stacey Truex
// test_graph.cpp
// April 2024
// This file tests methods from the Graph class.
//========================================================

#include "graph.h"

Graph<string, string> *generate_graph(string fname)
{
    string line;
    ifstream infile(fname);
    vector<string> keys = {};
    vector<string> data = {};
    vector<vector<string>> adjs = {};
    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            size_t delim = line.find(":");
            string key = line.substr(0, delim);
            string adj = line.substr(delim + 1);

            keys.push_back(key);
            data.push_back(key + " data");
            delim = adj.find(",");
            vector<string> adj_lst = {};
            while (delim != string::npos)
            {
                adj_lst.push_back(adj.substr(0, delim));
                adj = adj.substr(delim + 1);
                delim = adj.find(",");
            }
            adj_lst.push_back(adj);
            adjs.push_back(adj_lst);
        }
        infile.close();
    }
    Graph<string, string> *G = new Graph<string, string>(keys, data, adjs);
    return G;
}

void test_get(Graph<string, string> *G)
{
    try
    {
        if (G->get("S") == nullptr || G->get("S")->data != "S data")
        {
            cout << "Incorrect result getting vertex \"s\"" << endl;
        }
        if (G->get("a") != nullptr)
        {
            cout << "Incorrect result getting non-existant vertex \"a\"" << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }
}

void test_get() {

    try {
        // KEY BOOL DATA STRINGS
        vector<bool> keys = {1};
        vector<string> data = {"aryah"};
        vector<vector<bool>> edges = {{1}};
        Graph<string, bool> G(keys, data, edges);

        // Test getting an existing vertex
        if (G.get(1) == nullptr || G.get(1)->data != "aryah") {
            cout << "Incorrect result getting vertex \"1\"" << endl;
        }

        // Test getting a nonexistent vertex
        if (G.get(0) != nullptr) {
            cout << "Incorrect result getting nonexistent vertex \"2\"" << endl;
        }

    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    try {
        // KEY INTEGERS DATA STRINGS
        vector<int> keys = {-1, 0, 1};
        vector<string> data = {"aryah", "lam", "phuong"};
        vector<vector<int>> edges = {{-1, 0, 1}, {-1, 1}, {}};
        Graph<string, int> G(keys, data, edges);

        // Test getting an existing vertex
        if (G.get(-1) == nullptr || G.get(-1)->data != "aryah") {
            cout << "Incorrect result getting vertex \"-1\"" << endl;
        }

        // Test getting a non-existent vertex
        if (G.get(2) != nullptr) {
            cout << "Incorrect result getting non-existent vertex \"2\"" << endl;
        }

        // Test getting a vertex in an empty graph
        Graph<string, int> emptyGraph({}, {}, {});
        if (emptyGraph.get(0) != nullptr) {
            cout << "Incorrect result getting vertex from an empty graph" << endl;
        }

    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    try {
        // KEY FLOATS DATA CHARACTERS
        vector<float> keys = {-1.1, 0.1, 1.1};
        vector<char> data = {'a', 'l', 'p'};
        vector<vector<float>> edges = {{-1.1, 0.1, 1.1}, {-1.1, 1.1}, {}};
        Graph<char, float> G(keys, data, edges);

        // Test getting an existing vertex
        if (G.get(-1.1) == nullptr || G.get(-1.1)->data != 'a') {
            cout << "Incorrect result getting vertex \"-1.1\"" << endl;
        }

        // Test getting a non-existent vertex
        if (G.get(2.1) != nullptr) {
            cout << "Incorrect result getting non-existent vertex \"2.1\"" << endl;
        }

        // Test getting a vertex in an empty graph
        Graph<char, float> emptyGraph({}, {}, {});
        if (emptyGraph.get(0) != nullptr) {
            cout << "Incorrect result getting vertex from an empty graph" << endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    try {
        // KEY CHARACTERS DATA FLOATS
        vector<char> keys = {'a', 'l', 'p'};
        vector<float> data = {-1.1, 0.1, 1.1};
        vector<vector<char>> edges = {{'a', 'l', 'p'}, {'a', 'p'}, {}};
        Graph<float, char> G(keys, data, edges);

        // Test getting an existing vertex
        if (G.get('a') == nullptr || G.get('a')->data < -1.2 || G.get('a')->data > -1.0) {
            cout << "Incorrect result getting vertex 'a'" << endl;
        }

        // Test getting a non-existent vertex
        if (G.get('b') != nullptr) {
            cout << "Incorrect result getting non-existent vertex 'b'" << endl;
        }

        // Test getting a vertex in an empty graph
        Graph<float, char> emptyGraph({}, {}, {});
        if (emptyGraph.get(0) != nullptr) {
            cout << "Incorrect result getting vertex from an empty graph" << endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    try {
        // KEY STRINGS DATA INTEGERS
        vector<string> keys = {"aryah", "lam", "phuong"};
        vector<int> data = {-1, 0, 1};
        vector<vector<string>> edges = {{"aryah", "lam", "phuong"}, {"aryah", "phuong"}, {}};
        Graph<int, string> G(keys, data, edges);

        // Test getting an existing vertex
        if (G.get("aryah") == nullptr || G.get("aryah")->data != -1) {
            cout << "Incorrect result getting vertex \"aryah\"" << endl;
        }

        // Test getting a non-existent vertex
        if (G.get("casey") != nullptr) {
            cout << "Incorrect result getting non-existent vertex \"casey\"" << endl;
        }

        // Test getting a vertex in an empty graph
        Graph<int, string> emptyGraph({}, {}, {});
        if (emptyGraph.get("lam") != nullptr) {
            cout << "Incorrect result getting vertex from an empty graph" << endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    try {
        // KEY STRINGS DATA BOOL
        vector<string> keys = {"aryah", "lam", "phuong"};
        vector<bool> data = {true, true, false};
        vector<vector<string>> edges = {{"aryah", "lam", "phuong"}, {"aryah", "phuong"}, {}};
        Graph<bool, string> G(keys, data, edges);

        // Test getting an existing vertex
        if (G.get("aryah") == nullptr || G.get("aryah")->data != true) {
            cout << "Incorrect result getting vertex \"aryah\"" << endl;
        }

        // Test getting a non-existent vertex
        if (G.get("casey") != nullptr) {
            cout << "Incorrect result getting non-existent vertex \"casey\"" << endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}

void test_reachable(Graph<string, string> *G)
{
    try
    {
        if (!G->reachable("R", "V"))
        {
            cout << "Incorrectly identified adjacent vertex \"V\" as unreachable from \"R\"" << endl;
        }
        if (!G->reachable("X", "W"))
        {
            cout << "Incorrectly identified \"W\" as unreachable from \"X\"" << endl;
        }
        if (G->reachable("S", "A"))
        {
            cout << "Incorrectly identified non-existant vetex \"A\" as reachable from \"S\"" << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing reachable : " << e.what() << endl;
    }
}

void test_reachable() {
    try {
        // KEY INTEGERS DATA STRINGS
        vector<int> keys = {-1, 0, 1};
        vector<string> data = {"aryah", "lam", "phuong"};
        vector<vector<int>> edges = {{-1, 0, 1}, {-1, 1}, {}};
        Graph<string, int> G(keys, data, edges);

        // Test reachability between adjacent vertices
        if (!G.reachable(-1, 1)) {
            cout << "Incorrectly identified adjacent vertex 1 as unreachable from -1" << endl;
        }

        // Test reachability in the opposite direction
        if (!G.reachable(0, -1)) {
            cout << "Incorrectly identified -1 as unreachable from 0" << endl;
        }

        // Test reachability to a non-existent vertex
        if (G.reachable(1, 2)) {
            cout << "Incorrectly identified non-existent vertex 2 as reachable from 1" << endl;
        }

        // Test reachability in a disconnected graph
        Graph<string, int> disconnectedGraph(keys, data, {{-1}, {0}, {1}});
        if (disconnectedGraph.reachable(-1, 0)) {
            cout << "Incorrectly identified 0 as reachable from -1 in a disconnected graph" << endl;
        }

        // Test reachability from a vertex to itself
        if (!G.reachable(-1, -1)) {
            cout << "Incorrectly identified vertex -1 as unreachable from itself" << endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    try {
        // KEY FLOATS DATA CHARACTERS
        vector<float> keys = {-1.1, 0.1, 1.1};
        vector<char> data = {'a', 'l', 'p'};
        vector<vector<float>> edges = {{-1.1, 0.1, 1.1}, {-1.1, 1.1}, {}};
        Graph<char, float> G(keys, data, edges);

        // Test reachability between adjacent vertices
        if (!G.reachable(-1.1, 1.1)) {
            cout << "Incorrectly identified adjacent vertex 1.1 as unreachable from -1.1" << endl;
        }

        // Test reachability in the opposite direction
        if (!G.reachable(0.1, -1.1)) {
            cout << "Incorrectly identified -1.1 as unreachable from 0.1" << endl;
        }

        // Test reachability to a non-existent vertex
        if (G.reachable(1.1, 2.1)) {
            cout << "Incorrectly identified non-existent vertex 2.1 as reachable from 1.1" << endl;
        }

        // Test reachability from a vertex to itself
        if (!G.reachable(-1.1, -1.1)) {
            cout << "Incorrectly identified vertex -1.1 as unreachable from itself" << endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    try {
        // KEY CHARACTERS DATA FLOATS
        vector<char> keys = {'a', 'l', 'p'};
        vector<float> data = {-1.1, 0.1, 1.1};
        vector<vector<char>> edges = {{'a', 'l', 'p'}, {'a', 'p'}, {}};
        Graph<float, char> G(keys, data, edges);

        // Test reachability between adjacent vertices
        if (!G.reachable('a', 'p')) {
            cout << "Incorrectly identified adjacent vertex 'p' as unreachable from 'a'" << endl;
        }

        // Test reachability in the opposite direction
        if (!G.reachable('l', 'a')) {
            cout << "Incorrectly identified 'a' as unreachable from 'l'" << endl;
        }

        // Test reachability to a non-existent vertex
        if (G.reachable('l', 'b')) {
            cout << "Incorrectly identified non-existent vertex 'b' as reachable from 'l'" << endl;
        }

        // Test reachability from a vertex to itself
        if (!G.reachable('a', 'a')) {
            cout << "Incorrectly identified vertex a as unreachable from itself" << endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    try {
        // KEY STRINGS DATA INTEGERS
        vector<string> keys = {"aryah", "lam", "phuong"};
        vector<int> data = {-1, 0, 1};
        vector<vector<string>> edges = {{"aryah", "lam", "phuong"}, {"aryah", "phuong"}, {}};
        Graph<int, string> G(keys, data, edges);

        // Test reachability between adjacent vertices
        if (!G.reachable("aryah", "phuong")) {
            cout << "Incorrectly identified adjacent vertex \"phuong\" as unreachable from \"aryah\"" << endl;
        }

        // Test reachability in the opposite direction
        if (!G.reachable("lam", "aryah")) {
            cout << "Incorrectly identified \"aryah\" as unreachable from \"lam\"" << endl;
        }

        // Test reachability to a non-existent vertex
        if (G.reachable("lam", "casey")) {
            cout << "Incorrectly identified non-existent vertex \"casey\" as reachable from \"lam\"" << endl;
        }

        // Test reachability from a vertex to itself
        if (!G.reachable("phuong", "phuong")) {
            cout << "Incorrectly identified vertex phuong as unreachable from itself" << endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}

void test_bfs(Graph<string, string> *G)
{
    try
    {
        G->bfs("T");
        string vertices[8] = {"V", "R", "S", "W", "T", "X", "U", "Y"};
        int distances[8] = {3, 2, 1, 1, 0, 2, 1, 2};
        for (int i = 0; i < 8; i++)
        {
            if (G->get(vertices[i]) == nullptr || G->get(vertices[i])->distance != distances[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"t\"" << endl;
                cout << G->get(vertices[i])->distance << endl;
            }
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs : " << e.what() << endl;
    }
}

void test_bfs()
{
    try
    {
        // KEY INTEGERS DATA STRINGS
        vector<int> keys = {-1,0,1,2};
        vector<string> data = {"aryah", "lam", "phuong", "rao"};
        vector<vector<int>> edges = {{-1,0,1},{-1,1},{}, {}}; 

        Graph<string, int> G(keys, data, edges);

        // Test BFS on regular graph with one unconnected vertex
        G.bfs(-1);
        int vertices[4] = {-1,0,1,2};
        int distances[4] = {0,1,1,-1};
        for (int i = 0; i < 3; i++)
        {
            if (G.get(vertices[i]) == nullptr || G.get(vertices[i])->distance != distances[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"-1\"" << endl;
                cout << G.get(vertices[i])->distance << endl;
            }
        }

        // Test BFS on non-existent source
        G.bfs(3);

        for (int i = 0; i < 4; i++)
        {
            if (G.get(keys[i])->distance != -1)
            {
                cout << "Incorrect bfs result. Vertex " << keys[i] << " should have distance " << -1 << " from source vertex \"3\"" << endl;
                cout << G.get(keys[i])->distance << endl;
            }
        }

        // Test BFS on empty graph 
        Graph<string, int> emptyGraph({}, {}, {});
        emptyGraph.bfs(1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        // KEY FLOATS DATA CHARACTERS
        vector<float> keys = {-1.1,0.1,1.1,2.1};
        vector<char> data = {'a', 'l', 'p', 'r'};
        vector<vector<float>> edges = {{-1.1,0.1,1.1},{-1.1,1.1},{},{}}; 

        Graph<char, float> G(keys, data, edges);

        // Test BFS on regular graph with one unconnected vertex
        G.bfs(-1.1);
        float vertices[4] = {-1.1,0.1,1.1,2.1};
        int distances[4] = {0,1,1,-1};
        for (int i = 0; i < 4; i++)
        {
            if (G.get(vertices[i]) == nullptr || G.get(vertices[i])->distance != distances[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"-1\"" << endl;
                cout << G.get(vertices[i])->distance << endl;
            }
        }

        // Test BFS on non-existent source
        G.bfs(3.1);

        for (int i = 0; i < 4; i++)
        {
            if (G.get(keys[i])->distance != -1)
            {
                cout << "Incorrect bfs result. Vertex " << keys[i] << " should have distance " << -1 << " from source vertex \"3.1\"" << endl;
                cout << G.get(keys[i])->distance << endl;
            }
        }

        // Test BFS on empty graph 
        Graph<char, float> emptyGraph({}, {}, {});
        emptyGraph.bfs(1.1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        // KEY CHARACTERS DATA FLOATS
        vector<char> keys = {'a','l','p','r'};
        vector<float> data = {-1.1, 0.1, 1.1,2.1};
        vector<vector<char>> edges = {{'a','l','p'},{'a','p'},{},{}}; 

        Graph<float, char> G(keys, data, edges);

        // Test BFS on regular graph with one unconnected vertex
        G.bfs('a');
        char vertices[4] = {'a','l','p','r'};
        int distances[4] = {0,1,1,-1};
        for (int i = 0; i < 4; i++)
        {
            if (G.get(vertices[i]) == nullptr || G.get(vertices[i])->distance != distances[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex 'a' "<< endl;
                cout << G.get(vertices[i])->distance << endl;
            }
        }

        // Test BFS on non-existent source
        G.bfs('d');

        for (int i = 0; i < 4; i++)
        {
            if (G.get(keys[i])->distance != -1)
            {
                cout << "Incorrect bfs result. Vertex " << keys[i] << " should have distance " << -1 << " from source vertex \"d\"" << endl;
                cout << G.get(keys[i])->distance << endl;
            }
        }

        // Test BFS on empty graph 
        Graph<float, char> emptyGraph({}, {}, {});
        emptyGraph.bfs('d');
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        // KEY STRINGS DATA INTEGERS
        vector<string> keys = {"aryah","lam","phuong", "rao"};
        vector<int> data = {-1, 0, 1, 2};
        vector<vector<string>> edges = {{"aryah","lam","phuong"},{"aryah","phuong"},{}, {}}; 

        Graph<int, string> G(keys, data, edges);

        // Test BFS on regular graph with one unconnected vertex
        G.bfs("aryah");
        string vertices[4] = {"aryah","lam","phuong", "rao"};
        int distances[4] = {0,1,1,-1};
        for (int i = 0; i < 4; i++)
        {
            if (G.get(vertices[i]) == nullptr || G.get(vertices[i])->distance != distances[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"-1\"" << endl;
                cout << G.get(vertices[i])->distance << endl;
            }
        }

        // Test BFS on non-existent source
        G.bfs("do");

        for (int i = 0; i < 4; i++)
        {
            if (G.get(keys[i])->distance != -1)
            {
                cout << "Incorrect bfs result. Vertex " << keys[i] << " should have distance " << -1 << " from source vertex \"3.1\"" << endl;
                cout << G.get(keys[i])->distance << endl;
            }
        }

        // Test BFS on empty graph 
        Graph<int, string> emptyGraph({}, {}, {});
        emptyGraph.bfs("do");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void test_print_path(Graph<string, string> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path("T", "V");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T -> S -> R -> V")
        {
            cout << "Incorrect path from vertex \"T\" to vertex \"V\". Expected: T -> S -> R -> V but got : " << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }
}

void test_print_path()
{
    try
    {
        // KEY INTEGERS DATA STRINGS
        vector<int> keys = {-1,0,1};
        vector<string> data = {"aryah", "lam", "phuong"};
        vector<vector<int>> edges = {{-1,0,1},{-1,1},{}}; 

        Graph<string, int> G(keys, data, edges);

        // Print regular path
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());

        G.print_path(-1,1);
        cout.rdbuf(prevbuf);
        if (buffer.str() != "-1 -> 1")
        {
            cout << "Incorrect path from vertex \"-1\" to vertex \"1\". Expected: -1 -> 1 but got : " << buffer.str() << endl;
        }

        // Print non-existent path
        stringstream buffer1;
        streambuf *prevbuf1 = cout.rdbuf(buffer1.rdbuf());

        G.print_path(1,-1);
        cout.rdbuf(prevbuf1);
        if (buffer1.str() != "")
        {
            cout << "Incorrect path from vertex 1 to vertex -1. Expected: empty string but got : " << buffer.str() << endl;
        }

    }
    catch(const std::exception& e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }

    try
    {
        // KEY FLOATS DATA CHARACTERS
        vector<float> keys = {-1.1,0.1,1.1};
        vector<char> data = {'a', 'l', 'p'};
        vector<vector<float>> edges = {{-1.1,0.1,1.1},{-1.1,1.1},{}}; 

        Graph<char, float> G(keys, data, edges);

        // Print regular path
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G.print_path(-1.1,1.1);
        cout.rdbuf(prevbuf);
        if (buffer.str() != "-1.1 -> 1.1")
        {
            cout << "Incorrect path from vertex -1.1 to vertex 1.1. Expected: -1.1 -> 1.1 but got : " << buffer.str() << endl;
        }

        // Print non-existent path
        stringstream buffer1;
        streambuf *prevbuf1 = cout.rdbuf(buffer1.rdbuf());

        G.print_path(1.1,2.1);
        cout.rdbuf(prevbuf1);
        if (buffer1.str() != "")
        {
            cout << "Incorrect path from vertex 1.1 to vertex 2.1. Expected: empty string but got : " << buffer.str() << endl;
        }
    }
    catch(const std::exception& e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }

    try
    {
        // KEY CHARACTERS DATA FLOATS
        vector<char> keys = {'a','l','p'};
        vector<float> data = {-1.1, 0.1, 1.1};
        vector<vector<char>> edges = {{'a','l','p'},{'a','p'},{}}; 

        Graph<float, char> G(keys, data, edges);

        // Print regular path
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G.print_path('a','p');
        cout.rdbuf(prevbuf);
        if (buffer.str() != "a -> p")
        {
            cout << "Incorrect path from vertex a to vertex p. Expected: a -> p but got : " << buffer.str() << endl;
        }

        // Print non-existent path
        stringstream buffer1;
        streambuf *prevbuf1 = cout.rdbuf(buffer1.rdbuf());

        G.print_path('p','a');
        cout.rdbuf(prevbuf1);
        if (buffer1.str() != "")
        {
            cout << "Incorrect path from vertex p to vertex a. Expected: empty string but got : " << buffer.str() << endl;
        }
    }
    catch(const std::exception& e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }

    try
    {
        // KEY STRINGS DATA INTEGERS
        vector<string> keys = {"aryah","lam","phuong"};
        vector<int> data = {-1, 0, 1};
        vector<vector<string>> edges = {{"aryah","lam","phuong"},{"aryah","phuong"},{}}; 

        Graph<int, string> G(keys, data, edges);

        // Print regular path
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G.print_path("aryah","phuong");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "aryah -> phuong")
        {
            cout << "Incorrect path from vertex \"aryah\" to vertex \"phuong\". Expected: aryah -> phuong but got : " << buffer.str() << endl;
        }

        // Print non-existent path
        stringstream buffer1;
        streambuf *prevbuf1 = cout.rdbuf(buffer1.rdbuf());

        G.print_path("phuong","aryah");
        cout.rdbuf(prevbuf1);
        if (buffer1.str() != "")
        {
            cout << "Incorrect path from vertex \"phuong\" to vertex \"aryah\". Expected: empty string but got : " << buffer.str() << endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void test_edge_class(Graph<string, string> *G)
{
    try
    {
        string e_class = G->edge_class("R", "V"); // tree edge
        if (e_class != "tree edge")
        {
            cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
        }
        e_class = G->edge_class("X", "U"); // back edge
        if (e_class != "back edge")
        {
            cout << "Misidentified back edge (\"X\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("R", "U"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"R\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "W"); // forward edge
        if (e_class != "forward edge")
        {
            cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "S"); // cross edge
        if (e_class != "cross edge")
        {
            cout << "Misidentified forward edge (\"T\", \"S\") as : " << e_class << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
}

void test_edge_class()
{
    // KEY FLOAT DATA CHAR
    try
    {
        vector<float> keys = {-1.5,0.5,1.5,2};
        vector<char> data = {'a','l', 'm','c'};
        vector<vector<float>> edges = {{-1.5,0.5,1.5,2},{2},{-1.5,0.5},{2,-1.5}}; 

        Graph<char, float> G(keys, data, edges);
        string e_class = G.edge_class(-1.5, 0.5); // tree edge
        if (e_class != "tree edge")
        {
            cout << "Misidentified tree edge (-1.5, 0.5) as : " << e_class << endl;
        }
        e_class = G.edge_class(2,-1.5); // back edge
        if (e_class != "back edge")
        {
            cout << "Misidentified back edge (2,-1.5) as : " << e_class << endl;
        }
        e_class = G.edge_class(1.5,1.5); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (1.5,1.5) as : " << e_class << endl;
        }
        e_class = G.edge_class(2,1.5); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (2,1.5) as : " << e_class << endl;
        }
        e_class = G.edge_class(-1.5,2); // forward edge
        if (e_class != "forward edge")
        {
            cout << "Misidentified forward edge (-1.5,2) as : " << e_class << endl;
        }
        e_class = G.edge_class(1.5,0.5); // cross edge
        if (e_class != "cross edge")
        {
            cout << "Misidentified forward edge (1.5,0.5) as : " << e_class << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }

    // KEY INTEGER DATA FLOAT
    try
    {
        vector<int> keys = {-1,0,1,2};
        vector<float> data = {0.5,0.5,3.5,7.5};
        vector<vector<int>> edges = {{-1,0,1,2},{2},{-1,0},{2,-1}}; 

        Graph<float, int> G(keys, data, edges);
        string e_class = G.edge_class(-1, 0); // tree edge
        if (e_class != "tree edge")
        {
            cout << "Misidentified tree edge (-1, 0) as : " << e_class << endl;
        }
        e_class = G.edge_class(2,-1); // back edge
        if (e_class != "back edge")
        {
            cout << "Misidentified back edge (2,-1) as : " << e_class << endl;
        }
        e_class = G.edge_class(1,1); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (1,1) as : " << e_class << endl;
        }
        e_class = G.edge_class(2,1); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (2,1) as : " << e_class << endl;
        }
        e_class = G.edge_class(-1,2); // forward edge
        if (e_class != "forward edge")
        {
            cout << "Misidentified forward edge (-1,2) as : " << e_class << endl;
        }
        e_class = G.edge_class(1,0); // cross edge
        if (e_class != "cross edge")
        {
            cout << "Misidentified forward edge (1,0) as : " << e_class << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }

    // KEY CHAR DATA STRING
    try
    {
        vector<char> keys = {'3','0','1','2'};
        vector<string> data = {"0.5","0.5","3.5","7.5"};
        vector<vector<char>> edges = {{'3','0','1','2'},{'2'},{'3','0'},{'2','3'}}; 

        Graph<string, char> G(keys, data, edges);
        string e_class = G.edge_class('3', '0'); // tree edge
        if (e_class != "tree edge")
        {
            cout << "Misidentified tree edge ('3', '0') as : " << e_class << endl;
        }
        e_class = G.edge_class('2','3'); // back edge
        if (e_class != "back edge")
        {
            cout << "Misidentified back edge ('2','3') as : " << e_class << endl;
        }
        e_class = G.edge_class('1','1'); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge ('1','1') as : " << e_class << endl;
        }
        e_class = G.edge_class('2','1'); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge ('2','1') as : " << e_class << endl;
        }
        e_class = G.edge_class('3','2'); // forward edge
        if (e_class != "forward edge")
        {
            cout << "Misidentified forward edge ('3','2') as : " << e_class << endl;
        }
        e_class = G.edge_class('1','0'); // cross edge
        if (e_class != "cross edge")
        {
            cout << "Misidentified forward edge ('1','0') as : " << e_class << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }

    // KEY STRING DATA INT
    try
    {
        vector<string> keys = {"3","0","1","2"};
        vector<int> data = {0,0,3,7};
        vector<vector<string>> edges = {{"3","0","1","2"},{"2"},{"3","0"},{"2","3"}}; 

        Graph<int, string> G(keys, data, edges);
        string e_class = G.edge_class("3", "0"); // tree edge
        if (e_class != "tree edge")
        {
            cout << "Misidentified tree edge (\"3\", \"0\") as :  "<< e_class << endl;
        }
        e_class = G.edge_class("2","3"); // back edge
        if (e_class != "back edge")
        {
            cout << "Misidentified back edge (\"2\",\"3\") as :  "<< e_class << endl;
        }
        e_class = G.edge_class("1","1"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"1\",\"1\") as :  "<< e_class << endl;
        }
        e_class = G.edge_class("2","1"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"2\",\"1\") as :  "<< e_class << endl;
        }
        e_class = G.edge_class("3","2"); // forward edge
        if (e_class != "forward edge")
        {
            cout << "Misidentified forward edge (\"3\",\"2\") as :  "<< e_class << endl;
        }
        e_class = G.edge_class("1","0"); // cross edge
        if (e_class != "cross edge")
        {
            cout << "Misidentified forward edge (\"1\",\"0\") as :  "<< e_class << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree :  "<< e.what() << endl;
    }
}

void test_bfs_tree(Graph<string, string> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree("T");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T\nS U W\nR Y X\nV")
        {
            cout << "Incorrect bfs tree. Expected : \nT\nS U W\nR Y X\nV \nbut got :\n"
                 << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
}

void test_bfs_tree()
{
    // KEY FLOAT DATA CHAR
    try
    {
        vector<float> keys = {-1.5,0.5,1.5};
        vector<char> data = {'a','l', 'm'};
        vector<vector<float>> edges = {{-1.5,0.5,1.5},{-1.5,1.5},{}}; 

        Graph<char, float> G(keys, data, edges);

        // Test regular BFS tree
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G.bfs_tree(-1.5);
        cout.rdbuf(prevbuf);
        if (buffer.str() != "-1.5\n0.5 1.5")
        {
            cout << "Incorrect bfs tree. Expected : \n-1\n0 1 \n but got :\n"
                 << buffer.str() << endl;
        }

        // Test BFS tree with one level
        stringstream buffer1;
        streambuf *prevbuf1 = cout.rdbuf(buffer1.rdbuf());
        G.bfs_tree(1.5);
        cout.rdbuf(prevbuf1);
        if (buffer1.str() != "1.5")
        {
            cout << "Incorrect bfs tree. Expected : 1.5 but got :\n"
                 << buffer1.str() << endl;
        }

        // Test non-existent BFS tree
        stringstream buffer2;
        streambuf *prevbuf2 = cout.rdbuf(buffer2.rdbuf());
        G.bfs_tree(3.5);
        cout.rdbuf(prevbuf1);
        if (buffer2.str() != "")
        {
            cout << "Incorrect bfs tree. Expected : empty string but got :\n"
                 << buffer2.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }

    // KEY INTEGERS DATA STRINGS
    try
    {
        vector<int> keys = {-1,0,1};
        vector<string> data = {"aryah", "lam", "phuong"};
        vector<vector<int>> edges = {{-1,0,1},{-1,1},{}}; 

        Graph<string, int> G(keys, data, edges);

        // Test regular BFS tree
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G.bfs_tree(-1);
        cout.rdbuf(prevbuf);
        if (buffer.str() != "-1\n0 1")
        {
            cout << "Incorrect bfs tree. Expected : \n-1\n0 1 \n but got :\n"
                 << buffer.str() << endl;
        }

        // Test BFS tree with one level
        stringstream buffer1;
        streambuf *prevbuf1 = cout.rdbuf(buffer1.rdbuf());
        G.bfs_tree(1);
        cout.rdbuf(prevbuf1);
        if (buffer1.str() != "1")
        {
            cout << "Incorrect bfs tree. Expected : 1 but got :\n"
                 << buffer1.str() << endl;
        }

        // Test non-existent BFS tree
        stringstream buffer2;
        streambuf *prevbuf2 = cout.rdbuf(buffer2.rdbuf());
        G.bfs_tree(3);
        cout.rdbuf(prevbuf1);
        if (buffer2.str() != "")
        {
            cout << "Incorrect bfs tree. Expected : empty string but got :\n"
                 << buffer2.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }

    // KEY CHAR DATA INT
    try
    {
        vector<char> keys = {'a','b','c'};
        vector<int> data = {1, 2, 3};
        vector<vector<char>> edges = {{'a','b','c'},{'a','c'},{}}; 

        Graph<int, char> G(keys, data, edges);

        // Test regular BFS tree
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G.bfs_tree('a');
        cout.rdbuf(prevbuf);
        if (buffer.str() != "a\nb c")
        {
            cout << "Incorrect bfs tree. Expected : \na\nb c \n but got :\n"
                 << buffer.str() << endl;
        }

        // Test BFS tree with one level
        stringstream buffer1;
        streambuf *prevbuf1 = cout.rdbuf(buffer1.rdbuf());
        G.bfs_tree('c');
        cout.rdbuf(prevbuf1);
        if (buffer1.str() != "c")
        {
            cout << "Incorrect bfs tree. Expected : c but got :\n"
                 << buffer1.str() << endl;
        }

        // Test non-existent BFS tree
        stringstream buffer2;
        streambuf *prevbuf2 = cout.rdbuf(buffer2.rdbuf());
        G.bfs_tree('f');
        cout.rdbuf(prevbuf1);
        if (buffer2.str() != "")
        {
            cout << "Incorrect bfs tree. Expected : empty string but got :\n"
                 << buffer2.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }

    // KEY STRING DATA FLOAT
    try
    {
        vector<string> keys = {"a","b","c"};
        vector<float> data = {1.5,2.5, 3.5};
        vector<vector<string>> edges = {{"a","b","c"},{"a","c"},{}}; 

        Graph<float, string> G(keys, data, edges);

        // Test regular BFS tree
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G.bfs_tree("a");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "a\nb c")
        {
            cout << "Incorrect bfs tree. Expected : \na\nb c \n but got :\n"
                 << buffer.str() << endl;
        }

        // Test BFS tree with one level
        stringstream buffer1;
        streambuf *prevbuf1 = cout.rdbuf(buffer1.rdbuf());
        G.bfs_tree("c");
        cout.rdbuf(prevbuf1);
        if (buffer1.str() != "c")
        {
            cout << "Incorrect bfs tree. Expected : c but got :\n"
                 << buffer1.str() << endl;
        }

        // Test non-existent BFS tree
        stringstream buffer2;
        streambuf *prevbuf2 = cout.rdbuf(buffer2.rdbuf());
        G.bfs_tree("f");
        cout.rdbuf(prevbuf1);
        if (buffer2.str() != "")
        {
            cout << "Incorrect bfs tree. Expected : empty string but got :\n"
                 << buffer2.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }

    // KEY STRING DATA FLOAT WITH DUPLICATE KEY
    try
    {
        vector<string> keys = {"c","c"};
        vector<float> data = {2.5, 3.5};
        vector<vector<string>> edges = {{"c","c"},{"c","c"}}; 

        Graph<float, string> G(keys, data, edges);

        // Test non-existent BFS tree
        stringstream buffer2;
        streambuf *prevbuf2 = cout.rdbuf(buffer2.rdbuf());
        G.bfs_tree("c");
        cout.rdbuf(prevbuf2);
        if (buffer2.str() != "")
        {
            cout << "Incorrect bfs tree. Expected : empty string but got :\n"
                 << buffer2.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
    
}

int main()
{
    // Test case passed in by text file (From test_graph_example.cpp)
    Graph<string, string> *G = generate_graph("graph_description.txt");
    test_get(G);
    test_reachable(G);
    test_bfs(G);
    test_print_path(G);
    test_edge_class(G);
    test_bfs_tree(G);

    // Hard-coded test case
    test_get();
    test_reachable();
    test_bfs();
    test_edge_class();
    test_print_path();
    test_bfs_tree();

    cout << "Testing completed" << endl;

    delete G;

    return 0;
}


