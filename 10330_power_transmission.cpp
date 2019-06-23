/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/103/10330.pdf
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <map>
#include <queue>

using namespace std;

#define INFINITE 2147483647

short open_search_id = 0;

struct Node {
    short               last_search_id = -1;
    map< Node* , int >  adjacents;
    Node*               tree_parent = NULL;
};

// BFS any available path
vector<Node*>   get_any_available_path( Node* source , Node* destiny ) {
    short search_id = open_search_id ++;
    queue<Node*> bfs_queue;
    bfs_queue.push( source );

    source->last_search_id = search_id;
    source->tree_parent = NULL;
    destiny->tree_parent = NULL;
    while( bfs_queue.size() ){
        Node* next_to_explore = bfs_queue.front();
        bfs_queue.pop();
        if( next_to_explore == destiny ){
            break;
        }
        else{
            for( auto edge : next_to_explore->adjacents ){
                Node* adjacent = edge.first;
                if( edge.second > 0 && adjacent->last_search_id != search_id ){
                    adjacent->tree_parent = next_to_explore;
                    adjacent->last_search_id = search_id;
                    bfs_queue.push(adjacent);
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
    int flux_passed = INFINITE; // 2^31 - 1
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
    int N , capacity , M , i1 , i2 , C , B , D;
    while( cin >> N ){
        vector<Node*> regulators_input;
        vector<Node*> regulators_output;
        Node* source = new Node();
        Node* destiny = new Node();

        for( int i = 0 ; i < N ; i ++ ){
            cin >> capacity;
            Node* new_input = new Node();
            Node* new_output = new Node();
            regulators_input.push_back( new_input );
            regulators_output.push_back( new_output );
            new_input->adjacents[new_output] = capacity;
        }
        cin >> M;
        for( int i = 0 ; i < M ; i++ ){
            cin >> i1 >> i2 >> C;
            Node* node_1 = regulators_output[i1-1];
            Node* node_2 = regulators_input[i2-1]; 
            node_1->adjacents[node_2] = C;
        }
        cin >> B >> D;
        for( int i = 0 ; i < B ; i++ ){
            cin >> i1;
            source->adjacents[regulators_input[i1-1]] = INFINITE;
        }
        for( int i = 0 ; i < D ; i++ ){
            cin >> i1;
            regulators_output[i1-1]->adjacents[destiny] = INFINITE;
        }

        int flux = 0;
        while( true ){
            vector<Node*> path = get_any_available_path(source,destiny);
            if( path.size() > 0 ){
                flux += fill_path(path);
            }
            else break;
        }

        cout << flux << endl;

        for( auto n : regulators_input ) delete n;
        for( auto n : regulators_output ) delete n;
        delete source;
        delete destiny;

    }
}