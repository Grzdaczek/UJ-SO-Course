# Rozwiązania do zestawu 3.
Grzegorz Janysek, 12 kwietnia 2021r.

### Opis użycia i działania programów
-   ##### obsluga.c
    lorem ipsum
-   ##### wysylaj.c
    lorem ipsum
-   ##### grupa.c
    lorem ipsum

### Funkcje i znaczenie wybraych sygnałów
-   ##### SIGALRM
    Jest wysyłany gdy upłynie czas `t` po wywołaniu `alarm(t)`. Odbiorcą sygnału jest proces który wywołał `alarm()`. Standardowo powoduje zakończenie proeceu.
-   ##### SIGUSR1, SIGUSR2
    Sygnały których funkcja zdefiniowana jest przez urzytkownika, Standardowo odebranie powoduje zakończenie procesu.
-   ##### SIGINT
    Przerwanie z klawiatury, za pomocą skróru `Ctrl + C`, Standardowo zakańcza proces.
-   ##### SIGKILL
    Sygnał powoduje bezwarunkowe zakończenie procesu, nie może zostać zignorowany.

### Sygnały możliwe do wysłąnia w terminalu przy użyciu skrótów klawiszowych
-   `Ctrl + C` : SIGINIT
-   `Ctrl + \` : SIGQUIT
-   `Ctrl + Z` : SIGTSTP

---

### Pytania do zestawu
-   ##### Do czego służą sygnały?
    Do komunikacji międzyprocesowej. Umożliwaiją asynchroniczne przerwanie procesu.
-   ##### Co robi a czego nie robi funkcja `signal()`?
    Ustawia sposób obsługi sygnału, Może ustawić obsługę na domyślną, ignorowanie i funkcje zdefiniowaną przez programistę i przekazaną jako wskaźnik. Funkcja `signal()` nie wysyła sygnału. 
-   ###### Jak działa funkcja `kill()`? Podaj trzy przykłady uwzględniające rolę pierwszego argumentu?
    Służy do wysyłania, bądź sprawdzenia możliwości wysłania sygnału. Pierwszy argument `pid` określa adresata. Jeżeli `pid > 0`, sygnał zostanie wysłany do procesu o `PID == pid`. Jeżeli `pid == 0`, sygnał zostanie wysłany do każdego procesu o `GID` równym `GID`owi nadawcy. Dla `pid == -1`, sygnał trafi do każdego procesu do którego nadawca ma uprawnienia do wysłania.
-   ##### Jak sprawdzić czy istnieje proces `pid` lub grupa `pgid` i czy możemy do nich wysyłać sygnały?
    Przy użyciu `kill(pid, 0)` lub `kill(pgid, 0)`.
-   #### Jaki sens ma wywołanie `kill(0, 0)`?
-   ##### Jak i dlaczego należy uodpornić proces macierzysty w programie grupa.c na sygnał?
-   ##### Jak wznowić proces zatrzymany sygnałem `SIGSTOP`?
-   ##### Opisać sygnał `SIGCHLD`.
    Sygnał `SIGCHLD` jest wysyłany do rodzica po tym jak proces dziecko zostanie zatrzymany lub się zakończy.
-   ##### Które sygnały możemy wysłać w terminalu przy użyciu skrótów klawiszowych?
    - `Ctrl + C` : SIGINIT
    - `Ctrl + \` : SIGQUIT
    - `Ctrl + Z` : SIGTSTP
-   ##### Jak działa funkcja `pause()`?
    Funkcja powoduje uśpienie procesu do momentu otrzymania sygnału.