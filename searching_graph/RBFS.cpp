//
// Created by SHIV SHANKAR SINGH on 18-08-2018.
//

#include <bits/stdc++.h>

using namespace std;

#define REP(i, s, e) for(int i = s; i < e; i++)
#define INF 1000000007

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

void reshape(){
    Nodes.resize(nodes_count);
    edges.resize(nodes_count, vector<int>(nodes_count));
    parent.resize(nodes_count, -1);
    dis.resize(nodes_count);
    state.resize(nodes_count);
    G.resize(nodes_count);
}

void print_path( int n, int test ){
    if( n == test ){
        if( ascii_mode )
            cout << " " << (char)(n+'A');
        else
            cout << " " << n+1;
    }else{
        print_path( parent[n], test );
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

class Comparator{
public:
    bool operator()(const int a, const int b){
        if( dis[a] == dis[b] )
            return a < b;
        return dis[a] > dis[b];
    }
};

int find_best(vector<int> &successors){
    int best = INF;
    int node = INF;
    for(int c: successors)
        if(best > dis[c]){
            best = dis[c];
            node = c;
        }else if( best == dis[c] && c < node){
            node = c;
        }
    return node;
}

int find_second_best(vector<int> &successors, int node){
    int best = dis[node];
    int sbest = INF;
    int snode = INF;
    for(int c: successors)
        if( dis[c] < sbest && c != node){
            sbest = dis[c];
            snode = c;
        }else if( dis[c] == sbest && c < snode)
            snode = c;
    return sbest;
}

vector<int> moveGen(int node, int goal, int g){
    vector<int> neighbour;
    REP(i, 0, nodes_count)
        if( edges[i][node] != 0 ){ // is a neighbour
            neighbour.push_back(i);
            G[i] = g + edges[node][i];
            dis[i] = G[i] + heuristic_manhattan(i, goal);
            //parent[i] = node;
        }
    return neighbour;
}

int RBFS(int node, int f_limit, int goal, int g, string formatter){
    if( ascii_mode )
        cout << formatter << "Node : " << (char)(node+'A') << " f: " << setw(3) << g+heuristic_manhattan(node,goal) << " f_limit: " << setw(3) << f_limit << endl;
    else
       cout << formatter << "Node : " << setw(3) << node+1 << " f: " << setw(3) << g+heuristic_manhattan(node,goal) << " f_limit: " << setw(3) << f_limit << endl;
    if( node == goal )
        return -1; //success
    vector<int> successors = moveGen(node, goal, g);
    if( successors.size() == 0 )
        return INF; // failure
    while( true ){
        int best = find_best(successors);
        if ( dis[best] > f_limit){
            if( ascii_mode )
                cout << formatter << "Returning : " << dis[best] << " " << (char)(best+'A') << endl;
            else
                cout << formatter << "Returning : " << dis[best] << " " << best+1 << endl;
            return dis[best];
        }
        int alt = find_second_best(successors, best);
        parent[best] = node;
        if( ascii_mode )
            cout << formatter << (char)(best+'A') << " -> " << (char)(node+'A') << " f(best) : " << setw(3) << dis[best] << " Alt: " << setw(3) << alt<< endl;
        else
          cout << formatter << setw(3) << best+1 << " -> " << setw(3) << node+1 << " f(best) : " << setw(3) << dis[best] << " Alt: " << setw(3) << alt<< endl;

        int res = RBFS(best, min(alt, f_limit), goal, g+edges[node][best], formatter+"   ");
        if( res == -1 )
            return res;
        if( res != INF )
            dis[best] = res;
    }
    cout << endl;
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

    int res;
    if( res = RBFS(x, INF, y, 0, "") == -1 ){
        cout << "\nGoal Node Found!!!\n";
        print_path(y, x);
        cout << endl;
    }else{
        cout << "RESULT: " << res << endl;
        cout << "Goal Node not Found '|'\n";
    }

    return 0;
}