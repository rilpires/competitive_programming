/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#define INFINITE 2147483647
using namespace std;

struct Node{
    int busyness;
};
struct Matrix{
    size_t width , height;
    vector<int> v;
    Matrix( size_t w , size_t h ){
        width = w ; height = h;
        v.resize(w*h);
    };
    int     get( size_t row , size_t column ){
        return v[ column + row*width ];
    }
    void    set( size_t row , size_t column , int new_value ){
        v[ column + row*width ] = new_value;
    }
};


int main(){
    int number_of_junctions , number_of_roads , j1 , j2 ,case_number = 1;
    int number_of_queries, D , d1 , d2;
    while( cin >> number_of_junctions ){
        
        vector<Node> junctions(number_of_junctions);
        for( int i = 0 ; i < number_of_junctions ; i++ )
            cin >> junctions[i].busyness;      
        
        
        // Floyd-Warshall matrix
        Matrix M(number_of_junctions,number_of_junctions);
        for( int i = 0 ; i < number_of_junctions ; i ++ )
        for( int j = 0 ; j < number_of_junctions ; j ++ ){
            if(i==j)    M.set(i,j,0);
            else        M.set(i,j,INFINITE);
        }


        cin >> number_of_roads;
        for( int i = 0 ; i < number_of_roads ; i++ ){
            cin >> j1 >> j2;
            Node& source_junction   = junctions[j1-1];
            Node& destiny_junction  = junctions[j2-1];
            int power = pow(destiny_junction.busyness - source_junction.busyness , 3);
            M.set( j1-1 , j2-1 , power );
        }

        // Building up the matrix
        for( int h = 0 ; h < 2 ; h++ )
        for( int i = 0 ; i < number_of_junctions ; i++ )
        for( int j = 0 ; j < number_of_junctions ; j++ )
        for( int k = 0 ; k < number_of_junctions ; k++ ){
            D = M.get(i,j);
            d1 = M.get(i,k);
            d2 = M.get(k,j);
            if( d1 < INFINITE && d2 < INFINITE && D > -INFINITE ){
                
                if( d1 == -INFINITE || d2 == -INFINITE ){
                    M.set(i,j,-INFINITE);
                }
                else if( D > d1 + d2  ){
                    //cout << "Setando " << i << " para " << j << " em " << d1 <<" + "<< d2 <<  endl;
                    if( i == j && d1+d2 < 0 ){
                        M.set(i,j,-INFINITE);
                    } else{
                        M.set(i,j, d1 + d2 );
                    }
                }
            }
        }

        cout << "Set #" << case_number++ << endl;
        cin >> number_of_queries;
        while( number_of_queries-- ){
            cin >> j1;
            j2 = M.get(0,j1-1);
            if( j2 < 3 )
                cout << '?' << endl;
            else
                cout << j2 << endl;
        }

    }
}