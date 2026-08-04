#include <iostream>
#include <iomanip>
#include "csr_graph.hpp"
#include "timer.hpp"

using namespace std;

static void printCSRSummary(const CSRGraph& g){
    cout << "- \n";
    cout << CSR GRAPH SUMMARY \n";
    cout << "- \n";
    cout << "Vertices: " g.num_vertices << "\n";
    cout << "Edges : " << g.num_edges << "\n";
    cout << "source : " << g.source_vertex << "\n";
    cout << "row_ptr size : " << g.row_ptr.size() << " (Expected: " << g.num_vertices + 1 << ")\n";
    cout << "col_idx size : " << g.col_idx.size() << "\n";
    cout << "values size  : " << g.values.size() << "\n\n";

 // PRINTING ELEMENTS FOR PREVIEW

cout << "row_ptr : ";
for(size_t i=0; i < min<size_t>(11, g.row_ptr.size()); ++i){
   cout << g.row_ptr[i] << " ";
  }
cout << "/n";

cout << "col_idx :";
for(size_t i=0; i < min<size_t>(10, g.col_idx.size()); ++i){
cout << g.col_idx[i] << " ";
   }

cout << "\n --             \n";

}


int main(int argc, char* argv[]){
   if(argc < 2){
        cerr<< "Usage :" << argv[0] << " <path to graph input file\n";
        return 1;
    }



string filepath = argv[1];
bool isWeighted = (argc >=3 && string(argv[2]) == "weighted");


try {
    Timer timer;

    timer.start();
    CSRGraph graph = isWeighted ? readWeightedGraphToCSR(filepath): readUnweightedGraphToCSR(filepath);

    timer.stop();

    printCSRSummary(graph);
    cout << fixed << setprecision(4);
    cout << "CSR Data structure built  sucessfully\n";

}

catch (const exception& e){
    cerr << "Error : " << e.what() << "\n";
    returen 1;
}

return 0;

}

