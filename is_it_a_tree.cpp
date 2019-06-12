/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/6/615.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

struct Graph {
    

    enum {
        UNVISITED ,
        VISITED 
    };

    struct Node{
        int ID;
        char visited_flag;
        vector<Node*> incoming;
        vector<Node*> outgoing;

        Node( int id ){
            ID = id;
            visited_flag = UNVISITED;
        }
    };

    map<int,Node*> nodes;
    bool is_tree;
    
    Graph(){
        is_tree = false;
    }
    ~Graph(){
        for( auto p : nodes ){
            delete p.second;
        }
    }
    void add_new_node( int new_node_id ){
        Node* new_node = new Node(new_node_id);
        nodes[new_node_id] = new_node;
    }
    void set_new_edge( int id1 , int id2 ){
        nodes[id1]->outgoing.push_back(nodes[id2]);
        nodes[id2]->incoming.push_back(nodes[id1]);
    }
    void check_if_is_tree(){
        is_tree = true;
        Node* possible_root = NULL;
        for( auto it : nodes ){
            if( it.second->incoming.size() == 0 ){
                if( possible_root == NULL){
                    possible_root = it.second;
                }
                else{
                    is_tree = false;
                    return;
                }
            }
        }
        if( possible_root == NULL && nodes.size() > 0 ){ 
            is_tree = false;
            return;
        }
        if(possible_root)search( possible_root );
        if( is_tree )for( auto it : nodes ){
            if( it.second->visited_flag == UNVISITED ){
                is_tree = false;
                return;
            }
        }
    }
    void search( Node* node ){
        node->visited_flag = VISITED;
        for( auto n : node->outgoing ){
            if( n->visited_flag == UNVISITED ){
                search(n);
            } else is_tree = false;
        }
    }

};

int main(){
    int case_number = 1;
    int e1 , e2;
    while( cin >> e1 >> e2 ){
        if( e1 < 0 && e2 < 0 ) break;
        else {
            Graph graph;
            set<int> existent_nodes;
            vector< pair<int,int> > existent_edges;

            while( e1>0 && e2>0 ){
                existent_edges.push_back( pair<int,int>(e1,e2) );
                existent_nodes.insert(e1);
                existent_nodes.insert(e2);
                cin >> e1 >> e2;
            }
            
            for( auto it : existent_nodes ){
                graph.add_new_node(it);
            }
            for( auto it : existent_edges ){
                graph.set_new_edge( it.first , it.second );
            }

            graph.check_if_is_tree();

            if( graph.is_tree ){
                cout << "Case " << case_number++ << " is a tree." << endl;
            }else{
                cout << "Case " << case_number++ << " is not a tree." << endl;
            }

        }
    }
}