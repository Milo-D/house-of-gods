/* a vulnerable sandbox (UAF on non-fastchunks) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <unistd.h>

#define MAX_ALLOCS 480

/* forward declarations */

static uint64_t leak_libc(void);
static uint64_t leak_heapbase(void);

static void repl_menu(void);

static void allocate_chunk(void);
static void free_chunk(void);
static void write_chunk(void);
static void read_chunk(void);

/* struct, enums, ... */

typedef struct request {

	uint64_t size;
	void *chunk;

} request_t;

/* globals */

uint32_t top = 0;
request_t chunkbox[MAX_ALLOCS];

/* main */

int main(void) {

	setvbuf(stdout, NULL, 2, 0);
	setvbuf(stdin,  NULL, 2, 0);

	const uint64_t symbol = leak_libc();
	printf("puts: 0x%"PRIx64"\n", symbol);

	const uint64_t heapbase = leak_heapbase();
	printf("heapbase: 0x%"PRIx64"\n\n", heapbase);

	while(true) {

		repl_menu();

		uint32_t choice;
		scanf("%d", &choice);

		switch(choice) {

			case 1: allocate_chunk();    break;
			case 2: free_chunk();        break;
			case 3: write_chunk();       break;
			case 4: read_chunk();        break;

			default: puts("Invalid.\n"); break;
		}
	}

	return EXIT_SUCCESS;
}

/* helpers */

static uint64_t leak_libc(void) {

	puts("\x00\xde\xad\xbe\xef");
	return *((uint64_t*) 0x602028);
}

static uint64_t leak_heapbase(void) {

	void *leak = malloc(0x88);
	free(leak);

	return *((uint64_t*) &leak) - 0x10;
}

static void repl_menu(void) {

	puts("1: allocate chunk");
	puts("2: free chunk");
	puts("3: write chunk");
	puts("4: read chunk\n");

	printf("> ");
}

static void allocate_chunk(void) {

	if(top == MAX_ALLOCS) {

		puts("too many chunks.");
		return;
	}

	puts("chunksize: ");

	uint64_t chunksize;
	scanf("%lu", &chunksize);

	chunkbox[ top ].chunk = malloc(chunksize);
	chunkbox[ top ].size  = chunksize;

	top += 1;
}

static void free_chunk(void) {

	puts("index: ");
	
	uint32_t index;
	scanf("%d", &index);

	if(index >= top) {

		puts("out of bounds.");
		return;
	}

	if(chunkbox[ index ].chunk == NULL) {

		puts("invalid chunk.");
		return;
	}

	free(chunkbox[ index ].chunk);

	if(chunkbox[ index ].size < 0x88)
		chunkbox[ index ].chunk = NULL;
}

static void write_chunk(void) {

	puts("index: ");

	uint32_t index;
	scanf("%d", &index);

	if(index >= top) {

		puts("out of bounds.");
		return;
	}

	if(chunkbox[ index ].chunk == NULL) {

		puts("no UAF on fastchunks.");
		return;
	}

        puts("data: ");

	const uint64_t size = chunkbox[ index ].size;
	read(0, chunkbox[ index ].chunk, size);
}

static void read_chunk(void) {

	puts("index: ");

	uint32_t index;
	scanf("%d", &index);

	if(index >= top) {

		puts("out of bounds.");
		return;
	}

	if(chunkbox[ index ].chunk == NULL) {

		puts("no UAF on fastchunks.");
		return;
	}

	const uint64_t size = chunkbox[ index ].size;
	write(1, chunkbox[ index ].chunk, size);

	printf("\n");
}
