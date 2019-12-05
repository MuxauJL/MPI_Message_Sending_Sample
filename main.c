#include "mpi.h"
#include "stdio.h"

#define MAX_MESSAGE_BUFFER_SIZE 21

int main(int argc, char* argv[]) {
	const int TAG = 1;
	MPI_Init(&argc, &argv);
	int process_count;
	int process_rank;
	MPI_Comm_size(MPI_COMM_WORLD, &process_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

	char message[MAX_MESSAGE_BUFFER_SIZE] = "";
	if (process_rank > 0) {
		MPI_Status status;
		printf("Start message receiving in process %d\n", process_rank);
		MPI_Recv(message, MAX_MESSAGE_BUFFER_SIZE, MPI_CHAR,
			process_rank - 1, TAG,
			MPI_COMM_WORLD, &status);
		printf("End message receiving in process %d\n",
			process_rank);
		printf("Message in process %d from process %d: %s\n",
			process_rank, status.MPI_SOURCE, message);
	}
	if (process_rank + 1 < process_count) {
		if (process_rank == 0)
			strcpy(message, "hello from process 0");
		printf("Start message sending from process %d\n", process_rank);
		MPI_Send(message, strlen(message), MPI_CHAR,
			process_rank + 1, TAG, MPI_COMM_WORLD);
		printf("End message sending from process %d\n", process_rank);
	}
	MPI_Finalize();
}