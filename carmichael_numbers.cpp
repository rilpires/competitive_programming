/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/100/10006.pdf       
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <set>
using namespace std;

vector<int> crivo;
vector<int> primes;
set<int> fermat_pass;
set<int> carmichaels;

void fillCrivo( size_t crivo_size ){
    crivo.clear();crivo.resize(crivo_size);
    crivo[0] = 1;
    for( size_t i = 1 ; i < crivo_size ; i++ ){
        if( crivo[i] == 0 ){
            primes.push_back(i+1);
            for( size_t j = i + (i+1) ; j<crivo_size ; j += (i+1) ){
                crivo[j] = 1;
            }
        }
    }
}

int fermatModule( int a , int n ){
    long long left_side = 1;
    for( size_t i = 1 ; i <= n ; i++ ){
        left_side = (left_side*a)%n;
        if( i > 1 && i < n && left_side % n == a % n ){
            int new_n = (n-1)%(i-1); 
            if( new_n == 0 ) return left_side;
            return fermatModule( a , new_n );
        }
    }
    return left_side%n;
}
int fermatPeriod( int a , int n ){
    long long left_side = 1;
    for( size_t i = 1 ; i <= n ; i++ ){
        left_side = (left_side*a)%n;
        if( i > 1 && i < n && left_side % n == a % n ){
            return i;
        }
    }
    return left_side%n;
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    fillCrivo( 99999 );
    for( int a = 2 ; a < 65000 ; a++ ){
        int a_period = 1;
        for( int n = 2 ; n < 65000 ; n++ ){
            
        }
    }
    long long N;
    while( cin >> N && N != 0 ){
            if( carmichaels.find(N) != carmichaels.end() )
                cout << "The number " << N << " is a Carmichael number." << endl;
            else
                cout << N << " is normal." << endl;
        }

    }
    return 0;
}