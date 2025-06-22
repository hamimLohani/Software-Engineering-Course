#include <stdio.h>

void shape(char a1, char a2, char a3, char a4, char a5, char a6, char a7, char a8, char a9);
char check(char a1, char a2, char a3, char a4, char a5, char a6, char a7, char a8, char a9);

int main()
{

  printf("\n======================================\n");
  printf("||\t\t\t\t\t\t\t\t\t||\n||\t\t\tW E L C O M E\t\t\t||\n");
  printf("||\t\t\t\t\t\t\t\t\t||\n======================================\n");
  printf("\nPress enter to start...");
  getchar();

  char a1 = ' ', a2 = ' ', a3 = ' ', a4 = ' ', a5 = ' ', a6 = ' ', a7 = ' ', a8 = ' ', a9 = ' ';
  char move = 'X';
  int index;

  printf("\n\nIndex number :\n");
  shape('1', '2', '3', '4', '5', '6', '7', '8', '9');
  while (1)
  {
    printf("\nPlayer-%c,Enter index : ", move);
    scanf("%d", &index);

    if (index == 1 && a1 == ' ')
      a1 = move;
    else if (index == 2 && a2 == ' ')
      a2 = move;
    else if (index == 3 && a3 == ' ')
      a3 = move;
    else if (index == 4 && a4 == ' ')
      a4 = move;
    else if (index == 5 && a5 == ' ')
      a5 = move;
    else if (index == 6 && a6 == ' ')
      a6 = move;
    else if (index == 7 && a7 == ' ')
      a7 = move;
    else if (index == 8 && a8 == ' ')
      a8 = move;
    else if (index == 9 && a9 == ' ')
      a9 = move;
    else
    {
      printf("Invalid index!!");
      continue;
    }

    shape(a1, a2, a3, a4, a5, a6, a7, a8, a9);

    if (check(a1, a2, a3, a4, a5, a6, a7, a8, a9) == 'X' || check(a1, a2, a3, a4, a5, a6, a7, a8, a9) == 'O')
    {
      printf("WINNER is player-%c\n",check(a1, a2, a3, a4, a5, a6, a7, a8, a9));
      break;
    }
    if (check(a1, a2, a3, a4, a5, a6, a7, a8, a9) == 'T')
    {
      printf("Match Tie.\n");
      break;
    }

    if (move == 'X')
      move = 'O';
    else
      move = 'X';
  }

  return 0;
}

void shape(char a1, char a2, char a3, char a4, char a5, char a6, char a7, char a8, char a9)
{
  printf("\n\t %c | %c | %c ", a1, a2, a3);
  printf("\n\t---+---+---");
  printf("\n\t %c | %c | %c", a4, a5, a6);
  printf("\n\t---+---+---");
  printf("\n\t %c | %c | %c\n\n", a7, a8, a9);
}

char check(char a1, char a2, char a3, char a4, char a5, char a6, char a7, char a8, char a9)
{
  char ch;
  if ((a1 == a2 && a2 == a3 && a1 != ' ') || (a1 == a4 && a4 == a7 && a1 != ' ') || (a1 == a5 && a5 == a9 && a1 != ' ') || (a2 == a5 && a5 == a8 && a2 != ' ') || (a3 == a6 && a6 == a9 && a3 != ' ') || (a3 == a5 && a5 == a7 && a3 != ' ') || (a4 == a5 && a5 == a6 && a4 != ' ') || (a7 == a8 && a8 == a9 && a9 != ' '))
  {
    if (a1 == 'X' || a5 == 'X' || a9 == 'X')
      ch = 'X';
    else
      ch = 'O';
  }
  else if (a1 != ' ' && a2 != ' ' && a3 != ' ' && a4 != ' ' && a5 != ' ' && a6 != ' ' && a7 != ' ' && a8 != ' ' && a9 != ' ')
    ch = 'T';

  return ch;
}