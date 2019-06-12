/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/104/p10480.pdf
*/

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <set>

using namespace std;

short open_search_id = 0;

struct Node {
    short               last_search_id = -1;
    int                 id = -1;
    map< Node* , int >  original_adjacents;
    map< Node* , int >  adjacents;
    Node*               tree_parent = NULL;
    Node(int _id):id(_id){}
};

// DFS any available path
vector<Node*>   get_any_available_path( Node* source , Node* destiny ) {
    short search_id = open_search_id ++;
    stack<Node*> dfs;
    dfs.push( source );

    source->last_search_id = search_id;
    source->tree_parent = NULL;
    destiny->tree_parent = NULL;
    while( dfs.size() ){
        Node* next_to_explore = dfs.top();
        dfs.pop();
        if( next_to_explore == destiny ){
            break;
        }
        else{
            vector<Node*> candidates;
            for( auto edge : next_to_explore->adjacents ){
                if( (edge.second > 0 ) && edge.first->last_search_id != search_id ){
                    candidates.push_back( edge.first );
                }
            }
            /**
            sort( candidates.begin() , candidates.end() , [next_to_explore](Node* n1 , Node* n2){
                
            });
            **/
            for( auto candidate : candidates ){
                candidate->tree_parent = next_to_explore;
                candidate->last_search_id = search_id;
                dfs.push(candidate);
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
    } else return vector<Node*>();
}

// Returns the two nodes that has it's connection cut
pair<Node*,Node*>             fill_path( vector<Node*>& path ){
    pair<Node*,Node*> ret;
    int flux_passed = 2147483647; // 2^31 - 1
    for( int i = 0 ; i + 1 < path.size() ; i++ ){
        Node* n1 = path[i];
        Node* n2 = path[i+1];
        if( n1->adjacents[n2] < flux_passed ){
            flux_passed = n1->adjacents[n2];
            ret.first = n1;
            ret.second = n2;
        }
    }
    if( flux_passed > 0 ){
        for( int i = 0 ; i + 1 < path.size() ; i++ ){
            Node* n1 = path[i];
            Node* n2 = path[i+1];
            n1->adjacents[n2] -= flux_passed;
            n2->adjacents[n1] -= flux_passed;
        }
    } else {
        ret.first->adjacents[ret.second] = 0;
    }
    return ret;
}

int main(){
    int N,M,id1,id2,cost;
    while( cin >> N >> M ){
        if( N == 0 && M == 0 ) break;
        
        vector<Node*> cities;
        Node* source;
        Node* destiny;

        for( int i = 0 ; i < N ; i++ ){
            cities.push_back( new Node(i+1) );
        }
        source = cities[0];
        destiny = cities[1];
        for( int i = 0 ; i < M ; i++ ){
            cin >> id1 >> id2 >> cost;
            Node* n1 = cities[id1-1];
            Node* n2 = cities[id2-1];
            n1->adjacents[n2] = cost;
            n2->adjacents[n1] = cost;
        }
        for( auto n : cities ) n->original_adjacents = n->adjacents;

        // Pass max flow
        while(true){
            vector<Node*> path = get_any_available_path(source,destiny);
            if( path.size() > 0 ){
                fill_path(path);
            } else break;
        }

        // Finding reachables
        set< Node* > reachable;
        short search_id = open_search_id+1;
        stack<Node*> dfs_stack;
        Node* next_to_explore = cities[0];
        next_to_explore->last_search_id = search_id;
        dfs_stack.push(next_to_explore);
        while( dfs_stack.size() > 0 ){
            next_to_explore = dfs_stack.top();
            dfs_stack.pop();
            reachable.insert( next_to_explore );
            for( auto adj : next_to_explore->adjacents )
            if(adj.second>0 && adj.first->last_search_id != search_id ){
                adj.first->last_search_id = search_id;
                dfs_stack.push(adj.first);
            }
        }
        
        // Finding the pairs we need to cut
        vector< pair<Node*,Node*> > to_cut;
        for( auto c : reachable )
        for( auto adj : c->original_adjacents )
        if( adj.second > 0 && reachable.find(adj.first) == reachable.end() )
            to_cut.push_back( pair<Node*,Node*>(c,adj.first) );

        for( auto n : to_cut ){
            Node* n1 = n.first;
            Node* n2 = n.second;
            cout << n1->id << " " << n2->id << endl;
        } 
        cout << endl;

        for( auto n : cities ) delete n;

    }
}