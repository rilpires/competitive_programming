/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/5/p526.pdf
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

int mem[82][82];


int min( int a , int b , int c ){
    return min( min(a,b) , c );
}

int main(){
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    
    string str1, str2;
    while( cin >> str1 >> str2 )
    {

        // Levshtein
        // Filling the memory initially
        for( int ind1 = 0 ; ind1 <= str1.size() ; ind1++ )
        mem[ind1][0] = ind1;
        for( int ind2 = 0 ; ind2 <= str2.size() ; ind2++ )
        mem[0][ind2] = ind2;

        for( int ind1 = 1 ; ind1 <=  str1.size() ; ind1++ )
        for( int ind2 = 1 ; ind2 <=  str2.size() ; ind2++ )
        {
            if( str1[ind1-1] == str2[ind2-1] ){
                mem[ind1][ind2] = mem[ind1-1][ind2-1];
            } else {
                mem[ind1][ind2] = 1 + min( mem[ind1-1][ind2-1] , mem[ind1-1][ind2] , mem[ind1][ind2-1] );
            }
        }

        int result = mem[str1.size()][str2.size()];
        cout << result << endl;

        int current_x = str1.size();
        int current_y = str2.size();
        int n = result;
        int order = 1;
        while( n > 0 ){
            int left = mem[current_x-1][current_y];
            int top_left = mem[current_x-1][current_y-1];
            int top = mem[current_x][current_y-1];
            if( left == n-1 ){
                // Erased
                current_x--;
                n--;
                cout << order++ << " Delete " << current_x+1 << endl;;
            } else if ( top_left == n-1 ){
                // Replaced
                current_x--;
                current_y--;
                n--;
                cout << order++ << " Replace " << current_x+1 << "," << str2[current_y] << endl;
            } else if ( top == n-1 ){
                // Inserted
                current_y--;
                n--;
                cout << order++ << " Insert " << current_x+1 << "," << str2[current_y] << endl;
            } else {
                if( top_left == n ){
                    current_x--;
                    current_y--;
                } else cout << "uhhh\n";
            }
        }
        cout << endl;
        
    }

}