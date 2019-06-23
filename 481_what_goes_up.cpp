/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/4/481.pdf
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    vector<vector<int> > active_sequences(2);
    vector<int>          sequence_ends(20000);
    int largest_ever = -2000000000;
    int smallest_ever = 2000000000;
    int i;
    while( cin >> i ){
        
        // Create a new best sequence with size 1
        if( i < smallest_ever )
        {
            smallest_ever = i;
            vector<int>& v = active_sequences[1];
            v.clear();
            v.push_back(i);
            sequence_ends[1] = i;
        }

        // Clone+extends the largest sequence
        else if( i > largest_ever )
        {
            largest_ever = i ;
            vector<int> clone = active_sequences.back();
            clone.push_back(i);
            active_sequences.push_back(clone);
            sequence_ends[clone.size()] = i;
        }
        
        // Looks for the tallest sequence's end smaller than i, clone+extend it
        else 
        {
            // At first I thought it wasn't a big deal because normally we don't have THAT much
            // active sequences to look for it. Apparently I was understimating worst case scenario
            // Without C++'s algorithm lib it was receiving TLE
            // Looks like lower_bound uses binary search (O(logN)) to find it
            auto upper_bound = lower_bound( sequence_ends.begin()+1 , sequence_ends.begin()+active_sequences.size() , i )-1;
            int index_we_want =  ( upper_bound - sequence_ends.begin() );
            
            //Cloning + extending it
            vector<int> clone = active_sequences[index_we_want];
            clone.push_back(i);
            active_sequences[ clone.size() ] = clone;
            sequence_ends[clone.size()] = i;
            
            // Maybe we changed the largest_ever
            if( clone.size() == active_sequences.size() - 1 ){
                largest_ever = clone.back();
            }

        }

        // Nice way to view progress
        /**
        cout << " ==" << endl;
        for( auto s : active_sequences ){
            for( auto n : s ) cout << n << " ";
            cout << endl;
        }
        **/
        
    }


    // Printing result
    vector<int>&    largest_sequence = active_sequences.back();

    cout << largest_sequence.size() << endl << "-" << endl;
    for( auto n : largest_sequence ){
        cout << n << endl;
    }

}