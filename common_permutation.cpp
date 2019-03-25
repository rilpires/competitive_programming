#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int main(){
#ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
#endif
    string line;
    stringstream line_stream;
    string a;
    string b;
    while( getline(cin,line) ){
        a = line;
        getline(cin,b);

        sort(a.begin(),a.end());
        sort(b.begin(),b.end());
        size_t indice_a = 0;
        size_t indice_b = 0;

        string comum = "";

        while( indice_a < a.size() && indice_b < b.size() ){
            if(a[indice_a] == b[indice_b]){
                comum.push_back( a[indice_a] );
                indice_a++;indice_b++;
            }else{
                if( a[indice_a] < b[indice_b] ){
                    while( indice_a < a.size()-1 && a[indice_a]==a[indice_a+1] )
                        indice_a++;
                    indice_a++;
                }else{
                    while( indice_b < b.size()-1 && b[indice_b]==b[indice_b+1] )
                        indice_b++;
                    indice_b++;
                }
            }
        }

        sort(comum.begin(),comum.end());

        cout << comum << endl;

    }
}
