/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/105/p10541.pdf
        
*/


import java.math.BigInteger;
import java.util.Scanner;
import java.io.*;


class Main{
    public static void main( String args[] ){
        try{
            
            //==========Don't forget to comment input/output from file============
            //Scanner input_scanner  = new Scanner( new File("entrada.txt") );
            //PrintWriter output_writer = new PrintWriter( new File("saida.txt") );
            Scanner input_scanner  = new Scanner( System.in );
            PrintWriter output_writer = new PrintWriter( System.out );
            
            int T,N,K,tam;
            T = input_scanner.nextInt();
            for( int t = 0 ; t<T ; t++ ){
                N = input_scanner.nextInt();
                K = input_scanner.nextInt();

                int espaco_livre = N;
                for( int k = 0 ; k < K ; k++ ){
                    tam = input_scanner.nextInt();
                    espaco_livre -= tam;
                }
                if( espaco_livre + 1 - K < 0 ) 
                    output_writer.println( 0 );
                else if( espaco_livre + 1 - K == 0 || K == 0) 
                    output_writer.println( 1 );
                else
                    output_writer.println( nCr( espaco_livre + 1 , K ) );
            }

            input_scanner.close();
            output_writer.close();
        }catch(Exception e){
            System.err.println("Error: " + e);
        }
    }

    public static BigInteger nCr( int N , int K ){
        if( K < N/2 ) K = N - K;
        return permutation(N, K).divide( factorial(N-K) );
    }
    public static BigInteger permutation( int N , int K ){
        BigInteger ret = BigInteger.valueOf(N);
        for( int n = N-1 ; n > K ; n-- ){
            ret = ret.multiply(BigInteger.valueOf(n));
        }
        return ret;
    }
    public static BigInteger factorial( int N ){
        if(N<=1)return BigInteger.valueOf(1);
        BigInteger ret = BigInteger.valueOf(N);
        for( int n = N-1 ; n >= 1 ; n-- ){
            ret = ret.multiply(BigInteger.valueOf(n));
        }
        return ret;
    }
    

}

