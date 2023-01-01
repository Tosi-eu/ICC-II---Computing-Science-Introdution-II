#include <stdio.h>
#include <stdlib.h>

/** 
 * @author Guilherme Henrique Galdini Tosi  <--> NUSP 11781587
 * @author Yazid Alamou Bouari <--> N°USP 13551034
 */

#define EMPTY_ARRAY -1

static int getRange(int rows, int columns);
static void fillArray(int *array, int array_size);
int maxFriendsOnTheWay(int *cache, int *friendsOnTheBestWay, int origin, int rows, int columns);

int main()
{
    int rows, columns;
    int range;
    int *friendsOnTheBestWay;
    int *cache;

    if(!(scanf("%d %d", &rows, &columns)))
    {
        exit(-2);
    } 

    friendsOnTheBestWay = (int *)malloc(sizeof(int)*(2*(rows*columns - 1))); //2*(rows*columns - 1) == ways amount
    cache = (int *)malloc(sizeof(int)*(2*(rows*columns - 1)));
    
    if(friendsOnTheBestWay != NULL || cache != NULL)
    {
         fillArray(friendsOnTheBestWay, (2*(rows*columns - 1))); //initialize with -1
         fillArray(cache, (2*(rows*columns - 1))); //initialize with -1
         range = getRange(rows, columns);
    }
    else
       exit(-1);
    
    for(int i = 0; i < range; i++)
    {
        int origin, end, friends;

        if(!(scanf("%d %d %d", &origin, &end, &friends)))
        {
            exit(-3);
        }

        if(end - origin == 1)
        {
            friendsOnTheBestWay[2 * origin] = friends;
        }
        else
        {
            friendsOnTheBestWay[2 * origin + 1] = friends;
        }
    }

    int result = maxFriendsOnTheWay(cache, friendsOnTheBestWay, 0, rows, columns);
    printf("%d\n", result);

    free(friendsOnTheBestWay);
    free(cache);
    return 0;
}

int maxFriendsOnTheWay(int *cache, int *friendsOnTheBestWay, int origin, int rows, int columns)
{
    int rightHasBiggestValue = 0;
    int downHasTheBiggestValue = 0;

    if(cache[origin] == EMPTY_ARRAY)// != empty
    {
        int result = 0; //if origin is -1, so array is empty

        if(origin == rows*columns - 1)
        {
            result = 0; //in this case, origin is in array's final
        }
        else if(origin >= (rows - 1) * columns)
        {
            if(friendsOnTheBestWay[2 * origin] != EMPTY_ARRAY)// != empty == -1
            {
                result = friendsOnTheBestWay[2 * origin] + maxFriendsOnTheWay(cache, friendsOnTheBestWay, origin + 1, rows, columns); //origin + 1 => advance on right
            }
        }
        else if((origin + 1) % columns == 0)
        {
            if(friendsOnTheBestWay[2*origin + 1] != EMPTY_ARRAY)// != empty
            {
                result = friendsOnTheBestWay[2 * origin + 1] + maxFriendsOnTheWay(cache, friendsOnTheBestWay, origin + columns, rows, columns); //origin + columns => jump to the below column
            }
        }
        else
        {
            if(friendsOnTheBestWay[2 * origin] != EMPTY_ARRAY) // != empty
            {
                rightHasBiggestValue = friendsOnTheBestWay[2 * origin] + maxFriendsOnTheWay(cache, friendsOnTheBestWay, origin + 1, rows, columns);
            }
            if(friendsOnTheBestWay[2 * origin + 1] != -1)// != empty
            {
                downHasTheBiggestValue = friendsOnTheBestWay[2 * origin + 1] + maxFriendsOnTheWay(cache, friendsOnTheBestWay, origin + columns, rows, columns);
            }
            
            if(rightHasBiggestValue > downHasTheBiggestValue)
                result = rightHasBiggestValue;
            else
                result = downHasTheBiggestValue;
        }
        cache[origin] = result;
    }
    return cache[origin];
}

static void fillArray(int *array, int array_size)
{
    for(int i = 0; i < array_size; i++)
     {
        array[i] = EMPTY_ARRAY;
     }
}

static int getRange(int rows, int columns)
{
    int range = rows*(columns - 1) + columns*(rows - 1);

    return range;
}