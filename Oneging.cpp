#include <stdio.h>
#include <windows.h>
#include <string.h>

#define MAX 0xEF

/* Swap two elements function.
 * ARGUMENTS:
 *   - point to the first element:
 *        char *str1;
 *   - point to the second element:
 *        char *str2;
 * RETURNS: None.
 */
void Swap(char **str1, char **str2)
{
  char *tmp = *str1;
  *str1 = *str2;
  *str2 = tmp;

}/* End of 'Swap' function */

/* Strings comparing function.
 * ARGUMENTS:
 *   - point to first string:
 *        char *str1;
 *   - point to second string:
 *        char *str2;
 * RETURNS: number > 0 if (str1 > str2) and number < 0 if (str1 < str 2) and 0 if (str1 = str2) 
 */
int StrCompare(char *str1, char *str2)
{
  while (*str1 == ' ' || *str1 == '\t')
    str1++;
  while (*str2 == ' ' || *str2 == '\t')
    str2++;

  while (*str1 == *str2 && *str1 != 0)
  {
    str1++;
    str2++;

    while (*str1 == ' ' || *str1 == '\t')
      str1++;
    while (*str2 == ' ' || *str2 == '\t')
      str2++;
  }

  return (int)*str1 - (int)*str2;
} /* End of 'StrCompare' function */

/* Sort array of string function.
 * ARGUMENTS:
 *   - array of strokes:
 *        char **str;
 *   - size of array:
 *        int N;
 * RETURNS: None.
 */
void QuickSortStrings(char **A, int N)
{
  long b = 0, e = N - 1;
  char *x = A[N / 2];
  
  if (N < 2)
    return;
  
  while (b <= e)
  {
    while (StrCompare(x, A[b]) > 0)
      b++;
    while (StrCompare(A[e], x) > 0)
      e--;
    if (b <= e)
    {
      if (b != e)
        Swap(A + b, A + e);
      b++;
      e--;
    }
  }
  QuickSortStrings(A, e + 1);
  QuickSortStrings(A + b, N - b);
}/* End of 'QuickSort' function */

/* Read strokes from file function.
 * ARGUMENTS:
 *   - array of strings:
 *        char **str;
 *   - name of file:
 *        char *FilaName;
 *   - point to the size of array:
 *        int *size;
 * RETURNS: array of strings.
 */
char ** ReadStr(char **str, char *FileName, int *size)
{
  char newstr[MAX] = {};
  FILE *F = fopen(FileName, "r");

  if (F == NULL)
  {
    printf("We can't find the file...\n");
    getchar();
    return 0;
  }

  char x = fgetc(F);
  while (x != EOF)
  {
    if (x == '\n')
      (*size)++;
    x = fgetc(F);
  }
  (*size)++;

  rewind(F);

  str = (char **)malloc((*size) * sizeof(char*));
  
  for (int i = 0; i < *size; i++)
  {
    fgets(newstr, MAX, F);
   
    str[i] = (char *)malloc((strlen(newstr) + 1) * sizeof(char));
    
    strcpy(str[i], newstr);
    
    for (int k = 0; k < MAX; k++)
      newstr[k] = 0;
  }

  fclose(F);
  return str;
} /* End of 'ReadStr' function */

/* Write array of strings to the file function.
 * ARGUMENTS: 
 *   - array of strings:
 *        char **str;
 *   - name of file:
 *        char *FileName;
 *   - size of array:
 *        int size;
 * RETURNS: None.
 */
void WriteStr(char **str, char *FileName, int size)
{
  FILE *F;
  int i = 0, k = 0;
  F = fopen(FileName, "w");

  if (F == NULL)
  {
    printf("We can't create the file...\n");
    getchar();
    return;
  }

  for (i = 0; i < size; i++)
    fprintf(F, "%s", str[i]);

  fclose(F);
}/* End of 'WriteStr' function */

/* Main function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
int main(void)
{
  char **str = NULL, InFileName[] = "IN_onegin.txt", OutFileName[] = "OUT_onegin.txt";
  int size = 0;
  
  str = ReadStr(str, InFileName, &size);  
  QuickSortStrings(str, size);
  WriteStr(str, OutFileName, size);

  return 0;
}/* End of 'main' function */