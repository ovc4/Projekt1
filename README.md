# Projekt: Arkanoid – SFML 3.0.2

Projekt to prosta gra typu Arkanoid, napisana w języku C++ z użyciem biblioteki **SFML 3.0.2**.  
Celem projektu jest pokazanie obiektowego podejścia do tworzenia gry: ruch piłki, sterowanie paletką, kolizje oraz menu.

---

## Scenariusz gry

1. Gra uruchamia okno o rozmiarze **640 × 480**.
2. Na dole ekranu znajduje się **paletka**, którą sterujemy:
   - `A` lub `←` – ruch w lewo  
   - `D` lub `→` – ruch w prawo
3. Piłka porusza się po ekranie i odbija od:
   - lewej i prawej ściany
   - sufitu
   - paletki (od góry)
4. Jeśli piłka spadnie poniżej dolnej krawędzi ekranu, **gra się kończy**.

---

## Funkcjonalności

### Klasa `Paletka`

- Przechowuje **pozycję**, **rozmiar** i **prędkość** paletki.
- Odpowiada za:
  - ruch w lewo/prawo,
  - ograniczenie ruchu do granic ekranu,
  - rysowanie paletki w oknie gry.

### Klasa `Pilka`

- Zawiera **pozycję**, **prędkość** i **promień** piłki.
- Obsługuje:
  - ruch piłki po ekranie,
  - odbijanie od ścian,
  - kolizję z paletką,
  - rysowanie piłki w oknie gry.

---

## Wymagania

- C++17 lub nowszy
- **SFML 3.0.2**
- System: Windows/Linux/macOS

---

