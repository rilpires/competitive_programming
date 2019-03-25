#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int main(){
    //ifstream cin("entrada.txt");
    //ofstream cout("saida.txt");
    string line;
    getline( cin , line );
    int N_casos;
    stringstream line_stream(line);
    line_stream >> N_casos;
    for( int i = 0 ; i < N_casos ; i++ ){
        getline(cin,line);
        line_stream = stringstream(line);
        int N_familiares;
        line_stream >> N_familiares;
        
        //=====
        vector<int> numeros;
        int next_casa;
        for( int j = 0 ; j < N_familiares ; j++ ){
            line_stream >> next_casa;
            numeros.push_back( next_casa );
        }
        sort(numeros.begin(),numeros.end());
        int mediana = numeros[numeros.size()/2];
        int distancia = 0;
        for( auto it : numeros )
            distancia += (mediana>it)?(mediana-it):(it-mediana);
        cout << distancia << endl;
    }
}
