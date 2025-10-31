#include "snake_desktop.h"

#include <iostream>
#include <string>

#include "../../../brick_game/snake/common/snake_consts.h"

namespace s21 {

SnakeDesktop *game_view_instance = nullptr;

const GdkRGBA SNAKE_COLOR = {0.0, 1.0, 0.0, 1.0};
const GdkRGBA FOOD_COLOR = {1.0, 0.0, 0.0, 1.0};
const GdkRGBA BORDER_COLOR = {1.0, 1.0, 1.0, 1.0};
const GdkRGBA BG_COLOR = {0.0, 0.0, 0.0, 1.0};

SnakeDesktop::SnakeDesktop() : game_over(false), paused(false) {
  game_view_instance = this;
}

SnakeDesktop::~SnakeDesktop() { cleanup(); }

bool SnakeDesktop::initialize(int argc, char **argv) {
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Snake Game");
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_container_add(GTK_CONTAINER(window), main_box);

  drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area, FIELD_WIDTH * 20 + 40,
                              FIELD_HEIGHT * 20 + 40);
  gtk_box_pack_start(GTK_BOX(main_box), drawing_area, TRUE, TRUE, 0);

  auto draw_func = +[]([[maybe_unused]] GtkWidget *widget, cairo_t *cr,
                       [[maybe_unused]] gpointer data) -> gboolean {
    if (game_view_instance) {
      cairo_set_source_rgb(cr, 0, 0, 0);
      cairo_paint(cr);

      game_view_instance->drawBorders(cr);
      game_view_instance->drawField(game_view_instance->current_game_info.field,
                                    cr);

      if (game_view_instance->game_over) {
        game_view_instance->showGameOver();
      } else if (game_view_instance->paused) {
        game_view_instance->showPause();
      }
    }
    return FALSE;
  };

  g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_func), NULL);

  sidebar_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_box_pack_start(GTK_BOX(main_box), sidebar_box, FALSE, FALSE, 0);
  gtk_widget_set_size_request(sidebar_box, 200, -1);

  gtk_widget_show_all(window);

  return true;
}

void SnakeDesktop::render(const GameInfo &game_info) {
  current_game_info = game_info;
  game_over = false;
  paused = game_info.pause;

  drawSidebar(game_info);
  gtk_widget_queue_draw(drawing_area);
}

void SnakeDesktop::drawField(const std::vector<std::vector<int>> &field,
                             cairo_t *cr) {
  const int cell_size = 20;
  const int offset_x = 20;
  const int offset_y = 20;

  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      int cell = field[y][x];
      int pos_x = offset_x + x * cell_size;
      int pos_y = offset_y + y * cell_size;

      if (cell == 1) {
        gdk_cairo_set_source_rgba(cr, &SNAKE_COLOR);
        cairo_rectangle(cr, pos_x, pos_y, cell_size, cell_size);
        cairo_fill(cr);
      } else if (cell == 2) {
        gdk_cairo_set_source_rgba(cr, &FOOD_COLOR);
        cairo_arc(cr, pos_x + cell_size / 2, pos_y + cell_size / 2,
                  cell_size / 2, 0, 2 * M_PI);
        cairo_fill(cr);
      }
    }
  }
}

void SnakeDesktop::drawSidebar(const GameInfo &game_info) {
  GList *children = gtk_container_get_children(GTK_CONTAINER(sidebar_box));
  for (GList *iter = children; iter != NULL; iter = iter->next) {
    gtk_widget_destroy(GTK_WIDGET(iter->data));
  }
  g_list_free(children);

  auto create_label = [](const char *text, const GdkRGBA *color) {
    GtkWidget *label = gtk_label_new(text);

    PangoAttrList *attrs = pango_attr_list_new();

    pango_attr_list_insert(
        attrs,
        pango_attr_foreground_new(static_cast<guint16>(color->red * 65535),
                                  static_cast<guint16>(color->green * 65535),
                                  static_cast<guint16>(color->blue * 65535)));

    pango_attr_list_insert(attrs, pango_attr_size_new(16 * PANGO_SCALE));

    gtk_label_set_attributes(GTK_LABEL(label), attrs);
    pango_attr_list_unref(attrs);

    return label;
  };

  char buffer[100];

  std::snprintf(buffer, sizeof(buffer), "SCORE: %d", game_info.score);
  GtkWidget *score_label = create_label(buffer, &BG_COLOR);

  std::snprintf(buffer, sizeof(buffer), "HIGH: %d", game_info.high_score);
  GtkWidget *high_score_label = create_label(buffer, &BG_COLOR);

  std::snprintf(buffer, sizeof(buffer), "LEVEL: %d", game_info.level);
  GtkWidget *level_label = create_label(buffer, &BG_COLOR);

  std::snprintf(buffer, sizeof(buffer), "SPEED: %d", game_info.speed);
  GtkWidget *speed_label = create_label(buffer, &BG_COLOR);

  GtkWidget *info_label = create_label(
      "Press R for start the game.\nPress P for pause.\nControl the movement "
      "of the snake\nusing the arrows or the WSAD key.",
      &BG_COLOR);

  gtk_box_pack_start(GTK_BOX(sidebar_box), score_label, FALSE, FALSE, 20);
  gtk_box_pack_start(GTK_BOX(sidebar_box), high_score_label, FALSE, FALSE, 20);
  gtk_box_pack_start(GTK_BOX(sidebar_box), level_label, FALSE, FALSE, 20);
  gtk_box_pack_start(GTK_BOX(sidebar_box), speed_label, FALSE, FALSE, 20);
  gtk_box_pack_start(GTK_BOX(sidebar_box), info_label, FALSE, FALSE, 20);

  gtk_widget_show_all(sidebar_box);
}

void SnakeDesktop::drawBorders(cairo_t *cr) {
  const int cell_size = 20;
  const int offset_x = 20;
  const int offset_y = 20;
  const int border_width = 2;

  gdk_cairo_set_source_rgba(cr, &BORDER_COLOR);
  cairo_set_line_width(cr, border_width);

  cairo_rectangle(cr, offset_x - border_width, offset_y - border_width,
                  FIELD_WIDTH * cell_size + 2 * border_width,
                  FIELD_HEIGHT * cell_size + 2 * border_width);
  cairo_stroke(cr);
}

void SnakeDesktop::showGameOver() {
  GtkWidget *dialog;
  GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_toplevel(drawing_area));

  dialog = gtk_message_dialog_new(parent_window, GTK_DIALOG_MODAL,
                                  GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                  "GAME OVER!\nPress START to restart");

  gtk_window_set_title(GTK_WINDOW(dialog), "Game Over");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

void SnakeDesktop::showPause() {
  cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(drawing_area));

  cairo_set_source_rgba(cr, 0, 0, 0, 0.5);
  cairo_paint(cr);

  cairo_set_source_rgb(cr, 1, 1, 0);
  cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                         CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, 24);

  const char *text = "PAUSED";
  cairo_text_extents_t extents;
  cairo_text_extents(cr, text, &extents);

  int x = (FIELD_WIDTH * 20 + 40) / 2 - extents.width / 2;
  int y = (FIELD_HEIGHT * 20 + 40) / 2 - extents.height / 2;

  cairo_move_to(cr, x, y);
  cairo_show_text(cr, text);

  cairo_destroy(cr);
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif

void SnakeDesktop::cleanup() {
  if (window) {
    gtk_widget_destroy(window);
  }
  game_view_instance = nullptr;
}

}  // namespace s21
