/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester
    - Problem PDF:
        https://uva.onlinejudge.org/external/12/p1220.pdf
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

bool unique_tree;

struct Node {
    string          name;
    vector<Node*>   children;
    short           invited;
    
    Node( string _name ):name(_name){}
};

enum {
    INVITED ,
    NOT_INVITED,
    WHATEVER
};

int get_maximum_amount( Node* node , short CASE ){
    switch(CASE){
        
        case INVITED :{
            int ret = 1;
            for( auto child : node->children ){
                ret += get_maximum_amount(child,NOT_INVITED);
            }
            return ret;
        }

        case NOT_INVITED :{
            int ret = 0;
            for( auto child : node->children ){
                ret += get_maximum_amount(child,WHATEVER);
            }
            return ret;
        }

        case WHATEVER:{
            int r1 = get_maximum_amount(node,INVITED);
            int r2 = get_maximum_amount(node,NOT_INVITED);
            int ret = max(r1,r2);
            if( r1 > r2 ) node->invited = INVITED;
            else if( r1 < r2 ) node->invited = NOT_INVITED;
            else node->invited = WHATEVER;
            return ret;
        }

    }
    return 0;
}


void search_for_invites( Node* node ){
    if( node->invited == INVITED ){
        for( auto child : node->children ){
            for( auto grandchild : child->children ){
                search_for_invites(grandchild);
            }
        }
    } else if ( node->invited == NOT_INVITED ){
        for( auto child : node->children ){
            search_for_invites( child );
        }
    } else if( node->invited == WHATEVER ){
        unique_tree = false;
    } 
}

int main(){
    int N;
    string name1, name2;
    while( cin >> N ){
        if(N==0)break;

        map<string,Node*>   employees;
        Node*               big_boss;

        cin >> name1;
        big_boss = new Node(name1);
        employees[name1] = big_boss;
        for( int i = 0 ; i < N-1 ; i++ ){
            cin >> name1 >> name2;
            if( employees.find(name1) == employees.end() ){
                Node* node1 = new Node(name1);
                employees[name1] = node1;
            }
            if( employees.find(name2) == employees.end() ){
                Node* node2 = new Node(name2);
                employees[name2] = node2;
            }
            employees[name2]->children.push_back(employees[name1]);
        }

        int result = get_maximum_amount(big_boss,WHATEVER);
        unique_tree = true;
        search_for_invites(big_boss);
        cout << result << " " << ((unique_tree)?("Yes"):("No")) << endl;

        for( auto it : employees ) delete it.second;

    }
}