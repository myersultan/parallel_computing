#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<ctime>
using namespace std;

int main (int argc, char** argv) {

	MPI_Init(NULL, NULL);
	int id, njumps = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	int ntasks;
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
	int rnd;
	int token = -1;
	int id_send = 0;
	int id_recv = 1;

	int send_recv_trials[3] = { id_send, id_recv, njumps };

	while (id_recv < ntasks) {
		if (id == 0) {
			cout << "sender = " << id_send << "send to receiver = " << id_recv << "\n";
		}

		if (id == id_send) {
			MPI_Send(&token, 1, MPI_INT, id_recv, 99, MPI_COMM_WORLD);
			
		}

		if (id == id_recv) {
			MPI_Recv(&token, 1, MPI_INT, id_send, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}

		if (id == 0) {
			// srand ( time(NULL) );
			rnd = rand() % 2;
			cout << "rnd = " << rnd << "\n";

			njumps++;

			id_send = id_recv;

			if (rnd == 0 && id_send != 0) {
				id_recv = id_send - 1;
			} else {
				id_recv = id_send + 1;
			}

			send_recv_trials[0] = id_send;
			send_recv_trials[1] = id_recv;
			send_recv_trials[2] = njumps;
		}

		MPI_Bcast(&send_recv_trials, 3, MPI_INT, 0, MPI_COMM_WORLD);

		id_send = send_recv_trials[0];
		id_recv = send_recv_trials[1];
		njumps = send_recv_trials[2];

	}

	MPI_Finalize();

	if (id == 0) {
		cout << "njumps = " << njumps << "\n";
	}

}