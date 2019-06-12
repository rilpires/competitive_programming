/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/109/p10976.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;


int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    int x , y , k ;
    vector< pair<int,int> > solutions;
    while( cin >> k ){
        solutions.clear();
        for( y = k + 1 ; y <= 2*k ; y++ ){
            if( (y*k)%(y-k) == 0 ){
                x = (y*k)/(y-k);
                solutions.push_back(pair<int,int>(x,y));
            } 
        }
        cout << solutions.size() << endl;
        for( auto p : solutions ){
            cout << "1/" << k << " = 1/"<< p.first <<" + 1/" << p.second << endl;
        }
    }
}