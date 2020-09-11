/* FILE NAME   : Onegin.cpp
 * PURPOSE     : Main start module.
 * PROGRAMMER  : Matvei Kreinin,    
 * LAST UPDATE : 10.09.2020.
 * NOTE        : None.
 */

#include <stdio.h>
#include <assert.h>
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
void Swap(char **str1, char **str2);

/* Strings comparing function.
 * ARGUMENTS:
 *   - point to first string:
 *        char *strA;
 *   - point to second string:
 *        char *str2;
 * RETURNS: number > 0 if (strA > strB) and number < 0 if (strA < strB) and 0 if (strA = strB)
 */
int StrCompare(const void *strA, const void *strB);

/* Sort array of string function.
 * ARGUMENTS:
 *   - array of strokes:
 *        char **str;
 *   - size of array:
 *        int N;
 *   - point for comparing function:
 *        int (*Compare)(char *, char *);
 * RETURNS: None.
 */
void QuickSortStrings(char **A, int N, int(*Compare)(const void *, const void *));

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
int ReadStr(char ***STR, const char *FileName);

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
void WriteStr(char **str, const char *FileName, int size);

/* Clearing memory of array function.
 * ARGUMENTS:
 *   - array of strings:
 *        char **str;
 *   - size of array:
 *        int size;
 * RETURNS: none.
 */
void ClearMemory(char **str, int size);

/* Reverse array function.
 * ARGUMENTS:
 *   - array of strings:
 *        char **str;
 *   - size of array:
 *        int size;
 * RETURNS: None.
 */
void Reverse(char **str, int size);

/* Main function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
int main( void )
{
  char **str = NULL;
  char const InFileName[] = "IN_onegin.txt", OutFileName[] = "OUT_onegin.txt";
  int size = ReadStr(&str, InFileName);

  QuickSortStrings(str, size, StrCompare);
  WriteStr(str, OutFileName, size);
  ClearMemory(str, size);

  return 0;
}/* End of 'main' fu  nction */

/* Swap two elements function.
 * ARGUMENTS:
 *   - point to the first element:
 *        char *str1;
 *   - point to the second element:
 *        char *str2;
 * RETURNS: None.
 */
void Swap( char **str1, char **str2 )
{
  char *tmp = *str1;
  *str1 = *str2;
  *str2 = tmp;

}/* End of 'Swap' function */

/* Strings comparing function.
 * ARGUMENTS:
 *   - point to first string:
 *        char *strA;
 *   - point to second string:
 *        char *str2;
 * RETURNS: number > 0 if (strA > strB) and number < 0 if (strA < strB) and 0 if (strA = strB) 
 */
int StrCompare( const void *strA, const void *strB )
{
  char *str1 = (char *)strA, *str2 = (char *)strB;

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
 *   - point for comparing function:
 *        int (*Compare)(char *, char *);
 * RETURNS: None.
 */
void QuickSortStrings( char **A, int N, int (*Compare)(const void *, const void *) )
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
int ReadStr( char ***STR, const char *FileName )
{
  int size = 0;
  FILE *F = fopen(FileName, "r");

  if (F == NULL)
  {
    printf("We can't find the file...\n");
    assert(0);
  }

  int tmp = 0;
  do 
  {
    if (tmp == '\n')
      size++;
    tmp = fgetc(F);
  } while (tmp != EOF);

  rewind(F);

  char **str = (char **)calloc(size, sizeof(char *));
  long lencur = 0;

  for (int i = 0; i < size; i++)
  {
    int lenstr = 0;

    do
    {
      tmp = fgetc(F);
      lenstr++;
    } while (tmp != '\n' && tmp != EOF);

    lenstr++;
    fseek(F, lencur * sizeof(char), SEEK_SET);
    lencur += lenstr;
   

    str[i] = (char *)calloc(lenstr + 1, sizeof(char));
    fgets(str[i], lenstr, F);
    
  }

  *STR = str;
  fclose(F);

  return size;
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
void WriteStr( char **str, const char *FileName, int size )
{
  FILE *F = fopen(FileName, "w");

  if (F == NULL)
  {
    printf("We can't create the file...\n");
    assert(0);
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
void Reverse( char **str, int size )
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
void ClearMemory( char **str, int size )
{
  for (int i = 0; i < size; i++)
    free(str[i]);
  free(str);
} /* End of 'ClearMemory' function */