/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/116/11655.pdf
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define MAX_L 5001

set< pair<int,int> > adj;

int last_deep[MAX_L][MAX_L];
int aux[MAX_L][MAX_L];

int main(){
    int N;
    cin >> N;
    for( int case_number = 1 ; case_number <= N ; case_number++ ){
        int L,T,ind1,ind2;
        cin >> L >> T;

        // Reading adjs
        adj.clear();
        for( int i = 0 ; i < T ; i ++ ){
            cin >> ind1 >> ind2;
            adj.insert( pair<int,int>(ind1,ind2) );
            last_deep[ind1][ind2] = 1;
        }

        int routes_found = ( adj.find(pair<int,int>(1,L)) != adj.end() );
        int teams_sent = routes_found;

        //
        for( int distance = 2 ; distance < L ; distance++ ){
            // copying last_deep to aux
            for( int x = 1 ; x <= L ; x++ )
            for( int y = 1 ; y <= L ; y++ )
            aux[x][y] = 0;
            
            for( int y = 1 ; y <= L ; y++ )
            for( auto edge : adj ){
                aux[edge.first][y] += last_deep[edge.second][y] % 100000;
            }
            

            for( int x = 1 ; x <= L ; x++ )
            for( int y = 1 ; y <= L ; y++ )
            last_deep[x][y] = aux[x][y] % 100000;

            for( int x = 1 ; x <= L ; x++ )
            last_deep[x][x] = 0;

            routes_found += last_deep[1][L] % 100000;
            teams_sent += (last_deep[1][L] * distance) % 100000;

            routes_found = routes_found % 100000;
            teams_sent = teams_sent % 100000; 
        }

        cout << "Case " << case_number << ": " << teams_sent << " " << routes_found << endl;

    }

}

