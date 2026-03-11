# Procesor-stosowy-study-project
Projekt inteligentnego  emulatora procesora stosowego. Emulator wykonuje programy, operując na unikalnej architekturze stosowej, gdzie elementami stosu są listy znaków.

### Architektura
- Pamięć programu: Sekwencja instrukcji (znaków), adresowana od 0.
- Wskaźnik instrukcji (IP): Przechowuje numer aktualnie wykonywanej instrukcji.
- Stos (LIFO): Przechowuje dane w formie list znaków. 
- Reprezentacja liczb: Liczby przechowywane są jako listy znaków w odwrotnej kolejności (np. liczba -1234 to lista '4321-').

## Specyfikacja techniczna (Ograniczenia projektowe)
Zgodnie z wymogami przedmiotu Algorytmy i Struktury Danych, emulator został zaimplementowany z zachowaniem surowych restrykcji:
- Zakaz używania STL: Własna implementacja struktur danych (poza wejściem/wyjściem).
- Zakaz używania tablic: Wykorzystane wyłącznie do przechowywania kodu programu i bufora wejściowego.
- Ograniczenie pętli : W całym programie (poza wczytywaniem danych) użyto tylko jednej pętli. Cała logika sterowania i operacje na strukturach oparte są na rekurencji.
- Zarządzanie pamięcią: Ręczne zarządzanie pamięcią dynamiczną dla list i węzłów stosu.

## Lista instrukcji
| Znak | Opis |
| :--- | :--- |
| '     | Włóż na stos pustą listę |
| ,     | Zdejmij listę ze stosu |
| :     | Duplikuj wierzchołek stosu |
| ;     | Zamień miejscami dwa górne elementy |
| @     | Kopiuj element z głębi stosu (według indeksu) |
| .     | Wczytaj znak i dołącz na początek listy |
| >     | Wypisz pierwszy znak listy i usuń go z niej |
| !     | Negacja logiczna (pusta/'0' -> '1', inne -> '0') |
| < / = | Porównania liczb (B < A lub B = A) |
| ~     | Włóż na stos numer bieżącej instrukcji |
| ?     | Skok warunkowy (jeśli lista niepusta i nie '0') |
| - / ^ | Negacja znaku liczby / Wartość bezwzględna |
| $ / # | Podział listy (unstacking) / Łączenie list |
| +     | Dodawanie liczb w reprezentacji listowej |
| &     | Debug: Wypisz pełną zawartość stosu |
| [ / ] | Konwersja znak <-> ASCII |
| inne  | Każdy inny znak jest dopisywany na początek listy na szczycie |

