/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/109/10957.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

enum {
    INCORRECT ,
    CORRECT_INCOMPLETE ,
    CORRECT_COMPLETE ,
};

short checkRow( int row , const vector<short>& grid ){
    short ret = CORRECT_COMPLETE;
    set<short> passed;
    short n;
    for( size_t i = row*9 ; i < row*9 + 9 ; i += 1 ){
        n = grid[i];
        if( n == 0 ){
            ret = CORRECT_INCOMPLETE;
        }else{
            if( passed.find(n) == passed.end() ){
                passed.insert(n);
            } else {
                return INCORRECT;
            }
        }
    }
    return ret;
}
short checkColumn( int column , const vector<short>& grid ){
    short ret = CORRECT_COMPLETE;
    set<short> passed;
    short n;
    for( size_t i = column ; i < 81 ; i += 9 ){
        n = grid[i];
        if( n == 0 ){
            ret = CORRECT_INCOMPLETE;
        }else{
            if( passed.find(n) == passed.end() ){
                passed.insert(n);
            } else {
                return INCORRECT;
            }
        }
    }
    return ret;
}
short checkCell( int cell_x , int cell_y , const vector<short>& grid ){
    short ret = CORRECT_COMPLETE;
    set<short> passed;
    short n;
    for( size_t x = cell_x*3 ; x < cell_x*3 + 3 ; x ++ )
    for( size_t y = cell_y*3 ; y < cell_y*3 + 3 ; y ++ )
    {
        n = grid[ 9*y + x ];
        if( n == 0 ){
            ret = CORRECT_INCOMPLETE;
        }else{
            if( passed.find(n) == passed.end() ){
                passed.insert(n);
            } else {
                return INCORRECT;
            }
        }
    }
    return ret;
}
set<short> possibleValues( short row , short column , vector<short>& grid ){
    set<short> ret , has;
    for( size_t x = 0 ; x < 9 ; x++ )
        has.insert( grid[ row*9 + x ] );
    for( size_t y = 0 ; y < 9 ; y++ )
        has.insert( grid[ y*9 + column ] );
    for( size_t x = (column/3)*3 ; x < 3 + (column/3)*3 ; x++ )
    for( size_t y = (row/3)*3 ; y < 3 + (row/3)*3 ; y++ )
        has.insert( grid[ y*9 + x ] );
    auto end = has.end();
    for( short i = 1 ; i <= 9 ; i++ )
        if( has.find(i) == end )
            ret.insert(i);
    return ret;
}
bool validSudoku( vector<short>& grid ){
    for( size_t x = 0 ; x < 9 ; x++ )
        if( checkColumn(x,grid) == INCORRECT )
            return false;
    for( size_t y = 0 ; y < 9 ; y++ )
        if( checkRow(y,grid) == INCORRECT )
            return false;
    for( size_t x = 0 ; x < 3 ; x++ )
    for( size_t y = 0 ; y < 3 ; y++ )
        if( checkCell( x , y , grid ) == INCORRECT )
            return false;
    return true;
}
void backtracking( vector<short>& grid , vector< vector<short> >& solutions ){
    if( solutions.size() > 1 ) return;
    short next_pos = -1;
    for( short i = 0 ; i < 81 ; i++ ){
        if(grid[i]==0){
            next_pos = i ;
            break ;
        }
    }
    if( next_pos == -1 ){
        // check if ok?
        solutions.push_back(grid);
    }else{
        set<short> available_numbers = possibleValues(next_pos/9,next_pos%9,grid);
        for( auto n : available_numbers ){
            vector<short> new_grid = vector<short>(grid);
            new_grid[next_pos] = n;
            backtracking( new_grid , solutions );
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    int N , case_number = 1;
    vector<short> grid;
    while( cin >> N ){
        grid.clear();
        grid.push_back(N);
        for( int i = 0 ; i < 80 ; i++ ){
            cin >> N;
            grid.push_back(N);
        }
        vector< vector<short> > solutions;
        if( !validSudoku(grid) ){
            cout << "Case " << case_number++ << ": Illegal." << endl;
        }else{
            backtracking( grid , solutions );
            switch( solutions.size() ){
                case 0 :
                    cout << "Case " << case_number++ << ": Impossible." << endl;
                    break;
                case 1:
                    cout << "Case " << case_number++ << ": Unique." << endl;
                    break;
                default:
                    cout << "Case " << case_number++ << ": Ambiguous." << endl;
                    break;
            }
        }
    }
}