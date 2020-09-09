#include <stdio.h>
#include <windows.h>
#include <string.h>

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
void QuickSortStrings(char **A, int N, int (*Compare)(char *, char*))
{
  long b = 0, e = N - 1;
  char *x = A[N / 2];
  
  if (N < 2)
    return;
  
  while (b <= e)
  {
    while (Compare(x, A[b]) > 0)
      b++;
    while (Compare(A[e], x) > 0)
      e--;
    if (b <= e)
    {
      if (b != e)
        Swap(A + b, A + e);
      b++;
      e--;
    }
  }
  QuickSortStrings(A, e + 1, StrCompare);
  QuickSortStrings(A + b, N - b, StrCompare);
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
  char *newstr = NULL;
  char x = 0;
  int lencur = 0, lenstr = 0;
  FILE *F = fopen(FileName, "r");

  if (F == NULL)
  {
    printf("We can't find the file...\n");
    getchar();
    return 0;
  }
  
  do
  {
    if (x == '\n')
      (*size)++;
    x = fgetc(F);
  } while (x != EOF);

  rewind(F);

  str = (char **)calloc((*size), sizeof(char *));
  
  for (int i = 0; i < *size; i++)
  {
    do
    {
      x = fgetc(F);
      lenstr++;
    } while (x != '\n' && x != EOF);
    lenstr++;
    fseek(F, lencur * sizeof(char), SEEK_SET);
    lencur += lenstr;
    
    newstr = (char *)calloc(lenstr, sizeof(char));
    for (int i = 0; i < lenstr; i++)
      newstr[i] = 0;

    fgets(newstr, lenstr, F);

    str[i] = (char *)calloc(lenstr, sizeof(char));
    
    strcpy(str[i], newstr);
    printf("%s", str[i]);
    /* Clear newstr */
    lenstr = 0;
    free(newstr);
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
  FILE *F = fopen(FileName, "w");

  if (F == NULL)
  {
    printf("We can't create the file...\n");
    getchar();
    return;
  }

  for (int i = 0; i < size; i++)
    fprintf(F, "%s", str[i]);

  fclose(F);
}/* End of 'WriteStr' function */

/* Reverse array function. 
 * ARGUMENTS: 
 *   - array of strings:
 *        char **str;
 *   - size of array:
 *        int size;
 * RETURNS: None.
 */
void Reverse(char **str, int size)
{
  for (int i = 0; i < size / 2; i++)
    Swap(str + i, str + size - i - 1);
}
/* End of 'Reverse' function */

/* Clearing memory of array function.
 * ARGUMENTS:
 *   - array of strings:
 *        char **str;
 *   - size of array:
 *        int size;
 * RETURNS: none.
 */
void ClearMemory(char **str, int size)
{
  for (int i = 0; i < size; i++)
    free(str[i]);
} /* End of 'ClearMemory' function */

/* Main function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
int main(void)
{
  char **str = NULL, InFileName[] = "IN_onegin.txt", OutFileName[] = "OUT_onegin.txt";
  int size = 0;
  
  str = ReadStr(str, InFileName, &size);
  QuickSortStrings(str, size, StrCompare);
  WriteStr(str, OutFileName, size);
  ClearMemory(str, size);

  return 0;
}/* End of 'main' function */