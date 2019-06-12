/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/110/11080.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

struct Graph{
    
    struct Node {
        int group_id = -1;
        int bipart_flag = -1;
        vector<Node*> adjacents;
        Node(){}
    };

    int minimum_guards;
    int open_group_id = 0;
    map< int , Node* > nodes;

    Graph(){
    }
    ~Graph(){
        for( auto p : nodes ){
            delete p.second;
        }
    }

    void solve(){
        minimum_guards = 0;
        bool done = false;
        while( done == false ){
            Node* next_first = NULL;
            for( auto it = nodes.begin() ; it != nodes.end() ; it++ ){
                if(it->second->group_id==-1){
                    next_first = it->second;
                    break;
                }
            }
            if( next_first == NULL ){
                done = true;
            }else{
                next_first->bipart_flag = 0;
                next_first->group_id = open_group_id++;
                bool valid_bipart = true;
                set<Node*> connected_nodes;
                connected_nodes.insert(next_first);
                fill_bipart(next_first,valid_bipart,connected_nodes);
                int side_ZERO = 0;
                int side_ONE = 0;
                if( valid_bipart ){
                    for( auto n : connected_nodes ){
                        if(n->bipart_flag==0)
                            side_ZERO++;
                        else
                            side_ONE++;
                    }
                    if( side_ONE == 0 || side_ZERO == 0 )
                        minimum_guards ++;
                    else if( side_ONE < side_ZERO )
                        minimum_guards += side_ONE;
                    else
                        minimum_guards += side_ZERO;
                    //
                }else{
                    done = true;
                    minimum_guards = -1;
                }
            }
        }

    }

    void fill_bipart( Node* n , bool& still_valid , set<Node*>& connected_nodes ){
        connected_nodes.insert( n );
        for( auto n2 : n->adjacents ){
            n2->group_id = n->group_id;
        } 
        if( still_valid ){
            for( auto n2 : n->adjacents ){    
                if( n2->bipart_flag == -1 ){
                    if( n->bipart_flag == 0 )
                        n2->bipart_flag = 1;
                    else if( n->bipart_flag == 1 )
                        n2->bipart_flag = 0;
                    
                    fill_bipart(n2,still_valid,connected_nodes);
                }
                else{
                    still_valid = ( n->bipart_flag != n2->bipart_flag );
                }
            }
        }
    }


};

int main(){
    int T , V , E , e1 , e2;
    set<int> existent_nodes;
    vector< pair<int,int> > edges;
    cin >> T;
    while( T-- ){
        cin >> V >> E ;
        existent_nodes.clear();
        edges.clear();
        while( E-- ){
            cin >> e1 >> e2;
            existent_nodes.insert(e1);
            existent_nodes.insert(e2);
            edges.push_back( pair<int,int>(e1,e2) );
        }
        Graph g;
        for( int i = 0 ; i < V - (int)existent_nodes.size() ; i++ ){
            g.nodes[1000+i] = new Graph::Node();
        }
        for( auto node : existent_nodes ){
            g.nodes[node] = new Graph::Node();    
        }
        for( auto edge : edges ){
            Graph::Node* n1 ; Graph::Node* n2;
            n1 = g.nodes[edge.first];
            n2 = g.nodes[edge.second];
            n1->adjacents.push_back(n2);
            n2->adjacents.push_back(n1);    
        }
        g.solve();
        cout << g.minimum_guards << endl;
    }
}
