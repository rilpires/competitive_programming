#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct HeapOrdenada{
    vector<int> valores;
    size_t aux_tam = 0;
    bool ordenada = true;
    int max;

    inline void insere( const int& novo_valor ){
        if( valores.size() == 0 ){
            max = novo_valor;
        }
        valores.push_back(novo_valor);
        if( novo_valor > max ){
            max = novo_valor;
        } else{
            ordenada = false;
            conserta_subindo( valores.size() - 1 );
        }
    }

    inline void conserta_subindo( size_t index ) {
        size_t meu_pos = index;
        size_t pos_pai = (meu_pos-1)/2;
        while( meu_pos > 0 && valores[pos_pai] > valores[meu_pos] ){
            int temp = valores[pos_pai];
            valores[pos_pai] = valores[meu_pos];
            valores[meu_pos] = temp;
            meu_pos = pos_pai;
            pos_pai = (meu_pos-1)/2;
        }
    }
    inline void conserta_descendo( size_t index , vector<int>& arvore ) {
        size_t meu_pos = index;
        while(true){
            size_t left_pos = 2*meu_pos + 1U;
            size_t right_pos = left_pos + 1U;
            size_t menor_pos;
            bool itera_mais_uma_vez = false;
            // 1 filho
            if( left_pos + 1 == aux_tam ){
                if( arvore[left_pos] < arvore[meu_pos] ){
                    menor_pos = left_pos;
                    itera_mais_uma_vez = true;
                }
            }
            // 2 filhos
            else if( left_pos + 1 < aux_tam ){
                if( arvore[right_pos] < arvore[left_pos] ) 
                    menor_pos = right_pos;
                else menor_pos = left_pos;
                if( arvore[menor_pos] < arvore[meu_pos] ){
                    itera_mais_uma_vez = true;
                }
            }

            if( itera_mais_uma_vez ){
                troca( meu_pos , menor_pos , arvore );
                meu_pos = menor_pos;
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
            conserta_descendo(0,valores);
        }
        ordenada = true;
        valores = valores_ordenados;
    }
    inline int operator[]( size_t index ){
        if(!ordenada) ordena_tudo();
        return valores[index];
    }
    inline int get_ordem( size_t pos_ordenada ){
        if( ordenada ){
            return valores[pos_ordenada];    
        }
        else if( pos_ordenada >= valores.size()*0.2 ){
            ordena_tudo();
            return valores[pos_ordenada];
        }
        else{
            int ret;
            vector<int> aux_tree(valores);
            aux_tam = valores.size();
            for( size_t i = 0 ; i <= pos_ordenada ; i++ ){
                ret = aux_tree[0];
                aux_tree[0] = aux_tree[aux_tam-1];
                aux_tam--;
                conserta_descendo(0,aux_tree);
            }
            return ret;
        }
    } 
};

int K = 0;
int M;
int N;
vector<int> ADDs;
vector<size_t> GETs;

int main(){
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    string line;
    cin >> K;
    for( int i = 0 ; i < K ; i++ ){
        ADDs.clear(); 
        GETs.clear();
        HeapOrdenada black_box;
        
        cin >> M >> N;
        for( int j = 0 ; j < M ; j++ ){
            int next;
            cin >> next;
            ADDs.push_back(next);
        }
        for( int j = 0 ; j < N ; j++ ){
            size_t next;
            cin >> next;
            GETs.push_back(next);
        }
        
        //==========
        size_t num_ADD = 0;
        size_t next_get_index = 0;
        while(  next_get_index < GETs.size() ){
            int valor_adicionado = ADDs[num_ADD];
            black_box.insere(valor_adicionado);
            num_ADD++;

            while( next_get_index < GETs.size() && GETs[next_get_index] == num_ADD ){
                cout << black_box.get_ordem(next_get_index++) << endl;
            }
        }
        if(i < K - 1)cout << endl;
    }
    return 0;
}