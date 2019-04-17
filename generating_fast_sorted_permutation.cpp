/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/100/10098.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

// OMG no need if we use next_permutation
void backtracking( string& current_word , string& remaining_word , set<string>& all_permutations ){
    if( remaining_word.size() == 1 ){
        all_permutations.insert( current_word + remaining_word );
    }else{
        set<char> already_passed;
        for( size_t i = 0 ; i < remaining_word.size() ; i++ ){
            char c = remaining_word[i];
            if( already_passed.find(c) != already_passed.end() ) continue;

            string new_current_word = current_word;
            string new_remaining_word = remaining_word;

            new_current_word.push_back( c );
            new_remaining_word.erase( new_remaining_word.begin() + i );

            backtracking( new_current_word , new_remaining_word , all_permutations );
            already_passed.insert(c);
        }
    }
}

set<string> allPermutations( string word ){
    set<string> ret;
    string s = "";
    backtracking( s , word , ret );
    return ret;
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    int N;
    string word;
    cin >> N;
    while( N-- ){
        cin >> word;
        sort(word.begin() , word.end());
        bool next = true;
        while( next ){
            cout << word << endl;
            next = next_permutation( word.begin() , word.end() );
        }
        cout << endl;
    }
}