//
// Created by SHIV SHANKAR SINGH on 18-08-2018.
//

#include <bits/stdc++.h>

using namespace std;

#define REP(i, s, e) for(int i = s; i < e; i++)
#define NODES_COUNT 24

typedef pair<int, pair<string, int> > PISI;

// A list containing position of each node
vector< pair<int, int> > Nodes(NODES_COUNT);
// The adjacency matrix containing edges list
int edges[NODES_COUNT][NODES_COUNT];
string path ;
int maxi = INT32_MAX;

int heuristic_manhattan(int first, int second){
    int result = abs(Nodes[first].first - Nodes[second].first) + abs(Nodes[first].second - Nodes[second].second);
    result *= 10;
    return result;
}

vector<int> moveGen(int node){
    vector<int> neighbour;
    REP(i, 0, NODES_COUNT)
        if( edges[i][node] != 0 ) // is a neighbour
            neighbour.push_back(i);
    return neighbour;
}

string mapp(int s){
    string ss(1, (char)s+'A');
    return ss;
}

void branch_bound(int start, int end){
    priority_queue< PISI , vector< PISI >, greater< PISI > > Q;
    Q.push({0, {mapp(start), start}});
    while( !Q.empty()){
        auto b = Q.top();
        Q.pop();
        cout << "{ " << setw(4)<< b.first << " , { " << setw(10) << b.second.first << " , " << (char)('A'+b.second.second) << " }\n";
        if( b.first > maxi )
            break;
        if( b.second.second == end ){
            if( maxi != min(maxi, b.first)){
            	maxi = b.first;
            	path = b.second.first;
            }
        }
        for(int c: moveGen(b.second.second)){
            if( b.second.first.find(mapp(c)) == string::npos){
                Q.push({b.first+edges[c][b.second.second], {mapp(c)+b.second.first, c}});
            }
        }

    }
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
    branch_bound(x, y);
    if( maxi != INT32_MAX){
	    cout << "Path found :" << endl;
	    cout << "  " << path[path.size()-1];
	   	for(int i = path.size()-2; i >=0 ; i--)
	   		cout << " --> " << path[i];
	   	cout << endl;
	    cout << "  Distance : " << maxi << endl;
	}else{
		cout << "Path is not found!!!" << endl;
	}

    return 0;
}