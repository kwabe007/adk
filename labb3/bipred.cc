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
#include "solveflow.hpp"

using std::cin;
using std::cout;
using std::cerr;

const int LIST_SIZE = 10001;
std::vector<int> * grannlista[LIST_SIZE];
std::ofstream ERR_FS("log");
unsigned int GLOBAL_DEBUG_BITS = 0b10010001;

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


FlowGraph* writeFlowGraph() {
    int X = (*grannlista[0])[0], Y = (*grannlista[0])[1];
    int v = X + Y + 2, e = (*grannlista[0])[2];
    int s = X + Y + 1, t = X + Y + 2;

    std::stringstream ss;

    // Skriv ut antal hörn och kanter samt källa och sänka
    ss << v << "\n" << s << " " << t << "\n" << e + (X + Y) << "\n";
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
        ss << u << " " << v << " " << c << "\n";
        //cerr << u << " " << v << " " << c << "\n";
    }

    for (int i = 1; i <= X; ++i) {
        ss << s << " " << i << " " << 1 << "\n";
        //cerr << s << " " << i << " " << 1 << "\n";
    }

    for (int i = X + 1; i <= X + Y; ++i) {
        ss << i << " " << t << " " << 1 << "\n";
        //cerr << i << " " << t << " " << 1 << "\n";
    }

    // Var noggrann med att flusha utdata när flödesgrafen skrivits ut!
    ss.flush();

    FlowGraph* fg_ptr = readFlowGraphFromStream(ss);

    // Debug-utskrift
    debug_println(BIT0,"Flowgraph sent to be read by solveflow\n");
    return fg_ptr;
}

std::vector<int*> nodepair;
int flow;

void readMaxFlowSolution(FlowGraph* fg_ptr) {

    edmund_karp(*fg_ptr);
}


void writeBipMatchSolution(FlowGraph* fg_ptr) {
    std::cout << fg_ptr->to_bipart_matching(grannlista[0]->at(0),grannlista[0]->at(1)) << std::endl;
}


int main(void) {
    // Två trick för att göra cin/cout lite snabbare.
    // Se http://kattis.csc.kth.se/doc/iostreamio
    std::ios::sync_with_stdio(false);
    cin.tie(0);

    readBipartiteGraph();

    FlowGraph* fg_ptr = writeFlowGraph();

    readMaxFlowSolution(fg_ptr);

    writeBipMatchSolution(fg_ptr);

    // debugutskrift
    cerr << "Bipred avslutar\n";
    delete fg_ptr;
    return 0;
}
