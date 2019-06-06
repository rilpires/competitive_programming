/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/107/10779.pdf
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <map>
#include <queue>

using namespace std;

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
    for( int i = 0 ; i + 1 < path.size() ; i++ ){
        Node* n1 = path[i];
        Node* n2 = path[i+1];
        n1->adjacents[n2] -= 1;
        n2->adjacents[n1] += 1;
    }
    return 1;
}

int main(){
    int T , n , m , amount_of_cards , card_id , case_number = 1;
    cin >> T;
    while( T-- ){
        cin >> n >> m;
        Node *bob_source , *bob_destiny;
        vector<Node*> kids;
        vector<Node*> cards;

        bob_source = new Node();
        bob_destiny = new Node();
        for( int i = 1 ; i < n ; i++ ){
            kids.push_back(new Node());
        }
        for( int i = 0 ; i < m ; i++ ){
            Node* new_node = new Node(); 
            cards.push_back( new_node );
            new_node->adjacents[bob_destiny] = 1;
        }

        for( int i = 0 ; i < n ; i++ ){
            cin >> amount_of_cards ;
            
            // Bob's cards
            if( i == 0 ){ 
                while(amount_of_cards--){
                    cin >> card_id;
                    bob_source->adjacents[cards[card_id-1]] += 1;
                }
            }

            // Other kids cards
            else{
                Node* kid = kids[i-1];
                while(amount_of_cards--){
                    cin >> card_id;
                    kid->adjacents[cards[card_id-1]] += 1;
                }
                for( auto card: cards ){
                    if( kid->adjacents[ card ] == 0 ){
                        card->adjacents[kid] = 1;
                    } else if( kid->adjacents[card] > 0 ){
                        kid->adjacents[card] -= 1;
                    }
                }
            }
        }

        open_search_id = 0;
        while( true ){
            vector<Node*> path = get_any_available_path(bob_source,bob_destiny);
            if( path.size() > 0 ){
                fill_path( path );
            } else {
                break;
            }
        }

        int bob_owned_cards = 0;
        for( auto card : cards ){
            if( card->adjacents[bob_destiny] == 0 ) bob_owned_cards++;
        }

        cout << "Case #" << case_number++ << ": " << bob_owned_cards << endl;

        delete bob_source;
        delete bob_destiny;
        for( auto n : kids ) delete n;
        for( auto n : cards ) delete n;
    }
}