/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/105/p10576.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;


int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    int s , d , i;
    while( cin >> s >> d ){
        int superplus_per_part = 0;
        int max_income = 0;
        for( i = 1 ; i <= 5 ; i++ ){
            if( i*s - (5-i)*d > 0  ){
                superplus_per_part = i-1;
                break;
            }
        }
        switch( superplus_per_part ){
            case 0:
                max_income = 0*s - 12*d; 
                break;
            case 1:
                max_income = 3*s - 9*d; 
                break;
            case 2:
                max_income = 6*s - 6*d; 
                break;
            case 3:
                max_income = 8*s - 4*d; 
                break;
            case 4:
                max_income = 10*s - 2*d; 
                break;
        }
        if( max_income > 0 )
            cout << max_income << endl;
        else
            cout << "Deficit" << endl;
    }
}

