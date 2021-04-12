# Rozwiązania do zestawu 3.
Grzegorz Janysek, 12 kwietnia 2021r.

### Opis użycia i działania programów
-   ##### obsluga.c
    Program przyjmuje dwa argumenty, rodzaj obsługi sygnału, oraz numer sygnału: `./obsluga.x {d|i|p} <sig>`.
    - `d` - domyślna obsługa sygnału
    - `i` - ignorowanie sygnału
    - `p` - przechwycenie i wypisanie sygnału
    Program ustawia obsługę sygnału `sig`, a następnie czeaka na sygnał.
-   ##### wysylaj.c
    Program uruchamia `obsluga.x` w procesie potomnym, a następnie wysyła sygnał `sig` do tego procesu. Przyjmuje dwa argumenty rodzaj obsugi i numer sygnału: `./wysylaj.x {d|i|p} <sig>`. Do procesu potomnego przekazywane są argumenty procesu rodzica.
-   ##### grupa.c
    Proces *główny* tworzy proces *lidera*, który 5 razy w procesach potomnych uruchamia `obsluga.x` oraz staje się liderem własnej grupy. Następnie proces *główny* wysyła sygnał do grupy procesu *lider* i na niego czeka. Proces *lider* ignoruje ten sygnał, natomiast jego procesy potmne wypisują sygnał i zakańczają się. *Lider* czeka na swoje dzieci a następnie również się kończy. Program nie przyjuje żadnych argumentów. 

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
    Sprawdza możliwość wysłania sygnału do procesów w tej samej grupie co nadawca.
-   ##### Jak i dlaczego należy uodpornić proces macierzysty w programie grupa.c na sygnał?
    Ponieważ sygnał zosanie wysłany do każdego procesu z grupy procesu macieżystego, zostanie wysłany kakże do niego. Należy go uodpornić za pomocą `signal(sig, SIG_IGN)`.
-   ##### Jak wznowić proces zatrzymany sygnałem `SIGSTOP`?
-   ##### Opisać sygnał `SIGCHLD`.
    Sygnał `SIGCHLD` jest wysyłany do rodzica po tym jak proces dziecko zostanie zatrzymany lub się zakończy.
-   ##### Które sygnały możemy wysłać w terminalu przy użyciu skrótów klawiszowych?
    - `Ctrl + C` : SIGINIT
    - `Ctrl + \` : SIGQUIT
    - `Ctrl + Z` : SIGTSTP
-   ##### Jak działa funkcja `pause()`?
    Funkcja powoduje uśpienie procesu do momentu otrzymania sygnału.