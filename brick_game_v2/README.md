# BrickGame Змейка
В данном проекте предстояло улучшить [BrickGame version 1.0](https://github.com/funch0za/s21_projects/tree/main/brick_game_v1).

Для разработки змейки использовался патерн MVC:
```
+-------------+      +-----------------+      +-------+
|   Interface |<---->|  Controller     |<---->| Model |
|   (UI)      |      | (Event Handler) |      |       |
+-------------+      +-----------------+      +-------+
       ↑                      ↑
       | Event                | Update State
       | (User Action)        | (Change Data)
       |                      |
+-------------+               |
|   User      |---------------+
|             |
+-------------+
```
## Что добавлено
1. Разработана логика для игры "Змейка", а также консольный интерфейс для нее.
2. Разработан десктопный интерфейс для тетриса и змейки. В качестве графической библиотеки использовалась GTK+ 3.0. 
3. Добавлено меню выбора игры во всех интерфейсах.
## Зависимости
* GTK+ 3.0
* Google Test Framework
## Сборка
```bash
make
```
## Запуск с консольным интерфейсом
```bash
./brick_game_v2
```
## Запуск с десктопным интерфейсом
```bash 
./brick_game_v2_desktop
```
## Сборка документации
Для документирования используется Doxygen.
```bash
make dvi
```
## Запуск тестов
```bash
make test
```
## Структура проекта
```
├── app
│   ├── app.cpp
│   ├── app.h
│   └── main.cpp
├── brick_game
│   ├── snake
│   │   ├── common
│   │   │   ├── snake_consts.h
│   │   │   └── snake_types.h
│   │   ├── controller
│   │   │   ├── snake_controller.cpp
│   │   │   └── snake_controller.h
│   │   └── model
│   │       ├── snake_model.cpp
│   │       └── snake_model.h
│   └── tetris
│       ├── tetris_connect.c
│       ├── tetris_connect.h
│       ├── tetris_figure.c
│       ├── tetris_figure.h
│       ├── tetris_game_machine.c
│       ├── tetris_game_machine.h
│       ├── tetris_macroses.h
│       ├── tetris_map.c
│       ├── tetris_map.h
│       ├── tetris_matrix_operations.c
│       ├── tetris_matrix_operations.h
│       ├── tetris_objects.h
│       ├── tetris.c
│       └── tetris.h
├── Doxyfile
├── FSM_tetris.png
├── gui
│   ├── cli
│   │   ├── cli_params.h
│   │   ├── snake
│   │   │   ├── snake_cli.cpp
│   │   │   └── snake_cli.h
│   │   └── tetris
│   │       ├── tetris_cli.c
│   │       ├── tetris_cli.h
│   │       ├── tetris_input.c
│   │       └── tetris_input.h
│   └── desktop
│       ├── snake
│       │   ├── snake_desktop.cpp
│       │   └── snake_desktop.h
│       └── tetris
│           ├── tetris_desktop.c
│           └── tetris_desktop.h
├── Makefile
└── test
    ├── test_snake_model.cpp
    └── test_snake_model.h
```