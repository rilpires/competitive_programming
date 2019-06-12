/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/108/p10830.pdf      
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <map>
using namespace std;


long long CSOD( int N ){
    if( N <= 3 ) return 0;
    long long ret = 0;
    long long sqrt = pow(N,0.5);
    long long minor_number_of_repeats = sqrt+1;
    for( int i = 2 ; i <= sqrt - 1 ; i++ ){
        minor_number_of_repeats = (N/i) - 1;
        ret += i*minor_number_of_repeats;
    }
    for( int repeats = minor_number_of_repeats-1 ; repeats >= 1 ; repeats-- ){
        long long bot = (N/(repeats+2))+1;
        long long top = (N/(repeats+1));
        ret += (repeats)*(top-bot+1)*(top+bot)/2;
    }
    return ret;
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    int line_number = 1;
    int N;
    while( cin >> N && N > 0 ){
        cout << "Case " << line_number++ << ": " << CSOD(N) << endl;
    }
    return 0;
}