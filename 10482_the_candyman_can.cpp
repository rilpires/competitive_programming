/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/104/p10482.pdf
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

#define MAX_WEIGHT_KID 270
#define MAX_WEIGHT_KID_SQUARED 72900
#define STATE uint32_t

int total_weight;
vector<int> weights;

int main(){
    int T;
    cin >> T;
    for( int case_number = 1 ; case_number <= T ; case_number ++ ){
        int n,w;
        cin >> n;
        weights.assign( n , 0 );
        total_weight = 0;
        for( int i = 0 ; i < n ; i++ ){
            cin >> w;
            weights[i] = w;
            total_weight += w;
        }
        int best_result = total_weight;


        unordered_set<STATE> visited_states;
        vector<STATE> space_unexplored;
        visited_states.insert( 0 );
        space_unexplored.push_back( 0 );
        int still_available_to_gain = total_weight;
        for( int candy_id = 0 ; candy_id < n ; candy_id++ ){
            int candy_weight = weights[candy_id];
            unordered_set<STATE> next_states_to_add;
            for( auto state : space_unexplored ){
                int w1 = state % MAX_WEIGHT_KID;
                int w2 = (state/MAX_WEIGHT_KID) % MAX_WEIGHT_KID;
                int w3 = (state/(MAX_WEIGHT_KID_SQUARED)) % MAX_WEIGHT_KID;

                if( w1 > w2 + still_available_to_gain || w2 > w3 + still_available_to_gain || w1 > w3 + still_available_to_gain ) continue;

                if( w1 + candy_weight <= MAX_WEIGHT_KID ){
                    int new_state = (w1+candy_weight) + w2*MAX_WEIGHT_KID + w3*(MAX_WEIGHT_KID_SQUARED);
                    if( visited_states.find(new_state) == visited_states.end() ){
                        next_states_to_add.insert( new_state );
                    }
                }
                if( w2 + candy_weight <= MAX_WEIGHT_KID ){
                    int new_state = w1 + (w2+candy_weight)*MAX_WEIGHT_KID + w3*(MAX_WEIGHT_KID_SQUARED);
                    if( visited_states.find(new_state) == visited_states.end() ){
                        next_states_to_add.insert( new_state );
                    }
                }
                if( w3 + candy_weight <= MAX_WEIGHT_KID ){
                    int new_state = w1 + w2*MAX_WEIGHT_KID + (w3+candy_weight)*(MAX_WEIGHT_KID_SQUARED);
                    if( visited_states.find(new_state) == visited_states.end() ){
                        next_states_to_add.insert( new_state );
                    }
                }
            }
            still_available_to_gain -= candy_weight;
            space_unexplored.clear();
            for( auto state : next_states_to_add ){
                if( visited_states.find(state) == visited_states.end() ){
                    visited_states.insert(state);
                    space_unexplored.push_back(state);

                    if( still_available_to_gain == 0 ){
                        int w1 = state % MAX_WEIGHT_KID;
                        int w2 = (state/MAX_WEIGHT_KID) % MAX_WEIGHT_KID;
                        int w3 = (state/(MAX_WEIGHT_KID_SQUARED)) % MAX_WEIGHT_KID;
                        int _max = max(max(w1,w2),w3);
                        int _min = min(min(w1,w2),w3);
                        if( _max - _min < best_result ) best_result = _max - _min;
                    }
                }
            }
        }
        

        cout << "Case " << case_number << ": " << best_result << endl;
    }
}