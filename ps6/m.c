#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 200
#define COLS 200
#define MAX_DIGITS 10

void get_map(char array[ROWS][COLS], int *rows, int *cols) {
    int ch;

    *rows = 0;
    *cols = 0;

    FILE *file = fopen("map.txt", "r");

    if (file == NULL) {
        perror("Error loading the map");
        return;  // Return early if the file can't be opened
    }

    while ((ch = fgetc(file)) != EOF && *rows < ROWS && *cols < COLS - 1) {
        if (ch != '\n') {
            array[*rows][*cols] = (char)ch;
            (*cols)++;
        } else {
            array[*rows][*cols] = '\0';
            (*rows)++;
            *cols = 0;
        }
    }

    fclose(file);  // Close the file after reading

    (*rows)++;

    for (int i = 0; i < *rows; i++) {
        array[i][*cols] = '\0';
    }
}

void draw_map(char map[ROWS][COLS], int rows, int cols, int playerRow, int playerCol, int digits[MAX_DIGITS][2], int *numDigits) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int isDigit = 0;

            // Check if the current position has a digit
            for (int i = 0; i < *numDigits; i++) {
                if (row == digits[i][0] && col == digits[i][1]) {
                    isDigit = 1;
                    break;
                }
            }

            if (isDigit) {
                attron(COLOR_PAIR(4)); // Digit color pair
                mvaddch(row + 3, col + 2, '0'); // Display '0' for digits
                attroff(COLOR_PAIR(4));
            } else if (row == playerRow && col == playerCol) {
                // Draw the player character
                attron(COLOR_PAIR(3)); // Player color pair
                mvaddch(row + 3, col + 2, 'P');
                attroff(COLOR_PAIR(3));
            } else if (map[row][col] == '#') {
                attron(COLOR_PAIR(1)); // Wall color
                mvaddch(row + 3, col + 2, map[row][col]);
                attroff(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2)); // Empty space color
                mvaddch(row + 3, col + 2, map[row][col]);
                attroff(COLOR_PAIR(2));
            }
        }
    }
}

void generate_digits(int digits[MAX_DIGITS][2], int *numDigits, int rows, int cols, char array[ROWS][COLS]) {
    // Generate random positions for digits
    for (int i = 0; i < MAX_DIGITS; i++) {
        do {
            digits[i][0] = rand() % rows;
            digits[i][1] = rand() % cols;
        } while (array[digits[i][0]][digits[i][1]] == '#' || array[digits[i][0]][digits[i][1]] == '0' || array[digits[i][0]][digits[i][1]] == 'P');
    }
    *numDigits = MAX_DIGITS;
}

void handle_user_input(int *playerRow, int *playerCol, int rows, int cols, char array[ROWS][COLS]) {
    int key = getch();

    switch (key) {
        case KEY_UP:
            if (*playerRow > 0 && array[*playerRow - 1][*playerCol] != '#') {
                (*playerRow)--;
            }
            break;
        case KEY_DOWN:
            if (*playerRow < rows - 1 && array[*playerRow + 1][*playerCol] != '#') {
                (*playerRow)++;
            }
            break;
        case KEY_LEFT:
            if (*playerCol > 0 && array[*playerRow][*playerCol - 1] != '#') {
                (*playerCol)--;
            }
            break;
        case KEY_RIGHT:
            if (*playerCol < cols - 1 && array[*playerRow][*playerCol + 1] != '#') {
                (*playerCol)++;
            }
            break;
        case 27: // Escape key
            endwin(); // End curses mode
            exit(0);  // Exit the program
        default:
            break;
    }
}

void collect_digits(int digits[MAX_DIGITS][2], int *numDigits, int playerRow, int playerCol) {
    // Check if the player collects a digit
    for (int i = 0; i < *numDigits; i++) {
        if (playerRow == digits[i][0] && playerCol == digits[i][1]) {
            digits[i][0] = -1; // Mark the collected digit for removal
        }
    }
}

void remove_collected_digits(int digits[MAX_DIGITS][2], int *numDigits) {
    // Remove collected digits
    int j = 0;
    for (int i = 0; i < *numDigits; i++) {
        if (digits[i][0] != -1) {
            digits[j][0] = digits[i][0];
            digits[j][1] = digits[i][1];
            j++;
        }
    }
    *numDigits = j;
}

void generate_new_digits(int digits[MAX_DIGITS][2], int *numDigits, int rows, int cols, char array[ROWS][COLS]) {
    // Generate new digits if needed
    while (*numDigits < MAX_DIGITS) {
        do {
            digits[*numDigits][0] = rand() % rows;
            digits[*numDigits][1] = rand() % cols;
        } while (array[digits[*numDigits][0]][digits[*numDigits][1]] == '#' || array[digits[*numDigits][0]][digits[*numDigits][1]] == '0' || array[digits[*numDigits][0]][digits[*numDigits][1]] == 'P');
        (*numDigits)++;
    }
}

void start_game() {
    int rows, cols;
    char array[ROWS][COLS];
    get_map(array, &rows, &cols);

    int playerRow = 0; // Initial player row position
    int playerCol = 0; // Initial player column position

    int digits[MAX_DIGITS][2]; // Array to store digit positions
    int numDigits = 0;

    generate_digits(digits, &numDigits, rows, cols, array);

    // Game loop
    while (1) {
        clear();
        draw_map(array, rows, cols, playerRow, playerCol, digits, &numDigits);
        refresh();

        handle_user_input(&playerRow, &playerCol, rows, cols, array);
        collect_digits(digits, &numDigits, playerRow, playerCol);
        remove_collected_digits(digits, &numDigits);
        generate_new_digits(digits, &numDigits, rows, cols, array);
    }
}

void print_menu(int highlight) {
    // Print the menu options
    mvprintw(1, 2, "Select an option:");
    mvprintw(3, 2, "1. Start Game");
    mvprintw(4, 2, "2. Exit");

    // Highlight the current selection
    attron(COLOR_PAIR(1));
    mvprintw(2 + highlight, 2, "->");
    attroff(COLOR_PAIR(1));
}

int get_menu_choice() {
    int highlight = 1;
    int choice = 0;
    int c;

    while (1) {
        clear();  // Clear the screen
        print_menu(highlight);
        refresh();  // Refresh the screen

        // Get user input
        c = getch();

        switch (c) {
            case KEY_UP:
                highlight--;
                if (highlight < 1) {
                    highlight = 1;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight > 2) {
                    highlight = 2;
                }
                break;
            case 10:  // Enter key
                choice = highlight;
                break;
            default:
                break;
        }

        if (choice != 0) {
            break;  // Exit the loop if a choice is made
        }
    }

    return choice;
}

int main() {
    // Initialize curses
    initscr();
    raw();                  // Disable line buffering
    keypad(stdscr, TRUE);   // Enable special keys

    // Set up colors if supported
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);    // Wall color pair
        init_pair(2, COLOR_GREEN, COLOR_BLACK);  // Empty space color pair
        init_pair(3, COLOR_WHITE, COLOR_BLACK);  // Player color pair
        init_pair(4, COLOR_YELLOW, COLOR_BLACK); // Digit color pair
    }

    int choice;

    while (1) {
        clear();  // Clear the screen
        choice = get_menu_choice();

        // Perform actions based on the selected option
        switch (choice) {
            case 1:
                clear();
                mvprintw(1, 2, "Starting the game...");
                start_game();
                break;
            case 2:
                endwin(); // End curses mode
                exit(0);  // Exit the program
                break;
            default:
                break;
        }
    }

    return 0;
}