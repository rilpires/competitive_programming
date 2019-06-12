/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/101/10168.pdf   
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>

#define CRIVO_SIZE 10000000

using namespace std;

vector<int> crivo;
vector<int> primes;

void fillCrivo(){
    crivo.clear();crivo.resize(CRIVO_SIZE);
    crivo[0] = 1;
    for( size_t i = 0 ; i < CRIVO_SIZE ; i++ ){
        if( crivo[i] == 0 ){
            primes.push_back(i+1);
            for( size_t j = i + (i+1) ; j < CRIVO_SIZE ; j += (i+1) ){
                crivo[j] = 1;
            }
        }
    }
}

pair<int,int> conjectureGoldbach( int N ){
    for( auto p : primes ){
        if( crivo[N-p-1] == 0 ){
            return pair<int,int>( p , N-p );
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    fillCrivo();
    int N;
    vector<int> parts;
    pair<int,int> last_parts;
    while( cin >> N ){
        if( N < 8 )
            cout << "Impossible." << endl;
        else {
            parts.clear();
            
            if( N%2==0 ){
                parts.push_back(2);
                N-=2;
            }
            else{
                parts.push_back(3);
                N-=3;
            }

            parts.push_back(2);
            N-=2;
            
            last_parts = conjectureGoldbach(N);
            parts.push_back(last_parts.first);
            parts.push_back(last_parts.second);
            
            cout << parts[0] << " " <<parts[0] << " " << parts[0] << " " << parts[0] << endl;

        }
    }
}

