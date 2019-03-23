#include <iostream>
#include <fstream>
#include <map>

using namespace std;


string getPath( istream& is ){
    string ret = "";
    while( is.peek() == 'L' || is.peek() == 'R' ){
        char next_char;
        is >> next_char;
        ret.push_back(next_char);
    }
    return ret;
}

int pathToInt( string path ){
    int ret = 0;
    for( auto it = path.begin() ; it != path.end() ; it++ ){
        if( *it == 'L' ){
            ret = 2*ret + 1;
        }else{
            ret = 2*ret + 2;
        } 
    }
    return ret;
}

int main(){
    //ifstream cin("entrada.txt");
    //ofstream cout("saida.txt");
    char last_char = '$';

    while( cin.peek() != EOF ){
        map<int, map<string,int> > mapa_altura;
        bool valido = true;
        while( true ){
            while( last_char != '(' ){
                cin >> last_char;
            }

            if( cin.peek() == ')' ){
                cin >> last_char;
                break;
            }else{
                int valor;
                cin >> valor;
                cin >> last_char;
                string path = getPath(cin);
                int altura = path.size();
                map<string,int>& m = mapa_altura[altura];
                if( m.find(path) != m.end() ){
                    valido = false;
                }
                if(valido){
                    m[path] = valor;
                }
                
            }
            
            while( last_char != ')' )
                cin >> last_char;
            
        }
        if(valido){
            for( auto it = mapa_altura.begin() ; it != mapa_altura.end() && valido ; it++ ){
                int altura = it->first;
                auto m = it->second;
                
                if( altura >= 1 && mapa_altura.find(altura-1) == mapa_altura.end() ){
                    valido = false;
                    break;
                }else if(altura>=1){
                    map<string,int>& m_cima = mapa_altura[altura-1];
                    for( auto it2 = it->second.begin() ; it2 != it->second.end() ; it2++ ){
                        if( m_cima.find( it2->first.substr(0,altura-1) ) == m_cima.end() ){
                            valido = false;
                            break;
                        }
                    }

                }
            }
        }
        if(valido){
            auto last_it = --mapa_altura.end();
            for( auto it = mapa_altura.begin() ; it != mapa_altura.end() ; it++ ){
                auto last_it2 = --it->second.end();
                for( auto it2 = it->second.begin() ; it2 != it->second.end() ; it2++ ){
                    auto lastIt = --mapa_altura.end();
                    cout << it2->second << (it==last_it && it2==last_it2?"":" ") ;
                }
            }
            
        }else{
            cout << "not complete";
        }
        cout << endl;
        if( cin.peek() == '\n' ){
            cin >> last_char;
        }
    }

    return 0;
}