#ifndef _LIBSEM_H_
#define _LIBSEM_H_

#include <semaphore.h>

typedef sem_t* semid;

/* Tworzy semafor z wartością początkową val. */
semid semCreate(const char *name, int val);

/* Usuwa semafor. */
void semRemove(const char *name);

/* Uzyskuje dostęp do istniejącego semafora. */
semid semOpen(const char *name);

/* Zamyka semafor w danym procesie. */
void semClose(semid sem);

/* Opuszcza semafor: zmniejsza wartość semafora o 1 lub czeka. */
void semP(semid sem);

/* Podnosi semafor: zwiększa wartość semafora o 1 lub wznawia czekający proces. */
void semV(semid sem);

/* Funkcja wypisuje informację o wartości semafora, 
 * ewentualnie gdy system dopuszcza taką możliwość także o liczbie czekających procesów.
 */
void semInfo(semid sem);

#endif // _LIBSEM_H_
