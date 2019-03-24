#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct HeapOrdenada{
    private: 
    bool de_minimo;
    public:
    vector<int> valores;
    size_t aux_tam = 0;
    bool ordenada = true;

    HeapOrdenada(bool _heap_de_minimo=true):de_minimo(_heap_de_minimo){}

    inline void insere( const int& novo_valor ){
        valores.push_back(novo_valor);
        ordenada = false;
        conserta_subindo( valores.size() - 1 );
    }
    inline int retira_topo(){
        int ret = valores[0];
        valores[0] = *valores.rbegin();
        valores.pop_back();
        aux_tam = valores.size();
        conserta_descendo(valores);
        return ret;
    }
    inline void conserta_subindo( size_t index ) {
        size_t meu_pos = index;
        size_t pos_pai = (meu_pos-1)/2;
        while( meu_pos > 0 && !ordem(valores[pos_pai],valores[meu_pos]) ){
            int temp = valores[pos_pai];
            valores[pos_pai] = valores[meu_pos];
            valores[meu_pos] = temp;
            meu_pos = pos_pai;
            pos_pai = (meu_pos-1)/2;
        }
    }
    inline void conserta_descendo( vector<int>& arvore ) {
        size_t meu_pos = 0;
        while(true){
            size_t left_pos = 2*meu_pos + 1U;
            size_t right_pos = left_pos + 1U;
            size_t candidato_pos = left_pos;
            bool itera_mais_uma_vez = false;
            // 1 filho
            if( left_pos + 1 == aux_tam ){
                if( !ordem(arvore[meu_pos],arvore[left_pos]) ){
                    candidato_pos = left_pos;
                    itera_mais_uma_vez = true;
                }
            }
            // 2 filhos
            else if( left_pos + 1 < aux_tam ){
                if( ordem(arvore[right_pos],arvore[left_pos]) ) 
                    candidato_pos = right_pos;
                else candidato_pos = left_pos;
                if( !ordem(arvore[meu_pos],arvore[candidato_pos]) ){
                    itera_mais_uma_vez = true;
                }
            }

            if( itera_mais_uma_vez ){
                troca( meu_pos , candidato_pos , arvore );
                meu_pos = candidato_pos;
            }
            else break;
        }
    }
    inline void troca( size_t ind_1 , size_t ind_2 , vector<int>& arvore ){
        int temp = arvore[ind_1];
        arvore[ind_1] = arvore[ind_2];
        arvore[ind_2] = temp;
    }
    inline void ordena_tudo( ){
        vector<int> valores_ordenados(valores.size());
        aux_tam = valores.size();
        for( size_t i = 0 ; i < valores.size() ; i++ ){
            valores_ordenados[i] = valores[0];
            valores[0] = valores[aux_tam-1];
            aux_tam--;
            conserta_descendo(valores);
        }
        ordenada = true;
        valores = valores_ordenados;
    }
    inline int operator[]( const size_t& index ){
        if( ordenada ){
            return valores[index];    
        }
        else if( index == 0  ){
            return valores[0];
        }
        else{
            ordena_tudo();
            return valores[index];
        }
    }
    inline bool ordem( const int& cima , const int& baixo ) const {
        return ( de_minimo && (baixo>cima) ) || ( !de_minimo && (cima>baixo) ) ;
    }
    inline string toString(){
        string ret = "[";
        for( auto it = valores.begin() ; it != valores.end() ; it++ ) 
            ret += to_string(*it) + (it==(valores.end()-1)?"":",");
        ret = ret + "]";
        return ret;
    }
};
