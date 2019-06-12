/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/114/p11463.pdf
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

struct Node{
    set<Node*>  adjacents;
    int         distance_from_begin = -1;
    int         distance_from_final = -1;
};


int main(){
    int T , N , R , case_number = 1 , current_search_id = 0 , id1 , id2 ;
    cin >> T;
    while( T-- ){
        cin >> N >> R ;
        vector<Node> all_nodes(N);
        while (R--){
            cin >> id1 >> id2;
            Node& node1 = all_nodes[id1];
            Node& node2 = all_nodes[id2];
            node1.adjacents.insert(&node2);
            node2.adjacents.insert(&node1);
        }

        cin >> id1 >> id2;
        Node&   begin_node = all_nodes[id1]; 
        Node&   final_node = all_nodes[id2]; 
        // BFS from initial
        begin_node.distance_from_begin = 0;
        queue<Node*> bfs;
        bfs.push(&begin_node);
        while( bfs.size() ){
            Node& current_node = *(bfs.front());
            bfs.pop();
            for( auto it : current_node.adjacents ){
                if( it->distance_from_begin == -1 ){
                    it->distance_from_begin = current_node.distance_from_begin+1;
                    bfs.push(it);
                }
            }
        }

        // BFS from final
        final_node.distance_from_final = 0;
        bfs.push(&final_node);
        while( bfs.size() ){
            Node& current_node = *(bfs.front());
            bfs.pop();
            for( auto it : current_node.adjacents ){
                if( it->distance_from_final == -1 ){
                    it->distance_from_final = current_node.distance_from_final+1;
                    bfs.push(it);
                }
            }
        }
        
        int max_distance = 0;
        for( auto node : all_nodes ){
            if( node.distance_from_begin + node.distance_from_final > max_distance )
                max_distance = node.distance_from_begin + node.distance_from_final;
        }

        cout << "Case " << case_number++ << ": " << max_distance << endl;

    }
}