/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/110/p11085.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <set>
using namespace std;

bool validConfiguration( const vector<int>& config ){
    set<int> diagonals_1;
    set<int> diagonals_2;
    for( int x = config.size()-1 ; x >= 0 ; x-- ){
        int diag1_pos = x + config[x];
        int diag2_pos = x - config[x];
        diagonals_1.insert(diag1_pos);
        diagonals_2.insert(diag2_pos);
    }
    if( diagonals_1.size() != diagonals_2.size() || diagonals_1.size() != config.size() )
        return false;
    return true;
}

void backtrackingConfigurations( vector<int>& current_config , vector<int>& remaining , vector< vector<int> >& ret ){
    if( remaining.size() > 0 ){
        for( auto i = 0 ; i < remaining.size() ; i++ ){
            current_config.push_back( remaining[i] );

            if( validConfiguration(current_config) ){
                vector<int> new_remaining(remaining);
                new_remaining.erase( new_remaining.begin() + i );
                backtrackingConfigurations( current_config , new_remaining , ret );
            }

            current_config.pop_back();
        }
    }
    else if( validConfiguration(current_config) )
        ret.push_back(current_config);
}

vector< vector<int> > fillValidConfigurations(  ){
    vector< vector<int> > ret;

    vector<int> remaining;
    vector<int> current_config;
    for( int i = 1 ; i <= 8 ; i++ )
        remaining.push_back(i);

    backtrackingConfigurations( current_config , remaining , ret);
    
    //cout << ret.size() << " valids." << endl;
    
    return ret;
} 

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    auto valid_configurations = fillValidConfigurations( );
    
    string line;
    stringstream line_stream;
    vector<int> config;
    int i,n,case_number=1,max_correct=1;
    while( getline(cin,line) ){
        config.clear();
        line_stream = stringstream(line);
        for( i = 0 ; i < 8 ; i++ ){
            line_stream >> n;
            config.push_back(n);
        }
        max_correct = 1;
        for( auto v : valid_configurations ){
            int current_corrects = 0;
            for( int j = 0 ; j <= 7 ; j++ ){
                if( v[j] == config[j] ){
                    current_corrects++;
                }
            }
            if( current_corrects > max_correct )
                max_correct = current_corrects;
            if( max_correct == 8 ) break;
        }
        cout << "Case " << case_number++ << ": " << 8 - max_correct << endl;
    }
}