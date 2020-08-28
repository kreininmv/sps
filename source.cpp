#include <stdio.h>
#include <math.h>
#include <assert.h>

#define per_error 0.0000000005
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

/* Main function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void main(void)
{
  double a = 0xEF, b = 0xEF, c = 0xEF, sol1 = 0xEF, sol2 = 0xEF;
  int res = 0xEF, check = 0;

  printf("Progrram of solving equation, entered coefficients:\n");
  check = scanf("%lg %lg %lg", &a, &b, &c);
  while (check != 3)
  {
    printf("Something going wrong, please enter numbers!\n");
    getchar();
    check = scanf("%lg %lg %lg", &a, &b, &c);
  }

  printf("\n");

  res = SolveEq(a, b, c, &sol1, &sol2);
  
  switch (res)
  {
  case any_sol:
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
  default:
    printf("Something going wrong...\n");
    break;
  }
  getchar();
  getchar();
  
} /* End of 'main' function */