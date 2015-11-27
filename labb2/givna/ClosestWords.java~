/* Labb 2 i DD1352 Algoritmer, datastrukturer och komplexitet    */
/* Se labbanvisning under kurswebben https://www.kth.se/social/course/DD1352 */
/* Ursprunglig författare: Viggo Kann KTH viggo@nada.kth.se      */
import java.util.LinkedList;
import java.util.List;

public class ClosestWords {
  LinkedList<String> closestWords = null;

  int closestDistance = -1;
  int [][] partDistMatrix = new int [40][40];
  String previousWord = "";
  
  int partDistI(String w1, String w2, int w1len, int w2len) {
      int p;
      for (p = 0; p < Math.min(previousWord.length(), w2.length()); p++) {
          if (previousWord.charAt(p) != w2.charAt(p)) {
              break;
          }
      }
      for(int i = p + 1; i < w2len + 1; i++) {
          for(int j = 1; j < w1len + 1; j++) {
              partDistMatrix[i][j] = partDistMatrix[i - 1][j - 1] + 
	          (w1.charAt(j - 1) == w2.charAt(i - 1) ? 0 : 1);
              if (partDistMatrix[i - 1][j] + 1 < partDistMatrix[i][j]) {
                  partDistMatrix[i][j] = partDistMatrix[i - 1][j] + 1;
              }
              if (partDistMatrix[i][j - 1] + 1 < partDistMatrix[i][j]) {
                  partDistMatrix[i][j] = partDistMatrix[i][j - 1] + 1;
              }
          }
      }
      previousWord = w2;
      return partDistMatrix[w2len][w1len];
  }

  int Distance(String w1, String w2) {
    return partDistI(w1, w2, w1.length(), w2.length());
  }

  public ClosestWords(String w, List<String> wordList) {
    //Optimera detta!
    for (int i = 0; i < 40; i++) {
        partDistMatrix[i][0] = i;
    }
    for (int j = 0; j < 40; j++) {
        partDistMatrix[0][j] = j;
    }
    for (String s : wordList) {
      int dist = Distance(w, s);
      /*for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            System.out.print(partDistMatrix[i][j] + " ");
        }
        System.out.print("\n");
      }*/
      // System.out.println("d(" + w + "," + s + ")=" + dist);
      if (dist < closestDistance || closestDistance == -1) {
        closestDistance = dist;
        closestWords = new LinkedList<String>();
        closestWords.add(s);
      }
      else if (dist == closestDistance)
        closestWords.add(s);
    }
  }

  int getMinDistance() {
    return closestDistance;
  }

  List<String> getClosestWords() {
    return closestWords;
  }
}
