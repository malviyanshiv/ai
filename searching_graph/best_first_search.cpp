//
// Created by SHIV SHANKAR SINGH
//

#include <bits/stdc++.h>

using namespace std;

#define REP(i, s, e) for(int i = s; i < e; i++)
int nodes_count = 24;
bool ascii_mode = true;

// A list containing position of each node
vector< pair<int, int> > Nodes;
// The adjacency matrix containing edges list
vector< vector<int> > edges;
int heuristic_manhattan(int first, int second){
    int result = abs(Nodes[first].first - Nodes[second].first) + abs(Nodes[first].second - Nodes[second].second);
    result *= 10;
    return result;
}

void reshape(){
    Nodes.resize(nodes_count);
    edges.resize(nodes_count, vector<int>(nodes_count));
}

void print_path( vector<int>& parent, int n ){
    if( parent[n] == -1 ){
        if( ascii_mode )
            cout << " " << (char)(n+'A');
        else
            cout << " " << n+1;
    }else{
        print_path( parent, parent[n] );
        if( ascii_mode )
            cout << " -> " << (char)(n+'A');
        else
            cout << " -> " << n+1;
    }
}

vector<int> moveGen(int node){
    vector<int> neighbour;
    REP(i, 0, nodes_count)
        if( edges[i][node] == 1 ) // is a neighbour
            neighbour.push_back(i);
    return neighbour;
}

vector<int> best_first_search(int source, int end){
    priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > Q;
    vector<int> path(nodes_count, -1);
    vector<bool> visited(nodes_count, false);
    Q.push( make_pair( heuristic_manhattan(source, end), source));
    visited[source] = true;

    while( ! Q.empty() ){
        int current = Q.top().second;
        cout << (char) (current+'A') << " {" << Q.top().first << "} ";
        Q.pop();
        if( current == end )
            break;
        for(int next: moveGen(current)){
            if( ! visited[next] ){
                visited[next] = true;
                Q.push( make_pair( heuristic_manhattan(next, end), next));
                path[next] = current;
            }
        }
        if( !Q.empty())
            cout << "-> ";
    }
    cout << endl;
    return path;
}

int main(){
    char startc='a', endc='a';
    int starti=0, endi=0;
    int edge_count;
    int x, y, w;
    char mode='1';

    // Initialising edges matrix
    cin >> mode;
    if(mode == 'A')
        ascii_mode = true;
    else
        ascii_mode = false;
    cin >> nodes_count;
    reshape();
    REP(i, 0, nodes_count)
        REP(j, 0, nodes_count)
            edges[i][j] = 0;

    // Input position of every node assuming order
    REP(i, 0, nodes_count)
        cin >> Nodes[i].first >> Nodes[i].second;

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
    
    cout << "Oder of Nodes in Best First Search: \n";
    vector<int> b_path = best_first_search(x, y);
    if( b_path[y] == -1 ) {
        if( ascii_mode )
            cout << "Unable to find Best Fist Search Path between: " << startc << " -> " << endc << endl;
        else
            cout << "Unable to find Best Fist Search Path between: " << starti << " -> " << endi << endl;
    }
    else{
        cout << "Best First Search Path: \n";
        print_path( b_path, y );
        cout << endl;
    }

    return 0;
}