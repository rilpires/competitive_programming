/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://        
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

struct BigNumber{
    
};

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    int T = rand()%100;
    while( T-- ){
        int N = 1 + rand() % 50;
        int M = rand() % N;
        cout << N << " " << M << endl;
        for( int n = 0 ; n < N ; n++ )
            cout << rand()%N << " ";
        cout << endl;
        for( int m = 0 ; m < M ; m++ )
            cout << rand()%N << " ";
        cout << endl;
        
    }
    
}