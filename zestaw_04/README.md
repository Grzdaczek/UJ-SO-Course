# Rozwiązania do zestawu 4.
Grzegorz Janysek, 18 kwietnia 2021r.

---

### Pytania do zestawu
-   ##### Co zwraca funkcja `pipe()`?
	Zwraca `0` jeśli utworzenie poroku się powiedzie, w przeciwnym wypadku zwraca `-1`. 
-   ##### Czym się różni funkcja `pipe()` od `mkfifo()`? Co robią te funkcje?
	`pipe()` tworzy potok nienazwany, `mkfifo()` tworzy potok nazwany.
-   ##### Co oznacza akronim FIFO?
	First in, first out.
-   ##### Co to jest deskryptor?
	Jest nieujemną liczbą całkowitą, unikatowo określającą otwarty plik.
-   ##### Jak i dlaczego zamykamy deskryptory w zadaniu 1.?
	Zamykamy je za pomocą `close()`. Jest to konieczne do zakończenia działania procesu `konsument`, ponieważ będzie on czekał dopuki istnieje proces mający otwarty deskrypor zapisu do potoku. Po zamknięciu tego deskryptora funkcją `close()`, `konsument` zakończy się.
-   ##### Proszę sprawdzić co się stanie jeżeli nie zamkniemy deskryptorów w zadaniu 1.?
	Program nie zakończy się ponieważ gdy proces `producent` skończy zapisywać plik do potoku, czeka na proces `konsument`, który odczytawszy wszystko z potoku czeka na nowe dane. Oba procesy czekają, na warunki które nie zostaną spełnione.
-   ##### Jak utworzyć i usunąć potok nazwany z linii komend a jak z poziomu programu?
	Potok nazwany z lini komend moż utwożyć za pomocą polecenia `mkfifo [-m <mode>] <pathname>`. Usunięcie takiego potoku przebiega analogicznie do usunięcia każdego innego pliku, tj. za pomocą komendy `rm`. W przypadku utworzenie potoku nazwanego z programu należy użyć `int mkfifo(const char *pathname, mode_t mode)`. Aby programowo usunąć taki potok można użyć `int unlink(const char *path)`.

