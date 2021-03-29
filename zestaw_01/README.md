# Rozwiązania do zestawu 1.
Grzegorz Janysek, 22 marca 2021r. 

- Do skompilowania wszystkich zadań na raz można użyć `$ make`.
- Do kompilowania poszczególnych zadań należy użyć `$ make <plik_wykonywalny_zadania>`.
- W celu usunięcia plików tymczasowych należy użyć `$ make clean`.

---
### Zadanie 1. Procinfo
Nazwa pliku wykonywalnego to `z1_procinfo.x`. Program wypisuje informacje dotyczące procesu.
### Zadanie 2. Kopiowanie
Nazwa pliku wykonywalnego to `z2_kopiowanie.x`. Program kopiuje zawartość jednego do drugiego pliku.
### Zadanie 3. Procesy
Nazwa pliku wykonywalnego to `z3_procesy.x`. Wynikiem programu jest wyświetlenie listy procesów pogrupowanych zgodnie ze starszyzą procesu (najstarszy na górze listy).
```
$ ./z3_procesy.x
Name=./z3_procesy.x, UID=501, GID=20, PID=5354, PPID=1141, PGID=5354
Name=./z3_procesy.x, UID=501, GID=20, PID=5357, PPID=5354, PGID=5354
Name=./z3_procesy.x, UID=501, GID=20, PID=5356, PPID=5354, PGID=5354
Name=./z3_procesy.x, UID=501, GID=20, PID=5355, PPID=5354, PGID=5354
Name=./z3_procesy.x, UID=501, GID=20, PID=5359, PPID=5356, PGID=5354
Name=./z3_procesy.x, UID=501, GID=20, PID=5360, PPID=5355, PGID=5354
Name=./z3_procesy.x, UID=501, GID=20, PID=5358, PPID=5355, PGID=5354
Name=./z3_procesy.x, UID=501, GID=20, PID=5361, PPID=5358, PGID=5354
```
Na podstawie powyższej listy można utworzyć *drzewo genealogiczne* procesów.
- `PID=5354, PPID=1141, PGID=5354`
    - `PID=5357, PPID=5354, PGID=5354`
    - `PID=5356, PPID=5354, PGID=5354`
        - `PID=5359, PPID=5356, PGID=5354`
    - `PID=5355, PPID=5354, PGID=5354`
        - `PID=5360, PPID=5355, PGID=5354`
        - `PID=5358, PPID=5355, PGID=5354`
            - `PID=5361, PPID=5358, PGID=5354`
### Zadanie 4. lider.c
Nazwa pliku wykonywalnego to `z4_lider.x`. Zmodyfikowane rozwiązanie zadania 3. Wynikiem działania jest wyświetlenie takiej samej listy jak w zadaniu 3, z tą różnicą że każdy proces znajduje się w grupie o `PGID` równemu swojemu `PID`
```
./z4_lider.x
Name=./z4_lider.x, UID=501, GID=20, PID=8883, PPID=1141, PGID=8883
Name=./z4_lider.x, UID=501, GID=20, PID=8885, PPID=8883, PGID=8885
Name=./z4_lider.x, UID=501, GID=20, PID=8886, PPID=8883, PGID=8886
Name=./z4_lider.x, UID=501, GID=20, PID=8884, PPID=8883, PGID=8884
Name=./z4_lider.x, UID=501, GID=20, PID=8887, PPID=8885, PGID=8887
Name=./z4_lider.x, UID=501, GID=20, PID=8889, PPID=8884, PGID=8889
Name=./z4_lider.x, UID=501, GID=20, PID=8888, PPID=8884, PGID=8888
Name=./z4_lider.x, UID=501, GID=20, PID=8893, PPID=8888, PGID=8893
```
---
### Pytania do zestawu
-   ##### Opisać dokładnie jak działa funkcja `fork()`?
    > Funkcja `fork()` tworzy dokładną kopię procesu który ją wywoła. Skopiowane zostaną wartości zmiennych, w tym iteratorów. Program jest kontynuowany w obu procesach po wywołanou `fork()`, Dla procesu macieżystego funkcja zwraca `PID` procesu potomnego, zaś dla potomnego zwraca 0.
-   ##### Ile powstaje procesów w zadaniu procesy i dlaczego?
    > Powstaje 8 procesów, ponieważ każda iteracja pętli for powoduje podwojenie ilości procesów, 3 iteracje dają 2^3 = 8.
-   ##### Ile procesów powstanie przy n-krotnym wywołaniu funkcji `fork` i dlaczego?
    > Powstanie dokładnie *n* nowych procesów. Ponieważ każde wywołanie funkcji `fork()` tworzy jedną kopię procesu, w którym ta funkcja została wywołana.
-   ##### Jak używając funkcji `sleep` i bez odwoływania się do funkcji `wait()` zapewnić aby procesy macierzyste kończyły się dopiero po procesach potomnych.
    > Można użyć funkcji `sleep()` tylko w procesie macieżystym, i jako argument przekazać szacunkowy czas wykonywania się procesów potomnych.
-   ##### Jaką wartość zwraca `open()`?
    > Zwraca nieujemny `int`, który jest deskryptorem otwieranego pliku. W przypadku błędu zwraca `-1`.
-   ##### Jaką wartość zwraca `read()` i `write()`?
    > Zwracają ilość poprawnie przeczytanych/zapisanych bajtów. W przypadku błądu zwracają `-1`.