/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define MAX_X 301
#define MAX_Y 301
#define MAX_ID 41
#define INFINITE 2000000000

int mem[MAX_ID][MAX_X][MAX_Y];

int main(){
    int n,m,S,_x,_y;
    vector< pair<int,int> > coins;
    cin >> n;
    while(n--){
        cin >> m >> S ;
        coins.resize(m);
        for( int i = 0 ; i < m ; i++ ){
            cin >> _x >> _y;
            coins[i].first = _x;
            coins[i].second = _y;
        }

        for( int id = 0 ; id < m ; id++ )
        for( int x = 0 ; x <= S ; x++ )
        for( int y = 0 ; y <= S ; y++ )
        {
            mem[id][x][y] = INFINITE;
        }

        set< pair<int,int> > visited_points;

        // Filling with the first coin
        for( int amount = 0 , x = 0 , y = 0 ; 
        x <= S && y <= S ; 
        amount ++ , x += coins[0].first , y += coins[0].second )
        {
            for( int id = 0 ; id < m ; id++)
                mem[id][x][y] = amount;
            visited_points.insert( pair<int,int>(x,y) );
        }

        // Filling the rest
        for( int id = 1 ; id < m ; id++ )
        {
            int coin_x = coins[id].first;
            int coin_y = coins[id].second;
            for( auto point : visited_points )
            {
                int amount = 1;
                while( point.first + amount*coin_x <= S 
                && point.second + amount*coin_y <= S 
                && mem[id-1][point.first][point.second] + amount < mem[id][point.first+amount*coin_x][point.second+amount*coin_y] )
                {
                    visited_points.insert( pair<int,int>(point.first + amount*coin_x,point.second + amount*coin_y) );
                    for( int _id = id ; _id < m ; _id++){
                        mem[_id][point.first+amount*coin_x][point.second+amount*coin_y] = mem[id-1][point.first][point.second] + amount;
                    }
                    amount ++;
                }
            }
        }

        int result = INFINITE;
        for( int x = 0 ; x <= S ; x++ )
        for( int y = 0 ; y <= S ; y++ )
        if( x*x + y*y == S*S )
        {
            if( mem[m-1][x][y] < result ) result = mem[m-1][x][y];
            continue;
        }

        if( result != INFINITE )
        cout << result << endl;
        else
        cout << "not possible" << endl;

    }
}