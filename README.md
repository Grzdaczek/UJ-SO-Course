# Rozwiązania do zestawu 1.
autor: Grzegorz Janysek

### Zadanie 1. Procinfo
Nazwa pliku wykonywalnego to `z1_procinfo.x`.

### Zadanie 2. Kopiowanie
Nazwa pliku wykonywalnego to `z2_kopiowanie.x`.

### Zadanie 3. Procesy
Nazwa pliku wykonywalnego to `z3_procesy.x`.

### Zadanie 4. lider.c
Nazwa pliku wykonywalnego to `z4_lider.x`.

### Pytania do zestawu

-   ###### Opisać dokładnie jak działa funkcja fork()?
    funkcja `fork()` tworzy dokładną kopię procesu który ją wywoła. Skopiowane zostaną wartości zmiennych, w tym iteratorów. Program jest kontynuowany w obu procesach po wywołanou `fork()`, Dla procesu macieżystego funkcja zwraca `PID` procesu potomnego, zaś dla potomnego zwraca 0.
-   ###### Ile powstaje procesów w zadaniu procesy i dlaczego?
-   ###### Ile procesów powstanie przy n-krotnym wywołaniu funkcji fork i dlaczego?
-   ###### Jak używając funkcji sleep i bez odwoływania się do funkcji wait() zapewnić aby procesy macierzyste kończyły się dopiero po procesach potomnych.
-   ###### Jaką wartość zwraca open()?
    zwraca nieujemny `int`, który jest deskryptorem otwieranego pliku. W przypadku błędu zwraca `-1`
-   ###### Jaką wartość zwraca read() i write()?