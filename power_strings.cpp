/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/102/10298.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

int powerString( const string& msg ){
    for( int i = msg.size() ; i > 1 ; ){
        if( msg.size() % i != 0 ){
            i--;
        }else{
            int substr_size = msg.size()/i;
            string substr = msg.substr(0, substr_size );
            bool ok = true;
            
            for( int j = substr_size ; j < msg.size() ; j += substr_size )
            if( substr != msg.substr(j,substr_size) )
            {
                ok = false; break;
            }
            
            if(ok) return i;
            i = msg.size() / ( substr_size + 1 );
        }
    }
    return 1;
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========    
    
    string line;
    while( true ){
        getline( cin , line );
        if( line == "." ) break;
        else cout << powerString(line) << endl;
    }
    return 0;
}