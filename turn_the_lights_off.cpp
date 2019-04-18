/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:https://uva.onlinejudge.org/external/103/p10309.pdf

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

void clickGrid( vector<char>& grid , short position ){
    vector<short> all_possible_positions;
    
    if(position/10 > 0) all_possible_positions.push_back(position-10);
    if(position%10 > 0)all_possible_positions.push_back(position-1);
    all_possible_positions.push_back(position);
    if(position%10 < 9)all_possible_positions.push_back(position+1);
    if(position/10 < 9)all_possible_positions.push_back(position+10);
    
    for( auto p : all_possible_positions )
    if( grid[p] == 'O' ){
        grid[p] = '#';
    }
    else{
        grid[p] = 'O';
    }
}

void backtracking( const vector<char>& grid , const vector<short>& solution , vector< vector<short> >& all_solutions )
{
    if( solution.size() == 100 ){
        all_solutions.push_back( solution );
    }
    else
    {
        vector<short> new_definitives;
        short row = solution.size()/10;
        short column = solution.size()%10;
        if( row > 0 ) new_definitives.push_back( (row-1)*10 + column );
        if( row == 9 && column > 0 ) new_definitives.push_back( row*10 + (column-1) );
        if( row == 9 && column == 9 ) new_definitives.push_back( 99 );

        // No click
        auto new_solution_A = vector<short>(solution);
        auto new_grid_A = vector<char>(grid);
        new_solution_A.push_back(0);
        bool valid_solution_A = true;
        for( auto pos : new_definitives ){
            if( new_grid_A[pos] == 'O' )
            {
                valid_solution_A = false;
                break;
            }
        }

        // Clicking
        vector<short> new_solution_B = vector<short>(solution);
        vector<char> new_grid_B = vector<char>(grid);
        new_solution_B.push_back(1);
        clickGrid(new_grid_B,solution.size());
        bool valid_solution_B = true;
        for( auto pos : new_definitives ){
            if( new_grid_B[pos] == 'O' )
            {
                valid_solution_B = false;
                break;
            }
        }

        if( valid_solution_A ){
            backtracking( new_grid_A , new_solution_A , all_solutions);
        }
        if( valid_solution_B ){
            backtracking( new_grid_B , new_solution_B , all_solutions);
        }

    }
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    string case_name;
    vector<char> grid;
    vector<short> solution;
    vector< vector<short> > all_solutions;
    size_t min_presses;
    char c;
    while( cin >> case_name && case_name != "end" ){
        grid.clear();
        solution.clear();
        all_solutions.clear();
        min_presses = 999;
        for( int i = 0 ; i < 100 ; i++ ){
            cin >> c;
            grid.push_back(c);
        }
        backtracking( grid , solution , all_solutions );
        for( auto solution : all_solutions ){
            size_t amount_of_presses = 0;
            for( auto p : solution )
                amount_of_presses += (p==1);
            if( amount_of_presses < min_presses )
                min_presses = amount_of_presses;
        }
        if( min_presses > 100 )
            cout << case_name << " -1" << endl;
        else
            cout << case_name << " " << min_presses << endl; 
    }
}