 #include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SERVICE_UNAVAILABLE 500

void merge_logic(int *array, int array1_start, int mid, int array2_start, int array2_end, int *aux_vet, int *comparisons, int *changes);
void merge(int *array, int array_start, int array_end, int *aux_vet, int *comparisons, int *changes);
void mergesort(int *array, int array_size);
void insertion_sort(int *arr, int array_size);
void free_matrix(int **matrix, int rows);
int scanf_array(int *arr, int ARRAY_SIZE);

int main(){

    int Q, *N, **arrays_matrix; // respectivly: arrays amount, arrays size and matrix of arrays
    int *aux_array; //for mergesort

    scanf("%d", &Q);
    N = (int *) malloc(Q*sizeof(int));
    arrays_matrix = (int**) malloc(Q*sizeof(int*));

    if(N == NULL || arrays_matrix == NULL){
        return SERVICE_UNAVAILABLE;
    }

    scanf_array(N, Q); //scanf &N[i] Q times

    for(int i = 0; i < Q; i++){
        arrays_matrix[i] = (int*)malloc(N[i]*sizeof(int));
        if(arrays_matrix[i] == NULL){
            return SERVICE_UNAVAILABLE;
        }
    }

    //### STARTING LOOP OF SORTING LOGIC ### //
    for(int i = 0; i < Q; i++){
        aux_array = (int *) malloc(N[i]*sizeof(int)); // aux array -> necessary for mergesort
        for(int j = 0; j < N[i]; j++){
            scanf("%d", &arrays_matrix[i][j]);
            aux_array[j] = arrays_matrix[i][j];
        }
        insertion_sort(arrays_matrix[i], N[i]);
        mergesort(aux_array, N[i]);
        free(aux_array); // necessary to do here, else the arrays doesn't will be resetted (trust me)
    }

  free(N);
  free_matrix(arrays_matrix, Q);
  return 0;
}

void merge_logic(int *array, int array1_start, int mid, int array2_start, int array2_end, int *aux_vet, int *comparisons, int *changes){
    int indexes_array1 = array1_start, indexes_array2 = array2_start, aux_array_indexes = 0;


    if(array1_start >= array2_end){
        exit(SERVICE_UNAVAILABLE);
    }
    
    while (indexes_array1 <= mid && indexes_array2 <= array2_end){
        (*comparisons)++;
        (*changes)++;

        if(array[indexes_array1] <= array[indexes_array2]){
            aux_vet[aux_array_indexes++] = array[indexes_array1++];
        }else{
              aux_vet[aux_array_indexes++] = array[indexes_array2++];
       }
    }

    while(indexes_array1 <= mid){
        (*changes)++;
        aux_vet[aux_array_indexes++] = array[indexes_array1++];
    }

    while(indexes_array2 <= array2_end){
        (*changes)++;
        aux_vet[aux_array_indexes++] = array[indexes_array2++];
    }

    aux_array_indexes = 0; //resetting variable at the final for join the splitted arrays
    for(int i = array1_start; i <= array2_end; i++, aux_array_indexes++){
        (*changes)++; //if necessary while joining array1 in array2
        array[i] = aux_vet[aux_array_indexes];
    }
}

void merge(int *array, int array_start, int array_end, int *aux_vet, int *comparisons, int *changes){

    int mid;
    if(array_start >= array_end){
        return;
    }else{
        mid = floor((array_start + array_end) / 2);   
        merge(array, array_start, mid, aux_vet, comparisons, changes); //start to mid -> first array
        merge(array, mid + 1, array_end, aux_vet, comparisons, changes); // mid + 1 to end -> second array
        merge_logic(array, array_start, mid, mid + 1, array_end, aux_vet, comparisons, changes); //group all and merge
    }
}

void mergesort(int *array, int array_size){
    
    int *aux_vet = (int *)malloc(array_size*sizeof(int)), change = 0, compare = 0;

    if(aux_vet == NULL){
        printf("Impossible to allocate memory...");
        exit(SERVICE_UNAVAILABLE);
    }

    merge(array, 0, array_size - 1, aux_vet, &compare, &change);
    printf("M %d %d %d\n", array_size, change, compare);

    free(aux_vet);
}

void insertion_sort(int *arr, int array_size){
  
 int j, aux, changes = 0, comparisons = 0;
  
  for(int i = 1; i < array_size; i++){
    changes++;
    aux = arr[i];
    for(j = i - 1; j >= 0; j--){
      comparisons++;
      if(arr[j] > aux){
         changes++;
         arr[j + 1] = arr[j];
      }else
        break;
    }
    changes++;
    arr[j + 1] = aux;
  }
  printf("I %d %d %d\n", array_size, changes, comparisons);
}

int scanf_array(int *arr, int ARRAY_SIZE){
    for(int i = 0; i < ARRAY_SIZE; i++){
        scanf("%d", &(*(arr + i)));
    }
    return *arr;
}

void free_matrix(int **matrix, int rows){

    for(int i = 0; i < rows; i++){
        free(matrix[i]);
    }
    free(matrix);
    matrix = NULL;
}