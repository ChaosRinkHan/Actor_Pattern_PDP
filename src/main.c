#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/actorCode.h"
#include "../include/master.h"
#include "../include/utility.h"
#include "../lib/actor.h"
#include "../lib/pool.h"

int main(int argc, char *argv[]) {
	MPI_Init(&argc, &argv);
	int statusCode = processPoolInit();
//	void *buf;
//	buf = malloc((sizeof(int) + MPI_BSEND_OVERHEAD) * 200);
//	MPI_Buffer_attach(&buf, (sizeof(int) + MPI_BSEND_OVERHEAD) * 200);

	// Read parameters from file.
	int initN, Ncell, maxN, initInfection, timeAll;
	if (inputCheck(argc) == 0) {
		printf("Check input\nUsage: ./model [input parameter files]\n");
		return 0;
	} else {
		readPara(&initN, &Ncell, &maxN, &initInfection, &timeAll, argv);
	}

	// Actor pattern
	// Actor
	if (statusCode == 1) {
		actorCode(initN, Ncell, maxN, initInfection, timeAll);
	}
	// Master
	if (statusCode == 2) {
		masterSimulationInit(initN, Ncell, initInfection, timeAll, maxN);
		masterWait();
		printf("\t\tMASTER finished\n");
		// shutdownPool();
	}
//	int rank = actorGetID();
//	if (rank == 0) exit(0);
	processPoolFinalise();
	MPI_Finalize();
	return 0;
}
