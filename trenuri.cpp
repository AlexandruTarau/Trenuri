#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int m;

    // adj - adjacent list of graph
    unordered_map<string, vector<string>> adj;
    string start, destination;

    void read_input() {
        ifstream fin("trenuri.in");
        fin >> start >> destination;
        fin >> m;

        string x, y;

        // Reading the edges of the graph (the routes between each city)
        for (int i = 0; i < m; i++) {
            fin >> x >> y;
            adj[x].push_back(y);
        }
        fin.close();
    }

    // Helper function for solve_dfs
    void dfs(const string& node, unordered_set<string>& visited,
                                        vector<string>& topsort) {
        visited.insert(node);
        if (node == destination) {
            return;
        }
        if (adj.find(node) != adj.end()) {
            for (string neighbor : adj[node]) {
                if (visited.find(neighbor) == visited.end()) {
                    dfs(neighbor, visited, topsort);
                }
            }
        }
        topsort.push_back(node);
    }

    // Function that sorts the graph topologically
    vector<string> solve_dfs() {
        vector<string> topsort;
        unordered_set<string> visited;

        // Iterate through all nodes of graph
        for (auto pair : adj) {
            string node = pair.first;
            // If the node is not visited yet, we start a traversal
            if (visited.find(node) == visited.end()) {
                dfs(node, visited, topsort);
            }
        }

        // The result is reversed
        reverse(topsort.begin(), topsort.end());

        return topsort;
    }

    int get_result() {
        // Sort graph in topological order
        vector<string> topsort = solve_dfs();

        /* Using dynamic programming to count the maximum number of cities
        that can be visited from start to destination */
        unordered_map<string, int> dp;

        // Initialize distances
        for (string node : topsort) {
            dp[node] = node == start ? 1 : INT_MIN;
        }

        // Iterate through the nodes in topological order
        for (string node : topsort) {
            // Reached destination node, no need to process further
            if (node == destination) {
                break;
            }

            // If the node has been updated before and it has edges
            if (dp[node] != INT_MIN && adj.find(node) != adj.end()) {
                // Iterate through its neighbors
                for (string neigh : adj.at(node)) {
                    // Update distance to neighbor
                    dp[neigh] = max(dp[neigh], dp[node] + 1);
                }
            }
        }

        return dp[destination];
    }

    void print_output(const int d) {
        ofstream fout("trenuri.out");
        fout << d;
        fout.close();
    }
};

int main() {
    auto* task = new (nothrow) Task();
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
