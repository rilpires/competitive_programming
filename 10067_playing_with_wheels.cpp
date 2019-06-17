/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/100/10067.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

struct Table{
    struct Combination{
        short digits[4];
        Combination(short digit_0 = 0 , short digit_1 = 0 , short digit_2 = 0 , short digit_3 = 0){
            digits[0] = digit_0;
            digits[1] = digit_1;
            digits[2] = digit_2;
            digits[3] = digit_3;
        }
        void operator = (  Combination c){
            digits[0] = c.digits[0];
            digits[1] = c.digits[1];
            digits[2] = c.digits[2];
            digits[3] = c.digits[3];
        }
        bool operator == (  Combination c ){
            return digits[0] == c.digits[0] && digits[1] == c.digits[1] &&  digits[2] == c.digits[2] &&  digits[3] == c.digits[3];
        }
        int minimum_distance_to(  Combination c){
            int ret = 0 , delta;
            for( int d = 0 ; d < 4 ; d ++ ){
                delta = abs(digits[d] - c.digits[d]);
                ret += min( delta , 10-delta );
            }
            return ret;
        }
        int get_index(){
            return 1000*digits[0]+ 100*digits[1] + 10*digits[2] + digits[3];
        }
    };

    Combination                 current_combination;
    Combination                 destiny_combination;
    map< int , Combination >    forbiddens;
    
    Table( Combination initial_combination , Combination final_combination ){
        current_combination = initial_combination;
        destiny_combination = final_combination;
    }
    void add_forbidden_rule( Combination c ){
        forbiddens[ c.get_index() ] = c;
    }
    bool is_combination_forbidden(  Combination c )  {
        int index = 1000*c.digits[0] + 100*c.digits[1] +  + 10*c.digits[2] + c.digits[3] ;
        return forbiddens.find(index) != forbiddens.end();
    }
    vector<Combination> get_possible_adjacents()  {
        vector<Combination> ret;
        for( int d = 0 ; d < 4 ; d++ ){
            Combination c = current_combination;
            c.digits[d] = (current_combination.digits[d] + 10 + 1) % 10;
            if( is_combination_forbidden(c) == false )
                ret.push_back(c);
            c.digits[d] = (current_combination.digits[d] + 10 - 1) % 10;
            if( is_combination_forbidden(c) == false )
                ret.push_back(c);
        }
        return ret;
    }

};

ostream& operator<<( ostream& os ,  Table::Combination c ){
    cout << c.digits[0] << c.digits[1] << c.digits[2] << c.digits[3];
    return os;
}

template<typename T>
struct Node{
    int             depth;
    T               state;
    Node( T _state , int _depth ):depth(_depth),state(_state){};
};

int main(){
    int T,number_of_rules;
    short d0 , d1 , d2 , d3;
    cin >> T;
    while( T -- ){
        cin >> d0 >> d1 >> d2 >> d3;
        Table::Combination initial_combination(d0,d1,d2,d3);
        cin >> d0 >> d1 >> d2 >> d3;
        Table::Combination final_combination(d0,d1,d2,d3);
        Table game_table( initial_combination , final_combination);
        cin >> number_of_rules;
        while( number_of_rules-- ){
            cin >> d0 >> d1 >> d2 >> d3;
            Table::Combination forbidden_combination(d0,d1,d2,d3);
            game_table.add_forbidden_rule( forbidden_combination );
        }
        if( game_table.current_combination == game_table.destiny_combination ){
            cout << 0 << endl;
            continue;
        }
        if( game_table.is_combination_forbidden( game_table.destiny_combination ) ){
            cout << -1 << endl;
            continue;
        }

        // A* search
        Node<Table::Combination> root(game_table.current_combination,0);
        //root.parent = NULL;
        Node<Table::Combination>& next_to_explore = root;
        map<int,vector< Node<Table::Combination> > > min_costs;
        set<int> already_explored_combinations;
        bool found = true;
        while( !(next_to_explore.state == game_table.destiny_combination) ){
            game_table.current_combination = next_to_explore.state;
            auto new_possible_combinations = game_table.get_possible_adjacents();
            for( auto c : new_possible_combinations ){
                Node<Table::Combination> new_node(c,next_to_explore.depth+1);
                if( already_explored_combinations.find(new_node.state.get_index()) == already_explored_combinations.end() ){
                    min_costs[ new_node.depth + new_node.state.minimum_distance_to(game_table.destiny_combination) ].push_back( new_node );
                    already_explored_combinations.insert(new_node.state.get_index());
                }
            }
            if( min_costs.size() == 0 ){
                found = false;
                break;
            }else{
                int next_min = min_costs.begin()->first;
                for( auto it : min_costs )if(it.first < next_min)next_min = it.first;
                next_to_explore = min_costs[next_min].back() ;
                min_costs[next_min].pop_back();
                if( min_costs[next_min].size() == 0 ){
                    min_costs.erase(next_min);
                }
            }
        }
        if(found){
            cout << next_to_explore.depth << endl;
        } 
        else cout << "-1" <<endl;
    }
}