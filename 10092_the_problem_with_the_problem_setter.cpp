/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/100/10092.pdf
*/
#include <iostream>
#include <string>
#include <sstream>
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

    // BFS any available path
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
            n2->adjacents[n1] += minimum;
        }
        return minimum;
    }

};

int main(){
    int nk , np , category_size , categories_included , category_id;
    Node *source , *destiny;
    while( true ){
        cin >> nk >> np ;
        if( nk == 0 && np == 0 ) break;

        Graph graph;       
        vector<Node*> problem_pool , categories;

        source = new Node();
        destiny = new Node();
        for( int i = 0 ; i < nk ; i ++ )
            categories.push_back( new Node() );
        for( int i = 0 ; i < np ; i ++ )
            problem_pool.push_back( new Node() );

        graph.all_nodes.push_back( source );
        graph.all_nodes.push_back( destiny );
        for( auto n : problem_pool ){
            if( n == NULL ) cout << "NULL" << endl;
            source->adjacents[n] = 1;
            graph.all_nodes.push_back( n );
        }
        for( auto n : categories ){
            graph.all_nodes.push_back( n );
        }

        for( int i = 0 ; i < nk ; i++ ){
            cin >> category_size;
            categories[i]->adjacents[destiny] = category_size;
        }
        for( int i = 0 ; i < np ; i++ ){
            cin >> categories_included;
            for( int j = 0 ; j < categories_included ; j++ ){
                cin >> category_id;
                problem_pool[i]->adjacents[ categories[category_id-1] ] = 1;
            }
        }

        while( true ){
            vector<Node*> path = graph.get_any_available_path(source,destiny);
            if( path.size() > 0 ){
                graph.fill_path(path);
            }else break;
        }

        bool is_complete = true;
        for( auto n : categories ){
            if( n->adjacents[destiny]>0 ){
                is_complete = false;
                break;
            }
        }

        if( is_complete ){
            cout << "1" << endl;
            for( auto c : categories ){
                vector<int> numbers_to_print;
                for( size_t i = 0 ; i < problem_pool.size() ; i++ ){
                    Node* p = problem_pool[i];
                    if( c->adjacents[p] == 1 ){
                        numbers_to_print.push_back(i+1);
                    }
                }
                for( int i = 0 ; i < numbers_to_print.size() ; i++ ){
                    if( i < numbers_to_print.size() - 1 )
                        cout << numbers_to_print[i] << " ";
                    else
                        cout << numbers_to_print[i] << endl;
                }
            }
        }else{
            cout << "0" << endl;
        }

    }
}