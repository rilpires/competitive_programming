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
        line_stream = stringstream(line);
        double L , D , H , V;
        line_stream >> L >> D >> H >> V;
        L *= 0.001; D *= 0.001; H *= 0.001; V *= 0.001;
        double tempo_queda = pow( 2*H/9.81 , 0.5 );
        double distancia_queda = tempo_queda * V;
        if( distancia_queda < D - 0.5 || distancia_queda > L + D + 0.5 ){
            cout << "FLOOR" << endl;
        }else if ( distancia_queda > D + 0.5 && distancia_queda < L + D - 0.5 ){
            cout << "POOL" << endl;
        }else{
            cout << "EDGE" << endl;
        }
    } 

}