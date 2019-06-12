#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

using namespace std;

// 0 BARBARY
// 1 BUCCANEER
struct PirateLand{
    enum { NO_INTERSECTION , HALF_INSIDE , FULL_INSIDE , FULL_OUTSIDE };
    size_t N = 0;
    size_t vector_begin , tree_max_size;
    size_t limite_esq , limite_dir;
    vector<int> nodes;

    void fazInsercoes( list<pair<int,string> >& insercoes ){
        for( auto it : insercoes ){
            N += (it.first) * (it.second).size();
        }
        size_t menor_po2_suficiente = 1;
        while( menor_po2_suficiente < N)
            menor_po2_suficiente *= 2;
        vector_begin = menor_po2_suficiente - 1;
        tree_max_size = 2*menor_po2_suficiente-1;
        nodes = vector<int>(vector_begin);

        while(!insercoes.empty())
        {
            auto par = insercoes.front();
            insercoes.pop_front();
            for( int i = 0 ; i < par.first ; i++ )
                for( auto letrinha : par.second )
                    nodes.push_back( letrinha=='1'?1:0 );
        }
        consertaDescendo(0);
    }

    inline void consertaDescendo( size_t index_raiz ){
        size_t esq = 2*index_raiz + 1;
        size_t dir = 2*index_raiz + 2;
        nodes[index_raiz] = 0;
        if( esq < nodes.size() ){
            if( esq < vector_begin )
                consertaDescendo(esq);
            nodes[index_raiz] += nodes[esq];
            
        }
        if( dir < nodes.size() ){
            if( dir < vector_begin )
                consertaDescendo(dir);
            nodes[index_raiz] += nodes[dir];
        }
        
    }
    inline void consertaSubindo( size_t index_raiz ){
        while( index_raiz > 0 ){
            size_t pai = (index_raiz-1)/2;
            nodes[pai] = nodes[2*pai+1] + nodes[2*pai+2];
            index_raiz = pai;
        }
    }


    void seta1( size_t init , size_t end ){
        init = vector_begin + init;
        end = vector_begin + end;
        limite_esq = init;
        limite_dir = end;
        size_t pai_comum = pegaPaiComum(init,end); 
        setaTudo1( pai_comum );
        consertaDescendo( pai_comum );
        consertaSubindo( pai_comum );
    }
    void seta0( size_t init , size_t end ){
        init = vector_begin + init;
        end = vector_begin + end;
        limite_esq = init;
        limite_dir = end;
        size_t pai_comum = pegaPaiComum(init,end); 
        setaTudo1( pai_comum , true );
        consertaDescendo( pai_comum );
        consertaSubindo( pai_comum );
    }
    void flipa( size_t init , size_t end ){
        init = vector_begin + init;
        end = vector_begin + end;
        for( auto i = init ; i <= end ; i++ )
            nodes[i] = !nodes[i];
        size_t pai_comum = pegaPaiComum(init,end);
        consertaDescendo(pai_comum);
        consertaSubindo(pai_comum);
    }
    int somatorio( size_t init , size_t end ){
        init = vector_begin + init;
        end = vector_begin + end;
        limite_esq = init;
        limite_dir = end;
        return pegaSomatorio( 0 );
    }

    inline int pegaPaiComum( size_t index_esq , size_t index_dir ) const{
        if( index_dir == index_esq ) cout << " PERIGO "<<endl;
        size_t pai_esq = (index_esq-1)/2;
        size_t pai_dir = (index_dir-1)/2;
        if( pai_esq == pai_dir ) return pai_esq;
        else return pegaPaiComum(pai_esq,pai_dir);
    }
    inline int quantoDentro( pair<size_t,size_t> range ) const{
        if( range.first >= vector_begin 
        && range.first >= limite_esq 
        && range.first <= limite_dir ) 
            return 2;
        size_t meu_limite_esq = range.first;
        size_t meu_limite_dir = range.second;
        if( meu_limite_esq > limite_dir || meu_limite_dir < limite_esq){
            return NO_INTERSECTION;
        }else if( meu_limite_dir <= limite_dir && meu_limite_esq >= limite_esq ){
            return FULL_INSIDE;
        } else if( meu_limite_dir >= limite_dir && meu_limite_esq <= limite_esq ){
            return FULL_OUTSIDE;
        } else{
            return HALF_INSIDE;
        }
    }
    inline pair<size_t,size_t> maxRange( size_t index ) const{
        size_t meu_limite_esq = index;
        size_t meu_limite_dir = index;
        while( meu_limite_esq*2 + 1 < tree_max_size ) 
            meu_limite_esq = meu_limite_esq*2 + 1;
        while( meu_limite_dir*2 + 2 < tree_max_size ) 
            meu_limite_dir = meu_limite_dir*2 + 2;
        if(meu_limite_dir >= nodes.size() ) meu_limite_dir = nodes.size() - 1;
        return pair<size_t,size_t>(meu_limite_esq,meu_limite_dir);
    }
    inline int pegaSomatorio( size_t index_raiz ) const{
        if( index_raiz >= nodes.size() )return 0;
        auto meu_range = maxRange(index_raiz);
        int quanto_dentro = quantoDentro(meu_range);
        switch(quanto_dentro){
            case NO_INTERSECTION:
                return 0;
            case HALF_INSIDE:
                return pegaSomatorio(2*index_raiz+1) + pegaSomatorio(2*index_raiz+2);
            case FULL_INSIDE:
                return nodes[index_raiz];
            case FULL_OUTSIDE:
                return pegaSomatorio(2*index_raiz+1) + pegaSomatorio(2*index_raiz+2);
        }
    }
    inline void setaTudo1( size_t index_raiz , bool ou_zero = false ){
        if( index_raiz >= nodes.size() )return;
        pair<size_t,size_t> max_range = maxRange(index_raiz);
        int quanto_dentro = quantoDentro(max_range);
        switch(quanto_dentro){
            case HALF_INSIDE:
                setaTudo1(2*index_raiz+1,ou_zero);
                setaTudo1(2*index_raiz+2,ou_zero);
                break;
            case FULL_INSIDE:
                nodes[index_raiz] = (max_range.second - max_range.first)*ou_zero;
                consertaSubindo(index_raiz);
                break;
            case FULL_OUTSIDE:
                setaTudo1(2*index_raiz+1,ou_zero);
                setaTudo1(2*index_raiz+2,ou_zero);
                break;
        }
    }

    void printa(){
        cout << "Arvore: " << endl;
        for( size_t i = 0 ; i < nodes.size() ; i++ ){
            cout << "["<<i<<"]" << nodes[i] << '\t';
        }
        cout << endl;
    }

};

int main(){
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    string line;
    getline(cin,line);
    stringstream line_stream(line);
    int T;
    line_stream >> T;
    for( int test_case = 0 ; test_case < T ; test_case++ ){
        cout << "Case " << test_case + 1 << ":" << endl;
        PirateLand pirate_land;

        int M;
        getline(cin,line);
        line_stream = stringstream(line);
        line_stream >> M;
        
        list<pair<int,string>> insercoes;
        for( int m = 0 ; m < M ; m++ ){
            int T;
            getline(cin,line);
            line_stream = stringstream(line);
            line_stream >> T;
            getline(cin,line);
            insercoes.push_back( pair<int,string>(T,line) );
        }
        pirate_land.fazInsercoes( insercoes );

        //-------------
        
        int Q;
        getline(cin,line);
        line_stream = stringstream(line);
        line_stream >> Q;

        int questions_done = 0;
        for( int q = 1 ; q <= Q ; q++ ){
            char letrinha;
            size_t a;
            size_t b;
            getline(cin,line);
            line_stream = stringstream(line);
            line_stream >> letrinha >> a >> b;
            if( letrinha == 'F' ){
                pirate_land.seta1( a , b );
            }else
            if( letrinha == 'I' ){
                pirate_land.flipa( a , b );
            }else
            if( letrinha == 'E' ){
                pirate_land.seta0( a , b );
            }else
            if( letrinha == 'S' ){
                cout << "Q" << ++questions_done << ": " << pirate_land.somatorio(a,b) << endl;
            }
        }


    }

}