/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/101/10139.pdf       
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <map>
using namespace std;

vector<int> crivo;
vector<int> primes;
void fillPrimes(size_t crivo_size){
    crivo.clear();
    crivo.resize(crivo_size);
    crivo[0] = 1;
    for( size_t i = 0 ; i < crivo_size ; i++ ){
        if(crivo[i]==0){
            primes.push_back(i+1);
            for( size_t j = i + (i+1) ; j < crivo_size ; j += (i+1) )
                crivo[j] = 1;
        } 
    }
}
map<int,int> factored( int N ){
    map<int,int> ret;
    if( N <= 1 ) return ret;
    int sqrt = pow(N,0.5)+1;
    for( auto it = primes.begin() ; it != primes.end() && (*it) < sqrt ; it++ ){
        while( N % (*it) == 0 ){
            ret[*it]++;
            N = N/(*it);
        }
    }
    if( N != 1 )
        ret[N]++;
    return ret;
}
bool factorialHasFactors( int N , map<int,int> factors ){
    for( auto it = factors.begin() ; it != factors.end() ; it++ ){
        int prime = it->first;
        int how_many = it->second;
        int total_amount_available = 0;
        for( int current_power = 1 ; pow(prime,current_power) <= N ; current_power++ ){
            total_amount_available += N/(pow(prime,current_power));
        }
        if( total_amount_available < how_many ) return false;
    }
    return true;
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    fillPrimes(9999999);
    int A,B;
    while( cin >> A >> B ){
        if( factorialHasFactors(A,factored(B)) )
            cout << B << " divides " << A << "!"<< endl;
        else
            cout << B << " does not divide " << A << "!"<< endl;
    }
}