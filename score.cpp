#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    string line;
    stringstream line_stream;

    getline(cin,line);
    line_stream = stringstream(line);
    
    int T;
    line_stream>>T;
    for( auto t = 0 ; t < T ; t++ ){
        getline(cin,line);
        int ret = 0;
        int seq = 0;
        for( auto c : line ){
            if( c == 'O' ){
                ret += ++seq;
            }
            else{
                seq = 0;
            }
        }
        cout << ret << endl;
    } 

}