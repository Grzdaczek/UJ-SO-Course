#define CBUFF_SEM_RD "/cbuff_sem_rd"
#define CBUFF_SEM_WR "/cbuff_sem_wr"
#define CBUFF_SHMEM "/cbuff_shmem"
#define CBUFF_SIZE 8

typedef int data_t;

typedef struct {
	char eof;					// 0 dla aktywnego bufora
	int head;					// Pierwszy element do odczytu
	int tail;					// Element za ostatnim zapisanym elementem
	data_t data[CBUFF_SIZE];	// Dane
} cbuff_t;
