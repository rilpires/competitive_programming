#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

double getMolarMass( string formula ){
    double ret = 0;
    stringstream formula_stream(formula);
    char c;
    while( formula_stream >> c ){
        int qty = 1;
        double density;
        switch( c ){
            case 'C':
                density = 12.01;
                break;
            case 'H':
                density = 1.008;
                break;
            case 'O':
                density = 16.00;
                break;
            case 'N':
                density = 14.01;
                break;
        }
        
        int peek = formula_stream.peek();
        if( peek != 'C' && peek != 'H' && peek != 'O' && peek != 'N' )
            formula_stream>>qty;
        
        ret += (double)qty * density;
        
    }
    return ret;
}

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
    cout.precision(3);
    for( auto t = 0 ; t < T ; t++ ){
        getline(cin,line);
        cout << fixed << getMolarMass(line) << endl;
    } 

}