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
#include <iomanip>
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

void printa_matriz( Matrix& M ){
    cout  << endl;
    for( int y = 0 ; y < M.height ; y++ ){
        for( int x = 0 ; x < M.width ; x++ ){
            int val = M.get(y,x);
            if( val > -INFINITE && val < INFINITE ){
                cout << setw(7) << val ;
            } else if (val == -INFINITE){
                cout << setw(7) << "-I" ;
            } else {
                cout << setw(7) << "+I" ;
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    int number_of_junctions , number_of_roads , j1 , j2 ,case_number = 1;
    int number_of_queries, D , d1 , d2;
    while( cin >> number_of_junctions ){
        
        vector<Node> junctions(number_of_junctions);
        for( int i = 0 ; i < number_of_junctions ; i++ )
            cin >> junctions[i].busyness;      
        
        
        // Floyd-Warshall matrix
        Matrix M(number_of_junctions,number_of_junctions);
        
        // Setting the zeroes
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
        for( int k = 0 ; k < number_of_junctions ; k++ )
        for( int i = 0 ; i < number_of_junctions ; i++ )
        for( int j = 0 ; j < number_of_junctions ; j++ ){
            D = M.get(i,j);
            d1 = M.get(i,k);
            d2 = M.get(k,j);
            if( d1 < INFINITE && d2 < INFINITE && D > -INFINITE ){
                if( D > d1 + d2  ){
                    M.set(i,j, d1 + d2 );
                }
            }
        }

        // -infinite on i==j index
        for( int i = 0 ; i < number_of_junctions ; i++ )
        for( int j = 0 ; j < number_of_junctions ; j++ )
        if( i == j ){
            D = M.get(i,j);
            if( D < 0 ){
                for( int k = 0 ; k < number_of_junctions ; k++ ){
                    if( M.get(i,k) < INFINITE ){
                        M.set(i,k,-INFINITE);
                    }
                }
            }
        }

        // Build one more time
        for( int k = 0 ; k < number_of_junctions ; k++ )
        for( int i = 0 ; i < number_of_junctions ; i++ )
        for( int j = 0 ; j < number_of_junctions ; j++ ){
            d1 = M.get(i,k);
            d2 = M.get(k,j);
            if( d1 < INFINITE && d2 < INFINITE && D > -INFINITE ){
                if( d1 == -INFINITE || d2 == -INFINITE ){
                    M.set(i,j,-INFINITE);
                }
            }
        }

        cout << "Set #" << case_number++ << endl;
        cin >> number_of_queries;
        while( number_of_queries-- ){
            cin >> j1;
            j2 = M.get(0,j1-1);
            if( j2 < 3 || j2 == INFINITE )
                cout << '?' << endl;
            else
                cout << j2 << endl;
        }

    }
}