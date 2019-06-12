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

void backtracking( vector<char>& grid , vector<short>& solution , vector< vector<short> >& all_solutions )
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

        bool valid_solution;
        // No click
        solution.push_back(0);
        valid_solution = true;
        for( auto pos : new_definitives ){
            if( grid[pos] == 'O' ){
                valid_solution = false;
                break;
            }
        }
        if( valid_solution )
            backtracking( grid , solution , all_solutions);
        solution.pop_back();

        // Clicking
        clickGrid(grid,solution.size());
        solution.push_back(1);
        valid_solution = true;
        for( auto pos : new_definitives ){
            if( grid[pos] == 'O' ){
                valid_solution = false;
                break;
            }
        }
        if( valid_solution )
            backtracking( grid , solution , all_solutions);

        solution.pop_back();
        clickGrid(grid,solution.size());

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