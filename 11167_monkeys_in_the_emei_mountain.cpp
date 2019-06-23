/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/111/11167.pdf
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <set>

using namespace std;

short open_search_id = 0;
struct Node {
    short               last_search_id = -1;
    map< Node* , int >  adjacents;
    Node*               tree_parent = NULL;
};
struct Monkey : public Node {
    int                 drinks_left;
    vector<int>         hours_used;
    pair<int,int>       available_interval;
};
struct TimeInterval : public Node {
    size_t          total_to_drink = 0;
    pair<int,int>   time_window;
};
struct Hour : public Node {
    int drink_times_available = 0;
};

// DFS any available path
vector<Node*>   get_any_available_path( Node* source , Node* destiny ) {
    short search_id = open_search_id ++;
    stack<Node*> dfs_stack;
    dfs_stack.push( source );

    source->last_search_id = search_id;
    source->tree_parent = NULL;
    destiny->tree_parent = NULL;
    while( dfs_stack.size() ){
        Node* next_to_explore = dfs_stack.top();
        dfs_stack.pop();
        if( next_to_explore == destiny ){
            break;
        }
        else for( auto edge = next_to_explore->adjacents.begin() ; edge != next_to_explore->adjacents.end() ; edge++ ){
            Node* adjacent = edge->first;
            if( edge->second > 0 && adjacent->last_search_id != search_id ){
                adjacent->tree_parent = next_to_explore;
                adjacent->last_search_id = search_id;
                dfs_stack.push(adjacent);
            }
        }
    }
    if( destiny->tree_parent != NULL ){
        vector<Node*> reverse_path;
        reverse_path.push_back(destiny);
        while( reverse_path.back()->tree_parent != NULL ){
            reverse_path.push_back( reverse_path.back()->tree_parent );
        }
        return vector<Node*>( reverse_path.rbegin() , reverse_path.rend() );
    } else {
        return vector<Node*>();
    }
}

// Returns the amount of flux passed by this path (minimum edge)
int             fill_path( vector<Node*>& path ){
    int minimum = 999999;
    for( int i = 0 ; i < path.size() - 1 ; i++ ){
        Node* n1 = path[i];
        Node* n2 = path[i+1];
        int available = n1->adjacents[n2];
        if( available < minimum ) minimum = available;
    }
    for( int i = 0 ; i + 1 < path.size() ; i++ ){
        Node* n1 = path[i];
        Node* n2 = path[i+1];
        n1->adjacents[n2] -= minimum;
        n2->adjacents[n1] += minimum;
    }
    return minimum;
}

vector< pair<int,int> > get_monkey_drink_intervals( Monkey* monkey ){
    vector<int>& hours_used = monkey->hours_used;
    sort( hours_used.begin() , hours_used.end() );
    vector< pair<int,int> > ret;
    for( int i1 = 0 ; i1 < hours_used.size() ; ){
        pair<int,int> new_pair;
        new_pair.first = hours_used[i1];
        for( int i2 = i1+1 ; i2 <= hours_used.size() ; i2++ ){
            if( i2 == hours_used.size() || hours_used[i2] != hours_used[i2-1] + 1 ){
                new_pair.second = hours_used[i2-1];
                i1 = i2;
                break;
            }
            i1 = i2;   
        }
        ret.push_back(new_pair);
    }
    return ret;
}

int main(){
    int n , m , v , a , b , case_number = 1;
    vector<Node*> path;
    pair<int,int> window;
    while( true ){
        cin >> n >> m;
        if( n == 0 ) break;
        
        Node *source = new Node();
        Node *destiny = new Node(); 
        vector<Monkey*>         monkeys(n);
        vector<Hour*>           hours;
        vector<TimeInterval*>   time_intervals;
        set<int>                time_splitters;
        path.clear();
        
        // Constructing monkeys
        for( int i = 0 ; i < n ; i ++ ){
            cin >> v >> a >> b;
            while( hours.size() < b ){
                Hour* new_hour = new Hour();
                hours.push_back( new_hour );
                new_hour->drink_times_available = m;
            }
            monkeys[i] = new Monkey();
            Monkey* monkey = monkeys[i];
            source->adjacents[monkey] = v;
            monkey->drinks_left = v;
            monkey->available_interval.first = a;
            monkey->available_interval.second = b;
            time_splitters.insert( a );
            time_splitters.insert( b );
        }
        time_splitters.insert(0);
        time_splitters.insert(n);

        // Constructing time intervals
        for( auto it = time_splitters.begin() ; it != time_splitters.end() ; it++ ){
            int t1 = *it;
            it++;
            if( it == time_splitters.end() ) break;
            int t2 = *it;
            it--;

            TimeInterval* time_interval = new TimeInterval();
            time_interval->total_to_drink = (t2 - t1) * m;
            time_interval->adjacents[destiny] = (t2 - t1) * m;
            time_interval->time_window.first = t1;
            time_interval->time_window.second = t2;
            time_intervals.push_back( time_interval );
        }

        // Pointing monkeys to time intervals
        for( auto monkey : monkeys ){
            int first_time_interval_id = -1;
            int second_time_interval_id = -1;
            for( int i = 0 ; i < time_intervals.size() ; i++ ){
                if(time_intervals[i]->time_window.first == monkey->available_interval.first){
                    first_time_interval_id = i;
                    break;
                }
            }
            for( int i = first_time_interval_id ; i < time_intervals.size() ; i++ ){
                if(time_intervals[i]->time_window.second == monkey->available_interval.second){
                    second_time_interval_id = i;
                    break;
                }
            }
            for( int i = first_time_interval_id ; i <= second_time_interval_id ; i++ ){
                TimeInterval* time_interval = time_intervals[i];
                int window = time_interval->time_window.second - time_interval->time_window.first;
                monkey->adjacents[ time_interval ] = window; 
            }
        }

        while( true ){
            path = get_any_available_path( source , destiny );
            if( path.size() > 0 ){
                fill_path(path);
            } else break;
        }

        // Checking if completed
        bool completed = true;
        for( auto monkey : monkeys ){
            if( source->adjacents[monkey] > 0 ){
                completed = false;
                break;
            }
        }

        if( !completed ){
            cout << "Case " << case_number++ << ": No" << endl;
        }else{
            cout << "Case " << case_number++ << ": Yes" << endl;

            // Filling hours nodes. This took me a lot of time to realize what was going wrong.
            // This would be a new flux problem, but this one is particularly easy:
            // we know that it has an answer and it is complete , so we can easily 
            // fill the hours nodes of the interval between the monkeys of this interval.
            // We should give priority to the monkeys that drinks more in this interval AND 
            // also fill the more available hour node too. 
            for( auto time_interval : time_intervals ){
                vector<Monkey*> monkeys_in_this_interval;
                for( auto monkey : monkeys ){
                    if( time_interval->adjacents[monkey] != 0 ){
                        monkeys_in_this_interval.push_back(monkey);
                    }
                    
                }
                
                int hour_it = time_interval->time_window.first;
                
                for( auto monkey : monkeys_in_this_interval ){
                    int drinks_left_for_this_interval = time_interval->adjacents[monkey];
                    while( drinks_left_for_this_interval > 0 ){
                        Hour* hour = hours[ hour_it ];
                        hour->drink_times_available --;
                        drinks_left_for_this_interval--;
                        monkey->hours_used.push_back(hour_it);
                        hour_it = (hour_it+1);
                        if( hour_it >= time_interval->time_window.second ){
                            hour_it = time_interval->time_window.first;
                        }
                    }
                    if( drinks_left_for_this_interval > 0 ) cout << ":(" << endl;
                }
            }

            for( auto monkey : monkeys ){
                auto intervals = get_monkey_drink_intervals(monkey);
                cout << intervals.size();
                for( auto interval : intervals ){
                    cout << " (" << interval.first << "," << interval.second + 1 << ")";
                }
                cout << endl;
            }
        }

        delete source;
        delete destiny;
        for( auto n : monkeys ) delete n;
        for( auto n : hours ) delete n;
        for( auto n : time_intervals ) delete n;
    }
}