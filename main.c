#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

enum { 
    N = 1024,
    NREPS = 5
};

double A[N * N], B[N * N], C[N * N];

void dgemm_def(double *a, double *b, double *c, int n)
{
    int i, j, k;
    
    for (i = 0; i < n; i++) {
        for (k = 0; k < n; k++) {
            for (j = 0; j < n; j++) {
                *(c + i * n + j) += *(a + i * n + k) * *(b + k * n + j);
			}
		}
	}
}

void dgemm_parallel(double *a, double *b, double *c, int n, int st, int fn)
{
    int i, j, k;
    
    for (i = st; i < fn; i++) {
        for (k = 0; k < n; k++) {
            for (j = 0; j < n; j++) {
                *(c + i * n + j) += *(a + i * n + k) * *(b + k * n + j);
			}
		}
	}
}

void init_matrix(double *a, double *b, double *c, int n)
{
	int i, j, k;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
                *(a + i * n + j) = 1.0;
                *(b + i * n + j) = 2.0;
                *(c + i * n + j) = 0.0;
			}
		}
	}
}

void printMatrix(double *a, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%.2lf ", *(a + i * n + j));
		}
		printf("\n");
	}
	printf("\n");
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);

	double t;

	int rank;
	int size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
    int st = (N / size) * rank;
    int fn = ((rank + 1) == size) ? N : (st + (N / size));

    double t_all[size];

    init_matrix(A, B, C, N);



    t -= wtime();

    for (int i = 0; i < NREPS; i++) {
        dgemm_parallel(A, B, C, N, st, fn);
    }

    t += wtime();
    t /= NREPS;

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank != 0) {
        MPI_Send(C + (st * N), (fn - st) * N, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Status status;
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            int st_loc = (N / size) * i;
            int fn_loc = ((i + 1) == size) ? N : (st_loc + (N / size));
            MPI_Recv(C + (st_loc * N), (fn_loc - st_loc) * N, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank != 0) {
        MPI_Send(&t, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Recv(&t_all[i], 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
        }
    }

    if (rank == 0) {
        t_all[0] = t;
    }

    double max = -1;
    for (int i = 0; i < size; i++) {
        if (t_all[i] > max) {
            max = t_all[i];
        }
    }
    if (rank == 0) {
        printf("time = %.6f\n", max);
    }

	MPI_Finalize();
    free(A);
    free(B);
    free(C);

	return 0;
}