/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem URL (Google Code Jam 2019):
        https://codingcompetitions.withgoogle.com/codejam/round/0000000000051635/0000000000104e03

*/

#include <iostream>
#include <string>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;



struct Grid{
    int width;
    int height;
    int last_x;
    int last_y;
    bool first_fill;
    bool rotated = false;
    short* values;
    vector< pair<int,int> > steps;

    Grid( int w , int h ){
        first_fill = true;
        values = new short[w*h];
        width = w ; height = h;
        rotated = (width > height);
        for( int y = 0 ; y < height ; y++ )
        for( int x = 0 ; x < width ; x++ )
            values[ x + y*w ] = 0;
    }
    ~Grid(){
        delete[] values;
    }

    short read( int x , int y ){
        x = x % width; y = y % height;
        return values[ x + y*width ];
    }
    void fill( int x , int y ){
        if( rotated ){
            int temp = x;
            x = y;
            y = temp;
        }
        x = x % width; y = y % height;
        values[ x + y*width ] = 1;
        steps.push_back( pair<int,int>(x,y) );
        last_x = x; last_y = y;
        first_fill = false;
    }
    bool can_fill( int x , int y ){
        if( rotated ){
            int temp = x;
            x = y;
            y = temp;
        }
        if( read(x,y) == 1 )
            return false;
        if( last_x == x || last_y == y || x - y == last_x - last_y || x + y == last_x + last_y ){
            if( first_fill == false ){
                return false;
            }
        }
        return true;
    }
};


int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========
    int W , H , T , case_number = 1;
    cin >> T;
    while( T-- ){
        cin >> H >> W ;
        Grid grid(W,H);
        if( W > H ){
            int temp = W;
            W = H;
            H = temp;
        }
        int A = W*H , current_x = 0, current_y = 0 , safe_counter = 0;
        bool possible = true;
        while( A-- ){
            safe_counter = 0;
            while( grid.can_fill(current_x,current_y) == false ){
                current_y = (current_y+1)%H;
                safe_counter++;
                if( safe_counter == H*W ){
                    possible = false;
                    break;
                }else if ( safe_counter % H == 0 ){
                    current_x = (current_x+1) % W;
                }
            }
            if( possible ){
                grid.fill(current_x,current_y);
                current_x = (current_x+1)%W;
                current_y = (current_y+2)%H;
            }
        }
        if( possible ){
            cout << "Case #" << case_number++ << ": POSSIBLE" << endl;
            for( auto step : grid.steps ){
                cout << 1 + step.second << " " << 1 + step.first << endl;
            }
        } else{
            cout << "Case #" << case_number++ << ": IMPOSSIBLE" << endl;
        }
    }

}
