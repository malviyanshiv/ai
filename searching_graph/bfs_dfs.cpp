//
// Created by SHIV SHANKAR SINGH on 18-08-2018.
//

#include <bits/stdc++.h>

using namespace std;

#define REP(i, s, e) for(int i = s; i < e; i++)

bool ascii_mode = true;
int nodes_count  = 24;

// The adjacency matrix containing edges list
vector< vector<int> > edges;
// List containing parent pointers
vector<int> parent;
// List containing visited status
vector<bool> visited;

void print_path( int n ){
    if( parent[n] == -1 ){
        if( ascii_mode )
            cout << " " << (char)(n+'A');
        else
            cout << " " << n+1;
    }else{
        print_path( parent[n] );
        if( ascii_mode )
            cout << " -> " << (char)(n+'A');
        else
            cout << " -> " << n+1;
    }
}

void initialise(){
    edges.resize(nodes_count, vector<int>(nodes_count));
    parent.resize(nodes_count);
    visited.resize(nodes_count);
}

vector<int> moveGen(int node){
    vector<int> neighbour;
    REP(i, 0, nodes_count)
        if( edges[i][node] == 1 ) // is a neighbour
            neighbour.push_back(i);
    // Visited the neighbour in sorted order
    sort(neighbour.begin(), neighbour.end());
    return neighbour;
}

bool bfs(int start, int goal){
    queue<int> Q;
    Q.push(start);
    parent[start] = -1;
    visited[start] = true;
    while( !Q.empty() ){
        int node = Q.front();
        Q.pop();
        if( node == goal )
            return true;
        for(int c: moveGen(node)){
            if( ! visited[c] ){
                visited[c] = true;
                parent[c] = node;
                Q.push(c);
            }
        }
    }
    return false;
}

bool dfs(int start, int goal){
    stack<int> S;
    S.push(start);
    parent[start] = -1;
    visited[start] = true;
    while(! S.empty() ){
        int node = S.top();
        S.pop();
        if( node == goal )
            return true;
        for(int c: moveGen(node)){
            if( ! visited[c] ){
                visited[c] = true;
                parent[c] = node;
                S.push(c);
            }
        }
    }
    return false;
}

int main(){
    int edge_count;
    int x, y;
    int starti=0, endi=0;
    char startc='a', endc='a';
    char mode='1';

    //nodes count
    cin >> mode;
    cin >> nodes_count;
    initialise();
    if (mode == 'A')
        ascii_mode = true;
    else
        ascii_mode = false;
    // Initialising edges matrix
    REP(i, 0, nodes_count)
        REP(j, 0, nodes_count)
            edges[i][j] = 0;

    // Input edges count then each edge configuration
    cin >> edge_count;
    REP(i, 0, edge_count){
        if( ascii_mode )
            cin >> startc >> endc;
        else
            cin >> starti >> endi;
        if( ascii_mode ){
            x = startc - 'A';
            y = endc - 'A';
        }else{
            x = starti-1;
            y = endi-1;
        }
        edges[x][y] = 1;
        edges[y][x] = 1;
    }
    // Inputing source and destination
    if( ascii_mode )
        cin >> startc >> endc;
    else
        cin >> starti >> endi;
    if( ascii_mode ){
        x = startc - 'A';
        y = endc - 'A';
    }else{
        x = starti-1;
        y = endi-1;
    }
    if( ascii_mode )
        cout << "Source: " << char(startc) << "  Destination: " << char(endc) << endl;
    else
        cout << "Source: " << starti << "  Destination: " << endi << endl;
    cout << "Performing BFS: " << endl;
    if( bfs(x, y) ){
        cout << " Path Found: " << endl;
        print_path(y);
        cout << endl;
    }else{
        cout << " No Path Found!!!" << endl;
    }

    //clear visited
    REP(i, 0, nodes_count)
        parent[i] = -1;
    REP(i, 0, nodes_count)
        visited[i] = false;

    cout << "Performing DFS: " << endl;
    if( dfs(x, y) ){
        cout << " Path Found: " << endl;
        print_path(y);
        cout << endl;
    }else{
        cout << " No Path Found!!!" << endl;
    }
    

    return 0;
}