#ifndef _MSG_H
#define _MSG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define MSG_MAXSIZE 8192

mqd_t msgCreate(const char* name);
// Tworzy kolejkę komunikatów o nazwie name i zwraca do niej deskryptor.

mqd_t msgOpen(const char* name);
// Otwiera kolejkę komunikatów o nazwie name i zwraca do niej deskryptor.

void msgClose(mqd_t mqd);
// Zamyka dostęp do kolejki od deskryptorze msgid.

void msgRemove(const char* name);
// Usuwa kolejkę komunikatów nazwie name.

void msgSend(int msgid, void* msg, int msg_size);
// Wysyła komunikat wskazywany przez msg do kolejki o identyfikatorze msgid.

void msgRecv(int msgid, void* msg, int msg_size);
// Odbiera z kolejki msgid komunikat i zapisuje go do msg.

void msgInfo(int msgid);
// Wypisuje wszystkie informacje o kolejce komunikatów uzyskane przy pomocy mq_getattr().

#endif // _MSG_H
