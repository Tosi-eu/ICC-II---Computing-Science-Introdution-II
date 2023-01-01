#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SERVICE_UNAVAILABLE 500 
/*
  30th group:

  - Guilherme Henrique Galdini Tosi
  - Gabriel de Souza Dalcim
  - Gabriel de Moraes Andreghetti
  - Paulo Henrique Vedovatto Turquetti
*/

//sorting methods (O(n^2)) headers
void bolha(int *arr, int ARRAY_SIZE);
void selecao(int *arr, int ARRAY_SIZE);

//auxiliar functions
void choose_method(int *arr, char method_name[8], int ARRAY_SIZE);
void swap(int *x, int *y);
void print_array(int *arr, int ARRAY_SIZE);

int main(){

  int ARRAY_SIZE;
  char method_name[8];

  setbuf(stdin, NULL); 

  scanf("%s", method_name);
  scanf("%d", &ARRAY_SIZE);

  int *arr = malloc(ARRAY_SIZE*sizeof(int));

  for(int i = 0; i < ARRAY_SIZE; i++){
      scanf("%d", &arr[i]);
  }

  choose_method(arr, method_name, ARRAY_SIZE);
  
  free(arr);
  return 0;
}

void selecao(int *arr, int ARRAY_SIZE){
  int min_value; //selection always considers the first value like the lesser value

  for(int i = 0; i < ARRAY_SIZE; i++){
      min_value = i;
      for(int subsequent_value = i + 1; subsequent_value < ARRAY_SIZE; subsequent_value++){
          printf("C %d %d\n", min_value, subsequent_value);
          if(arr[min_value] > arr[subsequent_value]){
              min_value = subsequent_value;
          }
      }
      if(min_value != i){
        printf("T %d %d\n", i, min_value);
        swap(&arr[i], &arr[min_value]);
      }
  }
  print_array(arr, ARRAY_SIZE);
}

void bolha(int *arr, int ARRAY_SIZE) {

  int previous_modification = ARRAY_SIZE; //work as a sentinel
  int array_end;

  for(int i = 0; i < ARRAY_SIZE; i++){
      array_end = previous_modification;
        for(int j = 0; j < array_end - 1; j++){
            printf("C %d %d\n", j, j + 1);
            if(arr[j] > arr[j + 1]){
                previous_modification = j + 1;
                printf("T %d %d\n", j, previous_modification);
                swap(&arr[j], &arr[j + 1]);
            }
      }

        if(previous_modification == array_end){
          break;
          }//without this works either, but is a improvement but it avoids unnecessary comparisons
      }
    print_array(arr, ARRAY_SIZE);
  }

void choose_method(int *arr, char method_name[8], int ARRAY_SIZE){

    if(strcmp(method_name, "bolha") == 0){
        bolha(arr, ARRAY_SIZE);
    }else if(strcmp(method_name, "selecao") == 0){
        selecao(arr, ARRAY_SIZE);
    }else{
        printf("method not found in directory...\n");
        exit(SERVICE_UNAVAILABLE);
    }
}

void print_array(int *arr, int ARRAY_SIZE){

    for(int i = 0; i < ARRAY_SIZE; i++) {
      printf ("%d ", *(arr + i));
  }
  printf ("\n");
}

void swap(int *x, int *y){
  int swap_terms = *x;
  *x = *y;
  *y = swap_terms;
}