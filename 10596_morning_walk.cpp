/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/105/10596.pdf
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

struct Graph{
    struct Node{
        bool visited = false;
        vector<Node*> adjacents; 
    };
    map<int,Node*> nodes;
    Graph(  ){
        nodes.clear();
    }
    ~Graph(){
        for( auto it : nodes ){
            delete it.second;
        }
    }
    bool is_complete(){
        vector<Node*> to_visit;
        size_t visiteds = 0;
        to_visit.push_back( nodes.begin()->second );
        while( to_visit.size() ){
            Node* node = to_visit.back();
            to_visit.pop_back();
            node->visited = true;
            visiteds++;
            for( auto adj : node->adjacents ){
                if( adj->visited == false ){
                    adj->visited = true;
                    to_visit.push_back(adj);
                }
            }
        }
        return visiteds == nodes.size(); 
    }
};

int main(){
    int N,R,n1,n2;
    Graph::Node *node_1 , *node_2;
    while( cin >> N >> R ){
        Graph g;
        vector< pair< int , int > > roads;
        set<int> nodes_with_roads;
        for(int r = 0 ; r < R ; r++ ){
            cin >> n1 >> n2;
            roads.push_back( pair<int,int>(n1,n2) );
            nodes_with_roads.insert(n1);
            nodes_with_roads.insert(n2);
        }
        for( auto it : nodes_with_roads ){
            g.nodes[it] = new Graph::Node();
        }
        for( auto p : roads ){
            node_1 = g.nodes[p.first];
            node_2 = g.nodes[p.second];
            node_1->adjacents.push_back(node_2);
            node_2->adjacents.push_back(node_1);
        }

        bool ok = (R>0) && g.is_complete();
        if(ok){
            for( auto it : g.nodes ){
                if( it.second->adjacents.size() % 2 == 1 ){
                    ok = false;
                    break;  
                } 
            }
        }
        cout << ((ok)?("Possible"):("Not Possible")) << endl;
    }
}