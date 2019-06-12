/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/105/10503.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;

bool backtrackingConfigurations(    
    pair<short,short> first_part,
    pair<short,short> last_part,
    vector< pair<short,short> > remaining_pieces ,
    int remaining_parts )
{
    if( remaining_parts > remaining_pieces.size() ){
        return false;
    }
    else if( remaining_parts == 0 ){
        return first_part.second == last_part.first;
    } else {
        remaining_parts--;
        for( size_t i = 0 ; i < remaining_pieces.size() ; i++ ){
            auto p = remaining_pieces[i];
            if( p.first == first_part.second ){
                auto new_first = p;
                auto new_remaining = remaining_pieces;
                new_remaining.erase( new_remaining.begin() + i );

                if( backtrackingConfigurations( new_first , last_part , new_remaining , remaining_parts ) )
                    return true;
            }
            else if( p.second == first_part.second ){
                auto new_first = pair<short,short>( p.second , p.first );
                auto new_remaining = remaining_pieces;
                new_remaining.erase( new_remaining.begin() + i );

                if( backtrackingConfigurations( new_first , last_part , new_remaining , remaining_parts ) )
                    return true;
            }
        }
        return false;
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    int N , M , p1 , p2 ;
    pair<short,short> first_part , last_part;
    vector< pair<short,short> > all_pieces;
    while( cin >> N >> M && N != 0 ){
        all_pieces.clear();

        cin >> p1 >> p2;
        first_part.first = p1;
        first_part.second = p2;
        
        cin >> p1 >> p2;
        last_part.first = p1;
        last_part.second = p2;
        
        for( size_t i = 0 ; i < M ; i++ ){
            cin >> p1 >> p2;
            all_pieces.push_back( pair<short,short>(p1,p2) );
        }

        cout << ( backtrackingConfigurations(first_part,last_part,all_pieces,N) ? "YES":"NO") << endl;

    }
}