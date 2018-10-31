//
// Created by SHIV SHANKAR SINGH on 18-08-2018.
//

#include <bits/stdc++.h>

using namespace std;

#define REP(i, s, e) for(int i = s; i < e; i++)
#define NODES_COUNT 24

// A list containing position of each node
vector< pair<int, int> > Nodes(NODES_COUNT);
// The adjacency matrix containing edges list
int edges[NODES_COUNT][NODES_COUNT];
// List for keeping the parent pointers
vector<int> parent(NODES_COUNT, -1);
// List for maintaining the known best path
vector<int> dis(NODES_COUNT, 0), G(NODES_COUNT, 0);
// List for checking the presence of node in list
// 0 - new   1 - OPEN    2 - CLOSED
vector<int> state(NODES_COUNT, 0);

void initialise(){
    REP(i, 0, NODES_COUNT){
        parent[i] = -1;
        dis[i] = 0;
        G[i] = 0;
        state[i] = 0;
    }
}

void print_path(int n){
    if( parent[n] == -1){
        cout << (char)(n+'A') << " ";
        return;
    }
    print_path(parent[n]);
    cout << " --> " << (char)(n+'A');
}

int heuristic_manhattan(int first, int second){
    int result = abs(Nodes[first].first - Nodes[second].first) + abs(Nodes[first].second - Nodes[second].second);
    result *= 10;
    return result;
}

int heuristic_eucledian(int first, int second){
    int result = (Nodes[first].first - Nodes[second].first)*(Nodes[first].first - Nodes[second].first);
    result += (Nodes[first].second - Nodes[second].second)*(Nodes[first].second - Nodes[second].second);
    result*=100;
    return (int)sqrt(result);
}

class Comparator{
public:
    bool operator()(const int a, const int b){
        if( dis[a] == dis[b] )
            return a > b;
        return dis[a] > dis[b];
    }
};

vector<int> moveGen(int node){
    vector<int> neighbour;
    REP(i, 0, NODES_COUNT)
        if( edges[i][node] != 0 ) // is a neighbour
            neighbour.push_back(i);
    return neighbour;
}

void propagate_improvement(int m){
    for(int s: moveGen(m)){
        int new_val = G[m] + edges[s][m];
        if( new_val < G[s] ){
            parent[s] = m;
            G[s] = new_val;
            if( state[s] == 2 )
                propagate_improvement(s);
        }
    }
}

bool a_star_manhattan(int start, int end){
    vector<int> v;
    dis[start] = heuristic_manhattan(start, end);
    G[start] = 0;
    v.push_back(start);
    state[start] = 1;
    make_heap(v.begin(), v.end(), Comparator());
    while(!v.empty()){
        pop_heap(v.begin(), v.end(), Comparator());
        int node = v.back();
        v.pop_back();
        state[node] = 2;
        cout << " Node : " << (char)(node+'A') << " f(n): " << setw(3) << dis[node] << " g(n): " << setw(3) << G[node] << " h(n): " << setw(3) << heuristic_manhattan(node, end) << endl;
        if( node == end )
            return true;
        for(int c: moveGen(node)){
            if( state[c] == 0 ){
                state[c] = 1;
                parent[c] = node;
                G[c] = G[node] + edges[c][node];
                dis[c] = G[c] + heuristic_manhattan(c, end);
                v.push_back(c);
                push_heap(v.begin(), v.end(), Comparator());
            }else if( state[c] == 1){
                if( G[c] > (G[node] + edges[c][node])){
                    parent[c] = node;
                    G[c] = G[node] + edges[c][node];
                    dis[c] = G[c] + heuristic_manhattan(c, end);
                    make_heap(v.begin(),v.end(), Comparator());
                }
            }else{
                if( G[c] > (G[node] + edges[c][node])){
                    parent[c] = node;
                    G[c] = G[node] + edges[c][node];
                    dis[c] = G[c] + heuristic_manhattan(c, end);
                    propagate_improvement(c);
                    make_heap(v.begin(), v.end(), Comparator());
                }

            }
        }
    }
    return false;
}

bool a_star_euclidean(int start, int end){
    vector<int> v;
    dis[start] = heuristic_eucledian(start, end);
    G[start] = 0;
    v.push_back(start);
    state[start] = 1;
    make_heap(v.begin(), v.end(), Comparator());
    while(!v.empty()){
        pop_heap(v.begin(), v.end(), Comparator());
        int node = v.back();
        v.pop_back();
        state[node] = 2;
        cout << " Node : " << (char)(node+'A') << " f(n): " << setw(3) << dis[node] << " g(n): " << setw(3) << G[node] << " h(n): " << setw(3) << heuristic_eucledian(node, end) << endl;
        if( node == end )
            return true;
        for(int c: moveGen(node)){
            if( state[c] == 0 ){
                state[c] = 1;
                parent[c] = node;
                G[c] = G[node] + edges[c][node];
                dis[c] = G[c] + heuristic_eucledian(c, end);
                v.push_back(c);
                push_heap(v.begin(), v.end(), Comparator());
            }else if( state[c] == 1){
                if( G[c] > (G[node] + edges[c][node])){
                    parent[c] = node;
                    G[c] = G[node] + edges[c][node];
                    dis[c] = G[c] + heuristic_manhattan(c, end);
                    make_heap(v.begin(),v.end(), Comparator());
                }
            }else{
                if( G[c] > (G[node] + edges[c][node])){
                    parent[c] = node;
                    G[c] = G[node] + edges[c][node];
                    dis[c] = G[c] + heuristic_eucledian(c, end);
                    propagate_improvement(c);
                    make_heap(v.begin(), v.end(), Comparator());
                }

            }
        }
    }
    return false;
}

int main(){
    char start, end;
    int edge_count;
    int x, y, w;

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
        cin >> start >> end >> w;
        // Mapping character with integer
        x = start - 'A'; y = end - 'A';
        edges[x][y] = w;
        edges[y][x] = w;
    }

    // Inputing source and destination
    cin >> start >> end;
    x = start - 'A';
    y = end - 'A';

    cout << "Source : " << start << " , Destination: " << end <<endl;

    cout << "Using Manhattan Distance as heuristic function:" << endl;
    cout << "Oder of processing nodes: " << endl;
    if( a_star_manhattan(x, y) ){
        cout << "Path Found : \n" ;
        print_path(y);
        cout << endl;

        cout << "G(n) for all nodes:";
        REP(i, 0, NODES_COUNT){
            if(i%3 == 0)
                cout << endl;
            cout << (char)(i+'A') << " -> " << setw(3) << (state[i] != 0 ? to_string(G[i]): "no") <<"   ";
        }
        cout << endl;
    }else{
        cout << "No path was found!!!" << endl;
    }
    cout << endl;
    cout << "Using Eucledian Distance as heuristic function:" << endl;
    initialise();
    cout << "Oder of processing nodes: " << endl;
    if( a_star_euclidean(x, y) ){
        cout << "Path Found : \n" ;
        print_path(y);
        cout << endl;

        cout << "G(n) for all nodes:";
        REP(i, 0, NODES_COUNT){
            if(i%3 == 0)
                cout << endl;
            cout << (char)(i+'A') << " -> " << setw(3) << (state[i] != 0 ? to_string(G[i]): "no") <<"   ";
        }
        cout << endl;
    }else{
        cout << "No path was found!!!" << endl;
    }

    return 0;
}