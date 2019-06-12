/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/103/p10363.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
using namespace std;

struct TicTacToe{
    vector<char> grid;
    size_t nX , nO , n_empty;
    size_t current_pos = 0;
    
    void reset(){
        current_pos = 0;
        nX = 0 ; nO = 0 , n_empty = 0;
        grid.resize(9);
    };
    void insert(char c){
        grid[current_pos++] = c;
        nX += 1 * ( c == 'X' );
        nO += 1 * ( c == 'O' );
        n_empty += 1 * ( c == '.' );
    }
    bool isValid(){
        if( nX < nO || nX - nO > 1 ) return false;
        
        int total_X_wins = 0 , total_O_wins = 0;
        int X_wins, O_wins;
        
        // Horizontal
        X_wins = 0 , O_wins = 0;
        for( int y = 0 ; y <= 6 ; y+=3 ){
            if( grid[y] == grid[y+1] && grid[y+1] == grid[y+2] ){
                X_wins += (grid[y]=='X');
                O_wins += (grid[y]=='O');
            }
            if( X_wins > 1 || O_wins > 1 ) return false;
            total_X_wins += X_wins;
            total_O_wins += O_wins;
        }

        // Vertical
        X_wins = 0 , O_wins = 0;
        for( int x = 0 ; x < 3 ; x++ ){
            if( grid[x] == grid[x+3] && grid[x+3] == grid[x+6] ){
                X_wins += (grid[x]=='X');
                O_wins += (grid[x]=='O');
            }
            if( X_wins > 1 || O_wins > 1 ) return false;
            total_X_wins += X_wins;
            total_O_wins += O_wins;
        }

        //Diagonal
        if( (grid[0] == grid[4] && grid[4] == grid[8]) ||
        (grid[2] == grid[4] && grid[4] == grid[6])  ){
            total_X_wins += (grid[4]=='X');
            total_O_wins += (grid[4]=='O');
        }
        if( total_X_wins * total_O_wins > 0 ) return false;
        if( total_O_wins > 0 && total_X_wins == 0 && nO != nX ) return false;
        if( total_X_wins > 0 && total_O_wins == 0 && nX != nO + 1 ) return false;

        return true;
    }
};

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    int N;
    char c;
    TicTacToe tic_tac_toe;
    string line;
    stringstream line_stream;

    cin >> N;
    getline(cin,line);
    for( int n = 0 ; n < N ; n++ ){
        tic_tac_toe.reset();
        for( int l = 0 ; l < 3 ; l++ ){
            getline(cin,line);
            line_stream = stringstream(line);
            while( line_stream >> c && (c == '.' || c == 'X' || c == 'O') )
                tic_tac_toe.insert(c); 
        }
        getline(cin,line);
        cout << ( tic_tac_toe.isValid() ? "yes" : "no" ) << endl;
    }
}