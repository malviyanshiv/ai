//
// Created by SHIV SHANKAR SINGH on 18-08-2018.
//

#include <bits/stdc++.h>

using namespace std;

#define REP(i, s, e) for(int i = s; i < e; i++)
#define NODES_COUNT 24
#define H heuristic_manhattan
#define INF 1000000007
#define all(v) v.begin(), v.end()

// A list containing position of each node
vector< pair<int, int> > Nodes(NODES_COUNT);
// The adjacency matrix containing edges list
int edges[NODES_COUNT][NODES_COUNT];
// List for maintaining the known best path
vector<int> dis(NODES_COUNT, 0);
// List for checking the presence of node in list
// 0 - new   1 - OPEN    2 - CLOSED
vector<int> state(NODES_COUNT, 0);

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
			cout << (char)(path[i]+'A');
		else
			cout << (char)(path[i]+'A') << " --> ";
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
    REP(i, 0, NODES_COUNT)
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
	cout << (char)(node+'A') << "  g(" << (char)(node+'A') << "): " << setw(4) << g << "  f(" << (char)(node+'A') << "): " << setw(4)<< f << " bound: " << setw(4) << bound << endl;
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
    char start, goal;
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
        cin >> start >> goal >> w;
        // Mapping character with integer
        x = start - 'A'; y = goal - 'A';
        edges[x][y] = w;
        edges[y][x] = w;
    }

    // Inputing source and destination
    cin >> start >> goal;
    x = start - 'A';
    y = goal - 'A';

    cout << "Source : " << start << " , Destination: " << goal <<endl;
    if( ! ida_star(x, y)){
    	cout << "No path found to the goal node!!!\n";
    }

    return 0;
}