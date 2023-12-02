#include <curses.h>
#include <string.h>


int main() {
    // Initialize ncurses
    initscr();
    cbreak();  // Disable line buffering
    noecho();  // Disable automatic echoing of characters
    keypad(stdscr, TRUE);  // Enable special keys

    // Get screen dimensions
    int height, width;
    getmaxyx(stdscr, height, width);

    // Starting position
    int x = 0;
    int y = height / 2;

    // Text to be moved
    const char *message = "Hello, moving text!";

    // Main animation loop
    while (1) {
        clear();  // Clear the screen

        // Print the message at the current position
        mvprintw(y, x, "%s", message);

        // Refresh the screen
        refresh();

        // Pause for a short time to control the speed of the animation
        napms(100);  // 100 milliseconds

        // Move the text to the right
        x++;

        // Check if the text has reached the right edge of the screen
        if (x > width - strlen(message)) {
            x = 0;  // Move the text back to the left
        }
    }

    // Clean up
    endwin();

    return 0;
}