/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/103/10377.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Maze {
    vector<char> tiles;
    int W,H;
    Maze( int w , int h ):W(w),H(h){
        tiles.resize( w * h);
        for( int i = 0 ; i < w*h ; i++ ){
            tiles[i] = ' ';
        }
    }
};
struct Robot {
    int facing_angle; // Degrees
    int x , y;
    Robot(){
        facing_angle = 90;
    }
    void rotate( int delta_angle ){
        facing_angle = (facing_angle + 360 + delta_angle )%360;
    }
    void move_forward(){
        switch(facing_angle){
            case 0:
                x++;
                break;
            case 90:
                y--;
                break;
            case 180:
                x--;
                break;
            case 270:
                y++;
                break;
        }
    }
    char get_facing_angle_char(){
        switch(facing_angle){
            case 0:
                return 'E';
            case 90:
                return 'N';
            case 180:
                return 'W';
            case 270:
                return 'S';
        }
        return '?';
    }
    bool can_move_forward( const Maze& maze ) const {
        int next_x = x , next_y = y;
        switch( facing_angle ){
            case 0:
                next_x++;
                break;
            case 90:
                next_y--;
                break;
            case 180:
                next_x--;
                break;
            case 270:
                next_y++;
                break;
        }
        if( next_x < 0 || next_x >= maze.W || next_y < 0 || next_y >= maze.H ) 
            return false;
        if( maze.tiles[next_x + next_y*maze.W ] == '*' ){
            return false;
        }
        return true;
    }
};

int main(){
    int TEST_CASES,ROWS,COLUMNS;
    char next_command;
    string line;
    cin >> TEST_CASES;
    while( TEST_CASES-- ){
        cin >> ROWS >> COLUMNS ;
        
        Maze maze(COLUMNS,ROWS);
        Robot robot;

        getline( cin , line ); // Goes to next line, the beginning of the maze
        for( int r = 0 ; r < ROWS ; r++ ){
            getline( cin , line );
            for( int it = 0 ; it < line.size() ; it++ ){
                maze.tiles[r*COLUMNS + it] = line[it];
            }
        }
        cin >> robot.y >> robot.x;
        robot.x--;robot.y--;

        next_command = '_';
        while( next_command != 'Q' ){
            cin >> next_command;
            if( next_command == 'F' && robot.can_move_forward(maze) ){
                robot.move_forward();
            }
            else if( next_command == 'R' ){
                robot.rotate(-90);
            }
            else if( next_command == 'L' ){
                robot.rotate(90);
            }
        }

        cout << robot.y + 1 << " " << robot.x + 1 << " " << robot.get_facing_angle_char() << endl;
        if( TEST_CASES > 0 ) cout << endl;

    }
}