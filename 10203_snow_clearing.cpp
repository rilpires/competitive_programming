/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/102/10203.pdf
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

double distance( int x1 , int y1 , int x2 , int y2 ){
    if( x1 == x2 ){
        return abs(y1-y2);
    }
    if( y1 == y2 ){
        return abs(x1-x2);
    }
    return sqrt(pow(abs(x1-x2),2) + pow(abs(y1-y2),2));
}

int main(){
    int T,x1,y1,x2,y2;
    string line;
    stringstream line_stream;
    getline(cin,line);
    line_stream = stringstream(line);
    line_stream >> T;
    getline(cin,line);
    while( T-- ){
        
        getline(cin,line);
        line_stream = stringstream(line);
        line_stream >> x1 >> y1;
        

        double hours = 0;
        while(true){
            if( !getline(cin,line) ){
                break;
            }
            if( line.size() > 0 ){
                line_stream = stringstream(line);
                line_stream >> x1 >> y1 >> x2 >> y2;
                hours += 2.0*distance(x1,y1,x2,y2)/20000;
            } else {
                break;
            }
        }

        int H=0;
        int M=0;
        while( hours > 1 ){
            H++;hours--;
        }

        M = round(60*hours);
        while( M >= 60 ){
            H++;M-=60;
        }

        if( M >= 10 ){
            cout << H << ":" << M << endl;
        }
        else{
            cout << H << ":0" << M << endl;
        }
        if( T != 0 ) cout << endl;

    }
}