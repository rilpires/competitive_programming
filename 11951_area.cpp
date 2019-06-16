/*
    Made by: Romeu I. L. Pires
    for "Special TOP_EDGEics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/119/11951.pdf
*/

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

int column_price_sum[101][101];

int calculatePriceFromEdges( short TOP_EDGE , short BOTTOM_EDGE , short LEFT_EDGE , short RIGHT_EDGE ) {
    int ret = 0;
    for( int x = LEFT_EDGE ; x < RIGHT_EDGE ; x++ ){
        ret += column_price_sum[BOTTOM_EDGE][x] - column_price_sum[TOP_EDGE][x];
    }
    return ret;
}

int main(){
    int T,N,M,K,_p;
    cin >> T;

    for( int i = 0 ; i < 101 ; i++ ){
        column_price_sum[0][i] = 0;
    }

    for( int case_number = 1 ; case_number <= T ; case_number ++ ){
        cin >> N >> M >> K ;
        
        for( int y = 1 ; y <= N ; y++ )
        for( int x = 0 ; x < M ; x++ )
        {
            cin >> _p;
            column_price_sum[y][x] = column_price_sum[y-1][x] + _p;
        }

        int best_area = 0;
        int best_price = 2000000000;

        for( int top_edge = 0 ; top_edge < N ; top_edge++ )
        for( int bottom_edge = top_edge+1 ; bottom_edge <= N ; bottom_edge++ )
        {
            // We want to find the best area within these horizontal edges
            // We start with the maximum width possible
            for( int width = M ; width >= 1 ; width-- ){
                int area = (bottom_edge - top_edge)*width;
                if( area < best_area ) break;
                
                int price = -1;
                for( int left_edge = M - width ; left_edge >= 0 ; left_edge-- )
                {
                    if( area < best_area ) continue;

                    if( price == -1 ){
                        price = calculatePriceFromEdges(top_edge,bottom_edge,left_edge,left_edge+width);
                    } 
                    // In these cases, we don't need to calculate every column price to sum
                    // Run time improved from 0.190s to 0.060s
                    else {
                        price += calculatePriceFromEdges(top_edge,bottom_edge,left_edge,left_edge+1);
                        price -= calculatePriceFromEdges(top_edge,bottom_edge,left_edge+width,left_edge+width+1);
                    }

                    if( price > K || (area == best_area && price > best_price) ) continue;
                    best_price = price;
                    best_area = area;   
                }
            }
        }

        if( best_area == 0 ){
            cout << "Case #"<< case_number <<": " << 0 << " " << 0 << endl;
        } else {
            cout << "Case #"<< case_number <<": " << best_area << " " << best_price << endl;
        }


    }
}