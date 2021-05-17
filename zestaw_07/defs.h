#define BUFF_SIZE 8

typedef int data_t;

typedef struct {
	const int size; // == BUFF_SIZE
	data_t* end;
	data_t* start;
	data_t data[BUFF_SIZE];
} cbuffer;
