/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/8/p820.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

#define INT_MAX 2147483647

struct Node {
    short               last_search_id = -1;
    map< Node* , int >  adjacents;
    Node*               tree_parent = NULL;
};
struct Graph {

    short               open_search_id = 0;
    vector<Node*>       all_nodes;

    ~Graph(){
        for( auto n : all_nodes ) delete n;
    }

    vector<Node*>       get_any_available_path( Node* source , Node* destiny ) {
        if( source == destiny ) {
            vector<Node*> ret;
            ret.push_back( source );
            return ret;
        }
        short search_id = open_search_id ++;
        queue<Node*> bfs_queue;
        bfs_queue.push( source );

        source->last_search_id = search_id;
        source->tree_parent = NULL;
        destiny->tree_parent = NULL;
        while( bfs_queue.size() ){
            Node* next_to_explore = bfs_queue.front();
            bfs_queue.pop();
            if( next_to_explore == destiny ) break;
            else{
                for( auto edge : next_to_explore->adjacents ){
                    Node* adjacent = edge.first;
                    int path_available = edge.second;
                    if( path_available > 0 && adjacent->last_search_id != search_id ){
                        adjacent->last_search_id = search_id;
                        adjacent->tree_parent = next_to_explore;
                        bfs_queue.push( adjacent );
                    }
                }
            }
        }
        if( destiny->tree_parent != NULL ){
            vector<Node*> reverse_path;
            reverse_path.push_back(destiny);
            while( reverse_path.back()->tree_parent != NULL ){
                reverse_path.push_back( reverse_path.back()->tree_parent );
            }
            return vector<Node*>( reverse_path.rbegin() , reverse_path.rend() );
        } else {
            return vector<Node*>();
        }
    }

    // Returns the amount of flux passed by this path (minimum edge)
    int                fill_path( vector<Node*>& path ){
        int minimum = INT_MAX;
        for( int i = 0 ; i < path.size() - 1 ; i++ ){
            Node* n1 = path[i];
            Node* n2 = path[i+1];
            int available = n1->adjacents[n2];
            if( available < minimum ) minimum = available;
        }
        for( int i = 0 ; i < path.size() - 1 ; i++ ){
            Node* n1 = path[i];
            Node* n2 = path[i+1];
            n1->adjacents[n2] -= minimum;
            n2->adjacents[n1] -= minimum;
        }
        return minimum;
    }

};

int main(){
    int n,s,t,c,id1,id2,length,case_number=1;
    Node *node_1,*node_2;
    while( true ){
        cin >> n;
        if( n == 0 ) break;
        cin >> s >> t >> c ;
        
        //Filling the graph
        Graph g;
        for( int i = 0 ; i < n ; i++ ){
            g.all_nodes.push_back( new Node() );
        }
        while( c-- ){
            cin >> id1 >> id2 >> length;
            node_1 = g.all_nodes[ id1-1 ];
            node_2 = g.all_nodes[ id2-1 ];
            node_1->adjacents[node_2] += length;
            node_2->adjacents[node_1] += length;
        }

        Node *source , *destiny;
        source = g.all_nodes[ s-1 ];
        destiny = g.all_nodes[ t-1 ];

        int result = 0;
        while( true ){
            vector<Node*> path = g.get_any_available_path( source , destiny );
            if( path.size() == 0 ) break;
            else{
                result += g.fill_path(path);
            }
        }

        cout << "Network " << case_number++ << endl;
        cout << "The bandwidth is " << result << "." << endl << endl;

    }
}

