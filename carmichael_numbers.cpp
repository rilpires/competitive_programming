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

int fermatModule( int a , int N ){
    long long ret = 1;
    long long factor = a;
    int expoent = N;
    while( expoent > 0 ){
        if( expoent % 2 == 1 ){
            ret = (ret*factor)%N;
            expoent--;
        }
        else {
            factor = (factor*factor)%N;
            expoent = expoent/2;
        }
    }
    return ret;
}

bool isCarmichael( int n ){
    if( crivo[n-1] == 1 ){
        bool passed = true;
        int coprimes_passed = 0;
        for( int a = 2 ; a < n  ; a++ )
        {
            coprimes_passed++;
            if( fermatModule(a,n) != a ){
                passed = false;
                break;
            }
        }
        if( passed ) return true;
    }
    return false;
}


int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    fillCrivo( 66666 );
    long long N;
    while( cin >> N && N != 0 ){
        if( isCarmichael(N) )
            cout << "The number " << N << " is a Carmichael number." << endl;
        else
            cout << N << " is normal." << endl;
        
    }
    return 0;
}