#include <stdio.h>
#include <math.h>

#define per_error 0.0000000005
int Compr(double a, double b)
{
  if (fabs(a - b) <= per_error)
    return 1;
  return 0;
}
int SolveLin(double b, double c, double *sol1, double *sol2)
{
  if (b == 0 && c == 0)
    return 0x1E;
  if (b == 0)
    return 0;
  *sol1 = *sol2 = -c / b;
  return 1;
}
int SolveQuad(double a, double b, double c, double *sol1, double *sol2)
{
  double Dis = sqrt(b * b - 4 * a * c);
  *sol1 = (-b + Dis) / (2 * a);
  *sol2 = (-b - Dis) / (2 * a);
  return (Compr(Dis, 0)) ? 1 : 2;
}

int SolveEq(double a, double b, double c, double *sol1, double *sol2)
{
  if (a == 0)
    return SolveLin(b, c, sol1, sol2);
  if (b * b - 4 * a * c >= 0)
    return SolveQuad(a, b, c, sol1, sol2);

  /* Discriminant < 0, and equations has no solutions */
  return 0;
}
void main(void)
{
  double a = 0xEF, b = 0xEF, c = 0xEF, sol1 = 0xEF, sol2 = 0xEF;
  int res = 0xEF;
 
  scanf("%lg %lg %lg", &a, &b, &c);
  if (a == 0xEF || b == 0xEF || c == 0xEF)
  {
    printf("You entered the wrong data, write numbers\n");
    return;
  }
  res = SolveEq(a, b, c, &sol1, &sol2);
  
  switch (res)
  {
  case 0x1E:
    printf("Any number is solution!\n");
    break;
  case 0:
    printf("Equation has no solutions!\n");
    break;
  case 1:
    printf("Equation has 1 solution, x = %lg\n", sol1);
    break;
  case 2:
    printf("Equation has 2 solutions, x1 = %lg and x2 = %lg\n", sol1, sol2);
    break;
  }
  getchar();
  getchar();
  
}