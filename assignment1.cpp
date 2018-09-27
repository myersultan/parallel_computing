# include <cmath>
# include <mpi.h>

using namespace std;

void doTask ( int n, int id, int p) {
  
  	int mf = floor(n/p);
  	int from = 2 + id * mf;
  	int to = from + mf - 1;

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
	MPI_Init ( &argc, &argv );
	MPI_Comm_size ( MPI_COMM_WORLD, &p );
	MPI_Comm_rank ( MPI_COMM_WORLD, &id );
	
	doTask(n, id, p);

	MPI_Finalize ( );

	return 0;
}