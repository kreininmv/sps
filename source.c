#include <stdio.h>
#include <math.h>

int SolveEq(float a, float b, float c, float *x1, float *x2)
{
  float D;
  if (a == 0 && b == 0 && c == 0)
    return 0x1E;
  else if (a == 0 && b == 0)
    return 0;
  else if (a == 0)
  {
    *x1 = *x2 = -c / b;
    return 1;
  }
  else if (b * b - 4 * a * c >= 0)
  {
    D = sqrt(b * b - 4 * a * c);
    *x1 = (- b + D) / (2 * a);
    *x2 = (- b - D) / (2 * a);
    if (D == 0)
      return 1;
    else
      return 2;
  }
  else
    return 0;
}
void main(void)
{
  float a, b, c, res, x1, x2;
 
  scanf("%f %f %f", &a, &b, &c);

  res = SolveEq(a, b, c, &x1, &x2);
  
  if (res == 0x1E)
    printf("Any number is solution!\n");
  else if (res == 0)
    printf("Equation has no solutions!\n");
  else if (res == 1)
    printf("Equation has 1 solution, x = %f\n", x1);
  else
    printf("Equation has 2 solutions, x1 = %f and x2 = %f\n", x1, x2);
}