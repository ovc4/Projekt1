# Projekt: Arkanoid – SFML 3.0.2

Projekt to prosta gra typu **Arkanoid**, napisana w języku **C++** z użyciem biblioteki **SFML 3.0.2**.  
Celem projektu jest pokazanie obiektowego podejścia do tworzenia gry: ruch piłki, sterowanie paletką, kolizje, menu.

---

## Scenariusz gry

Po uruchomieniu pojawia się **menu główne**:

- `START (S)` – rozpoczyna grę  
- `EXIT (ESC)` – zamyka aplikację  

Po wybraniu *START*:

1. Pokazuje się okno gry **640 × 480**.
2. Na dole znajduje się **paletka** sterowana klawiszami:
   - `A` lub `←` – ruch w lewo  
   - `D` lub `→` – ruch w prawo
3. Piłka porusza się po ekranie.
4. Odbija się od:
   - lewej ściany
   - prawej ściany
   - sufitu
   - paletki (od góry)
5. Jeśli piłka spadnie poniżej dolnej krawędzi ekranu:
   - okno zamyka się.

---

## Funkcjonalności

### **Klasa Paletka**
- Przechowuje pozycję, rozmiar i prędkość.
- Odpowiada za:
  - ruch w lewo/prawo,
  - ograniczenie ruchu do granic ekranu,
  - rysowanie jej w oknie gry.

### **Klasa Pilka**
- Zawiera pozycję, prędkość i promień.
- Obsługuje:
  - ruch piłki,
  - odbijanie od ścian,
  - kolizję z paletką,
  - rysowanie w oknie.

---



