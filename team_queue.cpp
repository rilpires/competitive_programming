#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
using namespace std;

struct TeamQueue{
    queue<int>              team_ids;
    map< int , queue<int> > minor_queues;
    map< int , int >        pessoa_time;
    int                     open_team_id = 0;

    void criaTime( vector<int>& values ){
        int team_id = open_team_id++;
        minor_queues[team_id] = queue<int>();
        for( auto it = values.begin() ; it != values.end() ; it++ ){
            pessoa_time[*it] = team_id;
        }
    }
    int timeDesseValor( int valor ){
        return pessoa_time[valor];
    }
    void ENQUEUE( int valor ){
        int team_id = timeDesseValor(valor);
        queue<int>& fila_do_time = minor_queues[team_id]; 
        fila_do_time.push( valor );
        if( fila_do_time.size() == 1 ){
            team_ids.push( team_id );
        }
    }
    int DEQUEUE(){
        int team_id = team_ids.front();
        queue<int>& fila_do_time = minor_queues[team_id];
        int sainte = fila_do_time.front();
        fila_do_time.pop();
        if( fila_do_time.empty() ){
            team_ids.pop();
        }
        return sainte;
    }




};

int main(){
    //ifstream cin("entrada.txt");
    //ofstream cout("saida.txt");
    string line;
    stringstream line_stream;
    int numero_grupos;
    int numero_cenario = 1;
    while( true ){
        cin >> numero_grupos;
        if( numero_grupos == 0 ) break;
        //cout << "Numero de grupos " << numero_grupos << " no cenario " << numero_cenario << endl;
        TeamQueue team_queue;
        for( int i = 0 ; i < numero_grupos ; i++ ){
            getline(cin,line);
            line_stream = stringstream(line);
            vector<int> grupo;
            int numero_pessoas;
            line_stream>>numero_pessoas;
            int proxima_pessoa;
            while( line_stream >> proxima_pessoa ){
                grupo.push_back(proxima_pessoa);
            }
            team_queue.criaTime( grupo );
        }

        cout << "Scenario #" << numero_cenario << endl;
        int valor_lido;
        while( cin.peek() != 'S' ){
            getline(cin,line);
            line_stream = stringstream(line);
            char next_char = line_stream.peek();
            if( next_char == 'E' ){
                line_stream.ignore(7);
                line_stream >> valor_lido;
                team_queue.ENQUEUE(valor_lido);
            }else 
            if( next_char == 'D' ){
                cout << team_queue.DEQUEUE() << endl;
            }
        }
        getline(cin,line);
        numero_cenario++;
        cout << endl;
    }
}