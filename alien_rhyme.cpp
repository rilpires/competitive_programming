/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem URL (Google Code Jam 2019):
        https://codingcompetitions.withgoogle.com/codejam/round/0000000000051635/0000000000104e03
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;


struct Node {

    string substring;

    bool counted = false;
    Node* parent;
    set< Node* > childs;

    Node( string substr ){
        parent = NULL;
        substring = substr;
        childs.clear();
    }
    ~Node(){
        for( auto child : childs ){
            delete child;
        }
        if( parent )
            parent->childs.erase(this);
    }

    void add_word( string new_child ){
        Node* n = new Node( new_child );
        n->parent = this;
        childs.insert( n );
    }
    void build(){
        if( childs.size() > 2 ){
            int new_suffix_size = substring.size() + 1;
            map< string , vector< Node* > > new_suffix_map;
            
            for( auto child : childs ){
                string child_substr; 
                if( child->substring.size() >= new_suffix_size ){
                    child_substr = child->substring.substr( child->substring.size() - new_suffix_size );
                    new_suffix_map[child_substr].push_back( child );
                }
            }
            for( auto suffix : new_suffix_map ){
                Node* new_node = new Node(suffix.first);
                for( auto old_child : suffix.second ){
                    childs.erase( old_child );
                    old_child->parent = new_node;
                    new_node->childs.insert( old_child );
                }
                childs.insert(new_node);
                new_node->parent = this;

                new_node->build();
            }
        }
    }

    int form_pairs(){
        int ret = 0;
        for( auto child : childs ) ret += child->form_pairs();
        vector<Node*> single_childs = get_single_childs();
        if ( single_childs.size() >= 2 && counted == false ){
            for( int i = 0 ; i < 2 ; i++ ){
                Node* child = single_childs[i];
                child->parent = NULL;
                childs.erase(child);
                delete child;
            }
            counted = true;
            ret += 1;
        }
        return ret;
    }
    bool raise_singles(  ){
        bool ret = false;
        if( get_only_child() && get_only_child()->get_only_child() && get_only_child()->get_only_child()->childs.size() == 0 ){
            Node* filho = get_only_child();
            Node* neto = filho->get_only_child();
            filho->parent = NULL;
            neto->parent = this;
            childs.insert(neto);
            filho->childs.erase(neto);
            ret = true;
            childs.erase(filho);
            delete filho;
        }
        else for( auto child : childs ){
            ret = ret || child->raise_singles();
        }
        return ret;
    }
    Node* get_only_child(){
        if( childs.size() == 1 ){
            return *childs.begin();
        }
        return NULL;
    }
    
    vector<Node*> get_single_childs(){
        vector<Node*> ret(0);
        for( auto child : childs ){
            if( child->childs.size() == 0 ) ret.push_back(child);
        }
        return ret;
    }
    void get_all_counted_nodes( vector<Node*>& ret ){
        if( parent && counted )
            ret.push_back( this );
        for( auto child : childs )
            child->get_all_counted_nodes(ret);
    }

    void search_for( Node* n ){
        if( this == n ){
            cout << "Sou eu!! " << substring << endl;
        }
        for( auto child : childs ){
            child->search_for(n);
            cout << "terminei um search" << endl;
        }
    }

};

int main(){
    int T,N;
    string next_word;
    vector<string> dictionary;
    cin >> T;
    for( int case_number = 1 ; case_number <= T ; case_number++ ){
        cin >> N;

        dictionary.clear();
        while( N-- ){
            cin >> next_word;
            dictionary.push_back(next_word);
        }
        map< string , vector<string> > clusters;
        
        for( auto word : dictionary ){
            clusters[ word.substr(word.size()-1) ].push_back( word );
        }

        int max_pairs = 0;
        for( auto cluster : clusters ){
            Node root( cluster.first );
            for( auto word : cluster.second )
                root.add_word(word);
            root.build();

            while(true){
                int new_pairs = root.form_pairs();
                if( new_pairs > 0 ){
                    max_pairs += new_pairs;
                    // Deleting counted
                    vector<Node*> all_counteds;
                    all_counteds.clear();
                    root.get_all_counted_nodes(all_counteds);
                    //
                    for( auto counted_it = all_counteds.begin() ; counted_it != all_counteds.end() ; counted_it ++ ){
                        Node* counted = *counted_it;
                        for( auto child : counted->childs ){
                            //a
                            if( counted->parent->childs.find(child) == counted->parent->childs.end() )
                                counted->parent->childs.insert(child);
                            child->parent = counted->parent;
                            counted->parent->childs.erase(counted);
                            counted->parent = NULL;
                        }
                        counted->childs.clear();
                    }
                    for( auto it = all_counteds.begin() ; it != all_counteds.end() ; it++ ){
                        Node* n = *it;
                        cout << "Ja foi um counted " << endl;
                        root.search_for( n );
                        delete n;
                    }
                    // Raising singles
                    cout << "raising singles loop" << endl;
                    while(root.raise_singles()){
                    };

                }else{
                    break;
                }
            }
        }
        cout << "Case #" << case_number << ": " << max_pairs*2 << endl;
    }
}











