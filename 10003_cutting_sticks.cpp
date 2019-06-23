/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/100/p10003.pdf
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_L 1001
#define MAX_N 51

int mem[MAX_N][MAX_N];

vector<int> edges;

int main(){
    int l,n,c;
    while( cin >> l && l > 0 ){
        cin >> n;
        edges.clear();
        edges.push_back(0);
        for( int i = 0 ; i < n ; i++ ){
            cin >> c;
            edges.push_back(c);
        }
        edges.push_back(l);

        // Cleaning mem
        for( int x = 0 ; x <= edges.size() ; x++ )
        for( int y = 0 ; y <= x ; y++ )
        {
            mem[x][y] = 0;
        }

        // Filling mem
        for( int d = 2 ; d <= edges.size()-1 ; d++ )
        for( int x = d ; x <= edges.size() ; x++ )
        {
            int y = x-d;
            int min_sum = 2000000;
            for( int i = 1 ; i < d ; i++ ){
                if( mem[x-i][y] + mem[x][y+(d-i)] < min_sum ) 
                    min_sum = mem[x-i][y] + mem[x][y+(d-i)];
            }
            mem[x][y] = edges[x]-edges[y]+min_sum;
        }

        cout << "The minimum cutting is " << mem[edges.size()-1][0] << "." << endl;

    }
}