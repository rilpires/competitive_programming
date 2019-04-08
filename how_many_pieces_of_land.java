/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
        https://uva.onlinejudge.org/external/102/p10213.pdf
*/

import java.math.BigInteger;
import java.util.Scanner;
import java.io.*;


class Main{
    public static void main( String args[] ){
        try{
            
            //Scanner input_scanner  = new Scanner( new File("entrada.txt") );
            //PrintWriter output_writer = new PrintWriter( new File("saida.txt") );
            
            Scanner input_scanner  = new Scanner( System.in );
            PrintWriter output_writer = new PrintWriter( System.out );
            
            BigInteger one = new BigInteger("1");
            BigInteger two = new BigInteger("2");
            BigInteger three = new BigInteger("3");
            BigInteger four = new BigInteger("4");
            
            long T = input_scanner.nextInt();
            for( long t = 0 ; t < T ; t++ ){
                BigInteger N = input_scanner.nextBigInteger();
                BigInteger number_edges = N.multiply(N.subtract(three)).divide(two);
                BigInteger number_intersections = N.multiply(Sn(N.subtract(two))).divide(four); 
                BigInteger result = one.add(N).add( number_edges ).add(number_intersections);

                output_writer.println( result );
            }

            input_scanner.close();
            output_writer.close();
        }catch(Exception e){
            System.err.println("Error: " + e);
        }
    }

    public static BigInteger Sn( BigInteger N ){
        BigInteger one = new BigInteger("1");
        BigInteger six = new BigInteger("6");
        return N.multiply( N.subtract(one) ).multiply( N.add(one) ).divide( six );
    }

}

