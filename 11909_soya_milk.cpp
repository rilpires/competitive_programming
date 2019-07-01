/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/119/p11909.pdf
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int l,w,h,theta;
    while( cin >> l >> w >> h >> theta ){
        char str[64];
        double result;
        double tan_theta = tan( ((double)theta) * (M_PI) / (180.0) );
        double cotan_theta = 1.0L / tan_theta;
        
        if( l * tan_theta < h ){
            result = l*w*h - l*l*tan_theta*w/2;
        } else {
            result = h*h*cotan_theta*w/2;
        }
        
        sprintf( str , "%.3f mL" , result );
        cout << str << endl;
    }
}