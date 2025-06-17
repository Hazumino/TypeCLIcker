#ifndef SETTING_H
#define SETTING_H

#include <ncurses.h>

typedef enum {
    KEYBOARD_US = 1,
    KEYBOARD_DVORAK = 2
} keyboard_layout_t;

typedef struct {
    keyboard_layout_t keyboard_layout;
    int words_per_line;
    int total_words;
} user_settings_t;

// Global settings instance
extern user_settings_t g_settings;

// Function declarations
void settings();
void init_default_settings();
int load_settings();
int save_settings();
void settings_menu(WINDOW *win);
int settings_menu_handler(WINDOW *win);

#endif /* ifndef  */
