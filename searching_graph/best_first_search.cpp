//
// Created by SHIV SHANKAR SINGH
//

#include <bits/stdc++.h>

using namespace std;

#define REP(i, s, e) for(int i = s; i < e; i++)
#define NODES_COUNT 24

// A list containing position of each node
vector< pair<int, int> > Nodes(NODES_COUNT);
// The adjacency matrix containing edges list
int edges[NODES_COUNT][NODES_COUNT];

int heuristic_manhattan(int first, int second){
    int result = abs(Nodes[first].first - Nodes[second].first) + abs(Nodes[first].second - Nodes[second].second);
    result *= 10;
    return result;
}

void print_path( vector<int> path , int n ){
    if( path[n] == -1 ){
        cout << (char)(n+'A');
    }else{
        print_path( path, path[n] );
        cout << " -> " << (char)(n+'A');
    }
}

vector<int> moveGen(int node){
    vector<int> neighbour;
    REP(i, 0, NODES_COUNT)
        if( edges[i][node] == 1 ) // is a neighbour
            neighbour.push_back(i);
    return neighbour;
}

vector<int> best_first_search(int source, int end){
    priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > Q;
    vector<int> path(NODES_COUNT, -1);
    vector<bool> visited(NODES_COUNT, false);
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
    char start, end;
    int edge_count;
    int x, y;

    // Initialising edges matrix
    REP(i, 0, NODES_COUNT)
        REP(j, 0, NODES_COUNT)
            edges[i][j] = 0;

    // Input position of every node assuming order
    REP(i, 0, NODES_COUNT)
        cin >> Nodes[i].first >> Nodes[i].second;

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

    cout << "Source : " << start << " , Destination: " << end <<endl;
    cout << "Oder of Nodes in Best First Search: \n";
    vector<int> b_path = best_first_search(x, y);
    if( b_path[y] == -1 ) {
        cout << "Unable to find Best Fist Search Path between: " << start << " -> " << end << endl;
    }
    else{
        cout << "Best First Search Path: \n";
        print_path( b_path, y );
        cout << endl;
    }

    return 0;
}