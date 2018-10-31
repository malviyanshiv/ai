//
// Created by SHIV SHANKAR SINGH on 18-08-2018.
//

#include <bits/stdc++.h>

using namespace std;

#define REP(i, s, e) for(int i = s; i < e; i++)

bool ascii_mode = true;
int nodes_count  = 24;

typedef pair<int, pair<vector<int>, int> > PIVI;

// A list containing position of each node
vector< pair<int, int> > Nodes;
// The adjacency matrix containing edges list
vector< vector<int> > edges;
vector<int> path;
int maxi = INT32_MAX;

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
        if( edges[i][node] != 0 ) // is a neighbour
            neighbour.push_back(i);
    return neighbour;
}

string mapp(int s){
    string ss(1, (char)s+'A');
    return ss;
}

void branch_bound(int start, int end){
    priority_queue< PIVI , vector< PIVI >, greater< PIVI > > Q;
    vector<int> p = {start};
    Q.push({0, {p, start}});
    while( !Q.empty()){
        auto b = Q.top();
        Q.pop();
        //cout << "{ " << setw(4)<< b.first << " , { " << setw(10) << b.second.first << " , " << (char)('A'+b.second.second) << " }\n";
        if( b.first > maxi )
            break;
        if( b.second.second == end ){
            if( maxi != min(maxi, b.first)){
                maxi = b.first;
                path = b.second.first;
            }
        }
        for(int c: moveGen(b.second.second)){
            if( find(b.second.first.begin(), b.second.first.end(), c) == b.second.first.end()){
                vector<int> temp( b.second.first);
                temp.push_back(c);
                Q.push({b.first+edges[c][b.second.second], {temp, c}});
            }
        }

    }
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
    branch_bound(x, y);
    if( maxi != INT32_MAX){
        cout << "Path found :" << endl;
        if( ascii_mode )
            cout << "  " << (char)(path[0]+'A');
        else
           cout << "  " << path[0]+1;
        REP(i, 1, path.size()){
            if( ascii_mode )
                cout << " --> " << (char)(path[i]+'A');
            else
              cout << " --> " << path[i]+1;
        }
        cout << endl;
        cout << "  Distance : " << maxi << endl;
    }else{
        cout << "Path is not found!!!" << endl;
    }

    return 0;
}