//
// Created by Matthew on 8/9/2022.
//
#ifndef CS236_GRAPH_H
#define CS236_GRAPH_H

#include <set>
#include <map>
#include <vector>

using namespace std;

class Graph {
private:
    map<int,set<int>> edges;
    vector<bool> visited;
    vector<set<int>> SCCs;
    set<int> scc;

public:

    void dfsSCC(int v) {
        scc.insert(v);
        visited.at(v) = true;
        for (auto it = edges.at(v).begin(); it != edges.at(v).end(); it++) {
            if (!visited.at(*it)) {
                dfsSCC(*it);
            }
        }
    }

    void dfs(Graph graph, int vertex, vector<int>* result) {
        visited.at(vertex) = true;
        for (int w: edges.at(vertex)) {
            if (!visited.at(w)) {
                dfs(graph, w, result);
            }
        }
        result->push_back(vertex);
    }

    vector<int> dfsForest(Graph graph) {
        vector<vector<int>> forest;
        for (unsigned int v = 0; v < graph.edges.size(); v++) {
            graph.visited.at(v) = false;
        }
        for (unsigned int v = 0; v < graph.edges.size(); v++) {
            if (!graph.visited.at(v)) {
                vector<int> tree;
                dfs(graph, v, &tree);
                forest.push_back(tree);
            }
        }
        vector<int> result;
        for (auto it: forest) {
            for (auto itt: it) {
                result.push_back(itt);
            }
        }
        // remove duplicates
        set<int> resultSet;
        vector<int> output;
        for (int i: result) {
            if (resultSet.insert(i).second)
                output.push_back(i);
        }
        return output;
    }

    void dfsForestSCC(vector<int> postOrder) {
        // reset all visited nodes
        for (unsigned int v = 0; v < edges.size(); v++)
            visited.at(v) = false;
        for (int i = postOrder.size()-1; i>= 0; i--) {
            if (!visited.at(postOrder.at(i))) {
                dfsSCC( postOrder.at(i));
                SCCs.push_back(scc);
                scc.clear();
            }
        }
    }

    const vector<set<int>> &getSCCs() const {
        return SCCs;
    }

    void setEdges(const map<int, set<int>> &edges) {
        Graph::edges = edges;
    }

    const map<int, set<int>> &getEdges() const {
        return edges;
    }

    const vector<bool> &getVisited() const {
        return visited;
    }

    void addNode(/*pair<int, set<int>> node*/) {
        set<int> x;
        edges.insert({edges.size(), x});
        visited.push_back(false);
    }

    void editNode(int x, int y) {
        edges.at(x).insert(y);
    }

    string toString() {
        stringstream s;
        string sep;
        for (unsigned int i = 0; i < edges.size(); i++) {
            s << "R" << i << ":";
            for (int x : edges.at(i)) {
                s << sep << "R" << x;
                sep = ",";
            }
            sep = "";
            s << endl;
        }
        return s.str();
    }

    void flipItAndReverseIt() {
        // make a new graph with equal number of nodes as this
        // for each node
        // for each item in node
        // edit the node represented by that item to include the original node
        Graph graph;
        for (unsigned int i = 0; i < this->edges.size(); i++)
            graph.addNode();
        for (unsigned int i = 0; i < edges.size(); i++) { // each node
            for (int item: edges.at(i)) // each item in node
                graph.editNode(item, i);
        }
        setEdges(graph.getEdges());
    }
};

#endif //CS236_GRAPH_H
