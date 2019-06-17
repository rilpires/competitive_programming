/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/115/11566.pdf
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N,x,T,K,food_price,flavour;
    char result[64];
    while( cin >> N >> x >> T >> K ){
        if( N == 0 && x == 0 && T == 0 && K == 0 ) break;
        N += 1;

        double total_money = x*N;
        double available_money_after_charge = total_money *  0.90909090909;
        double total_money_available_for_dim = available_money_after_charge - T*N; 
        double available_money_for_dims = total_money_available_for_dim; 
        int available_dim_orders = 2*N;

        vector<int> prices(K);
        vector<int> flavours(K);
        vector< pair<int,double> > flavour_per_money(K);

        for( int food_index = 0 ; food_index < K ; food_index++ ){
            cin >> food_price;
            prices[food_index] = food_price;
            flavour_per_money[food_index] = pair<int,double>(food_index,0);
            int flavour_sum = 0;
            for( int person_index = 0 ; person_index < N ; person_index++ ){
                cin >> flavour;
                flavour_sum += flavour;
            }
            flavours[food_index] = flavour_sum;
            flavour_per_money[food_index].second = ((double)flavour_sum)/food_price ;
        }

        // Sorting the by flavour/money ratio
        sort( flavour_per_money.begin() , flavour_per_money.end() , [prices]( const pair<int,double>& p1 , const pair<int,double>& p2 ){
            if( p2.second != p1.second )
                return p2.second > p1.second;
            else
                return prices[p2.first] > prices[p1.first];
        });


        int total_flavour_sum = 0;
        for( auto it = flavour_per_money.begin() ; it != flavour_per_money.end() && available_dim_orders > 0 && available_money_for_dims > 0 ; it++ ){
            //cout << "vendo um de flavour ratio " << it->second << endl;
            for( int dim_amount = 0 ; dim_amount < 2 && available_dim_orders > 0 && available_money_for_dims > 0 ; dim_amount++ ){
                int food_index = it->first;
                if( available_money_for_dims >= prices[food_index] ){
                    available_money_for_dims -= prices[food_index];
                    available_dim_orders--;
                    total_flavour_sum += flavours[food_index];
                }
            }
        }

        sprintf( result , "%.2f" , ((double)total_flavour_sum)/N );
        cout << result << endl;

    }
}