#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

bool possivel(vector<int>& sequencia){
   queue<int> A;
   stack<int> Estacao;
   int passaram = 0;
   int proximo_desejado;
   for( int i = 1 ; i <= sequencia.size() ; i++ )
       A.push(i);
   while( passaram < sequencia.size() ){
        proximo_desejado = sequencia[passaram];
        if( !Estacao.empty() && Estacao.top() == proximo_desejado ){
            Estacao.pop();
            passaram++;
        }else if( !A.empty() ){
            int n = A.front();
            A.pop();
            Estacao.push(n);
        }else{
            return false;
        }
   }
   return true;
}

int main(){
    //ifstream cin("entrada.txt");
    //ofstream cout("saida.txt");
    string line;
    while( getline(cin,line) ){
        stringstream line_stream(line);
        int N;
        line_stream>>N;
        if( N == 0 ){
            break;
        }else{
            while(true){
                getline(cin,line);
                line_stream = stringstream(line);
                vector<int> sequencia;
                int proximo_valor;
                while( line_stream >> proximo_valor )
                    sequencia.push_back(proximo_valor);
                if( sequencia.size() != N && sequencia[0] == 0){
                    cout << endl;    
                    break;
                }
                else{
                    cout << (possivel(sequencia)?"Yes":"No") << endl;
                }
            }    
        }
    }
}