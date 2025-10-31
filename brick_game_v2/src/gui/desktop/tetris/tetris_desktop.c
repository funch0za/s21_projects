#include "tetris_desktop.h"

GameInfo_t game_state;

GtkWidget *main_window;
GtkWidget *game_area;
GtkWidget *next_figure_area;
GtkWidget *score_label;
GtkWidget *level_label;
GtkWidget *high_score_label;
GtkWidget *pause_label;

guint game_timer;
guint fall_timer;

gboolean draw_game_area(GtkWidget *widget, cairo_t *cr, gpointer data) {
  GameInfo_t *state = (GameInfo_t *)data;

  if (!state->field)
    return FALSE;

  GtkAllocation allocation;
  gtk_widget_get_allocation(widget, &allocation);
  int width = allocation.width;
  int height = allocation.height;

  int cell_size = height / FIELD_HEIGHT;
  int offset_x = (width - FIELD_WIDTH * cell_size) / 2;

  cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
  cairo_rectangle(cr, 0, 0, width, height);
  cairo_fill(cr);

  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      int cell_value = state->field[y][x];
      if (cell_value < 0 || cell_value > 7)
        cell_value = 0;

      GdkRGBA color = tetris_colors[cell_value];

      cairo_rectangle(cr, offset_x + x * cell_size, y * cell_size, cell_size,
                      cell_size);

      cairo_set_source_rgba(cr, color.red, color.green, color.blue,
                            color.alpha);
      cairo_fill(cr);

      cairo_rectangle(cr, offset_x + x * cell_size, y * cell_size, cell_size,
                      cell_size);
      cairo_set_source_rgb(cr, 0.3, 0.3, 0.3);
      cairo_stroke(cr);
    }
  }

  return FALSE;
}

gboolean draw_next_figure(GtkWidget *widget, cairo_t *cr, gpointer data) {
  GameInfo_t *state = (GameInfo_t *)data;

  if (!state->next)
    return FALSE;

  GtkAllocation allocation;
  gtk_widget_get_allocation(widget, &allocation);
  int width = allocation.width;
  int height = allocation.height;

  int cell_size = height / (NEXT_HEIGHT + 2);
  int offset_x = (width - NEXT_WIDTH * cell_size) / 2;
  int offset_y = (height - NEXT_HEIGHT * cell_size) / 2;

  cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
  cairo_rectangle(cr, 0, 0, width, height);
  cairo_fill(cr);

  for (int y = 0; y < NEXT_HEIGHT; y++) {
    for (int x = 0; x < NEXT_WIDTH; x++) {
      int cell_value = state->next[y][x];
      if (cell_value < 0 || cell_value > 7)
        cell_value = 0;

      if (cell_value > 0) {
        GdkRGBA color = tetris_colors[cell_value];

        cairo_rectangle(cr, offset_x + x * cell_size, offset_y + y * cell_size,
                        cell_size, cell_size);

        cairo_set_source_rgba(cr, color.red, color.green, color.blue,
                              color.alpha);
        cairo_fill(cr);

        cairo_rectangle(cr, offset_x + x * cell_size, offset_y + y * cell_size,
                        cell_size, cell_size);
        cairo_set_source_rgb(cr, 0.3, 0.3, 0.3);
        cairo_stroke(cr);
      }
    }
  }

  return FALSE;
}

void update_ui() {
  game_state = updateCurrentState();

  if (!game_state.field) {
    if (game_timer) {
      g_source_remove(game_timer);
      game_timer = 0;
    }
    if (fall_timer) {
      g_source_remove(fall_timer);
      fall_timer = 0;
    }

    char message[100];
    snprintf(message, sizeof(message), "Game Over!\nFinal Score: %d",
             game_state.score);

    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(main_window), GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    return;
  }

  char score_text[50];
  char level_text[50];
  char high_score_text[50];
  char pause_text[20];

  snprintf(score_text, sizeof(score_text), "Score: %d", game_state.score);
  snprintf(level_text, sizeof(level_text), "Level: %d", game_state.level);
  snprintf(high_score_text, sizeof(high_score_text), "High Score: %d",
           game_state.high_score);
  snprintf(pause_text, sizeof(pause_text), "Pause: %s",
           game_state.pause ? "Yes" : "No");

  gtk_label_set_text(GTK_LABEL(score_label), score_text);
  gtk_label_set_text(GTK_LABEL(level_label), level_text);
  gtk_label_set_text(GTK_LABEL(high_score_label), high_score_text);
  gtk_label_set_text(GTK_LABEL(pause_label), pause_text);

  gtk_widget_queue_draw(game_area);
  gtk_widget_queue_draw(next_figure_area);
}

gboolean game_update_timer([[maybe_unused]] gpointer data) {
  update_ui();
  return G_SOURCE_CONTINUE;
}

gboolean auto_fall_timer([[maybe_unused]] gpointer data) {
  if (!game_state.pause && game_state.field) {
    userInput(Down);
    update_ui();
  }
  return G_SOURCE_CONTINUE;
}

gboolean on_key_pressed([[maybe_unused]] GtkWidget *widget, GdkEventKey *event,
                        [[maybe_unused]] gpointer data) {
  UserAction_t action;

  switch (event->keyval) {
  case GDK_KEY_Left:
    action = Left;
    break;

  case GDK_KEY_Right:
    action = Right;
    break;

  case GDK_KEY_Down:
    action = Down;
    break;

  case GDK_KEY_space:
    action = Action;
    break;

  case GDK_KEY_Up:
    action = Up;
    break;

  case GDK_KEY_p:
  case GDK_KEY_P:
    action = Pause;

    userInput(action);
    update_ui();
    return TRUE;

  case GDK_KEY_r:
  case GDK_KEY_R:
    action = Start;
    userInput(action);

    if (!fall_timer) {
      fall_timer = g_timeout_add(1000, auto_fall_timer, NULL);
    }

    update_ui();
    return TRUE;
  case GDK_KEY_q:
  case GDK_KEY_Q:
    puts("OK");
    action = Terminate;
    if (game_timer) {
      g_source_remove(game_timer);
      game_timer = 0;
    }
    if (fall_timer) {
      g_source_remove(fall_timer);
      fall_timer = 0;
    }
    gtk_main_quit();
    return TRUE;

  default:
    return FALSE;
  }

  userInput(action);

  update_ui();

  return TRUE;
}

GtkWidget *create_tetris_ui() {
  GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  GtkWidget *left_panel = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget *right_panel = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

  game_area = gtk_drawing_area_new();
  g_signal_connect(G_OBJECT(game_area), "draw", G_CALLBACK(draw_game_area),
                   &game_state);
  gtk_widget_set_size_request(game_area, 300, 600);

  GtkWidget *next_frame = gtk_frame_new("Next Figure");
  next_figure_area = gtk_drawing_area_new();
  g_signal_connect(G_OBJECT(next_figure_area), "draw",
                   G_CALLBACK(draw_next_figure), &game_state);
  gtk_widget_set_size_request(next_figure_area, 120, 120);
  gtk_container_add(GTK_CONTAINER(next_frame), next_figure_area);

  score_label = gtk_label_new("Score: 0");
  level_label = gtk_label_new("Level: 1");
  high_score_label = gtk_label_new("High Score: 0");
  pause_label = gtk_label_new("Pause: No");

  GtkWidget *controls_frame = gtk_frame_new("Controls");
  GtkWidget *controls_text =
      gtk_label_new("←: Left\n→: Right\nSpace: Rotate\nP: Pause\nQ: Quit");
  gtk_container_add(GTK_CONTAINER(controls_frame), controls_text);

  gtk_box_pack_start(GTK_BOX(right_panel), next_frame, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(right_panel), score_label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(right_panel), level_label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(right_panel), high_score_label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(right_panel), pause_label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(right_panel), controls_frame, FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(left_panel), game_area, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(main_box), left_panel, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(main_box), right_panel, FALSE, FALSE, 0);

  return main_box;
}
