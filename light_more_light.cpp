/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/101/10110.pdf   
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <map>
using namespace std;

vector<long long> primes;
vector<long long> crivo;
void fillPrimes( size_t crivo_size ){
    crivo.clear(); crivo.resize(crivo_size);
    crivo[0] = 1;
    for( size_t i = 1 ; i < crivo_size ; i++ ){
        if( crivo[i] == 0 ){
            primes.push_back(i+1);
            for( size_t j = i + (i+1) ; j<crivo_size ; j+=(i+1) )
                crivo[j] = 1;
        }
    }
}
map<long long,int> factored( long long N ){
    map<long long,int> ret;
    if( N <= 1 ) return ret;
    long long sqrt = pow(N,0.5) + 1;
    for( auto it = primes.begin() ; it != primes.end() && *it < sqrt && N != 1 ; it++ ){
        while( N % *it == 0 ){
            ret[*it]++;
            N = N / *it;
            sqrt = pow(N,0.5)+1;
        }
    }
    if( N != 1 ) ret[N]++;
    return ret;
}
bool evenDivisors( long long N ){
    long long sqrt = pow(N,0.5) + 1;
    for( auto it = primes.begin() ; it != primes.end() && *it < sqrt && N != 1 ; it++ ){
        int this_exp = 0;
        while( N % *it == 0 ){
            N = N / *it;
            this_exp++;
        }
        if( this_exp > 0 )
            sqrt = pow(N,0.5)+1;
        if( this_exp % 2 == 1 ) return true; 
    }
    if( N != 1 ) return true;
    return false;
}
long long numberOfDivisor( long long N ){
    map<long long,int> factors = factored(N);
    long long ret = 1;
    for( auto it : factors )
        ret *= (it.second + 1);
    return ret;
}
vector<long long> divisors( long long N ){
    vector<long long> ret;
    map<long long,int> factors = factored(N);
    ret.push_back(1);
    for( auto it = factors.begin() ; it != factors.end() ; it++ ){
        vector<long long> to_add;
        for( long long e = 0 ; e < it->second ; e++ )
        for( auto div : ret )
            to_add.push_back( div * pow(it->first,e) );
        for( auto div : to_add )
            ret.push_back(div); 
    }
    return ret;
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    fillPrimes(65536);
    long long N;
    while( cin >> N && N != 0 ){
        long long x = sqrt(N); 
        if( N != x * x )
            cout << "no" << endl;
        else
            cout << "yes" << endl;
    }
}