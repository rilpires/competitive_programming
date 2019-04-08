/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/100/p10049.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int fn( int N , const vector<int>& milestones ){
    for( size_t t = 1 ; t < milestones.size() ; t++ ){
        if( N < milestones[t] ) return t;
    }
    int last_milestone = milestones[milestones.size()-1];
    if( N < last_milestone + milestones.size() ){
        return milestones.size();
    }else{
        return -1;
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========    

    //Pre-bake fn vector
    vector<int> milestones(0);
    milestones.push_back(1);
    int current_i = 1;
    int last_milestone = 1;
    while( milestones[milestones.size()-1] < 2000000000 ){ 
        milestones.push_back( last_milestone + fn(current_i++,milestones)  );
        last_milestone = milestones[milestones.size()-1];
    }

    int x;
    while( cin >> x && x > 0)
        cout << fn(x,milestones) << endl;

}