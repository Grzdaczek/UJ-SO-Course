#ifndef _LIBSHMEM_H_
#define _LIBSHMEM_H_

int shmCreate(const char* name, int size);
// Funkcja tworzy pamięć dzieloną o nazwie name i rozmiarze size.
// Funkcja zwraca deskryptor obiektu pamięci dzielonej.

int shmOpen(const char* name);
// Funkcja otwiera obiekt pamięci dzielonej i zwraca jego deskryptor.

void shmRm(const char* name);
// Usuwa obiekt pamięci dzielonej o nazwie name.

void* shmMap(int fd, int size);
// Odwzorowuje obiekt pamięci dzielonej o deskryptorze fd i rozmiarze size w przestrzeń adresową procesu.
// Funkcja zwraca adres początku odwzorowanego obszaru pamięci dzielonej.

void shmClose(void *ptr, int fd, int size);
// Usuwa odwzorowanie obiektu pamięci dzielonej i zamyka powiązany z nim deskryptor.

int shmSize(int fd);
// Zwraca rozmiar pamięci dzielonej określonej deskryptorem fd.
// Proszę użyć funkcji systemowej fstat.

void shmInfo(int fd);
// Wypisuje informacje o pamięci dzielonej: prawa dostępu, rozmiar, właściciel, etc.

#endif // _LIBSHMEM_H_
