#include <vector>
#include <map>
using namespace std;

vector<int> primes;

void fillPrimes( size_t crivo_size ){
    vector<int> crivo(crivo_size);
    crivo[0] = 1;
    for( size_t i = 1 ; i < crivo_size ; i++ )
    if( crivo[i] == 0 ){
        primes.push_back( i+1 );
        for( size_t j = i + (i+1) ; j < crivo_size ; j+= (i+1) ){
            crivo[j] = 1;
        }
    }
}

map<int,int> factored( int N ){
    map<int,int> ret ;
    while( N != 1 ){
        for( auto p : primes ){
            if( N % p == 0 ){
                ret[p]++;
                N = N/p;
                break;
            }
        }
    }
    return ret;
}

// not ordered!
vector<int> divisors( int N ){
    map<int,int> factors = factored(N);
    vector<int> ret(0);
    ret.push_back(1);
    for( auto it = factors.begin() ; it != factors.end() ; it++ ){
        for( int exp = 1 ; exp <= it->second ; exp++ ){
            vector<int> new_ones(0);
            for( auto div : ret )
                new_ones.push_back( div * pow(it->first,exp) );
            for( auto div : new_ones )
                ret.push_back(div);
        }
    }
    for( auto it : ret ) cout << it << endl;
    return ret;
}