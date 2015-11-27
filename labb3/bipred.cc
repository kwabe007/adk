/**
 * Exempel på in- och utdatahantering för maxflödeslabben i kursen
 * ADK.
 *
 * Använder iostreams i C++.
 * Anmärkning: scanf/printf-rutinerna från C-exemplet går att använda
 * även i C++ och är ofta märkbart snabbare än cin/cout som det här
 * programmet använder.
 *
 * Author: Per Austrin
 */

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;

const int LIST_SIZE = 10001;
std::vector<int> * grannlista[LIST_SIZE];

int s_i = 0, t_i = 0;

void readBipartiteGraph() {
    for(int j = 0; j < LIST_SIZE; ++j) {
        grannlista[j] = new std::vector<int>;
    }

    int x, y, e;
    // Läs antal hörn och kanter
    cin >> x >> y >> e;
    s_i = x;
    t_i = y;

    (*grannlista[0]).push_back(x);
    (*grannlista[0]).push_back(y);
    (*grannlista[0]).push_back(e);

    // Läs in kanterna
    for (int i = 0; i < e; ++i) {
        int a, b;
        cin >> a >> b;

        (*grannlista[a]).push_back(b);
    }
    cerr << "GRANNLISTA KLAR\n";
}


void writeFlowGraph() {
    int X = (*grannlista[0])[0], Y = (*grannlista[0])[1];
    int v = X + Y + 2, e = (*grannlista[0])[2];
    int s = X + Y + 1, t = X + Y + 2;

    // Skriv ut antal hörn och kanter samt källa och sänka
    cout << v << "\n" << s << " " << t << "\n" << e + (X + Y) << "\n";
    //cerr << v << "\n" << s << " " << t << "\n" << e + (X + Y) << "\n";

    int j = 1;
    for (int i = 0; i < e; ++i) {
        while((*grannlista[j]).empty()) {
            j++;
        }
        int u = j, v = (*grannlista[j]).back();
        int c = 1;

        (*grannlista[j]).pop_back();
        // Kant från u till v med kapacitet c
        cout << u << " " << v << " " << c << "\n";
        //cerr << u << " " << v << " " << c << "\n";
    }
    for (int i = 1; i <= X; ++i) {
        cout << s << " " << i << " " << 1 << "\n";
        //cerr << s << " " << i << " " << 1 << "\n";
    }
    for (int i = X + 1; i <= X + Y; ++i) {
        cout << i << " " << t << " " << 1 << "\n";
        //cerr << i << " " << t << " " << 1 << "\n";
    }
    // Var noggrann med att flusha utdata när flödesgrafen skrivits ut!
    cout.flush();

    // Debugutskrift
    cerr << "Skickade iväg flödesgrafen\n";
}

std::vector<int*> nodepair;
int flow;

void readMaxFlowSolution() {
    int v, e, s, t, f;

    // Läs in antal hörn, kanter, källa, sänka, och totalt flöde
    // (Antal hörn, källa och sänka borde vara samma som vi i grafen vi
    // skickade iväg)
    cin >> v >> s >> t >> f >> e;
    //cerr << v << "\n";
    //cerr << s << " " << t << " " << f << "\n";
    //cerr << e << "\n";
    flow = f;

    for (int i = 0; i < e; ++i) {
        int u, v, f;
        // Flöde f från u till v
        cin >> u >> v >> f;
        //cerr << u << " " << v << " " << f << "\n";
        if(u == s | v == t) {
            //NOP
        }
        else if(f <= 1) {
            int * lista = new int[3];
            lista[0] = u;
            lista[1] = v;
            lista[2] = f;
            nodepair.push_back(lista);
        } else {
            i--;
        }
    }
    cerr << "Läste flödesproblemlösningen\n";
}


void writeBipMatchSolution() {
    cout << s_i << " " << t_i << "\n" << flow << "\n";
    while(!nodepair.empty()) {
        cout << nodepair.back()[0] << " " << nodepair.back()[1] << "\n";
        nodepair.pop_back();
    }
}


int main(void) {
    // Två trick för att göra cin/cout lite snabbare.
    // Se http://kattis.csc.kth.se/doc/iostreamio
    std::ios::sync_with_stdio(false);
    cin.tie(0);

    readBipartiteGraph();

    writeFlowGraph();

    readMaxFlowSolution();

    writeBipMatchSolution();

    // debugutskrift
    cerr << "Bipred avslutar\n";
    return 0;
}
