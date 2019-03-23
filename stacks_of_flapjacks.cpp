#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct No{
    No* baixo;
    No* cima;
    int tam;
    No( int _tam ){
        tam = _tam ;
        baixo = NULL;
        cima = NULL;
    }
    No* insereEmbaixo( No* no ){
        baixo = no;
        no->cima = this;
        return no;
    }
    No* insereEmCima( No* no ){
        cima = no;
        no->baixo = this;
        return no;
    }
    void flip(){
        No* temp = baixo;
        baixo = cima;
        cima = temp;
    }
};

struct Pilha{

    No* base;
    Pilha(){
        base = NULL;
    }
    ~Pilha(){
        No* it = base;
        while( it && it->cima ){
            it = it->cima;
        }
        while( it && it->baixo ){
            it = it->baixo;
            delete it->cima;
        }
        delete it;
    }

    void flip( int index ){
        No* old_head = getTop();
        No* old_flip_base = getPos( index );
        No* temp_head = old_flip_base->baixo;
        No* it = old_flip_base;
        while( it != old_head ){
            it->flip();
            it = it->baixo;
        }
        it->flip();

        old_head->baixo = temp_head;
        if( temp_head ){
            temp_head->cima = old_head;
        }

        old_flip_base->cima = NULL;
        if( index == 1 ){
            base = old_head;
        }
    }
    No* getTop(){
        No* ret = base;
        while( ret && ret->cima )
            ret = ret->cima;
        return ret;
    }
    No* getPos( int ind ){
        No* ret = base;
        int count = ind;
        while( count > 1 ){
            count --;
            ret = ret->cima;
        }
        return ret;
    }
    int getPosValor( int valor ){
        int ret = 1;
        No* it = base;
        while( it && it->cima ){
            it = it->cima;
            ret ++;
        }
        while( it ){
            if( valor == it->tam )break;
            it = it->baixo;
            ret --;
        }
        return ret;
    }
};

int proxLiderPos( Pilha& p , vector<int>& v ){
    No* it = p.base;
    int ret = v.size();
    for( size_t i = 0 ; i < v.size() ; i++ , it=it->cima ){
        if( v[v.size()-i-1] != it->tam ){
            int tam_certo = v[v.size()-i-1];
            ret = p.getPosValor( tam_certo );
            break;
        }
    }
    return ret;
}
int quantidadeCorretos( Pilha& p , vector<int>& v ){
    int ret = 0;
    No* it = p.base;
    for( size_t i = 0 ; i < v.size() ; i++ , it=it->cima ){
        if( v[v.size()-i-1] == it->tam ) ret++; 
        else break;
    }
    return ret;
}

int main(){
    /*
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    */
    string line;
    while( getline(cin,line) ){
        stringstream line_stream(line);
        Pilha p;
        vector<int> vetor_ordenado;
        No* base = NULL;
        bool first_print = true;
        int v;
        while( line_stream >> v ){
            cout << (first_print?"":" ") << v;
            first_print = false;
            if( base == NULL ){
                base = new No( v );
            }else{
                No* no = new No(v);
                base->insereEmbaixo(no);
                base = no;
            }
            vetor_ordenado.push_back(v);
        }
        cout << endl;
        p.base = base;
        sort( vetor_ordenado.begin() , vetor_ordenado.end() );    

        int flips = 0;
        size_t quantidade_corretos = quantidadeCorretos(p,vetor_ordenado);
        while( quantidade_corretos != vetor_ordenado.size() ){
            size_t lider_pos = proxLiderPos( p , vetor_ordenado );
            
            if( lider_pos != vetor_ordenado.size() ){
                cout<< lider_pos << " ";
                p.flip( lider_pos );
                flips ++;
            }
            
            cout << quantidade_corretos + 1 << " ";
            p.flip( quantidade_corretos + 1 );
            flips ++;
            
            quantidade_corretos = quantidadeCorretos(p,vetor_ordenado);
        }
        cout << "0" << endl;

    }
    return 1;
}
