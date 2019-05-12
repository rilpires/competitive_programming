/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/106/10608.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

struct City{
    struct Citizen {
        int group_id = -1;
        set<Citizen*> friends;
    };

    vector<Citizen> citizens;
    size_t largest_group_size = 0;

    City( size_t number_of_citizens ){
        citizens.resize(number_of_citizens);
    };

    void form_pair( int citizen_1_id , int citizen_2_id ) {
        Citizen* citizen_1 = & (citizens[citizen_1_id-1]);
        Citizen* citizen_2 = & (citizens[citizen_2_id-1]);
        citizen_1->friends.insert( citizen_2 );
        citizen_2->friends.insert( citizen_1 );
    }

    void find_groups(){
        int open_group_id = 0;
        vector<Citizen*> left_to_check;
        for( int i = 0 ; i < citizens.size() ; i++ ){
            if( citizens[i].group_id == -1 ){
                left_to_check.clear();
                Citizen* current_citizen = &(citizens[i]);
                current_citizen->group_id = open_group_id;
                size_t group_size = 1;
                left_to_check.push_back( current_citizen );
                while( left_to_check.size() ){
                    current_citizen = left_to_check.back();
                    left_to_check.pop_back();
                    for( auto citizen : current_citizen->friends ){
                        if( citizen->group_id == -1 ){
                            group_size++;
                            citizen->group_id = open_group_id;
                            left_to_check.push_back(citizen);
                        }
                    }
                }
                if( group_size > largest_group_size ) largest_group_size = group_size;
                open_group_id++;
            }
        }
    }

};

int main(){
    int T , N , M , p1 , p2 ;
    cin >> T;
    while( T-- ){
        cin >> N >> M ;
        City city(N);
        while( M-- ){
            cin >> p1 >> p2;
            city.form_pair(p1,p2);
        }
        city.find_groups();
        cout << city.largest_group_size << endl;
    }
}