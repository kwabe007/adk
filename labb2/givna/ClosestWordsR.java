/* Labb 2 i DD1352 Algoritmer, datastrukturer och komplexitet    */
/* Se labbanvisning under kurswebben https://www.kth.se/social/course/DD1352 */
/* Ursprunglig författare: Viggo Kann KTH viggo@nada.kth.se      */
import java.util.LinkedList;
import java.util.List;

public class ClosestWords {
  LinkedList<String> closestWords = null;

  int closestDistance = -1;
  int [][] partDistMatrix = new int [1][1];
  int [][] oldPartDistMatrix;
  String previousWord = "";
  
  int partDistLookUp(String w1, String w2, int w1len, int w2len) {
    if (partDistMatrix[w1len][w2len] == 0) {
        partDistMatrix[w1len][w2len] = partDist(w1, w2, w1len, w2len);
    }
    return partDistMatrix[w1len][w2len];
  }

  int partDist(String w1, String w2, int w1len, int w2len) {
    if (w1len == 0)
      return w2len;
    if (w2len == 0)
      return w1len;
    int res = partDistLookUp(w1, w2, w1len - 1, w2len - 1) + 
	(w1.charAt(w1len - 1) == w2.charAt(w2len - 1) ? 0 : 1);
    int addLetter = partDistLookUp(w1, w2, w1len - 1, w2len) + 1;
    if (addLetter < res)
      res = addLetter;
    int deleteLetter = partDistLookUp(w1, w2, w1len, w2len - 1) + 1;
    if (deleteLetter < res)
      res = deleteLetter;
    return res;
  }
  
  /*int partDistI(String w1, String w2, int w1len, int w2len) {
      for(int i = p + 1; i < w2len; i++) {
          for(int j = 1; j < w1len; j++) {
              partDistMatrix[i][j] = partDistMatrix[i - 1][j - 1] + 
	          (w1.charAt(i - 1) == w2.charAt(j - 1) ? 0 : 1);
              if (partDistMatrix[i - 1][j] + 1 < partDistMatrix[i][j]) {
                  partDistMatrix[i][j] = partDistMatrix[i - 1][j] + 1;
              }
              if (partDistMatrix[i][j - 1] + 1 < partDistMatrix[i][j] {
                  partDistMatrix[i][j] = partDistMatrix[i][j - 1] + 1;
              }
          }
      }
  }*/

  int Distance(String w1, String w2) {
    int p;
    for (p = 0; p < Math.min(previousWord.length(), w2.length()); p++) {
        if (previousWord.charAt(p) != w2.charAt(p)) {
            break;
        }
    }
    //System.out.printf("%d %s %s %s\n", p, previousWord, w2, w1);
    
    oldPartDistMatrix = partDistMatrix;
    partDistMatrix = new int [w1.length() + 1][w2.length() + 1];
    
    for (int j = 0; j < Math.min(previousWord.length() + 1, w1.length() + 1); j++) {
        System.arraycopy(oldPartDistMatrix[j], 0, partDistMatrix[j], 0, p + 1);
    }
    /*for (int i = 0; i < w1.length() + 1; i++) {
        for (int k = 0; k < w2.length() + 1; k++) {
            System.out.print(partDistMatrix[i][k] + " ");
        }
        System.out.print("\n");
    }*/
    //System.out.print("^COPY \n");
    previousWord = w2;
    return partDist(w1, w2, w1.length(), w2.length());
  }

  public ClosestWords(String w, List<String> wordList) {
    for (String s : wordList) {
      int dist = Distance(w, s);
      /*for (int i = 0; i < w.length() + 1; i++) {
        for (int j = 0; j < s.length() + 1; j++) {
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
