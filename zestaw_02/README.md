# Rozwiązania do zestawu 1.
Grzegorz Janysek, 22 marca 2021r. 

---
### Pytania do zestawu
-   ##### Ile teraz powstaje procesów w zadaniu 2. i dlaczego?
    > powstaną 4 procesy, jeden rodzic, oraz 3 dzieci, ponieważ funkcja `fork()` zostanie wywołana 3 razy.
-   ##### Ile procesów powstanie przy n-krotnym wywołaniu funkcji fork-exec jak w zadaniu 2. i dlaczego?
    > Powstanie *n* nowych procesów, ponieważ funkcja `fork()` jest wywoływana tylko w rodzicu. Każdy nowy proces wywołuje `exec()`.
-   ##### Co robi funkcja execl()? Czym się różni od funkcji execv()
    > Zastępue dotychczasowy plik wykonywalny procesu, plikiem podanym jako argument .Funkcje różnią się tylko sposobem przekazywania argumenrów.
-   ##### Jaką rolę pełni proces init lub systemd?
    > Jest pierwszym procesem utworzonym przez kernel podczas bootowania systemu. Jego rolą jest zainicjalizowanie systemu. Adoptuje również procesy osierocone.
-   ##### Co to proces zombi?
    > To proces który się zakończył, ale którego rodzic na niego nie czeka. Proces zombie w dalszym ciągu posiada wpis w tabeli procesów.
-   ##### Co to proces osierocony?
    > To proces na który rodzic nie poczkał i zakończył się przed zakończeniem procesu dziecka. Porces osierocony zostaje adoptowany przez proces init pośmierci rodzica.