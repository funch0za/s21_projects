#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "objects.h"

/**
 * @brief coloring the figure field
 * [0] -
 *       [][][][]
 *
 * [1] - []
 *       [][][]
 *
 * [2] -     []
 *       [][][]
 *
 * [3] - [][]
 *       [][]
 *
 * [4] -   [][]
 *       [][]
 *
 * [5] - [][]
 *         [][] 
 *
 * [6] -   []
 *       [][][]
 */
static const figure_t FIGURES_LEFT[7] = {
    {{{1, 0}, {1, 1}, {1, 2}, {1, 3}}, F0, 0},
    {{{0, 0}, {1, 0}, {1, 1}, {1, 2}}, F1, 0},
    {{{0, 2}, {1, 0}, {1, 1}, {1, 2}}, F2, 0},
    {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}, F3, 0},
    {{{0, 1}, {0, 2}, {1, 0}, {1, 1}}, F4, 0},
    {{{0, 0}, {0, 1}, {1, 1}, {1, 2}}, F5, 0},
    {{{0, 0}, {1, 0}, {1, 1}, {1, 2}}, F6, 0}};
static const figure_t FIGURES_MID[7] = {
    {{{0, 4}, {0, 5}, {0, 6}, {0, 7}}, F0, 0},
    {{{0, 4}, {1, 4}, {1, 5}, {1, 6}}, F1, 0},
    {{{1, 4}, {1, 5}, {1, 6}, {0, 6}}, F2, 0},
    {{{0, 4}, {0, 5}, {1, 4}, {1, 5}}, F3, 0},
    {{{1, 4}, {1, 5}, {0, 5}, {0, 6}}, F4, 0},
    {{{0, 4}, {0, 5}, {1, 5}, {1, 6}}, F5, 0},
    {{{1, 4}, {0, 5}, {1, 5}, {1, 6}}, F6, 0}};

TetrisStatus_t *get_tetris_struct();
int randomizer();
void delete_tetris();
void create_matrix(int rows, int cols, int ***dest);
void delete_matrix(int rows, int ***dest);

move_stat figure_move(figure_t *f, vector_t v, map_t *game_map);
move_stat figure_rotate(figure_t *f, map_t *game_map);
bool figure_can_attached(figure_t *f, map_t *game_map);
void figure_attach(figure_t *f, map_t *game_map);

void map_init(map_t *game_map);
map_stat map_check(map_t *game_map);
void map_move_line(int x, int xnew, map_t *game_map);
int map_delete_filled(map_t *game_map);
bool game_is_over();

void update_score_level(int count_of_deleted_lines);

int get_hiscore();
void update_hiscore(int hiscore);

#endif
