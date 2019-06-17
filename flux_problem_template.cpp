/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <map>
#include <stack>

using namespace std;

short open_search_id = 0;

struct Node {
    short               last_search_id = -1;
    map< Node* , int >  adjacents;
    Node*               tree_parent = NULL;
};

// DFS any available path
vector<Node*>   get_any_available_path( Node* source , Node* destiny ) {
    short search_id = open_search_id ++;
    stack<Node*> dfs_stack;
    dfs_stack.push( source );

    source->last_search_id = search_id;
    source->tree_parent = NULL;
    destiny->tree_parent = NULL;
    while( dfs_stack.size() ){
        Node* next_to_explore = dfs_stack.top();
        dfs_stack.pop();
        if( next_to_explore == destiny ){
            break;
        }
        else{
            for( auto edge : next_to_explore->adjacents ){
                Node* adjacent = edge.first;
                if( edge.second > 0 && adjacent->last_search_id != search_id ){
                    adjacent->tree_parent = next_to_explore;
                    adjacent->last_search_id = search_id;
                    dfs_stack.push(adjacent);
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
int             fill_path( vector<Node*>& path ){
    int flux_passed = 2147483647; // 2^31 - 1
    for( int i = 0 ; i + 1 < path.size() ; i++ ){
        Node* n1 = path[i];
        Node* n2 = path[i+1];
        if( n1->adjacents[n2] < flux_passed ) flux_passed = n1->adjacents[n2];
    }
    for( int i = 0 ; i + 1 < path.size() ; i++ ){
        Node* n1 = path[i];
        Node* n2 = path[i+1];
        n1->adjacents[n2] -= flux_passed;
        n2->adjacents[n1] += flux_passed;
    }
    return flux_passed;
}

int main(){
    
}