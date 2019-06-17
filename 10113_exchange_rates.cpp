/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/101/10113.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

vector<int> primes , cribble;

#define MAX_PRIME 10000

void fill_primes(){
    cribble = vector<int>( MAX_PRIME );
    cribble[0] = 1;
    cribble[1] = 1;
    for( int i = 1 ; i < MAX_PRIME ; i++ ){
        if( cribble[i] == 0 ){
            primes.push_back(i);
            for( int j = 2*i ; j < MAX_PRIME ; j += i ){
                cribble[j] = 1;
            }
        }
    }
}

int mdc( int a , int b ){
    int temp;
    if( a > b ){
        temp = a;
        a = b;
        b = temp;
    }
    while( a > 1 && b > 1 ){
        if( b % a == 0 ){
            return a;
        } else{
            temp = a;
            a = b % a;
            b = temp;
        }
    }
    return 1;
}
int mmc( int a , int b ){
    return (a/mdc(a,b))*b;
}

int open_search_id = 0;
struct Node{
    int current_search_id = -1;
    int depth = 0;
    string name;
    map<string,pair<int,int> > adjacent_nodes;
};

vector<string> sequence_between( map<string,Node>& all_nodes , Node& node1 , Node& node2 , bool& found ){
    vector<string> ret,reverse_path;
    int search_id = open_search_id++;
    queue<string> bfs;
    bfs.push(node1.name);
    node1.current_search_id = search_id;
    node1.depth = 0;
    found = false;
    while( bfs.size() ){
        Node& node = all_nodes[bfs.front()];
        bfs.pop();
        if( node.name == node2.name ){
            found = true;
            break;
        }else for( auto it : node.adjacent_nodes ){
            Node& other_node = all_nodes[it.first]; 
            if( other_node.current_search_id != search_id ){
                other_node.current_search_id = search_id;
                other_node.depth = node.depth + 1;
                bfs.push(other_node.name);
            }else if( other_node.depth > node.depth ){
                cout << "What!" << endl;
            }
        }
    }
    if( found ){
        Node* current_step = &node2;
        while( current_step->depth > 0 ){
            reverse_path.push_back(current_step->name);
            for( auto it : current_step->adjacent_nodes ){
                Node& other_node = all_nodes[it.first];
                if( other_node.current_search_id == search_id && other_node.depth == current_step->depth-1 ){
                    current_step = &other_node;
                    break;
                }
            }
        }
        ret.push_back( node1.name );
        for( auto it = reverse_path.rbegin() ; it != reverse_path.rend() ; it++ ){
            ret.push_back( *it );
        }
    }
    return ret;
}

int main(){
    fill_primes();
    char next_command;
    string name1 , name2;
    int quant1 , quant2;
    map<string,Node> all_nodes;
    while( cin >> next_command ){
        switch( next_command ){
            case '.':
            {
                return 0;
            }
            case '!':
            {
                cin >> quant1 >> name1 >> next_command >> quant2 >> name2;
                Node& node1 = all_nodes[name1];
                Node& node2 = all_nodes[name2];
                node1.name = name1;
                node2.name = name2;
                node1.adjacent_nodes[name2] = pair<int,int>(quant1,quant2);
                node2.adjacent_nodes[name1] = pair<int,int>(quant2,quant1);
                break;
            }
            case '?':
            {
                cin >> name1 >> next_command >> name2;
                Node& node1 = all_nodes[name1];
                Node& node2 = all_nodes[name2];
                bool found;
                vector<string> sequence_of_names = sequence_between(all_nodes,node1,node2,found);
                if( name1 == name2 ){
                    cout << "1 " << name1 << " = 1 " << name2 << endl;
                }
                else if( found ){
                    int multiplier = 1;
                    int divisor = 1;
                    for( int i = 0 ; i+1 < sequence_of_names.size() ; i++ ){
                        Node& a = all_nodes[sequence_of_names[i]];
                        Node& b = all_nodes[sequence_of_names[i+1]];
                        divisor *= a.adjacent_nodes[b.name].first;
                        multiplier *= a.adjacent_nodes[b.name].second;
                        int common_divisor = mdc(divisor,multiplier);
                        divisor /= common_divisor;
                        multiplier /= common_divisor;
                    }
                    cout << divisor << " " << name1 << " = " << multiplier << " " << name2 << endl;
                } else {
                    cout << "? " << name1 << " = ? " << name2 << endl;
                }
                break;
            }
        }
    }
}