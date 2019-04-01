/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/102/p10213.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

int howMany( int N ){
    if( N % 2 == 0 ){
        return N + (N/2) * ( pow(2,N-3) ) ;
    }else{
        return -1;
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========

    int N, T;
    cin >> T;
    for( int t = 0 ; t < T ; t++ ){
        cin >> N;
        cout << howMany(N) << endl;
    }
}