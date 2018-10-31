//
// Created by SHIV SHANKAR SINGH on 18-08-2018.
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
// List for keeping the parent pointers
vector<int> parent;
// List for maintaining the known best path
vector<int> dis, G;
// List for checking the presence of node in list
// 0 - new   1 - OPEN    2 - CLOSED
vector<int> state;

void initialise(){
    REP(i, 0, nodes_count){
        parent[i] = -1;
        dis[i] = 0;
        G[i] = 0;
        state[i] = 0;
    }
}

void reshape(){
    Nodes.resize(nodes_count);
    edges.resize(nodes_count, vector<int>(nodes_count));
    parent.resize(nodes_count, -1);
    dis.resize(nodes_count);
    state.resize(nodes_count);
    G.resize(nodes_count);
}

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
    REP(i, 0, nodes_count)
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
        if( ascii_mode )
            cout << " Node : " << setw(3) << (char)(node+'A') << " f(n): " << setw(3) << dis[node] << " g(n): " << setw(3) << G[node] << " h(n): " << setw(3) << heuristic_manhattan(node, end) << endl;
        else
            cout << " Node : " << setw(3) << node+1 << " f(n): " << setw(3) << dis[node] << " g(n): " << setw(3) << G[node] << " h(n): " << setw(3) << heuristic_manhattan(node, end) << endl;
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
        if( ascii_mode )
            cout << " Node : " << setw(3) << (char)(node+'A') << " f(n): " << setw(3) << dis[node] << " g(n): " << setw(3) << G[node] << " h(n): " << setw(3) << heuristic_manhattan(node, end) << endl;
        else
            cout << " Node : " <<  setw(3) << node+1 << " f(n): " << setw(3) << dis[node] << " g(n): " << setw(3) << G[node] << " h(n): " << setw(3) << heuristic_manhattan(node, end) << endl;
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
            cin >> startc >> endc >> w;
        else
            cin >> starti >> endi >> w;
        if( ascii_mode ){
            x = startc - 'A';
            y = endc - 'A';
        }else{
            x = starti-1;
            y = endi-1;
        }
        edges[x][y] = w;
        edges[y][x] = w;
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

    cout << "Using Manhattan Distance as heuristic function:" << endl;
    cout << "Oder of processing nodes: " << endl;
    if( a_star_manhattan(x, y) ){
        cout << "Path Found : \n" ;
        print_path(y);
        cout << endl;

        cout << "G(n) for all nodes:";
        REP(i, 0, nodes_count){
            if(i%3 == 0)
                cout << endl;
            if( ascii_mode )
                cout << (char)(i+'A') << " -> " << setw(3) << (state[i] != 0 ? to_string(G[i]): "no") <<"   ";
            else
                cout << i+1 << " -> " << setw(3) << (state[i] != 0 ? to_string(G[i]): "no") <<"   ";

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
        REP(i, 0, nodes_count){
            if(i%3 == 0)
                cout << endl;
            if( ascii_mode )
                cout << (char)(i+'A') << " -> " << setw(3) << (state[i] != 0 ? to_string(G[i]): "no") <<"   ";
            else
                cout << i+1 << " -> " << setw(3) << (state[i] != 0 ? to_string(G[i]): "no") <<"   ";
        }
        cout << endl;
    }else{
        cout << "No path was found!!!" << endl;
    }

    return 0;
}