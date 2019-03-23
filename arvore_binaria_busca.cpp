#include <iostream>

using namespace std;

template<typename Tk, typename T>
class Map{
    private:
        struct No{
            Tk chave;
            mutable T valor;
            No* esq;
            No* dir;
            No* pai;
            No( Tk _chave , T _valor ){
                chave = _chave;
                valor = _valor;
                esq = NULL ; dir = NULL; pai = NULL;
            }
            void insereNo( No* no ){
                if(no->chave < chave){
                    if(esq){
                        esq->insereNo(no);
                    }else{
                        esq = no;
                        esq->pai = this;
                    }
                }else{
                    if(dir){
                        dir->insereNo(no);
                    }else{
                        dir = no;
                        dir->pai = this;
                    }
                }
            }
            T& procura( Tk _chave ) const {
                if( _chave == chave ){
                    return valor;
                }
                else if( _chave < chave)
                {
                    if(esq) return esq->procura(_chave);
                }
                else{
                    if(dir) return dir->procura(_chave);
                }
            }
            bool existe( Tk _chave ) const{
                if( _chave == chave ){
                    return true;
                }
                else if( _chave < chave)
                {
                    if(esq) return esq->existe(_chave);
                    else return false;
                }
                else{
                    if(dir) return dir->existe(_chave);
                    else return false;
                }
            }
        };
        No* raiz;

    public:
        Map(){
            raiz = NULL;
        }
        void insere( Tk chave , T valor ){
            if( raiz ){
                raiz->insereNo( new No(chave,valor) );
            }else{
                raiz = new No(chave,valor);
            }
        }
        T& operator[] (Tk chave) const{
            return raiz->procura(chave);
        }
};

