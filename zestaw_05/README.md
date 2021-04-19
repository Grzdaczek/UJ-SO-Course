# Rozwiązania do zestawu 5.
Grzegorz Janysek, 11 kwietnia 2021r.

---

### Pytania do zestawu
-   ##### Czym się różni funkcja `pipe()` od `mkfifo()`? Co robią te funkcje?
	`pipe()` tworzy potok nienazwany, `mkfifo()` tworzy potok nazwany.
-   ##### Co oznacza akronim FIFO?
	First in, first out.
-   ##### Jak utworzyć i usunąć potok nazwany z linii komend a jak z poziomu programu?
	Potok nazwany z lini komend moż utwożyć za pomocą polecenia `mkfifo [-m <mode>] <pathname>`. Usunięcie takiego potoku przebiega analogicznie do usunięcia każdego innego pliku, tj. za pomocą komendy `rm`. W przypadku utworzenie potoku nazwanego z programu należy użyć `int mkfifo(const char *pathname, mode_t mode)`. Aby programowo usunąć taki potok można użyć `int unlink(const char *path)`.
