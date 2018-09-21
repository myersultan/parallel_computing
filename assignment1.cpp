# include <cmath>
# include <mpi.h>

using namespace std;

void doTask ( int n, int id, int p) {
  
  	int mf = floor(n/p);
  	int from = 2 + id * mf;
  	int to = id * mf + mf + 1;

  	if (id == 3)
       	to++;

    cout << "id: " << id << " -> ";

    for (int i = from; i <= to; i++) {
    	cout << i << " " ;
    }

    cout << "\n";
    	 
}

int main ( int argc, char *argv[] ) {
	int id, p;
	int n = 10;
	int ierr = MPI_Init ( &argc, &argv );
	ierr = MPI_Comm_size ( MPI_COMM_WORLD, &p );
	ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &id );
	ierr = MPI_Bcast ( &n, 1, MPI_INT, 0, MPI_COMM_WORLD );
	doTask(n, id, p);

	MPI_Finalize ( );

	return 0;
}