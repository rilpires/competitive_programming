#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    string line;
    stringstream line_stream;
    int T;
    cin >> T;
    getline(cin,line);
    for( int t = 0 ; t < T ; t++ ){
        getline(cin,line);
        line_stream = stringstream(line);

        string string_a,string_b;
        line_stream >> string_a >> string_b ; 

        cout << string_a << " " << string_b << endl;
        string c,d;
        while( true ){
            c = "" , d="";
            for( size_t t = 0 ; t < 31 ; t++ ){
                size_t index = t;
                c.push_back( (string_a[index]!=string_b[index])?'1':'0' );
                d.push_back( (string_a[index]==string_b[index]&&string_a[index]=='1')?'1':'0' );
            }
            string_a = c ; string_b = d;
            string_b.push_back('0');
            if( string_b[0] == '1' ){
                cout << string_a << " overflow" << endl;
                break;
            }else
                string_b = string_b.substr(1);
            cout << string_a << " " << string_b << endl;
            // checa se terminou
            bool zerou = true;
            for( auto c : string_b ){
                if(c=='1'){
                    zerou = false;
                    break;
                }
            }
            if(zerou){
                break;
            }
        }
        
        if( t < T - 1) cout << endl;

    } 

}