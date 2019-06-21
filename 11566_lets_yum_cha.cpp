/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/115/11566.pdf
*/

#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_ID_FOOD 103
#define MAX_ORDERS 23
#define MAX_MONEY_SPENT 1005

int mem[MAX_ID_FOOD][MAX_ORDERS][MAX_MONEY_SPENT];


int main(){
    int N,x,T,K,food_price,flavour;
    char result[64];
    vector<int> food_prices , flavours;
    
    while( cin >> N >> x >> T >> K ){
        if( N == 0 && x == 0 && T == 0 && K == 0 ) break;
        N += 1;
        
        int available_money_for_food = floor(double(x*N) / 1.1L /** THIS motherfucker rIGHT HERE THIS 'L' IS THE DIFFERENCE BETWEEN 'WRONG ANSWER' AND 'ACCEPTED' im so angry **/ ) - T*N;
        if( available_money_for_food < 0 ) available_money_for_food = 0;
        int available_dim_orders = 2*N;

        food_prices.resize(K);
        flavours.resize(K);
        for( int food_index = 0 ; food_index < K ; food_index++ ){
            cin >> food_price;
            food_prices[food_index] = food_price;
            int flavour_sum = 0;
            for( int person_index = 0 ; person_index < N ; person_index++ ){
                cin >> flavour;
                flavour_sum += flavour;
            }
            flavours[food_index] = flavour_sum;
        }

        for( int x = 0 ; x <= K ; x++ )
        for( int y = 0 ; y <= available_dim_orders ; y++ )
        for( int z = 0 ; z <= available_money_for_food ; z++ )
        {
            mem[x][y][z] = 0;
        }

        
        for( int order = 1 ; order <= available_dim_orders ; order++ )
        for( int spent = food_prices[0] ; spent <= available_money_for_food ; spent++ )
        mem[0][order][spent] = flavours[0];
        
        for( int order = 2 ; order <= available_dim_orders ; order++ )
        for( int spent = 2*food_prices[0] ; spent <= available_money_for_food ; spent++ )
        mem[0][order][spent] = 2*flavours[0];

        for( int food_index = 1 ; food_index <= K-1 ; food_index++ )
        {
            int price = food_prices[food_index];
            int flavour = flavours[food_index];
            for( int spent = 0 ; spent <= available_money_for_food ; spent++ )
            for( int orders = 0 ; orders <=available_dim_orders ; orders++ ){

                int new_value;
                new_value = mem[food_index-1][orders][spent];

                if( spent >= price && orders >= 1 && mem[food_index-1][orders-1][spent-price] + flavour > new_value  ){
                    new_value = mem[food_index-1][orders-1][spent-price] + flavour;
                }
                if( spent >= 2*price && orders >= 2 && mem[food_index-1][orders-2][spent-2*price] + 2*flavour > new_value  ){
                    new_value = mem[food_index-1][orders-2][spent-2*price] + 2*flavour;
                }
                
                mem[food_index][orders][spent] = new_value;

            }

        }
        sprintf( result , "%.2lf" , ((double)mem[K-1][available_dim_orders][available_money_for_food])/((double)N) );
        cout << result << endl;

    }
}