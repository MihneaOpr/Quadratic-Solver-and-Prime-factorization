#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MXLEN 1024
void solve(char s[]) {
  int n = strlen(s), i;
  double coef[3];
  coef[0] = coef[1] = coef[2] = 0;
  int before_eq = 0, sgn = 1;
  double numeric = 0.0;
  for (i = 0; i < n; i++) {
    if (s[i] >= '0' && s[i] <= '9' && s[i - 1] != '^') {
      numeric = (s[i] - '0') + numeric * 10;
    } else {
      if (s[i] == 'x' && s[i + 1] == '^') {
        if (!numeric) numeric = 1;
        coef[0] += sgn * numeric;
        if (!before_eq)
          sgn = 1;
        else
          sgn = -1;
        numeric = 0;
      } else if (s[i] == 'x' && s[i + 1] != '^') {
        if (!numeric) numeric = 1;
        coef[1] += sgn * numeric;
        if (!before_eq)
          sgn = 1;
        else
          sgn = -1;
        numeric = 0;
      } else if (s[i] != ' ') {
        coef[2] += sgn * numeric;
        if (!before_eq)
          sgn = 1;
        else
          sgn = -1;
        numeric = 0;
        if (s[i] == '=') before_eq = 1, sgn = -1;
        if (s[i] == '-' && !before_eq)
          sgn = -1;
        else if (s[i] == '-' && before_eq)
          sgn = 1;
      }
    }
  }
  double delta = coef[1] * coef[1] - 4 * coef[0] * coef[2];
  if (delta < 0) {
    delta = -delta;
    double re, im;
    re = (-coef[1]) / (2 * coef[0]);
    im = (sqrt(delta)) / (2 * coef[0]);
    printf("The solutions are: x1 = %lf + %lfi x2 = %lf - %lfi\n", re, im, re,
           im);
  } else {
    double x1 = (-coef[1] + sqrt(delta)) / (2 * coef[0]);
    double x2 = (-coef[1] - sqrt(delta)) / (2 * coef[0]);
    printf("The solutions are: x1 = %lf  x2 = %lf\n", x1, x2);
  }
  printf("Command:\n");
}
void decompose(int nr) {
  int d = 2;
  while (nr > 1) {
    if (nr % d == 0) {
      printf("%d^", d);
    }
    int contor = 0;
    while (nr % d == 0) {
      contor++;
      nr /= d;
    }
    if (contor) {
      printf("%d ", contor);
    }
    d++;
  }
  printf("\n");
  printf("Command:\n");
}
void printLeaf() {
  char type[5] = {'.', '*', 'o', 'O', '+'};
  int wich = rand() % 5;
  if (wich == 1)
    printf("%c ", type[rand() % 5]);
  else
    printf("%c ", type[1]);
}
void make_trian(int base, int size, int fst) {
  int i, j, space = base / 2;
  for (i = 0; i < size; i++) {
    for (j = 0; j < space; j++) printf(" ");
    for (j = 0; j < fst; j++) printLeaf();
    space--;
    fst++;
    printf("\n");
  }
}
void make_tree() {
  int i;
  for (i = 1; i <= 4; i++) {
    make_trian(20, i + 3, i);
  }
  printf("Comand:\n");
}
int main() {
  char s[MXLEN], command[MXLEN], number[MXLEN];
  printf(
      "Hi! To see the available commands that this program offers type "
      "'help'\n");
  printf("Command:\n");
  int nr;
  fgets(command, MXLEN, stdin);
  while (1) {
    if (!strcmp(command, "exit\n")) {
      exit(0);
    } else if (!strcmp(command, "help\n")) {
      printf("Type 1 to solve a grade II equation\n");
      printf("Type 2 to decompose a number in prime factors\n");
      printf("Type 3 to summon a Christmas Tree \nCommand:\n");

    } else if (!strcmp(command, "1\n")) {
      printf("Write the equation:");
      fgets(s, MXLEN, stdin);
      solve(s);

    } else if (!strcmp(command, "2\n")) {
      printf("Write the number:");
      fgets(number, MXLEN, stdin);
      nr = atoi(number);
      decompose(nr);
    } else if (!strcmp(command, "3\n")) {
      make_tree();
    } else {
      printf("%s", command);
      printf("Wrong command. Type 'help' for guidance\nCommand:\n");
    }
    fgets(command, MXLEN, stdin);
  }
}
