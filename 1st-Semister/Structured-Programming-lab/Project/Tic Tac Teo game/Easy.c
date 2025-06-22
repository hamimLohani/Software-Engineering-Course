#include <stdio.h>
#include <stdlib.h>

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

  int index;

  printf("\n\nIndex number :\n");
  shape('1', '2', '3', '4', '5', '6', '7', '8', '9');
  printf("You : 'X'\nComputer : 'O'\n\n");
  
  while (1)
  {
    printf("\nEnter index : ");
    scanf("%d", &index);

    if (index == 1 && a1 == ' ')
      a1 = 'X';
    else if (index == 2 && a2 == ' ')
      a2 = 'X';
    else if (index == 3 && a3 == ' ')
      a3 = 'X';
    else if (index == 4 && a4 == ' ')
      a4 = 'X';
    else if (index == 5 && a5 == ' ')
      a5 = 'X';
    else if (index == 6 && a6 == ' ')
      a6 = 'X';
    else if (index == 7 && a7 == ' ')
      a7 = 'X';
    else if (index == 8 && a8 == ' ')
      a8 = 'X';
    else if (index == 9 && a9 == ' ')
      a9 = 'X';
    else
    {
      printf("Invalid index!!");
      continue;
    }

    while (1)
    {
      int index_com = rand() % 9;
      if (index_com == 1 && a1 == ' ')
      {
        a1 = 'O';
        break;
      }
      else if (index_com == 2 && a2 == ' ')
      {
        a2 = 'O';
        break;
      }
      else if (index_com == 3 && a3 == ' ')
      {
        a3 = 'O';
        break;
      }
      else if (index_com == 4 && a4 == ' ')
      {
        a4 = 'O';
        break;
      }
      else if (index_com == 5 && a5 == ' ')
      {
        a5 = 'O';
        break;
      }
      else if (index_com == 6 && a6 == ' ')
      {
        a6 = 'O';
        break;
      }
      else if (index_com == 7 && a7 == ' ')
      {
        a7 = 'O';
        break;
      }
      else if (index_com == 8 && a8 == ' ')
      {
        a8 = 'O';
        break;
      }
      else if (index_com == 9 && a9 == ' ')
      {
        a9 = 'O';
        break;
      }
      else if (a1 != ' ' && a2 != ' ' && a3 != ' ' && a4 != ' ' && a5 != ' ' && a6 != ' ' && a7 != ' ' && a8 != ' ' && a9 != ' ')
        break;
      else
        continue;
    }

    shape(a1, a2, a3, a4, a5, a6, a7, a8, a9);

    if (check(a1, a2, a3, a4, a5, a6, a7, a8, a9) == 'X')
    {
      printf("You have won this match.\n\n");
      break;
    }
    else if (check(a1, a2, a3, a4, a5, a6, a7, a8, a9) == 'O')
    {
      printf("Computer has won the match.\n\n");
      break;
    }
    
    if (check(a1, a2, a3, a4, a5, a6, a7, a8, a9) == 'T')
    {
      printf("Match Tie.\n\n");
      break;
    }
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
  if ((a1 == a2 && a2 == a3 && a1 == 'X') || (a1 == a4 && a4 == a7 && a1 == 'X') || (a1 == a5 && a5 == a9 && a1 == 'X') || (a2 == a5 && a5 == a8 && a2 == 'X') || (a3 == a6 && a6 == a9 && a3 == 'X') || (a3 == a5 && a5 == a7 && a3 == 'X') || (a4 == a5 && a5 == a6 && a4 == 'X') || (a7 == a8 && a8 == a9 && a9 == 'X'))
    ch = 'X';
  else if ((a1 == a2 && a2 == a3 && a1 == 'O') || (a1 == a4 && a4 == a7 && a1 == 'O') || (a1 == a5 && a5 == a9 && a1 == 'O') || (a2 == a5 && a5 == a8 && a2 == 'O') || (a3 == a6 && a6 == a9 && a3 == 'O') || (a3 == a5 && a5 == a7 && a3 == 'O') || (a4 == a5 && a5 == a6 && a4 == 'O') || (a7 == a8 && a8 == a9 && a9 == 'O'))
    ch = 'O';
  else if (a1 != ' ' && a2 != ' ' && a3 != ' ' && a4 != ' ' && a5 != ' ' && a6 != ' ' && a7 != ' ' && a8 != ' ' && a9 != ' ')
    ch = 'T';

  return ch;
}