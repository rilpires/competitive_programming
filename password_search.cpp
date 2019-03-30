/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/9/902.pdf
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

string passwordSearch( int N , const string& msg ){
    map<string,int> frequency_count;
    int msg_size = msg.length();
    string substring;
    for( int i = 0 ; i + N <= msg_size ; i++ ){
        substring = msg.substr( i , N );
        substring.assign( msg , i , N );
        frequency_count[substring]++;
    }

    int leading_count = 0;
    string leading_substr;
    for( auto it = frequency_count.begin() ; it != frequency_count.end() ; it++ ){
        if( it->second > leading_count ){
            leading_count = it->second;
            leading_substr = it->first;
        }
    }

    return leading_substr;
}

int main(){
    // ==========
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========    
    
    int N;
    string message = "";
    while( cin >> N >> message ){
        cout << passwordSearch(N,message) << endl;
    }

    return 0;
}