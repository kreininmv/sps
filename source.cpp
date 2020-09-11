#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <windows.h>

#define per_error 5e-4
#define any_sol 0x1E
#define TRUE 1

/* Check inaccuracy of 2 numbers.
 * ARGUMENTS:
 *   - first number:
 *       double a;
 *   - second number:
 *       double b;
 * RETURNS:
 *   (int) true or false.
 */
int Compr(double a, double b);

/* Check inaccuracy of numbers.
 * ARGUMENTS:
 *   - first group of number:
 *       double a0, double b0;
 *   - second group of number:
 *       double a1, double b1;
 * RETURNS:
 *   (int) true or false.
 */
int Compr2(double a0, double b0, double a1, double b1);

/* Solve linear equation function.
 * ARGUMENTS:
 *   - coefficient b:
 *       double b;
 *   - coefficient c:
 *       double c;
 *   - pointer to solution:
 *       double *sol;
 * RETURNS:
 *   (int) number of desicions.
 */
int SolveLin(double b, double c, double *sol);

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
int SolveQuad(double a, double b, double c, double *sol1, double *sol2);

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
int SolveEq(double a, double b, double c, double *sol1, double *sol2);

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
void Menu(int res, double *sol1, double *sol2);

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
void Input(double *a, double *b, double *c);

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
int Test(double a, double b, double c, double sol1, double sol2, int numroots);

/* Unit test function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void UTest(void);

/* Main function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
int main(void)
{
  double a = 0xEF, b = 0xEF, c = 0xEF, sol1 = 0xEF, sol2 = 0xEF;

  Input(&a, &b, &c);
  Menu(SolveEq(a, b, c, &sol1, &sol2), &sol1, &sol2);
  UTest();
  getchar();
  getchar();
  return 0;
} /* End of 'main' function */

/* Check inaccuracy of 2 numbers.
 * ARGUMENTS:
 *   - first number:
 *       double a;
 *   - second number:
 *       double b;
 * RETURNS:
 *   (int) true or false.
 */
int Compr( double a, double b )
{
  if (fabs(a - b) <= per_error)
    return 1;
  return 0;
} /* End of 'Compr' function */

/* Check inaccuracy of numbers.
 * ARGUMENTS:
 *   - first group of number:
 *       double a0, double b0;
 *   - second group of number:
 *       double a1, double b1;
 * RETURNS:
 *   (int) true or false.
 */
int Compr2( double a0, double b0, double a1, double b1 )
{
  if ((Compr(a0, a1) && Compr(b0, b1)))
    return 1;
  return 0;
} /* End of 'Compr' function */

/* Solve linear equation function.
 * ARGUMENTS:
 *   - coefficient b:
 *       double b;
 *   - coefficient c:
 *       double c;
 *   - pointer to solution:
 *       double *sol;
 * RETURNS:
 *   (int) number of desicions.
 */
int SolveLin( double b, double c, double *sol )
{
  if (Compr2(b, c, 0, 0))
    return any_sol;
  if (Compr(b, 0))
    return 0;
  
  *sol =  -c / b;
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
int SolveQuad( double a, double b, double c, double *sol1, double *sol2 )
{
  if (Compr(c, 0))
  {
    *sol1 = 0;
    SolveLin(a, b, sol2);
    return (Compr(*sol1, *sol2)) ? 1 : 2;
  }

  double Dis = b * b - 4 * a * c;
  if (Dis < 0 || (Compr(Dis, 0) != false))
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
int SolveEq( double a, double b, double c, double *sol1, double *sol2 )
{
  assert(isfinite(a));
  assert(isfinite(b));
  assert(isfinite(c));
  
  assert(sol1 != NULL);
  assert(sol2 != NULL);
  assert(sol1 != sol2);

  if (Compr(a, 0))
    return SolveLin(b, c, sol1);
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
void Menu( int res, double *sol1, double *sol2 )
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
void Input( double *a, double *b, double *c )
{
  int check = 0;
  
  printf("Progrram of solving equation, entered coefficients, a b c:");
  check = scanf("%lg %lg %lg", a, b, c);

  while (check != 3)
  {
    printf("\nSomething going wrong, please enter numbers!!!\n");
    printf("Progrram of solving equation, entered coefficients, a b c:");
    
    while (getchar() != '\n')
      ;

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
int Test( double a, double b, double c, double sol1, double sol2, int numroots )
{
  double localsol1 = 0, localsol2 = 0;

 /* Count of roots are the same and one of three conditions are true:
  * 1) count of roots - zero
  * 2) count of roots - one and root is similar
  * 3) count of roots - two and roots are similar
  * 4) count of roots - 0x1E
  */
  if ((numroots == SolveEq(a, b, c, &localsol1, &localsol2)) 
    && ((numroots == 0) 
       || (numroots == 1 && Compr(localsol1, sol1)) 
       || (numroots == 2 && Compr2(sol1, sol2, localsol1, localsol2)) 
       || (numroots == any_sol)))
    return 1;
    
  return 0;
}/* End of 'Test' function */

/* Unit test function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void UTest( void )
{
  FILE *FIn, *FOut;
  double a = 0, b = 0, c = 0, sol1 = 0, sol2 = 0;
  int i = 1, numr = 0;
  
  FIn = fopen("tests.dat", "r");
  FOut = fopen("results.dat", "w");
  
  if (FIn == NULL)
  {
    printf("We can't find the file...\n");
    assert(0);
  }
  if (FOut == NULL)
  {
    printf("We can't create this file...\n");
    assert(0);
  }
  
  while (fscanf(FIn, "%lg %lg %lg %lg %lg %d", &a, &b, &c, &sol1, &sol2, &numr) == 6)
  {
    if (Test(a, b, c, sol1, sol2, numr) != TRUE)
      fprintf(FOut, "TEST N - %i ERROR!!\n", i);
    else
      fprintf(FOut, "TEST N - %i GOOD!!!\n", i);
    i++;
  }
  fclose(FOut);
} /* End of 'UTest' function */