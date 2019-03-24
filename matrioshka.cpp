#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

struct Matrioshka{
    int tam;
    int tam_ocupado = 0;
    bool valida = false;
    
    Matrioshka( int _tam ){
        tam = _tam;
    }
    bool completaMatrioshka( istream& is ){
        int next_value;
        while( tam > 0 && is >> next_value ){

            if( next_value > 0 ){
                // Fechou certin
                valida = (next_value==tam && tam_ocupado<tam);
                break;
            }

            else 
            if( next_value < 0 ){
                Matrioshka filha(-next_value);
                if( filha.completaMatrioshka(is) ){
                    tam_ocupado += filha.tam;
                    if( tam_ocupado >= tam ){
                        return false;
                    }
                }else{
                    return false;
                }
            }

        }
        return valida;
    }


};

int main(){
    //ifstream cin("entrada.txt");
    //ofstream cout("saida.txt");   
    string line;
    while( getline(cin,line) ){
        stringstream line_stream(line);
        int next_value;
        int afinal = true;
        while( afinal && line_stream >> next_value ){
            int tam = -next_value;
            Matrioshka maezona(tam);
            afinal = afinal && maezona.completaMatrioshka(line_stream);
        }
        
        cout << ( afinal?
        ":-) Matrioshka!"
        :
        ":-( Try again."
        ) << endl;
    }
}

