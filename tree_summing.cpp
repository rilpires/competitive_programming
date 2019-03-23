#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

struct Node {
    int valor;
    Node* esq = NULL;
    Node* dir = NULL;
    Node( int _valor ):valor(_valor){}
    void insereEsquerda( Node* no ){
        esq = no;
    }
    void insereDireita( Node* no ){
        dir = no;
    }
    string getString(){
        string str_esq = "()";
        string str_dir = "()";
        if( esq )str_esq = esq->getString();
        if( dir )str_dir = dir->getString();
        return "(" + to_string(valor) + str_esq + str_dir + ")";
    }
    
    bool temCaminho( int dist ){
		if( esq == NULL && dir == NULL && dist == valor ) return true;
        bool lado_esq = ( esq && esq->temCaminho(dist-valor) );
		bool lado_dir = ( dir && dir->temCaminho(dist-valor) );
		return lado_esq || lado_dir;
	}
};

Node* leNode( istream& s ){
	char next_char ='a';
	Node* ret = NULL;
	while( next_char != '(' )
		s >> next_char;
	
    char peek = s.peek();
	if( ( peek >= '0' && peek <= '9' ) || peek == '-' ){
		int valor = -1;
		s >> valor;
        ret = new Node(valor);
        ret->insereEsquerda( leNode(s) );
        ret->insereDireita( leNode(s) );	
	}
	
	while( next_char != ')' )
		s >> next_char;
	
	return ret;
}


int main(){
	//ifstream cin("entrada.txt");
    //ofstream cout("saida.txt");
	int distancia = -1;
	cin >> distancia;
	while( cin.peek() != EOF ){
		Node* raiz = leNode(cin);
		
		if(raiz){ 
			//cout << "arvore " << raiz->getString() << endl;
			if( raiz->temCaminho(distancia) ){
				cout << "yes" << endl;
			}else{
				cout << "no" << endl;
			}
		}
		else{
			cout << "no" << endl;
		}
		cin >> distancia;
	}
}