#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
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
        //cout << (de_minimo?"de minimo ":"de maximo ");
        //cout << "antes de retirar topo " << toString() << endl;
        int ret = valores[0];
        valores[0] = *valores.rbegin();
        valores.pop_back();
        aux_tam = valores.size();
        conserta_descendo(valores);
        //cout << "depois de retirar topo " << toString() << endl;
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

struct BlackBox{
    HeapOrdenada heap_maximo = HeapOrdenada(false);
    HeapOrdenada heap_minimo = HeapOrdenada(true);
    int get_index = 0;
    inline void ADD( int valor ){
        if( get_index == 0 || valor > heap_maximo[0] ){
            heap_minimo.insere(valor);
        }else{
            heap_maximo.insere( valor );
            heap_minimo.insere( heap_maximo.retira_topo() );
        }
    }
    inline int GET(){
        int ret = heap_minimo[0];
        int topo_minimo = heap_minimo.retira_topo();
        heap_maximo.insere( topo_minimo );
        get_index++;
        //cout << "get " << ret << endl;
        return ret;
    }
};

int main(){
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    string line;
    int K = 0;
    int M;
    int N;
    vector<int> ADDs;
    vector<size_t> GETs;
    
    cin >> K;
    for( int i = 0 ; i < K ; i++ ){
        ADDs.clear(); 
        GETs.clear();
        BlackBox black_box;
        
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
        auto get_it = GETs.begin();
        while( get_it != GETs.end() ){
            int valor_adicionado = ADDs[num_ADD];
            black_box.ADD(valor_adicionado);
            num_ADD++;
            while( get_it != GETs.end() && *get_it == num_ADD ){
                cout << black_box.GET() << endl;
                get_it++;
            }
        }
        if(i < K - 1)cout << endl;
    }
    return 0;
}