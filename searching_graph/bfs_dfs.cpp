//
// Created by SHIV SHANKAR SINGH on 18-08-2018.
//

#include <bits/stdc++.h>

using namespace std;

#define REP(i, s, e) for(int i = s; i < e; i++)
#define NODES_COUNT 24

// The adjacency matrix containing edges list
int edges[NODES_COUNT][NODES_COUNT];
// List containing parent pointers
int parent[NODES_COUNT];
// List containing visited status
bool visited[NODES_COUNT];

void print_path( int n ){
    if( parent[n] == -1 ){
        cout << " " << (char)(n+'A');
    }else{
        print_path( parent[n] );
        cout << " -> " << (char)(n+'A');
    }
}

vector<int> moveGen(int node){
    vector<int> neighbour;
    REP(i, 0, NODES_COUNT)
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
    char start, end;
    int edge_count;
    int x, y;

    // Initialising edges matrix
    REP(i, 0, NODES_COUNT)
        REP(j, 0, NODES_COUNT)
            edges[i][j] = 0;

    // Input edges count then each edge configuration
    cin >> edge_count;
    REP(i, 0, edge_count){
        cin >> start >> end;
        // Mapping character with integer
        x = start - 'A'; y = end - 'A';
        edges[x][y] = 1;
        edges[y][x] = 1;
    }

    // Inputing source and destination
    cin >> start >> end;
    x = start - 'A';
    y = end - 'A';

    cout << "Source: " << char(start) << "  Destination: " << char(end) << endl;
    cout << "Performing BFS: " << endl;
    if( bfs(x, y) ){
        cout << " Path Found: " << endl;
        print_path(y);
        cout << endl;
    }else{
        cout << " No Path Found!!!" << endl;
    }

    //clear visited
    REP(i, 0, NODES_COUNT)
        parent[i] = -1;
    REP(i, 0, NODES_COUNT)
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