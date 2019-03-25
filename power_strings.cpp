#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


vector<int>& fatora( int N ){
    vector<int> ret();

    
    return ret;
}

int largestN( string str ){
    int fatores = fatora(str.size());
    for( auto fator = fatores.rbegin() ; fator != fatores.rend() ; fator++ ){
        int passo = str.size()/(*fator);
        string candidato = str.substr(0,passo );
        bool ta_ok = true;
        for( i = passo ; i < str.size() ; i += passo ){
            if( candidato != str.substr(i,passo) ){
                ta_ok = false;
                break;
            }
        }
        if( ta_ok ) return passo;
    }
    return 666;
}


int main(){
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    string line;
    while( getline(cin,line) ){
        if( line != "." )
            cout << largestN(line) << endl;
    }
}
