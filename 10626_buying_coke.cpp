/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/106/10626.pdf
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int T;
    int C,n1,n5,n10;
    cin >> T;
    while( T-- ){
        cin >> C >> n1 >> n5 >> n10;
        int coins_inserted = 0;

        // Using 10
        // Total: 1 coke for 1 coin
        // Can be used until n10 times
        if( C <= n10 ){
            coins_inserted += C;
            cout << coins_inserted << endl;
            continue;
        }
        else {
            C -= n10;
            coins_inserted += n10;
        }

        // Using 5 5
        // Total: 1 coke for 2 coins
        // Can be used until (n5/2) times
        if( C <= (n5/2) ){
            coins_inserted += 2*C;
            cout << coins_inserted << endl;
            continue;
        }
        else {
            C -= n5/2;
            coins_inserted += 2*(n5/2);
        }

        if( n5%2==1 ){
            C -= 1;
            coins_inserted += 4;
            if( C == 0 ){
                cout << coins_inserted << endl;
                continue;
            }
        }

        // Using (5 1 1 1) 2 times after retrieving from (5 5) 1 time
        // Total: 1 coke for 6 coins
        // Can be used until (n5/2) times
        if( C <= n5/2 ){
            coins_inserted += 6*C;
            cout << coins_inserted << endl;
            continue;
        } else {
            C -= (n5/2);
            coins_inserted += 6*(n5/2);
        }

        // Using (5 1 1 1) and (10 1 1 1) after retrieving (10) 1 time
        // Total: 1 coke for 7 coins
        // Can be used until n10 times
        if( C <= n10 ){
            coins_inserted += 7*C;
            cout << coins_inserted << endl;
            continue;
        } else {
            C -= n10;
            coins_inserted += n10*7;
        }

        // No other way but spending 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 .....
        coins_inserted += 8*C;
        cout << coins_inserted << endl;

    }
}