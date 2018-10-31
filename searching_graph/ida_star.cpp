//
// Created by SHIV SHANKAR SINGH on 18-08-2018.
//

#include <bits/stdc++.h>

using namespace std;

#define REP(i, s, e) for(int i = s; i < e; i++)
#define H heuristic_manhattan
#define INF 1000000007
#define all(v) v.begin(), v.end()

bool ascii_mode = true;
int nodes_count  = 24;

// A list containing position of each node
vector< pair<int, int> > Nodes;
// The adjacency matrix containing edges list
vector< vector<int> > edges;
// List for maintaining the known best path
vector<int> dis;
// List for checking the presence of node in list
// 0 - new   1 - OPEN    2 - CLOSED
vector<int> state;

void reshape(){
    Nodes.resize(nodes_count);
    edges.resize(nodes_count, vector<int>(nodes_count));
    dis.resize(nodes_count);
    state.resize(nodes_count);
}

bool is_visited(vector<int> &path, int node){
	for(int c: path)
		if( c == node )
			return true;
	return false;
}

void print_path(vector<int> &path, int bound){
	cout << "Path is found with bound : " << bound << endl;
	REP(i, 0, path.size()){
		if( i == path.size()-1)
			if( ascii_mode )
				cout << (char)(path[i]+'A');
			else
				cout << path[i]+1 ;
		else
			if( ascii_mode )
				cout << (char)(path[i]+'A') << " --> ";
			else
				cout << path[i]+1 << " --> ";
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
            return a < b;
    }
};

vector<int> moveGen(int node, int g, int goal){
    vector<int> neighbour;
    REP(i, 0, nodes_count)
        if( edges[i][node] != 0 ){ // is a neighbour
            neighbour.push_back(i);
            dis[i] = g + H(i, goal);
        }
    return neighbour;
}

int search(vector<int> &path, int g, int bound, int goal){
	int node = path.back();
	int f = g + H(node, goal);
	if ( f > bound )
		return f;
	if( ascii_mode )
		cout << (char)(node+'A') << "  g(" << (char)(node+'A') << "): " << setw(4) << g << "  f(" << (char)(node+'A') << "): " << setw(4)<< f << " bound: " << setw(4) << bound << endl;
	else
		cout << setw(4) << node+1 << "  g(" << setw(4) << node+1 << "): " << setw(4) << g << "  f(" << setw(4) << node+1 << "): " << setw(4)<< f << " bound: " << setw(4) << bound << endl;
	if ( node == goal )
		return 0;
	int mini = INF;
	vector<int> neighbour = moveGen(node, g, goal);
	sort(all(neighbour), Comparator());
	for( int c : neighbour){
		if( ! is_visited(path, c)){
			path.push_back(c);
			int t = search(path, g+edges[c][node], bound, goal);
			if( t == 0 )
				return 0;
			if( t < mini )
				mini = t;
			path.pop_back();
		}
	}
	return mini;
}


bool ida_star(int root, int goal){
	int bound = H(root, goal);
	while ( true ){
		vector<int> path;
		cout << " WORKING WITH NEW BOUND: " << bound << endl;
		path.push_back(root);
		int t = search(path, 0, bound, goal);
		if( t == 0 ){
			print_path(path, bound);
			return true;
		}else if( t == INF )
			return false;
		bound = t;
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

    if( ! ida_star(x, y)){
    	cout << "No path found to the goal node!!!\n";
    }

    return 0;
}