/*
    Made by: Romeu I. L. Pires
    for "Special bottomics in programming" course
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

#define MAX_LEN 82

int mem[MAX_LEN][MAX_LEN];
char path[MAX_LEN][MAX_LEN];

int min( int a , int b , int c ){
    return min( min(a,b) , c );
}

int main(){
    string str1, str2;
    bool first = true;
    while( getline(cin,str1) && getline(cin,str2) )
    {
        
        if( !first ) cout << endl;
        first = false;

        while( str1.front() == ' ' ) str1 = str1.substr(1,str1.size());
        while( str2.front() == ' ' ) str2 = str2.substr(1,str2.size());
        while( str1.back() == ' ' ) str1.pop_back();
        while( str2.back() == ' ' ) str2.pop_back();

        // Levshtein
        // Filling the memory initially
        for( int ind1 = 0 ; ind1 <= (int)str1.size() ; ind1++ ){
            mem[ind1][0] = ind1;
            path[ind1][0] = 'L';
        }
        for( int ind2 = 0 ; ind2 <= (int)str2.size() ; ind2++ ){
            mem[0][ind2] = ind2;
            path[0][ind2] = 'T';
        }
        vector<string> operations;

        // Filling mem
        for( int ind1 = 1 ; ind1 <=  (int)str1.size() ; ind1++ )
        for( int ind2 = 1 ; ind2 <=  (int)str2.size() ; ind2++ )
        {
            if( str1[ind1-1] == str2[ind2-1] ){
                mem[ind1][ind2] = mem[ind1-1][ind2-1];
                path[ind1][ind2] = 'D'; // Came from diag
            } else {
                mem[ind1][ind2] = 1 + min( mem[ind1-1][ind2-1] , mem[ind1-1][ind2] , mem[ind1][ind2-1] );
                if( mem[ind1][ind2] - 1 == mem[ind1-1][ind2-1] ){
                    path[ind1][ind2] = 'D'; // Came from diag
                } else if ( mem[ind1][ind2] - 1 == mem[ind1-1][ind2] ){
                    path[ind1][ind2] = 'L'; // Came from left
                } else if ( mem[ind1][ind2] - 1 == mem[ind1][ind2-1] ){
                    path[ind1][ind2] = 'T'; // Came from top
                } 
            }
        }

        int result = mem[str1.size()][str2.size()];
        cout << result <<  endl;

        vector< pair<int,int> > reversed_path;
        // Finding reverse path
        int current_x = str1.size();
        int current_y = str2.size();
        while( mem[current_x][current_y] != 0 ){
            reversed_path.push_back( pair<int,int>(current_x,current_y) );
            switch( path[current_x][current_y] ){
                case 'D':
                    current_x--;
                    current_y--;
                    break;
                case 'L':
                    current_x--;
                    break;
                case 'T':
                    current_y--;
                    break;
            }

        }

        // Printing path
        int n = 0;
        int order = 1;
        int delta_pos = 0;
        for( auto it = reversed_path.rbegin() ; it != reversed_path.rend() ; it++ ){
            int x = it->first;
            int y = it->second;
            if( mem[x][y] == n+1 ){
                n++;
                if(path[x][y] == 'D'){
                    cout << order++ << " Replace " << x + delta_pos << "," << str2[y-1] << endl;
                }else if(path[x][y] == 'L'){
                    cout << order++ << " Delete " << x + delta_pos << endl;
                    delta_pos--;
                }else if(path[x][y] == 'T'){
                    cout << order++ << " Insert " << x+1 + delta_pos << "," << str2[y-1] << endl;
                    delta_pos++;
                }
            }
        }
        
    }

}