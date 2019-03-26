#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
using namespace std;


void to_uppercase( string& str ){
    for( size_t i = 0 ; i < str.size() ; i++ )
        str[i] = toupper(str[i]);
}

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    //ofstream cout("saida.txt");
    #endif


    string next_input;
    vector<string> input;
    map<string,int> contagem;
    while( true ){
        cin >> next_input;
        if( next_input.size() == 1 && next_input[0] == '#' )break;
        input.push_back( next_input );
        to_uppercase( next_input );
        sort( next_input.begin() , next_input.end() );
        if( contagem.find(next_input) != contagem.end() ){
            contagem[next_input]++;
        }else{
            contagem[next_input] = 1;
        }
    }
    sort(input.begin() , input.end());
    for( auto str : input ){
        string transformado = str;
        to_uppercase(transformado);
        sort(transformado.begin(),transformado.end());
        if( contagem[transformado] == 1 )
            cout << str << endl;
    }
    

}