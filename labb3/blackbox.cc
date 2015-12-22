#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>
#include <unordered_set>
#include <limits.h>

using std::cin;
using std::cout;
using std::cerr;


class Edge;

struct Node {

    std::size_t index = 0;
    std::vector<Edge*> edge_ptr_vec;
    std::string get_str() const {
        return std::to_string(index);
    }
};

struct Edge {

    unsigned int capacity = 0;
    unsigned int flow = 0;
    Node* from_node_ptr = nullptr;
    Node* to_node_ptr = nullptr;

    Edge() {
    }

    Edge(Node* from, Node* to, unsigned int cap) {
        from_node_ptr = from;
        to_node_ptr = to;
        capacity = cap;
    }

    unsigned int get_capacity(Node* node) const {
        return capacity;
    }

    unsigned int get_rest_capacity(Node* node_ptr) const {
        if (node_ptr == from_node_ptr)
            return capacity-flow;
        if (node_ptr == to_node_ptr)
            return flow;
        throw std::invalid_argument("Non-matching node_ptr for getting rest capacity for edge " + get_str());
        return 0;
    }

    std::string get_str() const {
        if (from_node_ptr && to_node_ptr)
        return from_node_ptr->get_str() + "-" + to_node_ptr->get_str() + ":" + std::to_string(capacity);
        return "UNDEFINED";
    }

};

struct FlowGraph {
    unsigned int index_offset = 1;
    std::vector<Node> node_vec;
    std::vector<Edge> edge_vec;
    unsigned int source = 0;
    unsigned int target = 0;
    std::size_t edges = 0;

    FlowGraph(std::size_t size, std::istream& input_stream) : node_vec(size+index_offset) {
        for (std::size_t i = 0; i < node_vec.size(); ++i) {
            node_vec[i].index = i;
        }
        input_stream >> source >> target;
        input_stream >> edges;
        unsigned int index_from, index_to, cap;
        for (unsigned int i = 0; i < edges; ++i) {
            input_stream >> index_from >> index_to >> cap;
            setup_edge(index_from,index_to,cap);
        }
    }

    void setup_edge(unsigned int i_from, unsigned int i_to, unsigned int cap) {
        Node* node_from_ptr = &(node_vec[i_from]);
        Node* node_to_ptr = &(node_vec[i_to]);
        edge_vec.push_back(Edge(node_from_ptr, node_to_ptr, cap));
        node_from_ptr->edge_ptr_vec.push_back(&edge_vec.back());
        node_to_ptr->edge_ptr_vec.push_back(&edge_vec.back());
    }

    Node& operator [](std::size_t i) {
        if (i >= node_vec.size()) throw std::out_of_range("Can not access node_vec at pos " + std::to_string(i) + " vector size is " + std::to_string(node_vec.size()));
        return node_vec[i];
    }

    std::size_t get_edges() const {
        return edge_vec.size();
    }

    std::size_t get_nodes() const {
        return node_vec.size()-index_offset;
    }

    friend std::ostream& operator << (std::ostream& os, FlowGraph& flow);
};

struct Step {
    Step () {
    }
    Step (Node* nd) {
        current_node = nd;
    }
    Step (Node* fr_nd, Node* curr_nd, Edge* e) {
        from_node = fr_nd;
        current_node = curr_nd;
        edge = e;
    }

    Node* from_node = nullptr;
    Node* current_node = nullptr;
    Edge* edge = nullptr;
    bool shortest = false;
    Step* from = nullptr;
    unsigned int lowest_rest_capacity = UINT_MAX;

    Step new_step(Edge* edge) {
        Node* next_node = edge->to_node_ptr;
        Step step(current_node,edge->to_node_ptr,edge);
        return step;
    }
};

Step breadthFirst(FlowGraph& fg) {
    std::unordered_set<std::size_t> visited;
    std::vector<Step> steps(1,Step(&fg[fg.source]));
    return Step(nullptr);
}

void search(FlowGraph& fg) {
    std::vector<Step> steps;
}

std::ostream& operator << (std::ostream& os, FlowGraph& flow) {
    os << "Edges: " << flow.get_edges() << " Source: " << flow.source << " Target: " << flow.target << "\n";
    for (std::size_t i = 0; i < flow.edge_vec.size(); ++i) {
        os << flow.edge_vec[i].get_str() << "\n";
    }

    os << "Nodes: " << flow.get_nodes() << "\n";
    for (std::size_t i = flow.index_offset; i < flow.node_vec.size(); ++i) {
        os << flow.node_vec[i].get_str() << "\n";
    }
    return os;
}

/*FlowGraph readFlowFromFile(std::) {

}


FlowGraph readFlowFromFile(std::ifst) {

}*/


FlowGraph readFlowGraphFromStream(std::istream& input_stream) {
    std::size_t size;
    input_stream >> size;
    FlowGraph flow_graph(size, input_stream);
    return flow_graph;
}


int main(int argc, char* argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    //readFlowGraph(std::cin);
    FlowGraph flow_graph = readFlowGraphFromStream(std::cin);
    std::cout << flow_graph;
    //solveFlow();

    //writeFlow();

    return 0;
};

/*struct granne{
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

        while(!bfsQueue.empty()) {
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
        cerr << "\n";
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

*/
