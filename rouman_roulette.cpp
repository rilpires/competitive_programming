#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

struct No{
    No* anterior;
    No* seguinte;
    int numero;
    bool vivo;
    
    No( int _numero ){
        numero = _numero;
        anterior = NULL;
        seguinte = NULL;
        vivo = true;
    }

    No* pegaProximo( int pulos ){
        No* ret = this;
        while( pulos > 0 ){
            ret = ret->seguinte;
            if( ret->vivo ){
                pulos --;
            }
        }
        return ret;
    }

    void saiDaRoda(){
        anterior->seguinte = seguinte;
        seguinte->anterior = anterior;
    }

};



int main(){
    //ifstream cin("entrada.txt");
    //ofstream cout("saida.txt");
    string line;
    while( getline( cin , line ) ){
        stringstream line_stream(line);
        int n;
        int k;
        No* primeira_pessoa = NULL;
        No* ultima_pessoa_adicionada = NULL;
        line_stream >> n >> k ;
        if( n == 0 && k == 0 ) break;
        for( int i = 0 ; i < n ; i++ ){
            if( primeira_pessoa == NULL ){
                primeira_pessoa = new No( i+1 );
                ultima_pessoa_adicionada = primeira_pessoa;
            }else{
                No* nova_pessoa = new No( i+1 );
                ultima_pessoa_adicionada->seguinte = nova_pessoa;
                nova_pessoa->anterior = ultima_pessoa_adicionada;
                ultima_pessoa_adicionada = nova_pessoa;
            }
        }
        ultima_pessoa_adicionada->seguinte = primeira_pessoa;
        primeira_pessoa->anterior = ultima_pessoa_adicionada;

        // ---------------
        No* proximo_escolhido = primeira_pessoa->pegaProximo(k-1);
        while( proximo_escolhido->seguinte != proximo_escolhido ){
            No* morto = proximo_escolhido;
            morto->vivo = false;
            //cout << "Morreu: " << morto->numero << endl;
            proximo_escolhido = morto->pegaProximo(k);

            //Esse escolhido agora fica no lugar do morto
            proximo_escolhido->saiDaRoda();
            morto->anterior->seguinte = proximo_escolhido;
            morto->seguinte->anterior = proximo_escolhido;
            proximo_escolhido->seguinte = morto->seguinte;
            proximo_escolhido->anterior = morto->anterior;
            //cout << proximo_escolhido->numero << " enterrou " << morto->numero << endl;
            delete morto;

            proximo_escolhido = proximo_escolhido->pegaProximo(k);
        }
        int vencedor = proximo_escolhido->numero;
        int diferenca_pra_ganhar = n-vencedor+1;
        if( vencedor == 1 ) diferenca_pra_ganhar = 0;
        //cout << "Vencedor: " << proximo_escolhido->numero << endl;
        cout << 1 + diferenca_pra_ganhar << endl;
        delete proximo_escolhido;
    }
    return 0;    
}