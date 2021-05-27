# Rozwiązania do zestawu 9.
Grzegorz Janysek, 26 maja 2021r.

---

### Pytania do zestawu
-   ##### Czym się różni wątek od procesu?
	Wąek jest częścią procesu i najmniejszą jednostką egzekucyjną mogącą być zarządzaną i paralerizowaną przez scheduler. Tworzenie i obsługa wątku jest mniej kosztowna od procesu. Wątki dzelą przestrzeń pamięci w obrębie swojego procesu.
-   ##### Opisać działanie, argumenty i wartość zwracaną przez funkcję `pthread_create()`.
	funkja tworzy wątek, przyjmuje wskaźnik na ID wątka, wskaźnik na strukturę z atrybutami, wskaźnik do funkcji, oraz wskaźnik na argument tej funkcji. Zwraca 0 jeśli się powiedzie, w przypadku błędu zwraca kod błedu.
-   ##### Funkcja `pthread_join()` jest odpowiednikiem której funkcji dla procesów?
	`pid_t wait(int* status)`
-   ##### Czym się różnią muteksy od semaforów?
	O ile semafor może przyjmować każdą (oganiczoną typem) wartość liczbową większą od zera, tak muteks może jedynie zostać zablokowany (przez tylko jeden wątek na raz) oraz odblokowany (tylko przez wątek który go zablokował).
-   ##### Opisać działanie operacji, które możemy wykonać na muteksach.
	Muteks można: inicjalizować, zablokować, odblokować i usunąć.
-   ##### Dlaczego musimy zdefiniować makro `_REENTRANT`?
	Wskazauje to linkerowi na konieczność stosowania wersji _thread safe_ funkcji bibliotecznych.
-   ##### Co oznacza typ `void * (*) ()`?
    Wskaźnik na funkcje która zwraca `void *`.
-   #####Co to sa operacje atomowe? Czy są konieczne?
	To operacje które nie są podzielne. Są koniecne gdy chcemy mieć pewność że operacja zawsze zostanie wykonana poprawnie, nie zależnie od innych operacji wykonywanych jednocześnie w innch wątkach.
