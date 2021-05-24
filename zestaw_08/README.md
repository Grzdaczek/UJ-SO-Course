# Rozwiązania do zestawu 8.
Grzegorz Janysek, 20 maja 2021r.

---

### Pytania do zestawu
-	##### Opisać działanie, argumenty i wartość zwracaną przez funkcję `mq_open`
	Pozwa na utworzenie lub otwarcie kolejki komunikatów. Przyjmuje nazwę kolejki, i flagi `O_`, a w przypadku tworzenia dodatkowo tryb i atrybuty kolejki. Jeśli się powiedzie zwraca deskryptor, `-1` i ustawia `errno` w przypadku błędu. 
-	##### Opisać działanie, argumenty i wartość zwracaną przez funkcję `mq_send` i `mq_receive`
	Funkcje pozwalją na odbieranie i wysyłanie wiadomości w ramach kolejki komunikatów. Funkcje przyjmują kolenjo: deskryptor kolejki, wskaźnik do wiadomości, rozmiar wiadomości i priorytet wiadomości. obie funkcje zwracają `-1` i ustawiają `errno` w przypadku błędu. Przy nadawaniu rozmiar wiadomości musi być mniejszy lub równy maksymalnemu a przy odbieraniu musi być większy lub równy maksymalnemu. `mq_recive` dodatkowo zwraca rozmiar odczytanej wiadomości.
-	##### Czy kolejki komunikatów standardu POSIX są widoczne w systemie plików, gdzie?
	są widoczne w `/dev/mqueue`
-	##### Jak otrzymać informacje o parametrach kolejki komunikatów?
	należy użyć funkcji `mq_getattr`
