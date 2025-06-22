#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>

// Constants
#define MAX_STR_SIZE 1000
#define MAX_WORD_LENGTH 30
#define TOTAL_TIME 60

char ALL_WORD[MAX_STR_SIZE][MAX_WORD_LENGTH];
int TOTAL_WORD = 0; // for total words from file

//Taking string from file
void input_from_file() {
    char a[MAX_WORD_LENGTH];
    while (scanf("%s", a) != EOF) {
        if (TOTAL_WORD >= MAX_STR_SIZE) { // overflowing
            fprintf(stderr, "Too many words in the file! Maximum allowed is %d.\n", MAX_STR_SIZE);
            exit(1);
        }
        strncpy(ALL_WORD[TOTAL_WORD++], a, MAX_WORD_LENGTH - 1);
        ALL_WORD[TOTAL_WORD - 1][MAX_WORD_LENGTH - 1] = '\0'; // Ensure null-termination
    }

    if (TOTAL_WORD == 0) { // if the file hasn't any word
        endwin();
        fprintf(stderr, "No words read from input. Check the input file.\n");
    }
}

// Function prototypes
void welcome();
int selection(char *option[], int size_option);
int word_count(char str[]);
void random_word_generate(char str[], int difficulty);
void game(char level[], int selected_option);
void menu();
int correct_char(char u_str[], char str[]);
int wrong_word_count(char str[], char u_str[]);
void display_result(int _y, int time_delay, char u_str[], char str[], int num_backspace);

//Function todisplay welcome 
void welcome() {
    char *str[] = {
        "=====================",
        "=                   =",
        "=====================",
        NULL,
        "W E L C O M E"
    };
    
    int x, y;
    getmaxyx(stdscr, y, x);
    // move cursor in the middle
    for (int i = 0; str[i]; i++) {
        move((y - 2) / 2 - i, (x - strlen(str[i])) / 2);
        printw("%s", str[i]);
        refresh();
    }
    getmaxyx(stdscr, y, x);
    move((y - 4) / 2, (x - strlen(str[4])) / 2); // moving cursor in the box
    attron(A_BOLD);
    for (int i = 0; i < strlen(str[4]); i++) {
        printw("%c", str[4][i]);
        napms(50);
        refresh();
    }
    attroff(A_BOLD);
    napms(1500);
    clear();
}

//Function to select
int selection(char *option[], int size_option) {
    int selected_option = 0;
    int x, y, key = 0, _y;

    keypad(stdscr, TRUE); // for the arrows
    getmaxyx(stdscr, y, x); // move cursor in the middle
    y = (y - size_option) / 2;
    x = (x - strlen(option[0])) / 2;
    _y = y;
    noecho();
    while (key != 10) { // enter key to selection
        for (int i = 0; i < size_option; i++) {
            if (i == _y - y) {
                attron(A_REVERSE | A_BOLD);
                mvprintw(y + i, x, "  %d. %s", i + 1, option[i]); // moving cursor up or down
                attroff(A_REVERSE | A_BOLD);
            } else mvprintw(y + i, x, "  %d. %s", i + 1, option[i]);
        }  
        move(_y, x + 2);
        refresh();
        key = getch();
        if (key == KEY_UP) { // if press up key 
            _y--;
            if (_y < y) _y = y + size_option - 1; // when select option 1, pressing up key will select the last option 
        } else if (key == KEY_DOWN) { // if press down key
            _y++;
            if (_y > y + size_option - 1) _y = y; // when select option 1, pressing up key will select the last option 
        }
    }
    echo();
    keypad(stdscr, FALSE);
    selected_option = _y - y + 1;
    return selected_option;
}

//function to count word of str[]
int word_count(char str[]) {
    int num = 1;
    for (int i = 0; str[i]; i++)
        if (str[i] == ' ' && str[i + 1] != '\0' && str[i - 1] != ' ') // if find ' ' next letter != '\0' previous != ' ' then word++
            num++;
    if (strlen(str) == 0) num = 0; // if string length = 0, word = 0
    return num;
}

//checking character from file and user and return number of correct character
int correct_char(char u_str[], char str[]) {
    int i = 0, cor = 0;
    while (u_str[i] && str[i]) {
        if (u_str[i] == str[i]) cor++;
        i++;
    }
    return cor;
}

// function to count the wrong word
int wrong_word_count(char str[], char u_str[]) {
    int i = 0, j = 0, num_wrong_word = 0;
    
    while (str[i] != '\0' && u_str[j] != '\0') { // checking all character
        char temp1[MAX_WORD_LENGTH] = "", temp2[MAX_WORD_LENGTH] = "";
        int x = 0, y = 0;
        while (str[i] != ' ' && str[i] != '\0')
            temp1[x++] = str[i++]; // storing a single word
        temp1[x] = '\0'; // null character in the last
        while (u_str[j] != ' ' && u_str[j] != '\0')
            temp2[y++] = u_str[j++];
        temp2[y] = '\0';
        if (strcmp(temp1, temp2) != 0) num_wrong_word++;

        while (str[i] != '\0' && (isspace(str[i]) || str[i] == ' ')) i++; // finding ' ' character++
        while (u_str[j] != '\0' && (isspace(u_str[j]) || u_str[j] == ' ')) j++;
    }
    return num_wrong_word;
}

//function to show remain time
void timer(int x, int y, int time_rem) {
    int i;
    if (time_rem < 10) i = 3; // if time < 10, color red
    else if (time_rem >= 10 && time_rem < 30) i = 4; // if 10 <= time < 30, color yellow
    else if (time_rem >= 30) i = 2; // if time >= 30, color green
    attron(COLOR_PAIR(i) | A_BOLD);
    mvprintw(y , x, " Time : %ds ", time_rem);
    attroff(COLOR_PAIR(i) | A_BOLD);
}

//function to generate random words
void random_word_generate(char str[], int difficulty) {
    char temp[MAX_STR_SIZE][MAX_WORD_LENGTH], ch[MAX_WORD_LENGTH];
    int max_len, min_len, word_count, total_word = 0;
    
    switch (difficulty) {
        case 1: word_count = 20; min_len = 1; max_len = 4; break; // easy contains word(1-4character)
        case 2: word_count = 40; min_len = 5; max_len = 7; break; // mediam contains word(5-7character)
        case 3: word_count = 60; min_len = 8; max_len = 20; break; // hard contains word(8-20character)
    }

    //coping words from ALL_WORD to temp according to difficulty
    for (int i = 0; i < TOTAL_WORD; i++)
        if (strlen(ALL_WORD[i]) <= max_len && strlen(ALL_WORD[i]) >= min_len) 
            strcpy(temp[total_word++], ALL_WORD[i]);
    
    //when the file haven't word for the difficulty 
    if (total_word == 0) {
        int x, y;
        getmaxyx(stdscr, y, x);
        mvprintw(y / 2, x / 2 - 25, "No suitable words found for this difficulty !!!\n");
        refresh();
        napms(2000);
        menu();
    }

    //randomly choosing words
    srand(time(0));
    str[0] = '\0';
    for (int i = 0; i < word_count; i++) {
        int x = rand() % total_word;
        strcat(str, temp[x]);
        strcat(str, " "); // adding space after each word
    }
    str[strlen(str) - 1] = '\0'; // removing last space and null termination
    // No need to return because string is a pointer so in the str pointer the words will be saved
}

// function to display the result
void display_result(int _y, int time_delay, char u_str[], char str[], int num_backspace) {
    attron(A_BOLD);
    mvprintw(_y++, 5, "   ==== Result ====       ");
    attroff(A_BOLD);
    mvprintw(_y++, 5, "Time taken : %d seconds", time_delay);
    mvprintw(_y++, 5, "Correct word : %d", word_count(u_str) - wrong_word_count(str, u_str));
    mvprintw(_y++, 5, "Wrong word : %d", wrong_word_count(str, u_str));
    // accuracy = correct character - (backspace) / total character * 100%
    float accuracy = (((float)correct_char(u_str, str) - num_backspace) / (float)strlen(u_str)) * 100;
    if (accuracy >= 0 && accuracy <= 100) // if accuracy remains 0-100
    mvprintw(_y++, 5, "Accuracy : %.2f%%", accuracy);
    else
    mvprintw(_y++, 5, "Accuracy : 0.00%%");
    mvprintw(_y++, 5, "Correct character : %d", correct_char(u_str, str));
    mvprintw(_y++, 5, "Wrong character : %d", strlen(u_str) - correct_char(u_str, str));
    mvprintw(_y++, 5, "CPS : %.2f", (float)correct_char(u_str, str) / time_delay);
    float correct_words = word_count(u_str) - wrong_word_count(str, u_str);
    //WPS = correct word * 60 / time
    float wpm = (correct_words * 60.0f) / time_delay; 
    if (time_delay == 0)
        mvprintw(_y++, 5, "WPM : N/A (Time taken was zero)");
    else 
        mvprintw(_y++, 5, "WPM : %.2f\n", wpm);
    mvprintw(_y++, 5, "Press enter to continue...");
    refresh();
    getch();
}

void game(char level[], int selected_option) {
    // Clear the screen and refresh the display
    clear();
    refresh();

    int x, y;
    char u_str[MAX_STR_SIZE]; // User input string
    char str[MAX_STR_SIZE];  // Randomly generated string
    random_word_generate(str, selected_option); // Generate random words based on difficulty

    // Initialize color pairs for ncurses
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLUE);
    init_pair(6, COLOR_BLACK, COLOR_RED);
    init_pair(7, COLOR_BLACK, COLOR_BLUE);

    // Calculate the length of the difficulty level string length without space
    int len = 0;
    while (level[len++] != ' ') ;

    // Center the difficulty level text on the screen
    getmaxyx(stdscr, y, x);
    x = (x - len) / 2 - 18;
    y = y / 2 - 12;
    mvprintw(y - 5, x, "======= Difficulty level : ");
    attron(A_BOLD);
    for (int i = 0; i < len; i++) printw("%c", level[i]);
    attroff(A_BOLD);
    printw("=======");

    // Display instructions for the user
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(y - 2, x - 9, "Press 'ENTER' to start, 'ESC' to end and 'TAB' to restart.");
    attroff(COLOR_PAIR(1) | A_BOLD);
    refresh();

    // Wait for the user to press 'ENTER' to start
    noecho();
    while ((getch()) != 10) ;
    echo();

    // Initialize variables for displaying the random string
    int i = 0, _x, _y;
    getmaxyx(stdscr, y, x);
    _x = x = x / 5;
    _y = y = y / 2 - 10;

    // Display the random string 3/5 th middle of the screen
    while (str[i]) {
        if (_x > x * 4) {
            _x = x;
            _y++;
        }
        attron(COLOR_PAIR(7));
        refresh();
        mvprintw(_y, _x, "%c", str[i]);
        refresh();
        attroff(COLOR_PAIR(7));
        i++;
        _x++;
    }
    refresh();

    // Initialize variables for user input and timing
    getmaxyx(stdscr, y, x);
    _x = x = x / 5;
    _y = y = y / 2 - 10;
    time_t start_time = 0, end_time = 0;
    int time_delay = 0;

    noecho();
    int num_backspace = 0;
    int k = 0;
    char ch;
    start_time = time(NULL);
    keypad(stdscr, TRUE);

    // Main loop for user input
    do {
        // Display the remaining time
        timer(x, y - 2, TOTAL_TIME - time_delay);
        if (time_delay >= TOTAL_TIME) {
            nodelay(stdscr, TRUE);
            break;
        }
        move(_y, _x);
        if (_x > x * 4) {
            _x = x;
            _y++;
            move(_y, _x);
        } 
        refresh();
        ch = getch();

        // Handle backspace
        if (ch == 127 || ch == '\b') {
            if (k > 0) {
                printw("\b \b");
                k--;
                u_str[k] = '\0';
                if (_x < x + 1) {
                    _x = x * 4;
                    _y--;
                    move(_y, _x);
                } else move(_y, --_x);
                attron(COLOR_PAIR(7));
                refresh();
                printw("%c", str[k]);
                refresh();
                attroff(COLOR_PAIR(7));
                num_backspace++;
            }
        }
        // Handle 'TAB' key to restart the game
        else if (ch == 9) game(level, selected_option);
        // Handle 'ESC' key to exit the game
        else if (ch == 27) break;
        // Ignore invalid characters
        else if ((ch < 65 || (ch > 90 && ch < 97) || ch > 122) && ch != ' ') ;
        // Handle correct character input
        else if (ch == str[k]) {
            u_str[k] = ch;
            k++;
            attron(COLOR_PAIR(2) | A_BOLD);
            printw("%c", ch);
            attroff(COLOR_PAIR(2) | A_BOLD);
            refresh();
            move(_y, ++_x);
        }
        // Handle incorrect character input
        else {
            int x = (str[k] == ' ') ? 6 : 3;
            attron(COLOR_PAIR(x) | A_BOLD);
            printw("%c", str[k]);
            attroff(COLOR_PAIR(x) | A_BOLD);
            u_str[k] = ch;
            k++;
            refresh();
            move(_y, ++_x);
        }
        end_time = time(NULL);
        refresh();
        time_delay = difftime(end_time, start_time);
    } while (k < strlen(str));

    // Reset input settings
    keypad(stdscr, FALSE);
    echo();
    nodelay(stdscr, FALSE);
    u_str[k] = '\0';
    refresh();

    // Display the result
    _y = _y + 15;
    mvprintw(_y, 5, "Press enter for result");

    noecho();
    while (getch() != 10);
    echo();
    refresh();

    display_result(_y, time_delay, u_str, str, num_backspace);
    menu(); // Return to the menu
}
//function to show menu
void menu() {
    char *option[] = {
        "Easy       ",
        "Medium     ",
        "Hard       ",
        "Exit       "
    };
    int size_option = sizeof(option) / sizeof(option[0]); // total options
    int x, y;
    clear();
    refresh();
    getmaxyx(stdscr, y, x); // moving cursor to the middle
    y = (y - size_option) / 2 - 1;
    x = (x - strlen(option[0])) / 2 - 5;

    attron(A_BOLD);
    mvprintw(y, x, "==== Difficulty Level ====");
    attroff(A_BOLD);
    // printing options after a time delay
    for (int i = 0; i < size_option; i++) {
        mvprintw(++y, x, "       %d. ", i + 1);
        for (int j = 0; j < strlen(option[i]); j++) {
            if (option[i][j] == ' ') break;
            printw("%c", option[i][j]);
            napms(50);
            refresh();
        }
        printw("\n");
    }
    int selected_option = selection(option, size_option);
    
    if (selected_option >= 1 && selected_option <= 3) { // difficulty level
        game(option[selected_option - 1], selected_option);
    } else if (selected_option == 4) { // exit
        clear();
        refresh();
        getmaxyx(stdscr, y, x);
        attron(A_BOLD);
        mvprintw(y / 2, x / 2 - 10, "== Thanks for playing ==");
        refresh();
        attroff(A_BOLD);
        napms(1000);
        clear();
        refresh();
        exit(1);
    }
}

int main() {
    initscr();
    input_from_file();
    cbreak();

    // *** THIS IS THE CRUCIAL ADDITION ***
    if (freopen("/dev/tty", "r", stdin) == NULL) {  // Reopen stdin as /dev/tty
        endwin();
        fprintf(stderr, "Error reopening /dev/tty.\n"); // if file doesn't exist
        return 1;
    }

    
    welcome();
    menu();
    refresh();
    getch();
    endwin();
    return 0;
}