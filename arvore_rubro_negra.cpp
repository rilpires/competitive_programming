#include <iostream>
#include <string>

using namespace std;

template<typename Tk, typename T>
class Map{
    private:
        struct No{
            enum { RUBRO , NEGRO };
            
            Tk chave;
            mutable T valor;
            short cor = NEGRO;
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
                        checaFilhos();
                    }
                }else{
                    if(dir){
                        dir->insereNo(no);
                    }else{
                        dir = no;
                        dir->pai = this;
                        checaFilhos();
                    }
                }
            }
            bool souEsquerda(){
                return (pai && pai->esq == this);
            }
            bool souDireita(){
                return (pai && pai->dir == this);
            }
            T& procura( Tk _chave ) const {
                if( _chave == chave ){
                    return valor;
                }
                else if( _chave < chave )
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
            void checaFilhos(){
                if( esq && esq->cor == RUBRO && dir && dir->cor == RUBRO ){
                    cor = RUBRO;
                    esq->cor = NEGRO;
                    dir->cor = NEGRO;
                    if(pai)pai->checaFilhos();
                }
                else if( dir && dir->cor == RUBRO ){
                    dir->sobe();
                    pai->checaFilhos(); // pai agora eh dir da linha anterior
                }
                else if( cor == RUBRO && esq && esq->cor == RUBRO ){
                    esq->sobe();
                    pai->checaFilhos(); // pai agora eh esq da linha anterior
                }
            }
            // Rotaciona dependendo da posicao
            void sobe(){
                No* antigo_pai = pai;
                No* antigo_avo = pai->pai;
                No* antigo_dir = dir;
                No* antigo_esq = esq;
                
                if( antigo_avo ){
                    if( antigo_pai->souEsquerda() )
                        antigo_avo->esq = this;
                    else if( antigo_pai->souDireita() )
                        antigo_avo->dir = this;
                }
                pai = antigo_avo;

                if( antigo_pai ){
                    if( antigo_pai->esq == this ){
                        antigo_pai->esq = antigo_dir;
                        if(antigo_dir) antigo_dir->pai = antigo_pai;

                        this->dir = antigo_pai;
                        antigo_pai->pai = this;
                    }else if( antigo_pai->dir == this ){
                        antigo_pai->dir = antigo_esq;
                        if(antigo_esq) antigo_esq->pai = antigo_pai;

                        this->esq = antigo_pai;
                        antigo_pai->pai = this;
                    }
                    antigo_pai->cor = RUBRO;
                    cor = NEGRO;
                }

            }
            string getString(){
                string esq_str = "()";
                string dir_str = "()";
                if( esq ) esq_str = esq->getString();
                if( dir ) dir_str = dir->getString();
                
                return "("+to_string(chave) + (cor==RUBRO?"R":"B") + esq_str+dir_str+")" ;
            }
        };

        No* raiz;

    public:
        Map(){
            raiz = NULL;
        }
        string getString(){
            if(raiz) return raiz->getString();
            else return "()";
        }
        void insere( Tk chave , T valor ){
            if( raiz ){
                No* novo_no = new No(chave,valor);
                novo_no->cor = No::RUBRO;
                raiz->insereNo( novo_no );  
                while( raiz->pai ) raiz = raiz->pai;
                raiz->cor = No::NEGRO;
            }else{
                raiz = new No(chave,valor);
                raiz->cor = No::NEGRO;
            }
        }
        T& operator[] (Tk chave) const{
            return raiz->procura(chave);
        }
};

int main(){
    Map<int,int> mapa;
    for( int i = 0 ; i <= 10 ; i ++ ){
        mapa.insere( i , 1 );
    }
    return 0;
}

