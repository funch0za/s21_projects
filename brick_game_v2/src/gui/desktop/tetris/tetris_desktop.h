#ifndef TETRIS_DESKTOP_H
#define TETRIS_DESKTOP_H

#include <gtk/gtk.h>

#include "../../../brick_game/tetris/tetris.h"
#include "../../../brick_game/tetris/tetris_connect.h"

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define NEXT_WIDTH 4
#define NEXT_HEIGHT 4

extern GameInfo_t game_state;

const GdkRGBA tetris_colors[] = {{0.0, 0.0, 0.0, 1.0}, {0.0, 1.0, 1.0, 1.0},
                                 {0.0, 0.0, 1.0, 1.0}, {1.0, 0.5, 0.0, 1.0},
                                 {1.0, 1.0, 0.0, 1.0}, {0.0, 1.0, 0.0, 1.0},
                                 {1.0, 0.0, 0.0, 1.0}, {0.5, 0.0, 0.5, 1.0}};

extern GtkWidget *main_window;
extern GtkWidget *game_area;
extern GtkWidget *next_figure_area;
extern GtkWidget *score_label;
extern GtkWidget *level_label;
extern GtkWidget *high_score_label;
extern GtkWidget *pause_label;

extern guint game_timer; /* TIMER FOR UPDATE */
extern guint fall_timer; /* TIMER FOR FALL FIGURE */

#ifdef __cplusplus
extern "C" {
#endif

gboolean draw_game_area(GtkWidget *widget, cairo_t *cr, gpointer data);
gboolean draw_next_figure(GtkWidget *widget, cairo_t *cr, gpointer data);
void update_ui();
GtkWidget *create_tetris_ui();

gboolean on_key_pressed(GtkWidget *widget, GdkEventKey *event, gpointer data);
gboolean auto_fall_timer(gpointer data);
gboolean on_key_pressed(GtkWidget *widget, GdkEventKey *event, gpointer data);
gboolean game_update_timer(gpointer data);

#ifdef __cplusplus
}
#endif

#endif
