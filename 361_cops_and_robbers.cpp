/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/3/p361.pdf
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    double x;
    double y;
    Point( double _x , double _y ) : x(_x) , y(_y) {}
};

struct Line {
    // ax + by = c;
    double a , b , c;
    Line( Point p1 , Point p2 ){
        a = (p2.y - p1.y);
        b = (p1.x - p2.x);
        c = p2.y*p1.x - p1.y*p2.x;
    }

    Line 

};

int main(){
    Line l( Point(0,0) , Point(1,1) );
    cout << l.a << "x + " << l.b << "y = " << l.c << endl;
}