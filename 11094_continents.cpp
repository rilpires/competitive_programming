/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/110/11094.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <map>
using namespace std;

int dx[] = {1,-1,0,0};
int dy[] = {0,0,-1,1};
void search( int x , int y , int W , int H , vector<int>& ids , vector<char>& world , int& count ){
    int my_id = ids[ x + y*W ];
    char land_letter = world[x + y*W];
    for( int d = 0 ; d < 4 ; d++ ){
        int other_x = (x + dx[d] + W)%W;
        int other_y = y + dy[d];
        if( 0 <= other_x && other_x < W && 0 <= other_y && other_y < H ){
            if( world[other_x + other_y*W] == land_letter && ids[other_x + other_y*W] == -1 ){
                ids[other_x + other_y*W] = my_id;
                count ++;
                search(other_x , other_y , W , H , ids , world , count );
            }
        }
    }
}

int main(){
    int H , W , pos , king_x , king_y ;
    char c;
    while( cin >> H >> W ){
        vector<char> world;
        vector<int> ids;
        map<int,int> id_size;
        int open_id = 0;
        int king_id;
        for( int y = 0 ; y < H ; y ++ )
        for( int x = 0 ; x < W ; x ++ ){
            cin >> c;
            world.push_back( c );
            ids.push_back( -1 );
        }
        cin >> king_y >> king_x;
        char land_letter = world[ king_x + king_y*W ];

        for( int y = 0 ; y < H ; y ++ )
        for( int x = 0 ; x < W ; x ++ ){
            pos = x+y*W;
            if( world[pos] == land_letter && ids[pos] == -1 ){
                int size = 1;
                ids[pos] = open_id;
                search( x , y , W , H , ids , world , size );
                id_size[open_id++] = size;
            }
        }
        
        king_id = ids[king_x+king_y*W];
        int largest_land_size = 0;
        for( auto it : id_size ){
            if( it.second > largest_land_size && it.first != king_id )
                largest_land_size = it.second;
        }

        cout << largest_land_size << endl;

    }
}