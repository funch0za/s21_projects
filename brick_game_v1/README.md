# BrickGame Тетрис
В данном проекте предстояло реализовать игру "Тетрис".
Игра разработана на языке Си с использованием библиотеки ncurses.

## Зависимости
Установка ncurses на Debian.
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```

## Сборка
```
make
```

## Запуск игры
```
./brick_game/tetris
```

## Сборка документации
Для документирования используется Doxygen.
```
make dvi
```

## Запуск тестов
```
make test
```

## Структура проекта
```
brick_game_v1/
├── README.md
└── src
    ├── brick_game
    │   └── tetris
    │       ├── backend.c
    │       ├── connect.c
    │       ├── fsm.c
    │       └── include
    │           ├── backend.h
    │           ├── connect.h
    │           ├── fsm.h
    │           ├── macros.h
    │           └── objects.h
    ├── build
    ├── data
    │   └── hiscore.txt
    ├── Doxyfile
    ├── FSM.png
    ├── gui
    │   └── cli
    │       ├── frontend.c
    │       └── include
    │           └── frontend.h
    ├── Makefile
    ├── run
    │   └── main.c
    └── test
        ├── include
        │   └── test_brick_game_v1.h
        ├── logs
        ├── test_brick_game_v1.c
        └── test_start.c
```
