#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "settings.h"
#include "main_menu.h"

// Global settings instance
user_settings_t g_settings;

void init_default_settings()
{
    g_settings.keyboard_layout = KEYBOARD_US;
    g_settings.words_per_line = 15;
    g_settings.total_words = 80;
}

int load_settings()
{
    FILE *file = fopen("settings.conf", "r");
    if (file == NULL) {
        init_default_settings();
        return 0; // No existing settings file, use defaults
    }
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "keyboard_layout=", 16) == 0) {
            g_settings.keyboard_layout = atoi(line + 16);
        } else if (strncmp(line, "words_per_line=", 15) == 0) {
            g_settings.words_per_line = atoi(line + 15);
        } else if (strncmp(line, "total_words=", 12) == 0) {
            g_settings.total_words = atoi(line + 12);
        }
    }
    
    fclose(file);
    return 1; // Successfully loaded settings
}

int save_settings()
{
    FILE *file = fopen("settings.conf", "w");
    if (file == NULL) {
        return 0; // Failed to save
    }
    
    fprintf(file, "keyboard_layout=%d\n", g_settings.keyboard_layout);
    fprintf(file, "words_per_line=%d\n", g_settings.words_per_line);
    fprintf(file, "total_words=%d\n", g_settings.total_words);
    
    fclose(file);
    return 1; // Successfully saved
}

void settings_menu(WINDOW *win)
{
    int rows, cols;
    getmaxyx(win, rows, cols);
    
    wclear(win);
    box(win, 0, 0);
    
    // Title
    mvwprintw(win, 2, (cols - 8) / 2, "SETTINGS");
    
    // Menu options
    mvwprintw(win, 5, 4, "1. Keyboard Layout: %s", 
              g_settings.keyboard_layout == KEYBOARD_US ? "US QWERTY" : "DVORAK");
    mvwprintw(win, 6, 4, "2. Words per line: %d", g_settings.words_per_line);
    mvwprintw(win, 7, 4, "3. Total words: %d", g_settings.total_words);
    mvwprintw(win, 9, 4, "4. Save Settings");
    mvwprintw(win, 10, 4, "5. Back to Main Menu");
    
    mvwprintw(win, rows - 3, 4, "Use 1-5 to select option");
    
    wrefresh(win);
}

int settings_menu_handler(WINDOW *win)
{
    int ch;
    int rows, cols;
    getmaxyx(win, rows, cols);
    
    while ((ch = getch()) != ERR) {
        switch (ch) {
            case '1': // Keyboard Layout
                g_settings.keyboard_layout = (g_settings.keyboard_layout == KEYBOARD_US) ? 
                                           KEYBOARD_DVORAK : KEYBOARD_US;
                break;
                
            case '2': // Words per line
                mvwprintw(win, rows - 2, 4, "Enter words per line (5-25): ");
                wrefresh(win);
                echo();
                curs_set(1);
                char input[10];
                wgetnstr(win, input, 9);
                int new_words = atoi(input);
                if (new_words >= 5 && new_words <= 25) {
                    g_settings.words_per_line = new_words;
                }
                noecho();
                curs_set(0);
                break;
                
            case '3': // Total words
                mvwprintw(win, rows - 2, 4, "Enter total words (20-200): ");
                wrefresh(win);
                echo();
                curs_set(1);
                char input2[10];
                wgetnstr(win, input2, 9);
                int new_total = atoi(input2);
                if (new_total >= 20 && new_total <= 200) {
                    g_settings.total_words = new_total;
                }
                noecho();
                curs_set(0);
                break;
                
            case '4': // Save Settings
                if (save_settings()) {
                    mvwprintw(win, rows - 2, 4, "Settings saved successfully! Press any key...");
                } else {
                    mvwprintw(win, rows - 2, 4, "Failed to save settings! Press any key...");
                }
                wrefresh(win);
                getch();
                break;
                
            case '5': // Back
            case 'q':
            case 'Q':
                return 0;
        }
        
        settings_menu(win);
    }
    
    return 1;
}

void settings()
{
    int rows, cols;
    
    // Get terminal size
    getmaxyx(stdscr, rows, cols);
    WINDOW *win = newwin(rows, cols, 0, 0);
    
    settings_menu(win);
    settings_menu_handler(win);
    
    delwin(win);
}

