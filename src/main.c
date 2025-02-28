#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define STACK_COUNT 8
#define STACK_HEIGHT 4
#define TRUE 1
#define FALSE 0
#define ERROR -1

int issolvable(int *stack, int stackheights[]);
int* generate_stack();
void print_stack(int* stack);

int main(){
	int* stack;
	int i;
	int is_solvable;
	int stackheights[STACK_COUNT];
	for (i = 0; i < STACK_COUNT; i++)
		stackheights[i] = STACK_HEIGHT;

	srand(time(NULL));
	stack = generate_stack();
	print_stack(stack);

	is_solvable = issolvable(stack, stackheights);
	switch (is_solvable)
	{
	case TRUE:
		printf("The problem is solvable");
		break;
	case FALSE:
		printf("The problem is not solvable");
		break;
	default:
		printf("An error has occurred");
		break;
	}

	return EXIT_SUCCESS;
}

int issolvable(int *stack, int stackheights[]){
	int i, j, ret_val, is_solved = TRUE;
	int own_stackheights[STACK_COUNT];
	if(stack == NULL)
		return ERROR;

	for (i = 0; i < 8; i++){
		if(is_solved == TRUE && stackheights[i] != 0)
			is_solved = FALSE;
		own_stackheights[i] = stackheights[i];
	}

	if(is_solved == TRUE)
		return TRUE;

	for (i = 0; i < STACK_COUNT; i++)
	{
		if(own_stackheights[i] == 0)
			continue;
		for (j = i+1; j < STACK_COUNT; j++)
		{
			if(own_stackheights[j] == 0)
				continue;

			if(stack[(i * STACK_HEIGHT) + own_stackheights[i] - 1] == stack[ (j* STACK_HEIGHT) + own_stackheights[j] - 1]) {
				own_stackheights[i]--;
				own_stackheights[j]--;
				ret_val = issolvable(stack, own_stackheights);
				if(ret_val != FALSE){
					printf("(%i, %i)\n", i,j);
					return ret_val;
				}
				own_stackheights[i]++;
				own_stackheights[j]++;
			}
		}
	}

	return FALSE;
}

int* generate_stack()
{
	int i, j, r;
	int *ret = calloc(STACK_COUNT * STACK_HEIGHT, sizeof(int));
	if(ret == NULL)
		return NULL;

	/*Zeroes are left empty*/
	for (i = 1; i < STACK_COUNT; i++)
	{
		for (j = 0; j < STACK_HEIGHT; j++)
		{
			do
			{
				r = rand() % (STACK_COUNT * STACK_HEIGHT);

			} while (ret[r] != 0);
			ret[r] = i;
		}
	}
	return ret;
}

void print_stack(int* stack)
{
	int i;

	if(stack == NULL)
		return;

	for (i = 0; i < STACK_HEIGHT * STACK_COUNT; i++)
	{
		if((i+1) % STACK_HEIGHT == 0)
			printf("%i\n", stack[i]);
		else
			printf("%i, ", stack[i]);
	}
}