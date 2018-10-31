//
// Created by SHIV SHANKAR SINGH
//

#include <bits/stdc++.h>

using namespace std;

#define REP(i, s, e) for(int i = s; i < e; i++)

bool ascii_mode = true;
int nodes_count  = 24;

// A list containing position of each node
vector< pair<int, int> > Nodes;
// The adjacency matrix containing edges list
vector< vector<int> > edges;

void reshape(){
    Nodes.resize(nodes_count);
    edges.resize(nodes_count, vector<int>(nodes_count));
}

int heuristic_manhattan(int first, int second){
    int result = abs(Nodes[first].first - Nodes[second].first) + abs(Nodes[first].second - Nodes[second].second);
    result *= 10;
    return result;
}

vector<int> moveGen(int node){
    vector<int> neighbour;
    REP(i, 0, nodes_count)
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
    vector< pair<int,int> > h_path = hill_climbing(x, y);

    //Printing the collected path
    cout << "Hill-Climbing Search Path: \n";
    REP(i, 0, h_path.size()){
        if( ascii_mode )
            cout << (char)(h_path[i].first + 'A') << " {" << h_path[i].second << (i+1 == h_path.size() ? "}" : "} -> ");
        else
            cout << setw(3) << (h_path[i].first + 1) << " {" << h_path[i].second << (i+1 == h_path.size() ? "}" : "} -> ");
    }
    cout << endl;

    return 0;
}