//
// Created by SHIV SHANKAR SINGH on 18-08-2018.
//

#include <bits/stdc++.h>

using namespace std;

#define REP(i, s, e) for(int i = s; i < e; i++)
#define NODES_COUNT 24
#define INF 1000000007

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

void print_path(int n, int test){
    if( n == test){
        cout << (char)(n+'A');
        return;
    }
    print_path(parent[n], test);
    cout << " --> " << (char)(n+'A');
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
    REP(i, 0, NODES_COUNT)
        if( edges[i][node] != 0 ){ // is a neighbour
            neighbour.push_back(i);
            G[i] = g + edges[node][i];
            dis[i] = G[i] + heuristic_manhattan(i, goal);
            //parent[i] = node;
        }
    return neighbour;
}

int RBFS(int node, int f_limit, int goal, int g, string formatter){
	cout << formatter << "Node : " << setw(3) << (char)(node+'A') << " f: " << setw(3) << g+heuristic_manhattan(node,goal) << " f_limit: " << setw(3) << f_limit << endl;
	if( node == goal )
		return -1; //success
	vector<int> successors = moveGen(node, goal, g);
	if( successors.size() == 0 )
		return INF; // failure
	while( true ){
		int best = find_best(successors);
		if ( dis[best] > f_limit){
			cout << formatter << "Returning : " << dis[best] << " " << (char)(best+'A') << endl;
			return dis[best];
		}
		int alt = find_second_best(successors, best);
		parent[best] = node;
		cout << formatter << (char)(best+'A') << " -> " << (char)(node+'A') << " f(best) : " << setw(3) << dis[best] << " Alt: " << setw(3) << alt<< endl;

		int res = RBFS(best, min(alt, f_limit), goal, g+edges[node][best], formatter+"   ");
		if( res == -1 )
			return res;
		if( res != INF )
			dis[best] = res;
	}
    cout << endl;
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

    cout << "Source : " << start << " , Destination: " << end << endl << endl;
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