#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>
using namespace std;

struct Node
{
    vector<int> saidas;
};

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    string line;
    stringstream line_stream;
    while( getline(cin,line) ){
        if( line == "0 0" ) break;
        line_stream = stringstream(line);
        int N,M;
        line_stream >> N >> M;
        vector<Node> nodes(N);
        vector<int> ordem_topologica;
        vector<int> graus_de_entrada(N);
        for( int _m = 0 ; _m < M ; _m++ ){
            getline(cin,line);
            line_stream = stringstream(line);
            int i,j;
            line_stream >> i >> j;
            nodes[i-1].saidas.push_back(j-1);
        }
        for( auto node : nodes ){
            for( auto it : node.saidas ){
                graus_de_entrada[it]++;
            }
        }
        int indice_inseridos = 0;
        vector<int> faltantes;
        for( int i = 0 ; i < N ; i++ )
            faltantes.push_back(i);

        while( ordem_topologica.size() < N ){
            // Procura onde tem 0
            // Se nao tem 0, erro
            // Insere na pilha
            // Tira um de todos grau de entrada q apontava

            auto it = faltantes.begin();
            //for( auto v : faltantes ) cout << "falta " << v+1 << endl;
            while( it < faltantes.end() ){
                if( graus_de_entrada[*it] <= 0 ){
                    //cout << "achei o " << *it+1 << endl;
                    ordem_topologica.push_back(*it);
                    it = faltantes.erase(it);
                }
                it++;
            }
            
            int proximo_executar = ordem_topologica[indice_inseridos];
            Node proximo_node = nodes[proximo_executar];
            for( auto it : proximo_node.saidas ){
                graus_de_entrada[it] = graus_de_entrada[it]-1;
            }
            indice_inseridos++;
        }
        for( auto it = ordem_topologica.begin() ; it != ordem_topologica.end() ; it++ )
            cout << (*it + 1) << ((it==ordem_topologica.end()-1)?"":" ") ;
        cout << endl;
    }
}


