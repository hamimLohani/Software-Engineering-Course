#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Constants
#define MAX_STR_SIZE 1000
#define MAX_WORD_LENGTH 30
#define TOTAL_TIME 60

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
void history(char level[30]);

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
    for (int i = 0; str[i]; i++) {
        move((y - 2) / 2 - i, (x - strlen(str[i])) / 2);
        printw("%s", str[i]);
        refresh();
    }
    getmaxyx(stdscr, y, x);
    move((y - 4) / 2, (x - strlen(str[4])) / 2);
    attron(A_BOLD);
    for (int i = 0; i < strlen(str[4]); i++) {
        printw("%c", str[4][i]);
        napms(50);
        refresh();
    }
    attroff(A_BOLD);
    napms(1000);
    clear();
}

int selection(char *option[], int size_option) {
    int selected_option = 0;
    int x, y, key, _y;

    keypad(stdscr, TRUE);
    getmaxyx(stdscr, y, x);
    y = (y - size_option) / 2;
    x = (x - strlen(option[0])) / 2;
    _y = y;
    noecho();
    while (key != 10) {
        for (int i = 0; i < size_option; i++) {
            if (i == _y - y) {
                attron(A_REVERSE | A_BOLD);
                mvprintw(y + i, x, "  %d. %s", i + 1, option[i]);
                attroff(A_REVERSE | A_BOLD);
            } else mvprintw(y + i, x, "  %d. %s", i + 1, option[i]);
        }  
        move(_y, x + 2);
        refresh();
        key = getch();
        if (key == KEY_UP) {
            _y--;
            if (_y < y) _y = y + size_option - 1;
        } else if (key == KEY_DOWN) {
            _y++;
            if (_y > y + size_option - 1) _y = y;
        }
    }
    echo();
    keypad(stdscr, FALSE);
    selected_option = _y - y + 1;
    return selected_option;
}

int word_count(char str[]) {
    int num = 1;
    for (int i = 0; str[i]; i++)
        if (str[i] == ' ' && str[i + 1] != '\0' && str[i - 1] != ' ')
            num++;
    if (strlen(str) == 0) num = 0;
    return num;
}

int correct_char(char u_str[], char str[]) {
    int i = 0, cor = 0;
    while (u_str[i] && str[i]) {
        if (u_str[i] == str[i]) cor++;
        i++;
    }
    return cor;
}

int wrong_word_count(char str[], char u_str[]) {
    int i = 0, j = 0, num_wrong_word = 0;
    
    while (str[i] != '\0' && u_str[j] != '\0') {
        char temp1[MAX_WORD_LENGTH] = "", temp2[MAX_WORD_LENGTH] = "";
        int x = 0, y = 0;
        while (str[i] != ' ' && str[i] != '\0')
            temp1[x++] = str[i++];
        temp1[x] = '\0';
        while (u_str[j] != ' ' && u_str[j] != '\0')
            temp2[y++] = u_str[j++];
        temp2[y] = '\0';
        if (strcmp(temp1, temp2) != 0) num_wrong_word++;

        while (str[i] != '\0' && (isspace(str[i]) || str[i] == ' ')) i++;
        while (u_str[j] != '\0' && (isspace(u_str[j]) || u_str[j] == ' ')) j++;
    }
    return num_wrong_word;
}

void timer(int x, int y, int time_rem) {
    int i;
    if (time_rem < 10) i = 3;
    else if (time_rem >= 10 && time_rem < 30) i = 4;
    else if (time_rem >= 30) i = 2;
    attron(COLOR_PAIR(i) | A_BOLD);
    mvprintw(y , x, " Time : %ds ", time_rem);
    attroff(COLOR_PAIR(i) | A_BOLD);
}

void random_word_generate(char str[], int difficulty) {
    char temp[MAX_STR_SIZE][MAX_WORD_LENGTH], ch[MAX_WORD_LENGTH];
    int max_len, min_len, word_count, total_word = 0;
    FILE *fp;

    fp = fopen("word_pool.txt", "r");
    if (fp == NULL) {
        int x, y;
        getmaxyx(stdscr, y, x);
        mvprintw(y / 2, x / 2 - 25, "No file found !!!\n");
        refresh();
        napms(2000);
        menu();
    }

    switch (difficulty) {
        case 1: word_count = 20; min_len = 1; max_len = 4; break;
        case 2: word_count = 40; min_len = 5; max_len = 7; break;
        case 3: word_count = 60; min_len = 8; max_len = 20; break;
        default: word_count = 20; min_len = 1; max_len = 4; break;
    }

    while (fscanf(fp, "%s", ch) != EOF)
        if (strlen(ch) <= max_len && strlen(ch) >= min_len) 
            strcpy(temp[total_word++], ch);
    fclose(fp);

    if (total_word == 0) {
        int x, y;
        getmaxyx(stdscr, y, x);
        move(y / 2, x / 2 - 25);
        printw("No suitable words found for this difficulty !!!\n");
        refresh();
        napms(2000);
        menu();
    }
    

    srand(time(0));
    str[0] = '\0';
    for (int i = 0; i < word_count; i++) {
        int x = rand() % total_word;
        strcat(str, temp[x]);
        strcat(str, " ");
    }
    str[strlen(str) - 1] = '\0';
}

void display_result(int _y, int time_delay, char u_str[], char str[], int num_backspace) {
    attron(A_BOLD);
    mvprintw(_y++, 5, "   ==== Result ====       ");
    attroff(A_BOLD);
    mvprintw(_y++, 5, "Time taken : %d seconds", time_delay);
    mvprintw(_y++, 5, "Correct word : %d", word_count(u_str) - wrong_word_count(str, u_str));
    mvprintw(_y++, 5, "Wrong word : %d", wrong_word_count(str, u_str));
    float accuracy = (((float)correct_char(u_str, str) - num_backspace) / (float)strlen(u_str)) * 100;
    if (accuracy >= 0 && accuracy <= 100)
    mvprintw(_y++, 5, "Accuracy : %.2f%%", accuracy);
    else
    mvprintw(_y++, 5, "Accuracy : 0.00%%");
    mvprintw(_y++, 5, "Correct character : %d", correct_char(u_str, str));
    mvprintw(_y++, 5, "Wrong character : %d", strlen(u_str) - correct_char(u_str, str));
    mvprintw(_y++, 5, "CPS : %.2f", (float)correct_char(u_str, str) / time_delay);
    float correct_words = word_count(u_str) - wrong_word_count(str, u_str);
    float wpm = (correct_words * 60.0f) / time_delay; 
    if (time_delay == 0)
        mvprintw(_y++, 5, "WPM : N/A (Time taken was zero)");
    else 
        mvprintw(_y++, 5, "WPM : %.2f\n", wpm);
    
    char ch;
    do {
        refresh();
        mvprintw(_y++, 5, "Do you want to save your result? (y/n) : ");
        ch = getch();
        if (ch == 'n') {
            mvprintw(_y++, 5, "Press enter to continue...");
            refresh();
            getch();
            return;
        }
    } while (ch != 'y');
    char name[30];
    mvprintw(_y++, 5, "Enter your name (first name) : ");
    scanw("%s", name);
    FILE *fp = fopen("History.txt", "a");
    fprintf(fp, " %s       %ds     %.2f     %.2f\n", name, time_delay, wpm, accuracy);
    fclose(fp);

    mvprintw(_y++, 5, "Press enter to continue...");
    refresh();
    getch();
}

void game(char level[], int selected_option) {
    clear();
    refresh();
    int x, y;
    char u_str[MAX_STR_SIZE];
    char str[MAX_STR_SIZE];
    random_word_generate(str, selected_option);

    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_RED);
    init_pair(7, COLOR_BLACK, COLOR_BLUE);

    int len = 0;
    while (level[len++] != ' ') ;

    getmaxyx(stdscr, y, x);
    x = (x - len) / 2 - 18;
    y = y / 2 - 12;
    mvprintw(y - 5, x, "======= Difficulty level : ");
    attron(A_BOLD);
    for (int i = 0; i < len; i++) printw("%c", level[i]);
    
    attroff(A_BOLD);
    printw("=======");

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(y - 2, x - 9, "Press 'ENTER' to start, 'ESC' to end and 'TAB' to restart.");
    attroff(COLOR_PAIR(1) | A_BOLD);
    refresh();

    noecho();
    while ((getch()) != 10);
    echo();

    int i = 0, _x, _y;
    getmaxyx(stdscr, y, x);
    _x = x = x / 5;
    _y = y = y / 2 - 10;

    while (str[i]) {
        if (_x > x * 4) {
            _x = x;
            _y++;
        }
        if(str[i] == ' ') attron(COLOR_PAIR(7));
        refresh();
        mvprintw(_y, _x, "%c", str[i]);
        refresh();
        if(str[i] == ' ') attroff(COLOR_PAIR(7));
        i++;
        _x++;
    }
    refresh();

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
    do {
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
                if(str[k] == ' ') attron(COLOR_PAIR(7));
                refresh();
                printw("%c", str[k]);
                refresh();
                if(str[k] == ' ') attroff(COLOR_PAIR(7));
                num_backspace++;
            }
        }
        else if (ch == 9) game(level, selected_option);
        else if (ch == 27) break;
        else if ((ch < 65 || (ch > 90 && ch < 97) || ch > 122) && ch != ' ') ;
        else if (ch == str[k]) {
            u_str[k] = ch;
            k++;
            attron(COLOR_PAIR(2) | A_BOLD);
            printw("%c", ch);
            attroff(COLOR_PAIR(2) | A_BOLD);
            refresh();
            move(_y, ++_x);
        }
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
    keypad(stdscr, FALSE);
    echo();
    nodelay(stdscr, FALSE);
    u_str[k] = '\0';
    refresh();

    _y = _y + 15;
    mvprintw(_y, 5, "Press enter for result");

    noecho();
    while (getch() != 10) ;
    echo();
    refresh();

    display_result(_y, time_delay, u_str, str, num_backspace);
    menu();
}

void history(char level[30]) {
    int x, y;
    FILE *fp = fopen("History.txt", "r");
    if (fp == NULL) {
        clear();
        refresh();
        mvprintw(10, 10, "File doesn't exist.");
        refresh();
        napms(1000);
        menu();
    }
    char ch[100];
    clear();
    refresh();
    int len = 0;
    while (level[len++] != ' ') ;
    getmaxyx(stdscr, y, x);
    x = (x - len) / 2;
    y = y / 2 - 10;
    mvprintw(y++, x, "==== ");
    attron(A_BOLD);
    for (int i = 0; i < len; i++) printw("%c", level[i]);
    attroff(A_BOLD);
    printw("====");
    move(y += 2, x - 10);
    while (!feof(fp)) {
        fgets(ch, 100, fp);
        mvprintw(y++, x - 10, "%s", ch);
    }

    mvprintw(y += 3, x - 10, "Press enter to continue...");
    refresh();
    noecho();
    while (getch() != 10) ;
    echo();
    menu();
}

void menu() {
    char *option[] = {
        "Easy       ",
        "Medium     ",
        "Hard       ",
        "History    ",
        "Exit       "
    };
    int size_option = sizeof(option) / sizeof(option[0]);
    int x, y;
    clear();
    refresh();
    getmaxyx(stdscr, y, x);
    y = (y - size_option) / 2 - 1;
    x = (x - strlen(option[0])) / 2 - 5;

    attron(A_BOLD);
    mvprintw(y, x, "==== Difficulty Level ====");
    attroff(A_BOLD);

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

    if (selected_option >= 1 && selected_option <= 3) game(option[selected_option - 1], selected_option);
    else if (selected_option == 4) history(option[selected_option - 1]);
    else if (selected_option == 5) {
        clear();
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
    FILE *fp = fopen("History.txt", "r");
    if (fp == NULL) fp = fopen("History.txt", "w");
    fprintf(fp, " NAME       TIME      WPM    ACCURACY\n");
    fclose(fp);

    initscr();
    refresh();
    welcome();
    menu();
    refresh();
    getch();
    endwin();
    return 0;
}