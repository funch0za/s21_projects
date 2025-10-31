#include "app.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

namespace s21 {

#ifdef CLI_UI

void app::menu() {
  int ch = 0;

  while (ch != 'q') {
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    mvprintw(5, 0, "%s",
             "\t#### BRICK GAME 2.0 ###\n\nPress the [S] button to start "
             "Snake\nPress "
             "the [T] button to start Tetris\nPress the [Q] button to exit");

    refresh();

    ch = getch();
    if (ch == 's') {
      clear();
      refresh();
      snake_loop();
    } else if (ch == 't') {
      clear();
      refresh();
      tetris_loop();
    }
  }

  clear();
  endwin();
}

void app::tetris_loop() {
  srand(time(0));

  init_curses();
  draw_welcome();
  WINDOW *game, *hiscore, *score, *level, *next;
  init_windows(&game, &hiscore, &score, &level, &next);

  userInput(Start);

  GameInfo_t cur_tetris = updateCurrentState();
  update_screen(cur_tetris, &game, &hiscore, &score, &level, &next);

  int cnt_score = 0, cnt_level = 0;
  while (!GAME_IS_OVER) {
    cur_tetris = updateCurrentState();
    cnt_score = cur_tetris.score;
    cnt_level = cur_tetris.level;
    update_screen(cur_tetris, &game, &hiscore, &score, &level, &next);
    halfdelay(10 - cur_tetris.level);
    input_key();
  }

  delete_windows(&game, &hiscore, &score, &level, &next);
  draw_goodbye(cnt_score, cnt_level);

  endwin();
}

void app::snake_loop() {
  SnakeController controller;
  SnakeCLI view;

  if (!view.initialize()) {
    return;
  }

  bool running = true;
  bool game_started = false;

  GameInfo info = controller.updateCurrentState();
  view.render(info);
  refresh();

  while (running) {
    halfdelay(info.speed);
    int ch = getch();

    switch (ch) {
      case 'w':
      case KEY_UP:
        if (game_started) {
          controller.userInput(UserAction::Up, true);
        }
        break;
      case 's':
      case KEY_DOWN:
        if (game_started) {
          controller.userInput(UserAction::Down, true);
        }
        break;
      case 'a':
      case KEY_LEFT:
        if (game_started) {
          controller.userInput(UserAction::Left, true);
        }
        break;
      case 'd':
      case KEY_RIGHT:
        if (game_started) {
          controller.userInput(UserAction::Right, true);
        }
        break;
      case ' ':
        if (game_started) {
          controller.userInput(UserAction::Action, true);
        }
        break;
      case 'p':
        if (game_started) {
          controller.userInput(UserAction::Pause, true);
        }
        break;
      case 'r':
        controller.userInput(UserAction::Start, true);
        game_started = true;
        break;
      case 'q':
        controller.userInput(UserAction::Terminate, true);
        running = false;
        break;
      default:
        if (game_started) {
          controller.userInput(UserAction::Action, false);
        }
    }

    info = controller.updateCurrentState();
    view.render(info);

    if (info.pause) {
      mvprintw(22, 2, "Game PAUSED - Press P to resume");
    }
    refresh();
  }

  view.cleanup();
}

#elif defined(DESKTOP_UI)

static void signal_loop_tetris_desktop([[maybe_unused]] GtkWidget* widget,
                                       [[maybe_unused]] gpointer data) {
  app::tetris_loop();
}

static void signal_loop_snake_desktop([[maybe_unused]] GtkWidget* widget,
                                      [[maybe_unused]] gpointer data) {
  app::snake_loop();
}

static void signal_exit_desktop([[maybe_unused]] GtkWidget* widget,
                                [[maybe_unused]] gpointer data) {
  gtk_main_quit();
}

void app::menu() {
  gtk_init(NULL, NULL);

  /* MAIN WINDOW */
  GtkWidget* menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(menu), "Brick Game v2");
  gtk_window_set_default_size(GTK_WINDOW(menu), 400, 400);
  g_signal_connect(menu, "destroy", G_CALLBACK(gtk_main_quit), nullptr);
  gtk_container_set_border_width(GTK_CONTAINER(menu), 10);

  /* MAIN BOX */
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_container_add(GTK_CONTAINER(menu), box);

  /* WELCOME LABEL */
  GtkWidget* welcome = gtk_label_new("");
  gtk_label_set_markup(GTK_LABEL(welcome),
                       "<span font='30'>BRICK GAME v2</span>");
  gtk_box_pack_start(GTK_BOX(box), welcome, FALSE, FALSE, 0);

  /* GAME BUTTON */
  GtkWidget* start_tetris = gtk_button_new_with_label("");
  GtkWidget* start_snake = gtk_button_new_with_label("");
  /* EXIT BUTTON */
  GtkWidget* exit_app = gtk_button_new_with_label("");

  gtk_label_set_markup(GTK_LABEL(gtk_bin_get_child(GTK_BIN(start_tetris))),
                       "<span font='30'>START TETRIS</span>");
  gtk_label_set_markup(GTK_LABEL(gtk_bin_get_child(GTK_BIN(start_snake))),
                       "<span font='30'>START SNAKE</span>");
  gtk_label_set_markup(GTK_LABEL(gtk_bin_get_child(GTK_BIN(exit_app))),
                       "<span font='30'>EXIT</span>");

  g_signal_connect(start_tetris, "clicked",
                   G_CALLBACK(signal_loop_tetris_desktop), nullptr);
  g_signal_connect(start_snake, "clicked",
                   G_CALLBACK(signal_loop_snake_desktop), nullptr);
  g_signal_connect(exit_app, "clicked", G_CALLBACK(signal_exit_desktop),
                   nullptr);

  gtk_box_pack_start(GTK_BOX(box), start_tetris, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), start_snake, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), exit_app, TRUE, TRUE, 0);

  g_signal_connect(menu, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(menu);

  gtk_main();
}

void app::tetris_loop() {
  userInput(Start);
  game_state = ::updateCurrentState();

  /* MAIN WINDOW */
  main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(main_window), "Tetris");
  gtk_window_set_default_size(GTK_WINDOW(main_window), 600, 600);
  gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);

  /* CLOSE WINDOW */
  g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  /* UI */
  GtkWidget* main_content = ::create_tetris_ui();
  gtk_container_add(GTK_CONTAINER(main_window), main_content);

  /* KEY CONTROLLER */
  g_signal_connect(main_window, "key-press-event", G_CALLBACK(on_key_pressed),
                   NULL);

  /* TIMER FOR UPDATE */
  game_timer = g_timeout_add(100, game_update_timer, NULL);

  /* TIMER FOR FALL FIGURE */
  fall_timer = g_timeout_add(1000, auto_fall_timer, NULL);

  gtk_widget_show_all(main_window);

  update_ui();

  /* GAME LOOP */
  gtk_main();

  if (game_timer) {
    g_source_remove(game_timer);
  }
  if (fall_timer) {
    g_source_remove(fall_timer);
  }
}

SnakeController* g_controller = nullptr;
SnakeDesktop* g_view = nullptr;
bool g_game_started = false;
guint g_timer_id = 0;

static gboolean game_update_callback([[maybe_unused]] gpointer data) {
  if (g_controller && g_view && g_game_started) {
    GameInfo info = g_controller->updateCurrentState();
    g_view->render(info);

    g_controller->userInput(UserAction::Action, false);
    if (g_view->game_over) {
      g_view->showGameOver();
      g_timer_id = 0;
      return FALSE;
    }
  }
  return TRUE;
}

static gboolean on_key_press([[maybe_unused]] GtkWidget* widget,
                             GdkEventKey* event,
                             [[maybe_unused]] gpointer data) {
  if (!g_controller) return FALSE;

  auto create_timer = [](guint speed_) -> guint {
    return g_timeout_add(speed_ * 20, game_update_callback, NULL);
  };

  switch (event->keyval) {
    case GDK_KEY_Up:
    case GDK_KEY_w:
    case GDK_KEY_W:
      if (g_game_started) {
        g_controller->userInput(UserAction::Up, true);
      }
      break;

    case GDK_KEY_Down:
    case GDK_KEY_s:
    case GDK_KEY_S:
      if (g_game_started) {
        g_controller->userInput(UserAction::Down, true);
      }
      break;

    case GDK_KEY_Left:
    case GDK_KEY_a:
    case GDK_KEY_A:
      if (g_game_started) {
        g_controller->userInput(UserAction::Left, true);
      }
      break;

    case GDK_KEY_Right:
    case GDK_KEY_d:
    case GDK_KEY_D:
      if (g_game_started) {
        g_controller->userInput(UserAction::Right, true);
      }
      break;

    case GDK_KEY_space:
      if (g_game_started) {
        g_controller->userInput(UserAction::Action, true);
        GameInfo info = g_controller->updateCurrentState();
        if (g_timer_id) {
          g_source_remove(g_timer_id);
          g_timer_id = create_timer(info.speed);
        }
      }
      break;

    case GDK_KEY_p:
    case GDK_KEY_P:
      if (g_game_started) {
        g_controller->userInput(UserAction::Pause, true);
        GameInfo info = g_controller->updateCurrentState();
        if (info.pause) {
          g_view->showPause();
        } else {
          if (!g_timer_id) {
            g_timer_id = create_timer(info.speed);
          }
        }
      }
      break;

    case GDK_KEY_r:
    case GDK_KEY_R:
      g_controller->userInput(UserAction::Start, true);
      g_game_started = true;
      if (!g_timer_id) {
        GameInfo info = g_controller->updateCurrentState();
        g_timer_id = create_timer(info.speed);
      }
      break;

    case GDK_KEY_q:
    case GDK_KEY_Q:
      g_controller->userInput(UserAction::Terminate, true);
      if (g_timer_id) {
        g_source_remove(g_timer_id);
        g_timer_id = 0;
      }
      gtk_main_quit();
      break;

    default:
      if (g_game_started) {
        g_controller->userInput(UserAction::Action, false);
      }
  }

  return TRUE;
}

void app::snake_loop(void) {
  g_controller = new SnakeController();
  g_view = new SnakeDesktop();

  int argc = 0;
  char** argv = nullptr;
  if (!g_view->initialize(argc, argv)) {
    std::cerr << "Failed to initialize GTK view!" << std::endl;
    delete g_view;
    delete g_controller;
    return;
  }

  g_signal_connect(g_view->window, "key-press-event", G_CALLBACK(on_key_press),
                   NULL);

  GameInfo initial_info = g_controller->updateCurrentState();
  g_view->render(initial_info);

  gtk_main();

  if (g_timer_id) {
    g_source_remove(g_timer_id);
  }
  delete g_view;
  delete g_controller;
  g_view = nullptr;
  g_controller = nullptr;
}

#else

void app::menu() { std::cout << "NO UI\n"; }

void app::tetris_loop() {}

void app::snake_loop() {}

#endif

}  // namespace s21
