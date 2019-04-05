#include <bits/stdc++.h>
using namespace std;

int TSP(int st, vector<int> v, int **dist, map<pair<int, vector<int> >, int> &dp){
	if(dp[{st, v}]) return dp[{st, v}];
	int mn = INT_MAX;
	if(v.size() == 0) mn = dist[st][0];
	else{
		for(int i = 0; i < v.size(); i++){
			if(dist[st][v[i]] != INT_MAX){
				vector<int> vv = v;
				vv.erase(vv.begin() + i);
				int nxt = TSP(v[i], vv, dist, dp);
				if(nxt != INT_MAX)
					mn = min(mn, dist[st][v[i]] + nxt);
			}
		}
	}
	return dp[{st, v}] = mn;
}

void find_path(int st, vector<int> v, int index, int **dist, map<pair<int, vector<int> >, int> &dp, int *path){
	int i;
	for(i = 0; i < v.size(); i++){
		vector<int> vv = v;
		vv.erase(vv.begin() + i);
		if(dp[{st, v}] == dist[st][v[i]] + dp[{v[i], vv}]){
			path[index] = v[i];
			find_path(v[i], vv, index + 1, dist, dp, path);
		}
	}
}

void display(int n, map<pair<int, vector<int> >, int> &dp){
	map<pair<int, vector<int> >, int> :: iterator it, it1 = dp.begin();
	for(int i = 0; i < n; i++){
		cout << "|v| = " << i << "\n";
		for(it = dp.begin(); it != dp.end(); it++){
			if(it->first.second.size() == i){
				cout << "dp[{a, v}] : (" << it->first.first + 1 << " ,{";
				for(int j = 0; j < it->first.second.size(); j++){
					if(j == 0) cout << it->first.second[j] + 1;
					else cout << ", " << it->first.second[j] + 1;
				}
				cout << "}) = " << ((it->second == INT_MAX) ? (-1) : (it->second)) << "\n";
			}
		}
		it1++;
		cout << "\n";
	}
}

int main(){
	int n, i, j, min_cost, ch;
	vector<int> v;
	map<pair<int, vector<int> >, int> dp; 
	cout << "Enter the no of cities\n";
	cin >> n;
	while(n < 2){
		cout << "No of cities cannot by less than 2\nEnter the no of cities again\n";
		cin >> n;
	}
	int *path = (int *) malloc (sizeof(int) * n);
	int **dist = (int **) malloc(sizeof(int *) * n);
	for(int i = 0; i < n; i++)
		dist[i] = (int *) malloc (sizeof(int) * n);
	cout << "Select Choice:\n1) Enter graph as a matrix\n2)Enter graph edge by edge\n";
	cin >> ch;
	while(ch > 2 || ch < 1){
		cout << "Enter Valid Choice: ";
		cin >> ch;
	}
	if(ch == 1){
		for(i = 0; i < n; i++){
			cout << "Enter elements of the row: " << i + 1 << "\n";
			path[i] = 0;
			for(int j = 0; j < n;){
				cin >> dist[i][j];
				if(dist[i][j] < 0){
					cout << "Edges cannot be negative\n";
					cout << "Enter again\n";
				}
				else{
					j++;
				}
				if(i == j) dist[i][j] = INT_MAX;
			}
		}
	}
	else{
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n;  j++) dist[i][j] = INT_MAX;
		int e, i = 0, sc, d, w;
		cout << "Enter the no of edges\n";
		cin >> e;
		while(e < 0 && e > n * n - n){
			cout << "No of edges must be positive and maximum no of edges can be " << n * n - n  << " only\n";
			cout << "Enter the no of edges\n";
			cin >> e;
		}
		while(i < e){
			cout << "Enter the source, destination and weight of edge " << i + 1 << ": ";
			cin >> sc >> d >> w;
			if(sc > n || sc < 1 || d > n || d < 1 ||  sc== d || w <= 0) 
				cout << "Invalid Entry, Plz enter again\n";
			else if(dist[sc - 1][d - 1] != INT_MAX)
				cout << "Edge already exits, Plz enter again\n";
			else{
				dist[sc - 1][d - 1] = w;
				i++;
			}		
		}
	}
	for(int i = 1; i < n; i++) v.push_back(i);
	min_cost = TSP(0, v, dist, dp);
	cout << "\n**The DP TABLE**\n";
	display(n, dp);
	if(min_cost == INT_MAX)
		return cout << "Tour does not exits.\n", 0;
	cout << "The Shortest distance is: " << min_cost << "\n";
	find_path(0, v, 0, dist, dp, path);
	cout << "The Shortest Hamiltonian Tour is : ";
	cout << "1-->";
	for(i = 0; i < n - 1; i++) cout << path[i] + 1 << "-->";
	cout << "1\n";
	return 0;
}
