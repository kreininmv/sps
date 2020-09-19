/* FILE NAME   : Onegin.cpp
 * PURPOSE     : Main start module.
 * PROGRAMMER  : Matvei Kreinin,
 * LAST UPDATE : 13.09.2020.
 * NOTE        : None.
 */

#include <stdio.h>
#include <assert.h>
#include <windows.h>
#include <string.h>

 /*! Swap two elements function.
  * \param[in]  point to the first element  - void **str1;
  * \param[in]  point to the second element - void **str2;
  * \param[out] none.
  */
void Swap(void **str1, void **str2);

/* Strings comparing function.
 * \param[in]  point to first string  - char *str1;
 * \parma[in]  point to second string - char *str2;
 * \param[out] number > 0 if (str1 > str2) and number < 0 if (str1 < str2) and 0 if (str1 == str2)
 */
int StrCompare(const void *str1, const void *str2);

/* Strings comparing from endfunction.
 * \param[in]  point to first string  - char *strA;
 * \param[in]  point to second string - char *strB;
 * \param[out] number > 0 if (strA > strB) and number < 0 if (strA < strB) and 0 if (strA = strB)
 */
int StrCompareBehind(const void *strA, const void *strB);

/* Sort array of string function.
 * \param[in]  array of strokes             - char **str;
 * \param[in]  size of array                - int N;
 * \param[in]  point for comparing function - int (*Compare)(char *, char *);
 * \param[in]  size of data                 - int size;
 * \param[out] none.
 */
void QuickSortStrings(void **A, int N, int(*Compare)(const void *, const void *));

/* Read strokes from file function.
 * \param[in]  point to array of strings  - char ***str;
 * \param[in]  name of file               - char *FilaName;
 * \param[in]  point to the size of array - int *size;
 * \param[out] count of strokes.
 */
int ReadStr(char ***STR, const char *FileName);

/* Write array of strings to the file function.
 * \param[in]  array of strings - char **str;
 * \param[in]  name of file     - char *FileName;
 * \param[in]  size of array    - int size;
 * \param[out] none.
 */
void WriteStr(char **str, const char *FileName, int size);

/* Clearing memory of array function.
 * \param[in]  array of strings - char **str;
 * \param[in]  size of array    - int size;
 * \param[out] none.
 */
void ClearMemory(char **str, int size);
 
 /*! Main function.
 * \param[in]  none.
 * \param[out] none.
 */
int main(void)
{
  char **str = nullptr;
  char const InFileName[] = "IN_onegin.txt", OutFileName[] = "OUT_onegin.txt";
  int size = ReadStr(&str, InFileName);
  WriteStr(str, OutFileName, size);
  
  //QuickSortStrings((void **)str, size, StrCompare);

  QuickSortStrings((void **)str, size, StrCompareBehind);
  WriteStr(str, OutFileName, size);
  ClearMemory(str, size);

  return 0;
}/* End of 'main' fu  nction */

/*! Swap two elements function.
 * \param[in]  point to the first element  - void *str1;
 * \param[in]  point to the second element - void *str2;
 * \param[out] none.
 */
void Swap(void **str1, void **str2)
{
  void *tmp = *str1;
  *str1 = *str2;
  *str2 = tmp;

}/* End of 'Swap' function */

/*! Strings comparing from endfunction.
 * \param[in]  point to first string  - char *strA;
 * \param[in]  point to second string - char *strB;
 * \param[out] number > 0 if (strA > strB) and number < 0 if (strA < strB) and 0 if (strA = strB)
 */
int StrCompareBehind(const void *strA, const void *strB)
{
  int LenA = strlen((char *)strA), LenB = strlen((char *)strB);
  char *str1 = (char *)strA + LenA, *str2 = (char *)strB + LenB;

  while (*str1 == ' ' || *str1 == '.' || *str1 == '\n' || *str1 == 0 || *str1 == 't')
  {
    str1--;
    LenA--;
  }

  while (*str2 == ' ' || *str2 == '.' || *str2 == '\n' || *str2 == 0 || *str1 == 't')
  {
    str2--;
    LenB--;
  }

  while (*str1 == *str2 && LenA >= 0 && LenB >= 0)
  {
    str1--;
    str2--;
    LenA--;
    LenB--;

    while (*str1 == ' ' || *str1 == '\t')
    {
      str1--;
      LenA--;
    }
    while (*str2 == ' ' || *str2 == '\t')
    {
      str2++;
      LenB--;
    }
  }

  return (int)*str2 - (int)*str1;
}
/* End of 'StrCompareBehind' function */

/*! Strings comparing function.
 * \param[in]  point to first string  - void *strA;
 * \param[in]  point to second string - void *strB;
 * \param[out] number > 0 if (strA > strB) and number < 0 if (strA < strB) and 0 if (strA = strB)
 */
int StrCompare(const void *strA, const void *strB)
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

/*! Sort array of string function.
 * \param[in]  array of strokes             - char **str;
 * \param[in]  size of array                - int N;
 * \param[in]  point for comparing function - int (*Compare)(char *, char *);
 * \param[out] none.
 */
void QuickSortStrings(void **A, int N, int(*Compare)(const void *, const void *))
{
  long b = 0, e = N - 1;

  void *x = *(A + (N / 2));

  if (N < 2)
    return;

  while (b <= e)
  {
    while (Compare(x, *(A + b)) > 0)
      b++;
    while (Compare(*(A + e), x) > 0)
      e--;
    if (b <= e)
    {
      if (b != e)
        Swap((A + b), (A + e));
      b++;
      e--;
    }
  }
  QuickSortStrings(A, e + 1, StrCompare);
  QuickSortStrings(A + b, N - b, StrCompare);
}/* End of 'QuickSort' function */

/*! Read strokes from file function.
 * \param[in]  point to array of strings  - char ***str;
 * \param[in]  name of file               - char *FilaName;
 * \param[out] count of strokes.
 */
int ReadStr(char ***STR, const char *FileName)
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
  size++;

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

/*! Write array of strings to the file function.
 * \param[in]  array of strings - char **str;
 * \param[in]  name of file     - char *FileName;
 * \param[in]  size of array    - int size;
 * \param[out] none.
 */
void WriteStr(char **str, const char *FileName, int size)
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

/*! Clearing memory of array function.
 * \param[in]  array of strings - char **str;
 * \param[in]  size of array    - int size;
 * \param[out] none.
 */
void ClearMemory(char **str, int size)
{
  for (int i = 0; i < size; i++)
    free(str[i]);

  free(str);
} /* End of 'ClearMemory' function */