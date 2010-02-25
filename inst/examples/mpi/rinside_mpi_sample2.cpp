// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4;  tab-width: 8; -*-
//
// Simple example showing in R console information about current node
//
// MPI C++ API version of file contributed by Jianping Hua 

#include "mpi.h"     // mpi header
#include "RInside.h" // for the embedded R via RInside
#include "Rcpp.h"    // for the R / Cpp interface used for transfer

int main(int argc, char *argv[]) {

    MPI::Init(argc, argv);                      // mpi initialization
    int myrank = MPI::COMM_WORLD.Get_rank();    // obtain current node rank
    int nodesize = MPI::COMM_WORLD.Get_size();  // obtain total nodes running.

    RInside R(argc, argv);              	// create an embedded R instance

    std::stringstream txt;
    txt << "Hello from node " << myrank       	// node information
        << " of " << nodesize << " nodes!" << std::endl;
    R.assign( txt.str(), "txt");              	// assign string var to R variable 'txt'

    std::string evalstr = "cat(txt)"; 		// show node information
    R.parseEvalQ(evalstr);            		// eval the init string, ignoring any returns

    MPI::Finalize();  		  		// mpi finalization

    exit(0);
}
