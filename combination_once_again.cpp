/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF: 
        https://uva.onlinejudge.org/external/105/p10532.pdf
        
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;


void printMatrix( const vector<int>& a , const uint64_t matrix[50][50] ){
    for( auto x = 0 ; x < 10 ; x++ )
        cout << a[x] << "\t" ;
    cout << endl << endl;
    for( auto y = 0 ; y < 10 ; y++ ){
        for( auto x = 0 ; x < 10 ; x++ )
            cout << matrix[x][y] << "\t";
        cout << endl;
    }
    cout << "-----------------\n";
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    string line;
    stringstream line_stream;
    vector<int> a;
    uint64_t matrix[50][50];
    for( int case_number = 1 ; case_number <= 100 ; case_number++ ){
        int N,M;
        if( !(cin >> N >> M ) || N == 0 ) break;
        cout << "Case " << case_number << ":" << endl;
        a.clear();
        a.resize(0);
        map<int,int> entries;
        for( int n = 0 ; n < N ; n++ ){
            int next_int;
            cin >> next_int;
            if( next_int > 0 ){
                if( entries.find(next_int) == entries.end() ) entries[next_int] = 0;
                entries[next_int]++;
            }
        }
        a.resize( entries.size() );
        int open_slot = 0;
        for( auto entry = entries.begin() ; entry != entries.end() ; entry ++ ){
            a[open_slot++] = entry->second;
        }
        sort(a.rbegin() , a.rend());

        // Clearing matrix
        for( auto x = 0 ; x < 50 ; x++ ){
            for( auto y = 0 ; y < 50 ; y++ ){
                matrix[x][y]=0;
            }
        }
        int how_many_groups = a.size();
        //Setting first line && last columns
        for( int i = 0 ; i < how_many_groups ; i++ )
            matrix[i][0] = how_many_groups-i;
        for( int j = 0 ; j < a[how_many_groups-1] ; j++ )
            matrix[how_many_groups-1][j] = 1;
        
        //Reccurring
        int cumulative_k = a[how_many_groups-1];
        for( int i = how_many_groups-2 ; i >= 0 ; i-- ){
            int current_k = a[i];
            cumulative_k += current_k;
            for( int j = 1 ; j < current_k ; j++ ){
                matrix[i][j] = matrix[i+1][j] + matrix[i][j-1];
            }
            for( int j = current_k ; j < cumulative_k ; j++ ){
                matrix[i][j] = matrix[i+1][j];
                for( int n = 0 ; n < current_k ; n++ ){
                    matrix[i][j] += matrix[i+1][j-n-1];
                }
            }
        }

        //printMatrix( a , matrix );

        for( int m = 0 ; m < M ; m++ ){
            int next_int;
            cin >> next_int;
            if( next_int == 0 )
                cout << 1 << endl;
            else
                cout << matrix[0][next_int-1] << endl;
        }
    }
    return 0;
}
