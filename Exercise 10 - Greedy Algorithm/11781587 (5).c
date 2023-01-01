#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** 
 * @author Guilherme Henrique Galdini Tosi  <--> NUSP 11781587
 * @author Yazid Alamou Bouari <--> N°USP 13551034
 */

#define true 1
#define false 0 
#define UNINITIALIZATED_INDEX -1

typedef int boolean;

static char *substring(char *string, int size);
static boolean verifySubstring(char *string, char *substring);
static int getOverlap(char *prefixo, char *sufixo);
static int **createMatrixOverlaps(char **reads, int n);
static char **reduceReadsRecursive(char **reads, int *n);
static void *readAndsplitString(char line[], char *str);
static void freeMatrix(char **matrix, int n);
static void reduceAndPrintReads(char **reads, int n);
static int **fillMatrixWithValue(int **matrix, int value, int n);
int **insertOverlapsInMatrix(int **matrix, char **reads, int n);

int main() 
{
    int n;
    char line[100];
    char *str = "";
    char **reads;

    // Lê quantidade de reads
    if(!(scanf("%d", &n)))
    {
        exit(EXIT_FAILURE);
    }
    getchar();
    reads = (char **)malloc(sizeof(char *) * n);

    if(reads == NULL)
    {
        exit(EXIT_FAILURE);
    }
    //read user's input and split it
    for (int i = 0; i < n; i++)
     {
        reads[i] = readAndsplitString(line, str);
    }

    reduceAndPrintReads(reads, n);
    freeMatrix(reads, n);

    return 0;
}

char *substring(char *string, int size) 
{
    char *result = (char *)malloc(sizeof(char) * (strlen(string) + 1));
    if (result != NULL && size < strlen(string)) 
    {
        strcpy(result, string);
        result[size] = '\0';
    }
    return result;
}

boolean verifySubstring(char *string, char *substring)
 {
    int entireString = strlen(string);
    int substringGiven = strlen(substring);
    int i, j;

    if((entireString - substringGiven) <= 0)
    {
        return false;
    }

    for (i = 0; i <= entireString - substringGiven; i++) 
    {
        for (j = 0; j < substringGiven; j++) 
        {
         if (string[i + j] != substring[j])
          {
            break;
          }
        }
        if (j == substringGiven)
        {
            return true;
        }
    }
    return false;
}

int getOverlap(char *str1, char *str2)
 {
    int max = UNINITIALIZATED_INDEX;
    int lesserString;

    if(strlen(str1) < strlen(str2))
    {
        lesserString = strlen(str1);
    }
    else
        lesserString = strlen(str2);

    if (strlen(str2) <= strlen(str1))
     {
        if (verifySubstring(str1, str2)) 
        {
            return strlen(str2);
        }
    }

    for (int i = 1; i <= lesserString; i++) //index 0 is '\0', for concactenating reads
     {
        char *subStr = substring(str2, i);
        if (strcmp(&str1[strlen(str1) - i], subStr) == 0) 
        {
            if (max < i) 
            {
                max = i;
            }
        }
        free(subStr);
    }
    return max;
}

int **createMatrixOverlaps(char **reads, int n) 
{
    int **OverlapsMatrix;

    OverlapsMatrix = (int **)malloc(sizeof(int *) * n);
    if (OverlapsMatrix == NULL) 
    {
        return NULL;
    }
    for (int i = 0; i < n; i++)
     {
        OverlapsMatrix[i] = (int *)malloc(n*sizeof(int));
        if (OverlapsMatrix[i] == NULL) 
        {
            return NULL;
        }
    }
    OverlapsMatrix = fillMatrixWithValue(OverlapsMatrix, -1, n);
    OverlapsMatrix = insertOverlapsInMatrix(OverlapsMatrix, reads, n);

    return OverlapsMatrix;
}

int **insertOverlapsInMatrix(int **matrix, char **reads, int n)
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++)
         {
            if (i != j)
             {
                matrix[i][j] = getOverlap(reads[i], reads[j]);
            }
        }
    }
    return matrix;
}

char **reduceReadsRecursive(char **reads, int *n) 
{
    char **result;
    char *strConcatenated; //strings will be concated after in '\0', subscripting him
    int **OverlapsMatrix; 
    int size = *n; //it will be updated always that new substring is concatenated
    int strIndex[2] = {0, 1}; //[0] => i and [1] => j
    int max = UNINITIALIZATED_INDEX;
    int k = 1;
    int sizeStrConcactenated;

    OverlapsMatrix = createMatrixOverlaps(reads, *n);
    result = (char **)malloc(sizeof(char *) * (size - 1));

    if (OverlapsMatrix == NULL || result == NULL)
     {
        return NULL;
    }

    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            if (max < OverlapsMatrix[i][j]) 
            {
                max = OverlapsMatrix[i][j];
                strIndex[0] = i;
                strIndex[1] = j;
            }
        }
    }

    if (max > UNINITIALIZATED_INDEX) //it means that index is not
     {
        sizeStrConcactenated = strlen(reads[strIndex[0]]) + strlen(&reads[strIndex[1]][max]) + 1;
    } 
    else
     {
        sizeStrConcactenated = strlen(reads[strIndex[0]]) + strlen(reads[strIndex[1]]) + 1;
     }
     strConcatenated = (char *)malloc(sizeof(char) * sizeStrConcactenated);

    if (strConcatenated == NULL) 
    {
        return NULL;
    }
    else
    {
      strConcatenated[0] = '\0'; //because the next string/substring will concat behind/in it
      strConcatenated = strcat(strConcatenated, reads[strIndex[0]]);
    }

    if (max > UNINITIALIZATED_INDEX)//it means that matrix was filled
    {
        strConcatenated = strcat(strConcatenated, &reads[strIndex[1]][max]);
    } 
    else 
    {
        strConcatenated = strcat(strConcatenated, reads[strIndex[1]]);
    }

    result[0] = (char *)malloc(sizeof(char) * (strlen(strConcatenated) + 1));
    if(result[0] == NULL)
    {
        exit(EXIT_FAILURE);
    }
    strcpy(result[0], strConcatenated);
    free(strConcatenated);

    for (int i = 0; i < size; i++)
     {
        if (i != strIndex[0] && i != strIndex[1]) 
        {
            result[k] = (char *)malloc(sizeof(char) * (strlen(reads[i]) + 1));
            if (result[k] == NULL)
             {
                return NULL;
            }
            strcpy(result[k], reads[i]);
            k++;
        }
    }
     //'n' needs to be pointer because it's updated always that new substring is concatenated, in non-recursive form, 
     // it can consume a lot of memory, and the program gets slower either
    *n = size - 1;
    return result;
}

static void *readAndsplitString(char line[], char *str)
{
  setbuf(stdin, NULL); //clear buffer, avoiding I/O problems
  if(!(fgets(line, 100, stdin)))
    exit(EXIT_FAILURE);
  str = substring(line, strlen(line) - 1);

  return str;
}

static void freeMatrix(char **matrix, int n)
{
    for(int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    matrix = NULL;
}

static void reduceAndPrintReads(char **reads, int n)
{
    while (n > 1) 
    {
        reads = reduceReadsRecursive(reads, &n);
    }
    for (int i = 0; i < n; i++) 
    {
        printf("%s\n", reads[i]);
    }
} 
static int **fillMatrixWithValue(int **matrix, int value, int n)
{
    for(int i = 0; i < n; i++)
    {
     for (int j = 0; j < n; j++)
        {
            matrix[i][j] = value;
        }
    }
        return matrix;
}