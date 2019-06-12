/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/102/p10219.pdf        
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

const double ln10 = log(10);

double log10CnR( uint64_t N , uint64_t K = 1 ){
    double ret = 0;
    if( K > N/2 ) K = N-K;
    uint64_t initial_K = K;
    for( uint64_t i = 0 ; i < initial_K ; i++ ){
        ret += log10(N--) - log10(K--);
    }
    return ret;
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    uint32_t N,K;    
    while( cin >> N >> K ){
        cout << (int)floor( log10CnR(N,K) + 1) << endl;
    }
    return 0;
}