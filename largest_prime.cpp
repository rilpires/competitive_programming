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
#include <vector>
using namespace std;

vector<int> primes;
vector<int> crivo;

// 0 in primes
void fillPrimes( size_t crivo_size ){
    crivo.resize(crivo_size);
    primes.clear();
    crivo[0] = 1;
    for( size_t i = 1 ; i < crivo_size ; i++ ){
        if( crivo[i] == 0 ){
            primes.push_back(i+1);
            for( size_t j = i + (i+1) ; j < crivo_size ; j += (i+1) ) crivo[j] = 1;
        }
    }

    //for( size_t i = 0 ; i < 100 ; i++ ) if(crivo[i]==0)
        //cout << i << " , " << crivo[i] << endl;
}

// returns -1 if prime 
long long shortestPrime( long long N ){
    if(N<=2) return -1;
    if(N%2==0)return 2;
    long long sqrt = pow(N,0.5)+1;
    for( long long i = 2 ; i < sqrt ; i++ ){
        if( crivo[i-1] == 0 && N%i == 0 )
            return i;
    }
    return -1;
}

long long largestPrime( long long N ){
    long long shortest = shortestPrime(N);
    if( shortest < 0 ){
        return -1;
    }
    else{
        while( N % shortest == 0 ) N = N / shortest;
        shortest = shortestPrime(N);
        if( N > 2 && shortest == -1 ){
            return N;
        }else{
            long long temp = N;
            while ( temp % shortest == 0) temp = temp/shortest;
            if(shortestPrime(N) == shortest) return shortest;
            return largestPrime(N);
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    fillPrimes( 9999999 );
    long long N;
    while( cin >> N && N != 0 ){
        if( N < 0 ) N = -N;
        cout << largestPrime(N) << endl;
    }
    
    return 0;
}