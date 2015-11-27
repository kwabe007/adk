/* Labb 2 i DD1352 Algoritmer, datastrukturer och komplexitet    */
/* Se labbanvisning under kurswebben https://www.kth.se/social/course/DD1352 */
/* Ursprunglig författare: Viggo Kann KTH viggo@nada.kth.se      */
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.List;

public class test {

    static int [][] partDistMatrix;
    static int [][] oldPartDistMatrix;
    static int [][] zeroMatrix = new int [40][40];
  
	public static void main(String args[]) throws IOException {	  
	    long t1 = System.currentTimeMillis();
	    
	    int [][] partDistMatrix = int[40][40];
	    
	    for(int i = 0; i < 1000000; i++) {
	        partDistMatrix = int [10][10];
	        
	        /*for (int j = 0; j < 40; j++) {
                System.arraycopy(zeroMatrix[j], 0, partDistMatrix[j], 0, 40);
            }*/
	    }

        long tottime = (System.currentTimeMillis() - t1);
        System.out.println("CPU time: " + tottime + " ms");
	}
}



