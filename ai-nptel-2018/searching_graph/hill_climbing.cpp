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

vector< pair<int, int> > hill_climbing(int source, int end){
    vector< pair<int, int> > path;
    int current_node = source;
    int current_weight = heuristic_manhattan(source, end);
    path.push_back(make_pair(current_node, current_weight));
    while( true ){
        int next_best_node = -1, next_best_weight = INT32_MAX;
        for( int current : moveGen( current_node )){
            int weight = heuristic_manhattan( current, end );
            if( next_best_weight > weight ){
                next_best_node = current;
                next_best_weight = weight;
            }
        }
        if( next_best_weight < current_weight ){
            current_node = next_best_node;
            current_weight = next_best_weight;
            path.push_back(make_pair(current_node, current_weight));
        }else{
            break;
        }
    }
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
    vector< pair<int,int> > h_path = hill_climbing(x, y);
    cout << "Hill-Climbing Search Path: \n";
    REP(i, 0, h_path.size())
        cout << (char)(h_path[i].first + 'A') << " {" << h_path[i].second << (i+1 == h_path.size() ? "}" : "} -> ");
    cout << endl;

    return 0;
}