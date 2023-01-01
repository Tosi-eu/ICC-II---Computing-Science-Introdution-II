#include <stdio.h>
#include <stdlib.h>

#define QUICK 1
#define SHELL 0
#define NONE 2

typedef short int operatorType;
int quickCmp = 0, quickCopies = 0;

int shellsort(int *array, int n);
int quicksort(int *array, int start, int end);
void swap(int *x, int *y);

int main()
{
    int shell; //guarda operações do shell
    int quick; //guarda operações do quick
    int N; //tamahno do vetor
    operatorType select;

    scanf("%d", &N); //tamanho do mainArray
 
    int *mainArray = malloc(N * sizeof(int)); //vetor principal, será utilizado para as comapações do shell 
    int *auxArray = malloc(N * sizeof(int));  //vetor que será usado para as comparações do quick
    int *auxArray2 = malloc(N * sizeof(int)); //vetor auxiliar que só armazena os valores do mainArray

    if(mainArray == NULL || auxArray == NULL || auxArray2 == NULL)
    {
      exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < N; i++){
        scanf("%d", &mainArray[i]); //valores do vetor principal
        // quickCmp cada input os auxiliares recebem os valores do principal
        auxArray[i] = mainArray[i];
        auxArray2[i] = mainArray[i];
    }
    
    
    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            mainArray[j] = auxArray2[j];
            auxArray[j] = auxArray2[j];
        }

        shell = shellsort(mainArray, i);
        quick = quicksort(auxArray, 0, i-1); 

      //setando quem faz menos comparações + cópias
      if (shell == quick)
        {
            select = NONE;
        }

        if (shell > quick)
        {
            select = QUICK;
            }
        if (shell < quick)
        {
            select = SHELL;
        }

       //resultado das atribuições
       switch (select)
       {
       case NONE:
        printf("- ");
        break;

       case QUICK:
          printf("Q ");
          break;
        
       case SHELL:
          printf("S ");
          break;
       
       default:
        break;
       }
     quickCmp = 0; quickCopies = 0; 
    } 

  free(auxArray);
  free(auxArray2);
  free(mainArray);

  return 0;
}

int shellsort(int *array, int n)
{
    int comparisons = 0;
    int copies = 0;

    int gap = 1;

    while(gap <= n) { // tentando pegar o maior gap possivel 
        gap *= 2;
    }

    gap = (gap / 2) - 1; //muda a cada iteração doo loop

    while(gap > 0) //ordena a cada loop com um gap diferente
    {
        for (int i = gap; i < n; i += gap)
        { 
            int x = array[i];                 
            int j = i - gap;  
            copies++; 
            
            while(j >= 0 && array[j] > x)
            {
                array[j + gap] = array[j];
                comparisons++;
                j -= gap;
                copies++; 
            }

            if (j >= 0){
                comparisons++;
            }

            array[j + gap] = x;
            copies++;
        }
        gap /= 2;
    }
    return copies + comparisons;
}

int quicksort(int *array, int start, int end)
{

    if (start >= end)
    {
        return quickCmp + quickCopies;
    }

    int mid = (end + start) / 2;
    int pivot = array[mid];
    int right = start;
    int left = end;
    quickCopies++;  

    while(1)
    {
        while(array[right] < pivot)  //verificando se o vetor ultrapassou o meio do vetor, pela direita
        { 
         quickCmp++; 
            right++;
        }
        
     quickCmp++;
        
        while(array[left] > pivot) //verificando se o vetor ultrapassou o meio do vetor, pela esquerda
        { 
            left--;
         quickCmp++;
        }
        
     quickCmp++;

        if (right >= left)
        {
            break;
        }

        //vai fazendo trocas e continua no while at quickCmp condição ser falsa
        swap(&array[right], &array[left]);

        quickCopies += 3; // quickCmp cada passo da troca, quickCopies é incrementado, que dará 3 incrementos
        right++; 
        left--;  
    }

    quicksort(array, start, left);
    quicksort(array, left + 1, end); 

    return quickCmp + quickCopies;     
}

void swap(int *x, int *y)
{
  int aux = *x;
  *x = *y;
  *y = aux;
}