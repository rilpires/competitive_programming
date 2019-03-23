#include <iostream>
#include <chrono>
using namespace std;

struct Vetor{
    int tam = 0;
    int max_tam = 0;
    int* valores;

    int tam_ordenado = 0;
    int* valores_ordenados;
    
    ~Vetor(){
        delete[] valores;
        delete[] valores_ordenados;
    }
    void _insere( int val ){
        tam ++;
        if( tam > max_tam ){
            if( max_tam == 0 )max_tam = 1;
            max_tam = max_tam * 2;
            int* novos_valores = new int[max_tam];
            for( int i = 0 ; i < tam - 1 ; i ++ ){
                novos_valores[i] = valores[i];
            }
            delete[] valores;
            valores = novos_valores;
        }
        valores[tam-1] = val;
    }
    void insere(int val){
        _insere( val );
    }
    void printa(){
        cout << "O vetor eh : " << endl;
        for( int i = 0 ; i < tam ; i++ )
            cout << valores_ordenados[i] << ",";
        cout << endl;
    }

};

struct Heap : Vetor{

    void insere( int val ){
        _insere(val);
        conserta_subindo(tam-1);
    }

    void conserta_subindo( int pos ){
        int pos_pai = (pos-1)/2;
        if( valores[pos_pai] < valores[pos] ){
            int temp = valores[pos_pai] ;
            valores[pos_pai] = valores[pos] ;
            valores[pos] = temp ; 
            conserta_subindo( pos_pai );
        }
    }
    void conserta_descendo( int pos ){
        int pos_esq = 2*pos + 1;
        int pos_dir = 2*pos + 2;
        if( pos_dir < tam_ordenado )
        // 2 filhos
        {
            if( valores[pos_esq] > valores[pos_dir] ){
                if( valores[pos_esq] > valores[pos] ){
                    int temp = valores[pos_esq];
                    valores[pos_esq] = valores[pos];
                    valores[pos] = temp;
                    conserta_descendo(pos_esq);
                }
            }else if( valores[pos_dir] > valores[pos] ){
                    int temp = valores[pos_dir];
                    valores[pos_dir] = valores[pos];
                    valores[pos] = temp;
                    conserta_descendo(pos_dir);
            }
        }
        else if( pos_esq < tam_ordenado )
        // 1 filho
        {
            if( valores[pos_esq] > valores[pos] ){
                int temp = valores[pos_esq];
                valores[pos_esq] = valores[pos];
                valores[pos] = temp;
                conserta_descendo(pos_esq);
            }
        }
    }

    void ordena( ){
        delete[] valores_ordenados;
        valores_ordenados = new int[tam];
        
        tam_ordenado = tam;

        while( tam_ordenado > 0){
            valores_ordenados[tam_ordenado-1] = valores[0];
            tam_ordenado --;
            valores[0] = valores[tam_ordenado];
            conserta_descendo( 0 );
        }
    }
};

struct BubbleSort : Vetor{
    void ordena(){
        delete[] valores_ordenados;
        valores_ordenados = new int[tam];
        for( int i = 0 ; i < tam ; i++ )
            valores_ordenados[i] = valores[i];
        tam_ordenado = 0;
        while( tam_ordenado < tam ){
            int menor_i = tam_ordenado;
            for( int i = menor_i ; i < tam ; i ++ ){
                if( valores_ordenados[i] < valores_ordenados[menor_i] ){
                    menor_i = i;
                }
            }
            int temp = valores_ordenados[tam_ordenado];
            valores_ordenados[tam_ordenado] = valores_ordenados[menor_i];
            valores_ordenados[menor_i] = temp;
            tam_ordenado ++ ;
        }
    }
};

int main(){
    Heap heap;
    BubbleSort bsort;
    for( int i = 0 ; i < 10000 ; i ++ ){
        int r = rand()%1000;
        heap.insere( r );
        bsort.insere( r );
    }
    
    chrono::high_resolution_clock::time_point init;
    chrono::duration<double> duration;
    

    cout << "Bubblesort" << endl;
    init = chrono::high_resolution_clock::now();
    bsort.ordena();
    duration = chrono::high_resolution_clock::now() - init;
    cout << duration.count() << " s" << endl;

    cout << "Heapsort" << endl;
    init = chrono::high_resolution_clock::now();
    heap.ordena();
    duration = chrono::high_resolution_clock::now() - init;
    cout << duration.count() << " s" << endl;
    

    cout << "Fim" << endl;
    

    return 0;
}
