#ifndef SOLVE_FLOW_HPP
#define SOLVE_FLOW_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>
#include <unordered_set>
#include <limits.h>
#include <list>
#include <ctime>
#include <sstream>
#include "debugmacro.hpp"


struct Vertex {

    std::size_t index = 0;
    std::list<std::size_t> edge_index_list;

    std::string get_str() const {
        return std::to_string(index);
    }
};

struct Edge {

    unsigned int capacity = 0;
    unsigned int flow = 0;
    std::size_t from_vertex_index = 0;
    std::size_t to_vertex_index = 0;

    Edge() {
    }

    Edge(std::size_t from, std::size_t to, unsigned int cap) {
        from_vertex_index = from;
        to_vertex_index = to;
        capacity = cap;
    }

    unsigned int get_capacity() const {
        return capacity;
    }

    void add_flow (std::size_t flow_to_add, std::size_t vertex_index) {
         if (flow_to_add > get_rest_capacity(vertex_index)) throw std::out_of_range("Can not add flow " + std::to_string(flow_to_add) + " to edge " + get_str());
         if (vertex_index == from_vertex_index) {
             flow += flow_to_add;
             return;
         }
         if (vertex_index == to_vertex_index) {
             flow -= flow_to_add;
             return;
         }
         throw std::invalid_argument("Non-matching vertex index " + std::to_string(vertex_index) + " for adding flow to edge " + get_str());
    }

    unsigned int get_rest_capacity(std::size_t vertex_index) const {
        if (vertex_index == from_vertex_index)
            return capacity-flow;
        if (vertex_index == to_vertex_index)
            return flow;
        throw std::invalid_argument("Non-matching vertex index " + std::to_string(vertex_index) + " for getting rest capacity for edge " + get_str());
        return 0;
    }

    std::string get_str() const {
        return std::to_string(from_vertex_index) + "-" + std::to_string(to_vertex_index) + ":[" + std::to_string(flow) + "/" + std::to_string(capacity) + "]";
    }

    std::size_t get_other_vertex_index(std::size_t index) const {
        if (index == from_vertex_index) return to_vertex_index;
        if (index == to_vertex_index) return from_vertex_index;
        throw std::invalid_argument("Trying to get other vertex from edge " + get_str() + " with vertex index " + std::to_string(index) + " but it is not connected to the edge");
        return index;
    }

};

struct FlowGraph {
    unsigned int index_offset = 1;
    std::vector<Vertex> vertex_vec;
    std::vector<Edge> edge_vec;
    unsigned int source = 0;
    unsigned int target = 0;
    std::size_t edges = 0;

    FlowGraph (const FlowGraph& ref )=delete;
    FlowGraph& operator=(const FlowGraph& ref)=delete;

    FlowGraph(std::size_t size, std::istream& input_stream) : vertex_vec(size+index_offset) {
        for (std::size_t i = 0; i < vertex_vec.size(); ++i) {
            vertex_vec[i].index = i;
        }
        input_stream >> source >> target;
        input_stream >> edges;
        debug_println(BIT0, "Flow graph Source: " << source << " Target: " << target << " Edges: " << edges);
        unsigned int index_from, index_to, cap;
        for (unsigned int i = 0; i < edges; ++i) {
            input_stream >> index_from >> index_to >> cap;
            debug_println(BIT0, "Index from: " << index_from << " Index to: " << index_to << " Capacity: " << cap);
            setup_edge(index_from,index_to,cap);
        }
    }

    void setup_edge(unsigned int i_from, unsigned int i_to, unsigned int cap) {
        Vertex& vertex_from = vertex_vec[i_from];
        Vertex& vertex_to = vertex_vec[i_to];
        edge_vec.emplace_back(Edge(i_from, i_to, cap));
        vertex_from.edge_index_list.push_back(edge_vec.size()-1);
        vertex_to.edge_index_list.push_back(edge_vec.size()-1);
    }

    void add_flow_to_edge(std::size_t edge_index, std::size_t flow, std::size_t from_vertex_index) {
        edge_vec[edge_index].add_flow(flow,from_vertex_index);
    }

    Vertex& operator [](std::size_t i) {
        if (i >= vertex_vec.size()) throw std::out_of_range("Can not access vertex_vec at pos " + std::to_string(i) + " vector size is " + std::to_string(vertex_vec.size()));
        return vertex_vec[i];
    }

    std::size_t get_edges() const {
        return edge_vec.size();
    }

    std::size_t get_vertices() const {
        return vertex_vec.size()-index_offset;
    }

    Vertex& get_first_vertex() {
        return vertex_vec[source];
    }

    Vertex& get_last_vertex() {
        return vertex_vec[target];
    }

    std::size_t get_total_flow() const {
        std::size_t total_flow = 0;
        for (std::size_t edge_index : vertex_vec[source].edge_index_list) {
            const Edge& edge = edge_vec[edge_index];
            total_flow += edge.flow;
        }
    return total_flow;
    }

    std::string to_str() const {
        std::string output;

        output += "Edges: " + std::to_string(get_edges()) + " Source: " + std::to_string(source) + " Target: " + std::to_string(target) + "\n";
        for (std::size_t i = 0; i < edge_vec.size(); ++i) {
            output += edge_vec[i].get_str() + "\n";
        }

        output += "Vertices: " + std::to_string(get_vertices());
        return output;
    }

    std::string to_bipart_matching(unsigned int x, unsigned int y) const {
        std::string output;
        std::size_t no_of_edges = 0;
        std::string edges_str;
        output += std::to_string(x) + " " + std::to_string(y) + "\n";

        for (const Edge& edge : edge_vec) {
            debug_println(BIT4,"Checking edge " << edge.get_str());
            if (edge.flow > 0 && ((edge.from_vertex_index != source && edge.to_vertex_index != source) && (edge.from_vertex_index != target && edge.to_vertex_index != target))) {
                edges_str += "\n" + std::to_string(edge.from_vertex_index) + " " + std::to_string(edge.to_vertex_index);
                ++no_of_edges;
            }

        }
        output += std::to_string(no_of_edges) + edges_str;
        return output;
    }

    friend std::ostream& operator << (std::ostream& os, const FlowGraph& flow);
};

std::ostream& operator << (std::ostream& os, const FlowGraph& flow) {

    os << flow.get_vertices() << "\n" << flow.source << " " << flow.target << " " << flow.get_total_flow() << "\n";
    std::size_t pos_edges = 0;
    std::string edges_str;
    for (const Edge& edge : flow.edge_vec) {
        if (edge.flow > 0) {
            edges_str += "\n" + std::to_string(edge.from_vertex_index) + " " + std::to_string(edge.to_vertex_index) + " " + std::to_string(edge.flow);
            ++pos_edges;
        }
    }
    os << pos_edges << edges_str;
    return os;
}

struct Step {

    Step () {

    }

    Step (std::size_t vertex_index) {
        current_vertex_index = vertex_index;
    }

    Step (Step* daddy, std::size_t edge_i, std::size_t vertex_i) {
        from_vertex_index = daddy->current_vertex_index;
        current_vertex_index = vertex_i;
        edge_index = edge_i;
        from = daddy;
    }

    std::size_t from_vertex_index = 0;
    std::size_t current_vertex_index = 0;
    std::size_t edge_index = 0;
    bool shortest = false;
    Step* from = nullptr;
    unsigned int lowest_rest_capacity = UINT_MAX;

    bool operator==(const Step& ref) const {
        return current_vertex_index == ref.current_vertex_index;
    }

    static std::string get_step_chain (Step* step) {
        if (step->from) return get_step_chain(step->from) + " " + std::to_string(step->current_vertex_index);
        return std::to_string(step->current_vertex_index);
    }
};

struct StepHasher {
  std::size_t operator()(const Step& s) const {
    using std::size_t;
    using std::hash;

    return s.current_vertex_index;
  }
};

FlowGraph* readFlowGraphFromStream(std::istream& input_stream) {
    std::size_t size;
    input_stream >> size;
    debug_println(BIT0, "Number of vertices read from flow graph: " << size);
    FlowGraph* flow_graph_ptr = new FlowGraph(size, input_stream);
    return flow_graph_ptr;
}

FlowGraph* readFromFile(std::string filename) {
    std::ifstream fs(filename);
    FlowGraph *flow_graph_ptr = readFlowGraphFromStream(fs);
    fs.close();
    return flow_graph_ptr;
}

FlowGraph* readFlowGraphFromStandardInput() {
    FlowGraph* flow_graph_ptr = readFlowGraphFromStream(std::cin);
    return flow_graph_ptr;
}

void apply_step(FlowGraph& fg, const Step* end_step) {
    debug_println(BIT3,"Checking rest capacities...");
    const Step* current_step = end_step;
    std::size_t lowest_rest_capacity = UINT_MAX;

    while (current_step->from) {
        Edge& edge = fg.edge_vec[current_step->edge_index];
        debug_println(BIT3,"Checking edge: " + edge.get_str());
        if (edge.get_rest_capacity(current_step->from_vertex_index) < lowest_rest_capacity) {
            lowest_rest_capacity = edge.get_rest_capacity(current_step->from_vertex_index);
            debug_println(BIT3,"Lowest rest capacity set to " + std::to_string(lowest_rest_capacity));
        }
        current_step = current_step->from;
    }
    debug_println(BIT3,"Done with rest capacity checking, lowest found: " + std::to_string(lowest_rest_capacity));

    debug_println(BIT3,"Applying flow");
    current_step = end_step;
    while (current_step->from) {
        Edge& edge = fg.edge_vec[current_step->edge_index];
        debug_println(BIT3,"Adding flow to edge " + edge.get_str());
        edge.add_flow(lowest_rest_capacity,current_step->from_vertex_index);
        current_step = current_step->from;
    }
    debug_println(BIT3,"Done adding flow! Current flow graph:");
    debug_println(BIT3,fg.to_str());
}

bool expand_step_into_list(FlowGraph& fg, Step* step, std::list<Step*>& queue, std::vector<Step>& visited) {
    std::size_t vertex_index = step->current_vertex_index;
    debug_println(BIT2,"Expanding vertex " << vertex_index << ", Edges: " << fg[vertex_index].edge_index_list.size());
    Vertex& current_vertex = fg.vertex_vec[vertex_index];
    debug_println(BIT2,"Going through edges... ");
    for(std::list<std::size_t>::const_iterator i = current_vertex.edge_index_list.begin(); i != current_vertex.edge_index_list.end(); ++i) {
        Edge& edge = fg.edge_vec[*i];
        debug_println(BIT2,"Checking edge " << edge.get_str());
        if (edge.get_rest_capacity(vertex_index) == 0) {
            debug_println(BIT2,"Edge restcapacity is zero, skipping edge...");
            continue;
        }
        std::size_t to_vertex_index = edge.get_other_vertex_index(vertex_index);
        if(visited[to_vertex_index].current_vertex_index != 0) {
            debug_println(BIT2,"Destination vertex " << to_vertex_index << " already in vector, skipping edge...");
            continue;
        }
        visited[to_vertex_index] = Step(step, *i, to_vertex_index);
        queue.emplace_back(&visited[to_vertex_index]);
        debug_println(BIT2,"New step emplaced in queue, index of current vertex: " << queue.back()->current_vertex_index);
        if (to_vertex_index == fg.target)
            return true;
    }
    return false;
}

bool breadth_first(FlowGraph& fg) {
    std::size_t vertices_searched = 1;
    debug_println(BIT1,"Started Breadth First search");
    std::vector<Step> visited(fg.vertex_vec.size());
    visited[fg.source] = Step(fg.source);
    std::list<Step*> queue;
    queue.emplace_back(&visited[fg.source]);
    bool path_found = false;

    debug_println(BIT1,"Constructed queue");
    while (!queue.empty()) {
        ++vertices_searched;
        Step* step = queue.front();
        if (expand_step_into_list(fg,step,queue,visited)) {
            debug_println(BIT1,"Found shortest path to target vertex " << queue.back()->current_vertex_index << ":");
            debug_println(BIT1, Step::get_step_chain(queue.back()));
            debug_println(BIT1,"Searched through " << vertices_searched << " vertices");
            path_found = true;
            break;
        }
        queue.pop_front();
    }
    if (path_found) apply_step(fg,queue.back());
    else debug_println(BIT1,"No path found");
    return path_found;
}

void edmund_karp(FlowGraph& fg) {
    while (breadth_first(fg)) {

    }
}

void search(FlowGraph& fg) {
    std::vector<Step> steps;
}

#endif

/*int main(int argc, char* argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    FlowGraph* flow_graph_ptr = readFlowGraphFromStream(std::cin);
    clock_t begin(clock());
    debug_println(BIT0,flow_graph_ptr->to_str());
    while (breadth_first(*flow_graph_ptr)) {

    }
    clock_t end = clock();
    std::cout << *flow_graph_ptr << std::endl;

    delete flow_graph_ptr;

    double elapsed_clocks = end - begin;
    debug_println(BIT7,"No of clocks: " << elapsed_clocks);
    return 0;
};*/


