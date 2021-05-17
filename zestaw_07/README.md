# Rozwiązania do zestawu 7.
Grzegorz Janysek, 15 maja 2021r.

---

### Pytania do zestawu
-   ##### Szczegółowo opisz działanie semaforów z zadaniu 3.
	Wykożystane są dwa, zezwalający na zapis do bufora (SEM_WR) i zezwalający na odczyt (SEM_RD). Podczas odczytu z bufora zmniejszany jest SEM_RD, aby uniemożliwić czytanie z pustego bufora, wartość SEM_RD wskazuje na ilość zajętych elementów w buforze. SEM_WR jest zwiększany, wskazuje on na ilość wolnych elementów w buforze. Zapis do bufora działa analogicznie, przy czym SEM_WR jest zmniejszany a SEM_RD zwiększany. Wartość inicjalizacyjna dla SEM_WR określa wielkość bufora, dla
	SEM_RD jest równa 0.
-   ##### Podać w pseudokodzie uogólnienie rozwiązania problemu z zadania 3. na przypadek wielu producentów i konsumentów.
	```
	// konieczne są dwa dodatkowe semafory binarne,
	// tak aby w danej chwili tylko jeden proces mugł
	// zapisywać i odczytywać z bufora cyklicznego.

	// SEM_WR  - istnieje wolne miesce
	// SEM_RD  - istnieje element do odczytania
	// SEM_BWR - blokowanie odczytu
	// SEM_BRD - blokowanie zapisu

	fn cbuff_rd(x) {
		P(SEM_RD)
		V(SEM_BRD)
		
		x = buff[head]
		tail += 1
		tail %= size

		P(SEM_BRD)
		V(SEM_WR)

		return x
	}

	fn cbuff_wr(x) {
		P(SEM_WR)
		V(SEM_BWR)
		
		buff[tail] = x
		tail += 1
		tail %= size

		P(SEM_BRD)
		V(SEM_RD)
	}
	```
-   ##### Czym jest biblioteka dynamiczna? Jakie są jej zalety?
	To biblioteka która jest łączona z programem dopiero w chwili jego wykonywania. Pozwala to na współdzielenie plików biblioteki dynamicznej przez wiele programów.
-   ##### Jak utworzyć bibliotekę dynamiczną? Jak jej używać? Jakie są nazwy plików, które są bibliotekami dynamicznymi?
	Tworzy się ją używając odpowiednich opcji kompilatora. Używanie wymaga załączenia pliku nagłówkowego, linkowania biblioteki, oraz ustawienia zmiennej środowiskowej na ścieżkę do folderu z plikiem .so biblioteki. Biblioteki dynamiczne mają nazwy w postaci lib*.so 
