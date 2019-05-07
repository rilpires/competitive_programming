/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem URL (Google Code Jam 2019):
        https://codingcompetitions.withgoogle.com/codejam/round/0000000000051635/0000000000104f1a

*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

int v[] = { 17,16,13,11,9,7,5 };

pair<int,int> find_new_mod( pair<int,int> mod_A , pair<int,int> mod_B ){
    int k = 0;
    while( true ){
        if( (mod_A.second*k+mod_A.first)%mod_B.second == mod_B.first )
            return pair<int,int>( mod_A.second*k+mod_A.first , mod_A.second*mod_B.second );
        else 
            k++;
    }
    return pair<int,int>(-1,-1);
}
int guess_number( vector< pair<int,int> >& modules ){
    pair<int,int> a,b;
    while( modules.size() > 1){
        a = modules.back();
        modules.pop_back();
        b = modules.back();
        modules.pop_back();
        modules.push_back( find_new_mod( a , b) );
    }
    return modules[0].first;
}

int main(){
    int T,N,M,result;
    cin >> T >> N >> M;
    
    while( T-- ){
        int night_number = 0;
        vector< pair<int,int> > modules(7);

        while( night_number < 7 ){
            int gopher_sum = 0;
            int n;
            for( int i = 0 ; i < 18 ; i++ )
                cout << v[night_number] << ( (i<17) ? ' ' : '\n' );
            for( int i = 0 ; i < 18 ; i++ ){
                cin >> n;
                gopher_sum += n;
            }
            gopher_sum = gopher_sum % v[night_number];
            modules[night_number] = pair<int,int>(gopher_sum,v[night_number]);
            night_number++;
        }

        cout << guess_number( modules ) << endl;

        cin >> result;
        if( result == -1 ){
            cout << "Wrong answer :( " << endl;
        }

    }
}