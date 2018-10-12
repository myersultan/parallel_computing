// #include <stdafx.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<ctime>
using namespace std;

int main(int argc, char** argv) {
	
	

	MPI_Init(NULL, NULL);
	int id, ntrials = 50000, c_ounter = 0;;
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	int ntasks;
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
	int token = -1; // Значение передаваемого тоукена -1
	int id_send = 0;
	int id_recv = id_send;
	int GatheredData[ntasks] = {0};
	srand ( time(NULL) );
	while (id_recv == id_send) {id_recv = rand() % ntasks;}

	int send_recv_trials[3] = { id_send, id_recv, ntrials };
	while (ntrials > 0){
		// Проверка последовательности передачи тоукена между случайными партнерами :)
		if (id == 0){
		 // cout << "id_send = " << id_send << " send to id_recv = " << id_recv << "\n"; 
		}

		// Прием-передача осуществляются только между процессами выбранными процессом с id=0
		if (id == id_send) {
			MPI_Send(&token, 1, MPI_INT, id_recv, 99, MPI_COMM_WORLD);
			c_ounter++;
			 // MPI_Gather(&c_ounter, 1, MPI_INT, GatheredData, 1, MPI_INT, 0, MPI_COMM_WORLD);
		}
		if (id == id_recv) {
			MPI_Recv(&token, 1, MPI_INT, id_send, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);}
		
		if(id==0){
			// уменьшаем счетчик количества актов передачи на 1. 
			ntrials--;
			// Процесс принявший мяч (тоукен), становится теперь передающим
			id_send = id_recv;
			// случайным образом выбираем процесс принимающий тоукен
			srand ( time(NULL) );
			while (id_recv == id_send) { id_recv = rand() % ntasks; }
			send_recv_trials[0]=id_send;
			send_recv_trials[1]=id_recv;
			send_recv_trials[2]=ntrials;
		}
		// делаем информацию доступной всем процессом с помощью рассылки от id=0. это blocking communications!
		MPI_Bcast(&send_recv_trials, 3, MPI_INT, 0, MPI_COMM_WORLD);

		id_send = send_recv_trials[0];
		id_recv = send_recv_trials[1];
		ntrials = send_recv_trials[2];

	}

	MPI_Barrier(MPI_COMM_WORLD);
	cout << "\n" <<id<<", counter="<<c_ounter<< "\n";

	MPI_Gather(&c_ounter, 1, MPI_INT, GatheredData, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	
	MPI_Finalize();

	if(id==0) {
			// for(int i = 0; i < 4; i++) {
			// 	cout << "GatheredData[" << i << "] is: " << GatheredData[i] << endl;
			// }
			int i;
			cout << "GatheredData [";
			for(i = 0; i < ntasks-1; i++) {
				cout << GatheredData[i] << ", " ;
			}
			cout << GatheredData[i] << "]" << endl;
		}
}