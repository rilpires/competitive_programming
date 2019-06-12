/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/109/10986.pdf
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Graph{
    struct Node{
        int distance = -1;
        vector< pair<Node*,int> > adjacents;
    };
    
    vector<Node> nodes;
    
    Graph( const size_t& amount_of_nodes ){
        nodes.resize(amount_of_nodes);
    }

    size_t get_minimum_distance_between( const int& node_id_1 , const int& node_id_2 ){
        Node& source = nodes[node_id_1];
        Node& destination = nodes[node_id_2];
        queue<Node*> bfs;

        source.distance = 0;
        bfs.push(&source);
        Node *current_node , *adj_node;
        while( bfs.size() ){
            current_node = bfs.front(); 
            bfs.pop();
            for( auto adj : current_node->adjacents ){
                adj_node = adj.first; 
                if( adj_node->distance == -1 || current_node->distance + adj.second < adj_node->distance ){
                    bfs.push(adj_node);
                    adj_node->distance = current_node->distance + adj.second;
                }
            }
        }
        return destination.distance;
    }
};

int main(){
    int N , S , T , n , m , case_number = 1 , id1, id2 , latency;
    cin >> N ;
    while( N-- ){
        cin >> n >> m >> S >> T ;
        Graph g(n);
        
        while(m--){
            cin >> id1 >> id2 >> latency;
            Graph::Node& node1 = g.nodes[id1];
            Graph::Node& node2 = g.nodes[id2];
            node1.adjacents.push_back( pair<Graph::Node*,int>(&node2,latency) );
            node2.adjacents.push_back( pair<Graph::Node*,int>(&node1,latency) );
        }
        
        latency = g.get_minimum_distance_between(S,T);
        cout << "Case #" << case_number++ << ": " << ((latency>-1)?(to_string(latency)):("unreachable")) << endl;
    }
}