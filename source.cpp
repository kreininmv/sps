#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <windows.h>

#define per_error 5e-4
#define any_sol 0x1E

/* Check inaccuracy of numbers.
 * ARGUMENTS:
 *   - first number:
 *       double a;
 *   - second number:
 *       double b;
 * RETURNS:
 *   (int) true or false.
 */
int Compr(double a, double b)
{
  if (fabs(a - b) <= per_error)
    return 1;
  return 0;
} /* End of 'Compr' function */

/* Solve linear equation function.
 * ARGUMENTS:
 *   - coefficient b:
 *       double b;
 *   - coefficient c:
 *       double c;
 *   - pointer to solution 1:
 *       double *sol1;
 *   - pointer to solution 2:
 *       double *sol2;
 * RETURNS:
 *   (int) number of desicions.
 */
int SolveLin(double b, double c, double *sol1, double *sol2)
{
  if (b == 0 && c == 0)
    return any_sol;
  if (b == 0)
    return 0;
  *sol1 = *sol2 = -c / b;
  return 1;
} /* End of 'SolveLin' function */

/* Solve quadratic ecuation function.
 * ARGUMENTS:
 *   - coefficient a:
 *       double a;
 *   - coefficient b:
 *       double b;
 *   - coefficient c:
 *       double c;
 *   - pointer to solution 1:
 *       double *sol1;
 *   - pointer to solution 2:
 *       double *sol2;
 * RETURNS:
 *   (int) number of desicions.
 */
int SolveQuad(double a, double b, double c, double *sol1, double *sol2)
{
  double Dis = b * b - 4 * a * c;
  if (Dis < 0)
    return 0;
  *sol1 = (-b + sqrt(Dis)) / (2 * a);
  *sol2 = (-b - sqrt(Dis)) / (2 * a);
  return (Compr(Dis, 0)) ? 1 : 2;
} /* Enf of 'SolveQuad' function */

/* Solve equation function.
 * ARGUMENTS: 
 *   - coefficient a:
 *       double a;
 *   - coefficient b:
 *       double b;
 *   - coefficient c:
 *       double c;
 *   - pointer to solution 1:
 *       double *sol1;
 *   - pointer to solution 2:
 *       double *sol2;
 * RETURNS: 
 *   (int) number of desicions.
 */
int SolveEq(double a, double b, double c, double *sol1, double *sol2)
{
  assert(isfinite(a));
  assert(isfinite(b));
  assert(isfinite(c));
  
  assert(sol1 != NULL);
  assert(sol2 != NULL);
  assert(sol1 != sol2);

  if (a == 0)
    return SolveLin(b, c, sol1, sol2);
  return SolveQuad(a, b, c, sol1, sol2);
} /* End of 'SolveEq' function */

/* Menu function.
 * ARGUMENTS:
 *   - result of solve equation:
 *        int res;
 *   - point to first root of equation:
 *        double *sol1;
 *   - point to second root of equation:
 *        double *sol2;
 * RETURNS: None.
 */
void Menu(int res, double *sol1, double *sol2)
{
  switch (res)
  {
  case any_sol:
    printf("Any number is solution!\n");
    break;
  case 0:
    printf("Equation has no solutions!\n");
    break;
  case 1:
    printf("Equation has 1 solution, x = %lg\n", *sol1);
    break;
  case 2:
    printf("Equation has 2 solutions, x1 = %lg and x2 = %lg\n", *sol1, *sol2);
    break;
  default:
    printf("Something going wrong...\n");
    break;
  }
}
/* End of 'Menu' function */

/* Input function.
 * ARGUMENTS: 
 *   - coefficient a:
 *       double a;
 *   - coefficient b:
 *       double b;
 *   - coefficient c:
 *       double c;
 * RETURNS: None.
 */
void Input(double *a, double *b, double *c)
{
  int check = 0;
  printf("Progrram of solving equation, entered coefficients:\n");
  check = scanf("%lg %lg %lg", a, b, c);
  while (check != 3)
  {
    printf("Something going wrong, please enter numbers!\n");
    fflush(stdout);
    check = scanf("%lg %lg %lg", a, b, c);
  }
  printf("\n");
}
/* Enf of 'Input' function */

/* Test function.
 * ARGUMENTS:
 *   - coefficient a:
 *       double a;
 *   - coefficient b:
 *       double b;
 *   - coefficient c:
 *       double c;
 *   - first root of equation:
 *        double sol1;
 *   - second root of equation:
 *        double sol2;
 *   - num of roots:
 *        int numroots;
 * RETURNS: true or false.
 */
int Test(double a, double b, double c, double sol1, double sol2, int numroots)
{
  double localsol1, localsol2;

 /* Count of roots are the same and one of three conditions are true:
  * 1) count of roots - zero
  * 2) count of roots - one and root is similar
  * 3) count of roots - two and roots are similar
  * 4) count of roots - 0x1E
  */
  if (numroots == SolveEq(a, b, c, &localsol1, &localsol2))
  {
    if (numroots == 0)
      return 1;
    if (numroots == 1 && localsol1 == sol1)
      return 1;
    if (numroots == 2 && ((Compr(localsol1, sol1) && Compr(localsol2, sol2)) || (Compr(localsol2, sol1) && Compr(localsol1, sol2))))
      return 1;
    if (numroots == any_sol)
      return 1;
  }
  return 0;
}/* End of 'Test' function */

/* Unit test function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void UTest(void)
{
  FILE *FIn, *FOut;
  double a = 0, b = 0, c = 0, sol1 = 0, sol2 = 0, numr = 0;
  int i = 1;
  FIn = fopen("tests.dat", "r");
  FOut = fopen("results.dat", "w");
  if (FIn == NULL)
  {
    printf("We can't find the file...\n");
    getchar();
    return;
  }
  if (FOut == NULL)
  {
    printf("We can't create this file...\n");
    getchar();
    return;
  }
  while (fscanf(FIn, "%lg %lg %lg %lg %lg %lg", &a, &b, &c, &sol1, &sol2, &numr) == 6)
  {
    if (Test(a, b, c, sol1, sol2, (int)numr) != true)
      fprintf(FOut, "TEST N - %i ERROR!!\n", i);
    else
      fprintf(FOut, "TEST N - %i GOOD!!!\n", i);
    i++;
  }
  fclose(FOut);
} /* End of 'UTest' function */
/* Main function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void main(void)
{
  double a = 0xEF, b = 0xEF, c = 0xEF, sol1 = 0xEF, sol2 = 0xEF;

  Input(&a, &b, &c);
  Menu(SolveEq(a, b, c, &sol1, &sol2), &sol1, &sol2);
  UTest();
  getchar();
  getchar();
  
} /* End of 'main' function */