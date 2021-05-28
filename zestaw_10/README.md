# Rozwiązania do zestawu 10.
Grzegorz Janysek, 28 maja 2021r.

---

### Pytania do zestawu
-   ##### Dlaczego dwa procesy nie mają jednocześnie dostępu do sekcji krytycznej?
	Ponieważ zagwarantowane jest że warunek najniższego numerka i id wątku jest prawdziwy tylko dla jednego prcesu.
-   ##### Dlaczego algorytm nie prowadzi do zakleszczenia?
	Ponieważ tylko jeden proces na raz spełnia warukni do wejścia do sekcji krytycznej.
-   ##### Dlaczego algorytm nie prowadzi do zagłodzenia?
	Ponieważ wątek który odbierze numerek zostanie obsłużony po wszystkich poprzednikach o numerkach mniejszych.
-   ##### Jakie minimalne warunki muszą zostać spełnione przez kompilator i model pamięci aby algorytm działał poprawnie?
	Warunkiem jest to żeby zapis mógł być zrealizowany atomowo.
