#include <iostream>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::cerr;

struct granne{
    int self;
    int g;
    int c;
    int f;
    int cf;
    int p;
    granne * gp;
};

const int LIST_SIZE = 10001;
std::vector<granne *> * grannlista[LIST_SIZE];

int s, t;
void readFlowGraph() {
    for(int j = 0; j < LIST_SIZE; ++j) {
        grannlista[j] = new std::vector<granne>;
    }

    int v, e;
    cin >> v >> s >> t >> e;

    for (int i = 0; i < e; ++i) {
        //DET SISTA VI GJORDE VAR ATT ÄNDRA
        //granne * nyGranne = new granne;
        // ^^^^^
        //granne nyGranne;
        granne * nyGranne = new granne;

        cin >> nyGranne->self >> nyGranne->g >> nyGranne->c;
        nyGranne->cf = nyGranne->c;
        nyGranne->f = 0;
        nyGranne->p = -1;

        granne * inversGranne = new granne;
        inversGranne->self = nyGranne->g;
        inversGranne->g = nyGranne->self;
        inversGranne->c = nyGranne->c;
        inversGranne->cf = inversGranne->c;
        inversGranne->f = 0;
        inversGranne->p = -1;

        nyGranne->gp = inversGranne;
        inversGranne->gp = nyGranne;

        (*grannlista[nyGranne->self]).push_back(nyGranne);
        (*grannlista[nyGranne->g]).push_back(inversGranne);
    }
    for (int k = 0; k < e; ++k) {
        for (int l = 0; l < (*grannlista[k]).size(); ++l) {
            cerr << (*grannlista[k])[l].self << " " << (*grannlista[k])[l].g << "\n";
            cerr << "INVERS: " << (*grannlista[k])[l].gp->self << "\n";
        }
    }
}

std::queue<int> bfsQueue;
int visited[LIST_SIZE] = {0};
std::vector<int> stig;

int breathFirstSearch(int nod, int goal) {
    if (bfsQueue.size() > 0) {
        bfsQueue.pop();
    }

    for (int i = 0; i < (*grannlista[nod]).size(); i++) {
        cerr << (*grannlista[nod])[i].self << " " << (*grannlista[nod])[i].g << " " << (*grannlista[nod])[i].cf << "\n";
        if ((*grannlista[nod])[i].cf > 0 && !visited[(*grannlista[nod])[i].g]) {
            visited[(*grannlista[nod])[i].g] = 1;
            (*grannlista[nod])[i].p = nod;
            bfsQueue.push((*grannlista[nod])[i].g);

            cerr << "GODKÄND: " << (*grannlista[nod])[i].self << " " << (*grannlista[nod])[i].g << "\n";
            if((*grannlista[nod])[i].g == t) {
                stig.push_back(nod);
                return 1;
            }
        }
    }
    while (bfsQueue.size() > 0) {
        if (breathFirstSearch(bfsQueue.front(), t)) {
            stig.push_back(nod);
            return 1;
        }
    }
    return 0;
}

std::vector<granne *> stiglista;

int findMin() {
    int min_cf = LIST_SIZE;
    for (int i = 0; i < stiglista.size(); i++) {
        if ((*stiglista[i]).cf < min_cf) {
            min_cf = (*stiglista[i]).cf;
        }
    }
    return min_cf;
}

void solveFlow() {
    stig.push_back(t);
    visited[s] = 1;
    cerr << "BFS KLAR: " << breathFirstSearch(s, t) << "\n";

    cerr << stig[0] << " ";
    for (int i = 1; i < stig.size(); i++) {
        cerr << stig[i] << " ";
        stiglista.push_back(&((*grannlista[i])[i - 1]));
    }
    cerr << "\n";

    while (stig.size() > 1) {
        int r = findMin();
        for (int i = 0; i < stiglista.size(); i++) {
            stiglista[i]->f = stiglista[i]->f + r;
            stiglista[i]->gp->f = -(stiglista[i]->f);
            cerr << "ändrade " << stiglista[i]->gp->self << "\n";

            stiglista[i]->cf = (stiglista[i]->c) - (stiglista[i]->f);
            stiglista[i]->gp->cf = (stiglista[i]->gp->c) - (stiglista[i]->gp->f);
            break;
        }

        /*while(!bfsQueue.empty()) {
            bfsQueue.pop();
        }
        for(int i = 0; i < LIST_SIZE; i++) {
            visited[i] = 0;
        }
        while(!stig.empty()) {
            stig.pop_back();
        }
        while(!stiglista.empty()) {
            stiglista.pop_back();
        }

        stig.push_back(t);
        visited[s] = 1;
        cerr << "BFS KLAR: " << breathFirstSearch(s, t) << "\n";

        for (int i = 1; i < stig.size(); i++) {
            cerr << stig[i] << " ";
            stiglista.push_back(&((*grannlista[i])[i - 1]));
        }
        cerr << "\n";*/
        break;
    }


}

void writeFlow() {
    cout << s << " " << t << "\n";
    for(int i = 0; i < LIST_SIZE; i++) {
        for (int j = 0; j < (*grannlista[i]).size(); j++) {
            cout << (*grannlista[i])[j].self << " " << (*grannlista[i])[j].g << " " << (*grannlista[i])[j].f << "\n";
        }
    }
}

int main(void) {
    std::ios::sync_with_stdio(false);
    cin.tie(0);

    readFlowGraph();

    solveFlow();

    writeFlow();

    return 0;
}
