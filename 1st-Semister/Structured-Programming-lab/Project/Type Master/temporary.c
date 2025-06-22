#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

void disable_echo_mode()
{
    fflush(stdout);
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);          // Get current terminal attributes
    tty.c_lflag &= ~(ECHO | ICANON);        // Disable echo and canonical mode
    tcsetattr(STDIN_FILENO, TCSANOW, &tty); // Set the modified attributes
}

void enable_echo_mode()
{
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);          // Get current terminal attributes
    tty.c_lflag |= (ECHO | ICANON);         // Enable echo and canonical mode
    tcsetattr(STDIN_FILENO, TCSANOW, &tty); // Set the modified attributes
}

int word_count(char str[])
{
    int num = 1;
    for (int i = 0; str[i]; i++)
        if (str[i] == ' ' && str[i + 1] != '\0' && str[i - 1] != ' ')
            num++;
    return num;
}

int main()
{
    system("clear");
    char *red = "\033[31m";
    char *green = "\033[32m";
    printf("\n\t\t\t===Welcome===\n");
    printf("\t\t==Test your typing==\n");
    // char str[] = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
    char str[1000] = "When enabled, it will show the command line with all commands in a single list instead of submenu arrangements. Selecting 'manual' will expose all commands only after typing";
    char u_str[1000];
    int total_word = word_count(str);
    int flag;
    int index_wrong_word_arr[100];
    int index_num_cor_word_arr[100];
    int num_worng_word = 0;
    int num_backspace = 0;
    int avg = strlen(str) / total_word;

    int time_delay = 0;

    printf("\nYou have only 30s.\nPress enter to start the game...");
    getchar();

    printf("Time start.\n\nTEXT : \n%s\n\nSTART TYPE : \n", str);

    time_t start_time = 0, end_time = 0;
    start_time = time(NULL);

    disable_echo_mode();
    
    int k = 0;
    while (time_delay < 30 && k < strlen(str))
    {
        char ch;
        ch = getchar();

        if (ch == '\b' || ch == 127)
        {
            if (k > 0)
            {
                k--;
                printf("\b \b");
            u_str[k] = '\0';
            }
        }
        else if (ch == '\n')
            break;
        else if (ch == str[k])
        {
            u_str[k] = ch;
            printf("%s%c\033[0m", green, ch);
            k++;
        }
        else
        {
            num_backspace++;
            printf("%s%c\033[0m", red, ch);
            k++;
        }
        end_time = time(NULL);
        time_delay = difftime(end_time, start_time);
    }
    
    enable_echo_mode();

    int i = 0, j = 0;
    
    while (str[i] != '\0' && u_str[j] != '\0')
    {
        char temp1[20] = "", temp2[20] = "";
        int x = 0, y = 0;
        int index_cor = i;
        int index_wrong = j;
        while (str[i] != ' ' && str[i] != '\0')
        {
            temp1[x] = str[i];
            x++;
            i++;
        }
        temp1[x] = '\0';
        while (u_str[j] != ' ' && u_str[j] != '\0')
        {
            temp2[y] = u_str[j];
            y++;
            j++;
        }
        temp2[y] = '\0';
        flag = strcmp(temp1, temp2);

        while (str[i] == ' ')
            i++;
        while (u_str[j] == ' ')
            j++;

        if (flag)
        {
            index_wrong_word_arr[num_worng_word] = index_wrong;
            index_num_cor_word_arr[num_worng_word] = index_cor;
            num_worng_word++;
        }
    }

    printf("\n\nTime end.\nPress enter for the result...");
    getchar();
    printf("\n\n\t==Result==\n"); 

    int u_word = word_count(u_str);
    int num_cor_word = u_word - num_worng_word;
    float accuracy = ((float)(num_cor_word - (num_backspace / avg)) / (float)u_word);
    int wpm = num_cor_word * 60 / time_delay;

    if (num_cor_word == total_word)
        printf("Cogratulation...\n");

    printf("Total word : %d\n", total_word);
    printf("Your total word count : %d\n", u_word);
    printf("Your wrong word count : %d\n", num_worng_word);
    printf("Your correct word count : %d\n", num_cor_word);
    printf("Your backspace count : %d\n", num_backspace);
    printf("Your accuracy : %.2f%%\n", accuracy * 100);
    printf("Your time : %ds\n", time_delay);
    printf("Your WPM : %d\n", wpm);

    if (num_worng_word)
    {
        printf("---------------------------------------\n");
        printf(" Index |  Wrong Word  |   Correct Word  \n");
        printf("---------------------------------------\n");
        for (int i = 0; i < num_worng_word; i++)
        {
            printf("  %d \t\t", index_wrong_word_arr[i]);
            for (int j = index_wrong_word_arr[i]; u_str[j] != ' ' && u_str[j] != '\0'; j++)
                printf("%c", u_str[j]);
            printf("             ");
            for (int j = index_num_cor_word_arr[i]; str[j] != ' ' && str[j] != '\0'; j++)
                printf("%c", str[j]);
            printf("\n---------------------------------------\n");
        }
    }

    return 0;
}