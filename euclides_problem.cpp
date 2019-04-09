/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/101/p10104.pdf
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <stack>
using namespace std;


struct Euclides{
    long long A , X , B , Y , D;
    

    Euclides( long long _A , long long _B ){
        A = _A ; B = _B;
        if( A == B && A == 0 && B == 0 ){
            X = 1 ; Y = 0 ; D = 0;
            return;
        }
        if( A == 0 ){
            X = 0; Y = 1; D = B;
            return;
        }else if( B == 0 ){
            X = 1; Y = 0; D = A;
            return;
        }

        stack<long long> A_stack;
        stack<long long> B_stack;
        while( A % B != 0 ){
            A_stack.push(A); B_stack.push(B);
            long long temp = A;
            A = B;
            B = temp % B;
        }
        D = B;
        X = 0;
        Y = 1;
        while( !A_stack.empty() ){
            A = A_stack.top(); B = B_stack.top();
            A_stack.pop(); B_stack.pop();
            X = Y;
            Y = (D-A*X)/B;  
        }
        if( _A == _B && X > Y ){
            long long temp = Y; Y = X ; X = temp;
        }
    }
    

};

int main(){
    #ifndef ONLINE_JUDGE
    ifstream cin("entrada.txt");
    ofstream cout("saida.txt");
    #endif
    // ==========    
    long long A , B ;
    while( cin >> A >> B ){
        Euclides euc(A,B);
        cout << euc.X << " " << euc.Y << " " << euc.D << endl;
    }
}
