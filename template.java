/*
    Made by: Romeu I. L. Pires
    for "Special topics in programming" course
    in UFRJ (Universidade Federal do Rio de Janeiro),
    on 2019.1 semester

    - Problem PDF:
*/

import java.math.BigInteger;
import java.util.Scanner;
import java.io.*;


class Main{
    public static void main( String args[] ){
        try{
            
            //==========Don't forget to comment input/output from file============
            Scanner input_scanner  = new Scanner( new File("entrada.txt") );
            PrintWriter output_writer = new PrintWriter( new File("saida.txt") );
            //Scanner input_scanner  = new Scanner( System.in );
            //PrintWriter output_writer = new PrintWriter( System.out );
               
            while( input_scanner.hasNext() ){
            }

            input_scanner.close();
            output_writer.close();
        }catch(Exception e){
            System.err.println("Error: " + e);
        }
    }
}