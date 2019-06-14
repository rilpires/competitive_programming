/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/100/10051.pdf
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>

#define COLOR short
#define SIDE short
#define CUBE_ID short
#define MAX_CUBE_ID 500
#define MAX_COLOR_ID 100

using namespace std;




enum SIDES {
    FRONT ,
    BACK ,
    LEFT ,
    RIGHT ,
    TOP ,
    BOTTOM
};
const string SIDE_NAMES[6] = {
    "front",
    "back",
    "left",
    "right",
    "top",
    "bottom"
};
SIDE getOppositeSide( SIDE s ){
    switch ( s )
    {
        case FRONT:
            return BACK;
            break;
        case BACK:
            return FRONT;
            break;
        case TOP:
            return BOTTOM;
            break;
        case BOTTOM:
            return TOP;
            break;
        case LEFT:
            return RIGHT;
            break;
        case RIGHT:
            return LEFT;
            break;
        default:
            break;
    }
    return 0;
}

struct Cube {
    private : 
    SIDE   floor_side = 0;
    
    public :
    COLOR       colors[6];


    COLOR           getFloorColor() const { 
        return colors[floor_side]; 
    }
    COLOR           getTopColor() const { 
        return colors[ getOppositeSide(floor_side) ];
    }
    void            setFloorSide( SIDE WHICH_SIDE ) {
        floor_side = WHICH_SIDE;
    }
};
struct Node {
    short       tallest_size = 0;
    CUBE_ID     cube_id = -1;
    SIDE        bottom_side = -1;            
};

int main(){
    int N , case_number = 1;

    Node matrix[MAX_CUBE_ID][MAX_COLOR_ID];
    while( cin >> N && N != 0 ){
        vector<Cube*> cubes;
        cubes.resize(N);
        COLOR largest_color_id_recognized = -1;
        for( int i = 0 ; i < N ; i++ )
        {
            Cube* cube = new Cube();
            cubes[i] = cube;
            cin >> cube->colors[FRONT] >> cube->colors[BACK] ;
            cin >> cube->colors[LEFT] >> cube->colors[RIGHT] ;
            cin >> cube->colors[TOP] >> cube->colors[BOTTOM] ;
            for( COLOR c : cube->colors )
                if( c > largest_color_id_recognized ) 
                    largest_color_id_recognized = c;
        }


        // Cleaning matrix
        for( CUBE_ID cube_id = 1 ; cube_id <= N ; cube_id ++ )
        for( COLOR color_id = 1 ; color_id <= largest_color_id_recognized ; color_id++ )
        {
            Node& n = matrix[cube_id-1][color_id-1];
            n.tallest_size = 0;
        }

        // Filling the first column
        for( SIDE side = 0 ; side < 6 ; side++ ){
            Cube* cube = cubes[0];
            cube->setFloorSide(side);
            COLOR color = cube->getFloorColor();
            Node& n = matrix[0][color-1];
            n.tallest_size = 1;
            n.cube_id = 1;
            n.bottom_side = side;
        }

        // Filling the matrix
        for( int current_cube_id = 2 ; current_cube_id <= N ; current_cube_id ++ ){
            Cube* cube = cubes[current_cube_id-1];

            // Repeating columns 
            for( COLOR color_id = 1 ; color_id <= largest_color_id_recognized ; color_id++ )
            {
                Node& old_node = matrix[current_cube_id-2][color_id-1];
                Node& new_node = matrix[current_cube_id-1][color_id-1];
                new_node.cube_id = old_node.cube_id;
                new_node.tallest_size = old_node.tallest_size;
                new_node.bottom_side = old_node.bottom_side;
            }

            // Updating current column
            for( SIDE s = 0 ; s < 6 ; s++ ){
                cube->setFloorSide(s);
                COLOR top_color = cube->getTopColor();
                int previous_tallest_size = matrix[current_cube_id-2][top_color-1].tallest_size;
                Node& possibly_updated_node = matrix[current_cube_id-1][cube->getFloorColor()-1];
                if( previous_tallest_size + 1 > possibly_updated_node.tallest_size){
                    possibly_updated_node.tallest_size = previous_tallest_size + 1;
                    possibly_updated_node.bottom_side = s;
                    possibly_updated_node.cube_id = current_cube_id;
                }
            }
        }

        // Finding the largest height node in the last column
        Node* max_height_node = NULL;
        for( COLOR color_id = 1 ; color_id <= largest_color_id_recognized ; color_id++  ){
            Node& n = matrix[N-1][color_id-1];
            if( max_height_node == NULL || max_height_node->tallest_size <= n.tallest_size ){
                max_height_node = &n;
            }
        }



        // Finding the path from bottom to top
        vector<Node*> path;
        Node* next_node = max_height_node;
        while( true ){
            path.push_back(next_node);
            if( next_node->tallest_size == 1 ) break;
            
            Cube* cube = cubes[next_node->cube_id-1];
            cube->setFloorSide( next_node->bottom_side );
            COLOR next_top_color = cube->getTopColor();

            bool found = false;
            for( CUBE_ID possible_next_cube_id = next_node->cube_id-1 ; possible_next_cube_id >= 1 ; possible_next_cube_id-- ){
                Node* possible_next_node = & (matrix[possible_next_cube_id-1][ next_top_color - 1 ]);
                if( possible_next_node->tallest_size == next_node->tallest_size-1 ){
                    next_node = possible_next_node;
                    found = true;
                    break;
                }
            }
            if( !found ){
                cout << "There is something very wrong" << endl;
                break;
            }
        }

        vector<Node*> reverted_path = vector<Node*>(path.rbegin() , path.rend() );
        cout << "Case #" << case_number++ << endl;
        cout << reverted_path.size() << endl;
        for( auto n : reverted_path ){
            cout << n->cube_id << " " << SIDE_NAMES[ getOppositeSide(n->bottom_side) ] << endl;
        }
        cout << endl;

        for( auto cube : cubes ) delete cube;
    }

}