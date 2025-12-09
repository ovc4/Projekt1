cmake_minimum_required(VERSION 3.30)
project(sfml)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ścieżka do SFMLConfig.cmake
set(SFML_DIR "C:/Users/lbien/Documents/SFML-3.0.2-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.2/lib/cmake/SFML")

# Szukamy SFML
find_package(SFML 3 REQUIRED COMPONENTS System Window Graphics Audio)

# Tworzymy plik wykonywalny
add_executable(${PROJECT_NAME} main1.cpp
        Paddle.h
        stone.cpp
        stone.h
        Game.cpp
        Game.h
        GameState.cpp
        GameState.h)

# Linkujemy SFML
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::System SFML::Window SFML::Graphics SFML::Audio)

# Dodajemy katalog z nagłówkami SFML (żeby CLion nie podkreślał)
target_include_directories(${PROJECT_NAME} PRIVATE
        "C:/Users/lbien/Documents/SFML-3.0.2-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.2/include"
)
