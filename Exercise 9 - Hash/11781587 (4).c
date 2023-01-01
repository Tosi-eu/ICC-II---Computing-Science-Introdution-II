#include <stdio.h>
#include <stdlib.h>

/**
 * Nome: Guilherme Henrique Galdini Tosi || N°USP: 11781587
 */

typedef struct numbers NUMBER;
typedef int boolean;

#define something_bad_happened 0
#define false -1
#define true 0

struct numbers
{
    int key;
    int value;
};

NUMBER *create_hash_table(int hash_table_size);
NUMBER *fill_table_with_blank_spaces(NUMBER *hashTable, int hash_table_size);
int calculate_hash(int value, int hash_table_size);
boolean insert_in_hash_table(int value, int hash_table_size, NUMBER *array);
boolean restart_hash_table_index(int value, int hash_table_size, NUMBER *array);
boolean search_in_hash_table_and_print(int value, int hash_table_size, NUMBER * array);

int main()
{
    NUMBER *hashTable;
    int hash_table_size = 0;
    int insertions = 0;
    int remotions = 0;
    int searches = 0;
    int keyToBeRemoved;
    int key_to_search;
    int number;

    scanf("%d", &hash_table_size);
    scanf("%d", &insertions);

    if(hash_table_size <= 0 || insertions <= 0)
    {
        return something_bad_happened;
    }

    hashTable = create_hash_table(hash_table_size);
    if(hashTable == NULL)
    {
        exit(something_bad_happened);
    }
    else
    {
        hashTable = fill_table_with_blank_spaces(hashTable, hash_table_size);
    }

    for(int i = 0; i < insertions; i++)
    {
        if(!scanf("%d", &number))
        {
            return something_bad_happened;
        }
        else
        {
            insert_in_hash_table(number, hash_table_size, hashTable);
        }
    }

    scanf("%d", &remotions);
    if(remotions <= 0)
    {
        return something_bad_happened;
    }


    for(int i = 0; i < remotions; i++)
    {
        if(!scanf("%d", &keyToBeRemoved))
        {
            return something_bad_happened;
        }
        restart_hash_table_index(keyToBeRemoved, hash_table_size, hashTable);
    }

    if(!scanf("%d", &searches))
    {
        return something_bad_happened;
    }

    for(int i = 0; i < searches; i++)
    {
        if(!scanf("%d", &key_to_search))
        {
            return something_bad_happened;
        }
        search_in_hash_table_and_print(key_to_search, hash_table_size, hashTable);
    }

    free(hashTable);
    return 0;
}

NUMBER *create_hash_table(int hash_table_size)
{
    NUMBER *hashTable = (NUMBER*)malloc(hash_table_size*sizeof(NUMBER));

    if(hashTable != NULL)
    {
        return hashTable;
    }
    return NULL;
}

NUMBER *fill_table_with_blank_spaces(NUMBER *hashTable, int hash_table_size)
{
    for(int i = 0; i < hash_table_size; i++)
    {
        hashTable[i].value = false;
        hashTable[i].key = false;
    }
    return hashTable;
}

int calculate_hash(int value, int hash_table_size)
{
    int hash_index = value % hash_table_size;

    return hash_index;
}

boolean insert_in_hash_table(int value, int hash_table_size, NUMBER *array)
{
    for(int i = 0; i < hash_table_size; i++)
    {
        if(array[i].value == value)
            return false;
    }

    int poll = calculate_hash(value, hash_table_size);

    int i = 0;
    while(array[poll].value != false)
    {
        i++;
        poll = calculate_hash(value + i, hash_table_size);
    }

    array[poll].value = value;
    array[poll].key = poll;
    return true;
}

boolean search_in_hash_table_and_print(int value, int hash_table_size, NUMBER *array)
{
    for (int i = 0; i < hash_table_size; i++)
    {
        if (array[i].value == value)
        {
            printf("%d ", array[i].key);
            return false;
        }
    }
    printf("%d ", false);
    return true;
}

boolean restart_hash_table_index(int value, int hash_table_size, NUMBER *array)
{
    for (int i = 0; i < hash_table_size; i++)
    {
        if (array[i].value == value)
        {
            array[i].value = false;
            array[i].key = false;
            return true;
        }
    }
    return false;
}