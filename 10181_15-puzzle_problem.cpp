/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/101/10181.pdf
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

#define MAX_DEPTH 51

struct Puzzle{
    short tiles[16];
    short empty_x , empty_y;
    string current_steps = "";

    void find_zero(){
        for( int i = 0 ; i < 16 ; i++ ){
            if( tiles[i] == 0 ){
                empty_x = i % 4;
                empty_y = i / 4;
            }
        }
    }
    void move(char direction){
        current_steps += direction;
        switch(direction){
            case 'R':
                tiles[ empty_x + 4*empty_y ] = tiles[ (empty_x+1) + 4*empty_y ];
                tiles[ (empty_x+1) + 4*empty_y ] = 0;
                empty_x++;
                break;
            case 'L':
                tiles[ empty_x + 4*empty_y ] = tiles[ (empty_x-1) + 4*empty_y ];
                tiles[ (empty_x-1) + 4*empty_y ] = 0;
                empty_x--;
                break;
            case 'U':
                tiles[ empty_x + 4*empty_y ] = tiles[ empty_x + 4*(empty_y-1) ];
                tiles[ empty_x + 4*(empty_y-1) ] = 0;
                empty_y--;
                break;
            case 'D':
                tiles[ empty_x + 4*empty_y ] = tiles[ empty_x + 4*(empty_y+1) ];
                tiles[ empty_x + 4*(empty_y+1) ] = 0; 
                empty_y++;
                break;
        }
    }
    void undo_move(){
        char last_direction = current_steps[current_steps.size()-1];
        current_steps.pop_back();
        switch(last_direction){
            case 'L':
                last_direction = 'R';
                break;
            case 'R':
                last_direction = 'L';
                break;
            case 'U':
                last_direction = 'D';
                break;
            case 'D':
                last_direction = 'U';
                break;
        }
        switch(last_direction){
            case 'R':
                tiles[ empty_x + 4*empty_y ] = tiles[ (empty_x+1) + 4*empty_y ];
                tiles[ (empty_x+1) + 4*empty_y ] = 0;
                empty_x++;
                break;
            case 'L':
                tiles[ empty_x + 4*empty_y ] = tiles[ (empty_x-1) + 4*empty_y ];
                tiles[ (empty_x-1) + 4*empty_y ] = 0;
                empty_x--;
                break;
            case 'U':
                tiles[ empty_x + 4*empty_y ] = tiles[ empty_x + 4*(empty_y-1) ];
                tiles[ empty_x + 4*(empty_y-1) ] = 0;
                empty_y--;
                break;
            case 'D':
                tiles[ empty_x + 4*empty_y ] = tiles[ empty_x + 4*(empty_y+1) ];
                tiles[ empty_x + 4*(empty_y+1) ] = 0; 
                empty_y++;
                break;
        }
    }
    short get_how_many_rights() const{
        short ret = 0;
        for( int i = 0 ; i < 16 ; i++ ) ret += ( tiles[i] == (i+1) );
        return ret;
    }
    vector<char> get_possible_directions( ) const{
        vector<char> ret;
        char last_move = '_';
        if( current_steps.size() > 0 ) last_move = current_steps[current_steps.size()-1];
        if( empty_x > 0 && last_move != 'R'  )
            ret.push_back('L');
        if( empty_x < 3 && last_move != 'L'  )
            ret.push_back('R');
        if( empty_y > 0 && last_move != 'D'  )
            ret.push_back('U');
        if( empty_y < 3 && last_move != 'U' )
            ret.push_back('D');
        return ret;
    }
    void print(){
        cout << endl << "====Puzzle=========" << endl;
        for( int y = 0 ; y < 4 ; y ++ ){
            for( int x = 0 ; x < 4 ; x ++ ){
                cout << tiles[x+4*y] << '\t';
            }
            cout << endl;
        }
        cout << "Inversions: " << get_number_of_inversions() << endl;
        cout << "Manhattan distance: " << get_manhattan_distance() << endl;
        cout << endl;
    }
    int get_manhattan_distance(){
        int ret = 0;
        for( int TILE_Y = 0 ; TILE_Y <= 3 ; TILE_Y++ )
        for( int TILE_X = 0 ; TILE_X <= 3 ; TILE_X++ ){
            int EXPECTED_TILE_ID = TILE_X + 4*TILE_Y + 1;
            
            if( EXPECTED_TILE_ID != 16 )
            for( int SEARCH_Y = 0 ; SEARCH_Y <= 3 ; SEARCH_Y ++ )
            for( int SEARCH_X = 0 ; SEARCH_X <= 3 ; SEARCH_X ++ ){
                if( tiles[SEARCH_X + 4*SEARCH_Y] == EXPECTED_TILE_ID ){
                    ret += abs( SEARCH_X - TILE_X ) + abs( SEARCH_Y - TILE_Y );
                    break;
                }
            }    
        }
        return ret;
    }
    int get_number_of_inversions(){
        vector<int> tiles_copy;
        int ret = 0;
        for( int i = 0 ; i < 16 ; i++ )if( tiles[i] != 0 )
            tiles_copy.push_back( tiles[i] );
        for( int i = 0 ; i < 15 ; i++ ){
            int expected_id = i + 1;
            if( tiles_copy[i] != expected_id ){
                for( int j = i+1 ; j < 15 ; j++ ){
                    if( tiles_copy[j] == expected_id ){
                        int temp = tiles_copy[i] ;
                        tiles_copy[i] = tiles_copy[j];
                        tiles_copy[j] = temp;
                        ret++;
                        break;
                    }
                }
            }
        }
        return ret;
    }
    bool is_solvable(){
        return (get_number_of_inversions() + abs(3-empty_y) )%2 == 0;
    }
    void go_to( const string& new_steps ){
        size_t common_preffix_size = 0;
        while( current_steps.substr(0,common_preffix_size+1) == new_steps.substr(0,common_preffix_size+1) && common_preffix_size < min(current_steps.size(),new_steps.size()) ){
            common_preffix_size++;
        }
        string back_string = current_steps.substr(common_preffix_size);
        string forward_string = new_steps.substr(common_preffix_size);
        for( auto it = back_string.rbegin() ; it != back_string.rend() ; it++ )
            undo_move();
        for( auto it = forward_string.begin() ; it != forward_string.end() ; it++ )
            move(*it);
    }
};


string A_star( Puzzle& p  ){
    if( p.get_how_many_rights() == 15 ) return p.current_steps;
    bool solved = false;
    map<int,vector<string> > tree;
    string current_step = p.current_steps;
    while( !solved ){
        if( current_step.size() <= MAX_DEPTH ) {
            p.go_to(current_step);
            auto possible_steps = p.get_possible_directions();
            for( auto c : possible_steps ){
                p.move(c);
                if( p.get_how_many_rights() == 15 ){
                    return p.current_steps;
                }else{
                    int manhattan_distance = p.get_manhattan_distance();
                    int cost = p.current_steps.size();
                    if( manhattan_distance+cost <= MAX_DEPTH ){
                        tree[ manhattan_distance+cost ].push_back( p.current_steps );
                    }
                    p.undo_move();
                }
            }
        }
        if( !solved ){
            if( tree.size() == 0 ) return "This puzzle is not solvable.";
            int min_score = tree.begin()->first;
            for( auto it = tree.begin() ; it != tree.end() ; it++ ){
                if( it->first < min_score ) min_score = it->first;
            }
            vector<string>& best_candidates = tree[min_score];
            string next_candidate = best_candidates.back();
            best_candidates.pop_back(); 
            if( best_candidates.size() == 0 )tree.erase(min_score);
            current_step = next_candidate;
        }
    }
    return "This puzzle is not solvable.";
}

int main(){
    int T;
    cin >> T;
    while( T-- ){
        //cout << endl << endl << "T eh " << T << endl;
        Puzzle puzzle;
        for( int i = 0 ; i < 16 ; i++ )cin >> puzzle.tiles[i];
        puzzle.find_zero();
        //if(T!=0)continue;
        //if(T==0)puzzle.go_to("RRDDDLULURDRDRULLLDRRULURDLLDRRRUULURDDLLURRDLDR");
        //puzzle.print();
        // cout << "SOlvable? " << puzzle.is_solvable() << endl;
        //continue;
        if( puzzle.is_solvable() ){
            cout << A_star(puzzle);
            cout << endl;
        }
        else   
            cout << "This puzzle is not solvable." << endl;
    }
}