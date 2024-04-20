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

void test_get()
{
    try
    {
        // KEY INTEGERS DATA STRINGS
        vector<int> keys = {-1,0,1};
        vector<string> data = {"aryah", "lam", "phuong"};
        vector<vector<int>> edges = {{-1,0,1},{-1,1},{}}; 

        Graph<string, int> G(keys, data, edges);

        if (G.get(-1) == nullptr || G.get(-1)->data != "aryah")
        {
            cout << "Incorrect result getting vertex \"-1\"" << endl;
        }
        if (G.get(2) != nullptr)
        {
            cout << "Incorrect result getting non-existant vertex \"2\"" << endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        // KEY FLOATS DATA CHARACTERS
        vector<float> keys = {-1.1,0.1,1.1};
        vector<char> data = {'a', 'l', 'p'};
        vector<vector<float>> edges = {{-1.1,0.1,1.1},{-1.1,1.1},{}}; 

        Graph<char, float> G(keys, data, edges);

        if (G.get(-1.1) == nullptr || G.get(-1.1)->data != 'a')
        {
            cout << "Incorrect result getting vertex \"-1.1\"" << endl;
        }
        if (G.get(2.1) != nullptr)
        {
            cout << "Incorrect result getting non-existant vertex \"2.1\"" << endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        // KEY CHARACTERS DATA FLOATS
        vector<char> keys = {'a','l','p'};
        vector<float> data = {-1.1, 0.1, 1.1};
        vector<vector<char>> edges = {{'a','l','p'},{'a','p'},{}}; 

        Graph<float, char> G(keys, data, edges);

        if (G.get('a') == nullptr || G.get('a')->data > -1 && G.get('a')->data < -1.2)
        {
            cout << "Incorrect result getting vertex \'a\'" << endl;
        }
        if (G.get('b') != nullptr)
        {
            cout << "Incorrect result getting non-existant vertex \"b\"" << endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        // KEY STRINGS DATA INTEGERS
        vector<string> keys = {"aryah","lam","phuong"};
        vector<int> data = {-1, 0, 1};
        vector<vector<string>> edges = {{"aryah","lam","phuong"},{"aryah","phuong"},{}}; 

        Graph<int, string> G(keys, data, edges);

        if (G.get("aryah") == nullptr || G.get("aryah")->data != -1)
        {
            cout << "Incorrect result getting vertex \"aryah\"" << endl;
        }
        if (G.get("casey") != nullptr)
        {
            cout << "Incorrect result getting non-existant vertex \"aryah\"" << endl;
        }
    }
    catch(const std::exception& e)
    {
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

void test_reachable()
{
    try
    {
        // KEY INTEGERS DATA STRINGS
        vector<int> keys = {-1,0,1};
        vector<string> data = {"aryah", "lam", "phuong"};
        vector<vector<int>> edges = {{-1,0,1},{-1,1},{}}; 

        Graph<string, int> G(keys, data, edges);

        if (!G.reachable(-1, 1))
        {
            cout << "Incorrectly identified adjacent vertex 1 as unreachable from -1" << endl;
        }
        if (!G.reachable(0, -1))
        {
            cout << "Incorrectly identified -1 as unreachable from 0" << endl;
        }
        if (G.reachable(1,2))
        {
            cout << "Incorrectly identified non-existant vetex 2 as reachable from 1" << endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        // KEY FLOATS DATA CHARACTERS
        vector<float> keys = {-1.1,0.1,1.1};
        vector<char> data = {'a', 'l', 'p'};
        vector<vector<float>> edges = {{-1.1,0.1,1.1},{-1.1,1.1},{}}; 

        Graph<char, float> G(keys, data, edges);

        if (!G.reachable(-1.1, 1.1))
        {
            cout << "Incorrectly identified adjacent vertex 1.1 as unreachable from -1.1" << endl;
        }
        if (!G.reachable(0.1, -1.1))
        {
            cout << "Incorrectly identified -1.1 as unreachable from 0.1" << endl;
        }
        if (G.reachable(1.1,2.1))
        {
            cout << "Incorrectly identified non-existant vetex 2.1 as reachable from 1.1" << endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        // KEY CHARACTERS DATA FLOATS
        vector<char> keys = {'a','l','p'};
        vector<float> data = {-1.1, 0.1, 1.1};
        vector<vector<char>> edges = {{'a','l','p'},{'a','p'},{}}; 

        Graph<float, char> G(keys, data, edges);

        if (!G.reachable('a', 'p'))
        {
            cout << "Incorrectly identified adjacent vertex \'p\' as unreachable from \'a\'" << endl;
        }
        if (!G.reachable('l', 'p'))
        {
            cout << "Incorrectly identified \'l\' as unreachable from \'p\'" << endl;
        }
        if (G.reachable('l','b'))
        {
            cout << "Incorrectly identified non-existant vetex \'b\' as reachable from \'l\'" << endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        // KEY STRINGS DATA INTEGERS
        vector<string> keys = {"aryah","lam","phuong"};
        vector<int> data = {-1, 0, 1};
        vector<vector<string>> edges = {{"aryah","lam","phuong"},{"aryah","phuong"},{}}; 

        Graph<int, string> G(keys, data, edges);

        if (!G.reachable("aryah", "phuong"))
        {
            cout << "Incorrectly identified adjacent vertex \"phuong\" as unreachable from \"aryah\"" << endl;
        }
        if (!G.reachable("lam", "phuong"))
        {
            cout << "Incorrectly identified \"lam\" as unreachable from \"phuong\"" << endl;
        }
        if (G.reachable("lam","casey"))
        {
            cout << "Incorrectly identified non-existant vetex \"lam\" as reachable from \"casey\"" << endl;
        }
    }
    catch(const std::exception& e)
    {
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

        G.bfs(-1);
        int vertices[3] = {-1,0,1};
        int distances[3] = {0,1,1};
        for (int i = 0; i < 3; i++)
        {
            if (G.get(vertices[i]) == nullptr || G.get(vertices[i])->distance != distances[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"-1\"" << endl;
                cout << G.get(vertices[i])->distance << endl;
            }
        }

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

        G.bfs(-1.1);
        float vertices[3] = {-1.1,0.1,1.1};
        int distances[3] = {0,1,1};
        for (int i = 0; i < 3; i++)
        {
            if (G.get(vertices[i]) == nullptr || G.get(vertices[i])->distance != distances[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"-1\"" << endl;
                cout << G.get(vertices[i])->distance << endl;
            }
        }
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

        G.bfs('a');
        char vertices[3] = {'a','l','p'};
        int distances[3] = {0,1,1};
        for (int i = 0; i < 3; i++)
        {
            if (G.get(vertices[i]) == nullptr || G.get(vertices[i])->distance != distances[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"-1\"" << endl;
                cout << G.get(vertices[i])->distance << endl;
            }
        }
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

        G.bfs("aryah");
        string vertices[3] = {"aryah","lam","phuong"};
        int distances[3] = {0,1,1};
        for (int i = 0; i < 3; i++)
        {
            if (G.get(vertices[i]) == nullptr || G.get(vertices[i])->distance != distances[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"-1\"" << endl;
                cout << G.get(vertices[i])->distance << endl;
            }
        }
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

        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G.print_path(-1,1);
        cout.rdbuf(prevbuf);
        if (buffer.str() != "-1 -> 1")
        {
            cout << "Incorrect path from vertex \"-1\" to vertex \"1\". Expected: -1 -> 1 but got : " << buffer.str() << endl;
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

        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G.print_path(-1.1,1.1);
        cout.rdbuf(prevbuf);
        if (buffer.str() != "-1.1 -> 1.1")
        {
            cout << "Incorrect path from vertex \"-1.1\" to vertex \"1.1\". Expected: -1.1 -> 1.1 but got : " << buffer.str() << endl;
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

        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G.print_path('a','p');
        cout.rdbuf(prevbuf);
        if (buffer.str() != "a -> p")
        {
            cout << "Incorrect path from vertex \"a\" to vertex \"p\". Expected: a -> p but got : " << buffer.str() << endl;
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

        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G.print_path("aryah","phuong");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "aryah -> phuong")
        {
            cout << "Incorrect path from vertex \"aryah\" to vertex \"phuong\". Expected: aryah -> phuong but got : " << buffer.str() << endl;
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
    // KEY FLOAT DATA STRINGS
    try
    {
        vector<float> keys = {-1.5,0.5,1.5};
        vector<string> data = {"aryah", "lam", "phuong"};
        vector<vector<float>> edges = {{-1.5,0.5,1.5},{-1.5,1.5},{}}; 

        Graph<string, float> G(keys, data, edges);
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G.bfs_tree(-1.5);
        cout.rdbuf(prevbuf);
        if (buffer.str() != "-1.5\n0.5 1.5")
        {
            cout << "Incorrect bfs tree. Expected : \n-1\n0 1 \n but got :\n"
                 << buffer.str() << endl;
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
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G.bfs_tree(-1);
        cout.rdbuf(prevbuf);
        if (buffer.str() != "-1\n0 1")
        {
            cout << "Incorrect bfs tree. Expected : \n-1\n0 1 \n but got :\n"
                 << buffer.str() << endl;
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
    test_print_path();
    test_bfs_tree();

    cout << "Testing completed" << endl;

    delete G;

    return 0;
}


