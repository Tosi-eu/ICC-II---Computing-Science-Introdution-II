#include <stdio.h>
#include <stdlib.h>

/*
  Integrantes:

    - Guilherme Henrique Galdini Tosi - N°USP: 11781587
    -                                 - N°USP:
    -                                 - N°USP:
    -                                 - N°USP:
*/

typedef struct tree_ST TREE;
typedef struct node_ST NODE;

struct node_ST
{
    int value;
    NODE *left_son;
    NODE *right_son;
};

struct tree_ST
{
    NODE *root_knot;
    int height;
};

TREE *createTree();
NODE *insertNodeInTree(NODE *root, int value);
void insertValueInTree(TREE *tree, int value);
int findValue(NODE *root, int value);
void shuffleValues(int *array, int n);
void swap(int *x, int *y);
void deallocateNodes(NODE *root_knot);

int main() 
{
  int array_size;
  int searchLenght;
  int valueToBeFound;

  scanf("%d", &array_size);
  int *auxArray = malloc(array_size*sizeof(int));
  TREE *tree = createTree();

  for(int i = 0; i < array_size; i++)
  {
    scanf("%d", &auxArray[i]);
  }

  shuffleValues(auxArray, array_size); 
  
  for(int i = 0; i < array_size; i++)
  {
    tree->root_knot = insertNodeInTree(tree->root_knot, auxArray[i]);
  }

  scanf("%d", &searchLenght);

  for(int i = 0; i < searchLenght; i++)
  {
    scanf("%d", &valueToBeFound);
    if(findValue(tree->root_knot, valueToBeFound) == 0)
    {
      printf("0\n");
    }
    else  
      printf("1\n");
  }
  
  //WORK DONE -> FREE ALLOCS ONLY -> VERIFIED WITH VALGRIND
  free(auxArray);
  deallocateNodes(tree->root_knot);
  free(tree);

  return 0;
}

TREE *createTree()
{
    TREE *binaryTree;
    binaryTree = (TREE*)malloc(sizeof(TREE));

    if (binaryTree != NULL)
    {
        binaryTree->root_knot = NULL;
        binaryTree->height = -1;
        return binaryTree;
    }

    return NULL;
}

NODE *insertNodeInTree(NODE *root_knot, int value)
{
    if(root_knot == NULL)
    {
        NODE *auxNode = (NODE*)malloc(sizeof(NODE));//if declarated out of 'if' statement, it will alloc more memory 
        auxNode->value = value;
        auxNode->left_son = NULL;
        auxNode->right_son = NULL;

        return auxNode;
    }
    else{
        if(root_knot->value < value)
            root_knot->right_son = insertNodeInTree(root_knot->right_son, value);
        
        if(root_knot->value > value)
            root_knot->left_son = insertNodeInTree(root_knot->left_son, value);
        
        return root_knot;
    }
}

int findValue(NODE *root_knot, int value)
{
  if(root_knot != NULL)
  {
    if(root_knot->value == value)
    {
      return 1;
    }
    else if(root_knot->value < value)
    {
      return findValue(root_knot->right_son, value);
    }
    else
      return findValue(root_knot->left_son, value);
  }
  return 0;
}

void shuffleValues(int *array, int n)
{
    if (n > 1) 
    {
        int i;
        for (i = 0; i < n - 1; i++) 
        {
          int j = i + rand() / (RAND_MAX / (n - i) + 1);
          swap(&array[j], &array[i]);
        }
    }
}

void deallocateNodes(NODE *root_knot)
{
    if(root_knot == NULL)
        return;

    deallocateNodes(root_knot->right_son);
    deallocateNodes(root_knot->left_son);
    free(root_knot);
}

void swap(int *x, int *y)
{
  int aux = *x;
  *x = *y;
  *y = aux;
}