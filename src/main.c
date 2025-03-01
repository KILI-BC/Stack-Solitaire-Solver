#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*The stack count also is the number of different face values*/
#define STACK_COUNT 8
/*The stack height also is the number of cards per face value;
 it has to be even for the game to be potentially solvable*/
#define STACK_HEIGHT 4

#define TRUE 1
#define FALSE 0
#define ERROR -1

int run(int print);
int issolvable(int *stack, int stackheights[], int print);
int* generate_stack();
void print_stack(int* stack);

int main(){
	int i, res, success_cnt = 0;
	srand(time(NULL));

	for(i = 0; i < 100; i++){
		res = run(FALSE);

		if(res == ERROR){
			printf("An error has occurred!");
			return EXIT_FAILURE;
		}

		if(res == TRUE)
			success_cnt++;
	}

	printf("Relative solvability frequency: %f", success_cnt / 100.0);
	return EXIT_SUCCESS;
}

int run(int print)
{
	int* stack;
	int i;
	int is_solvable;
	int stackheights[STACK_COUNT];
	/*initialize stackheights*/
	for (i = 0; i < STACK_COUNT; i++)
		stackheights[i] = STACK_HEIGHT;


	stack = generate_stack();
	if(stack == NULL)
		return ERROR;
	if(print){
		printf("Stack:\n");
		print_stack(stack);
		putchar('\n');
	}

	is_solvable = issolvable(stack, stackheights, print);

	if(print == TRUE){
		switch (is_solvable){
		case TRUE:
			printf("\nThe problem is solvable (one solution above)");
			break;
		case FALSE:
			printf("The problem is not solvable");
			break;
		default:
			break;
		}
	}
	return is_solvable;
}


int issolvable(int *stack, int stackheights[], int print){
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
		for (j = (i + 1); j < STACK_COUNT; j++)
		{
			if(own_stackheights[j] == 0)
				continue;

			if(stack[(i * STACK_HEIGHT) + own_stackheights[i] - 1] == stack[ (j* STACK_HEIGHT) + own_stackheights[j] - 1]) {
				own_stackheights[i]--;
				own_stackheights[j]--;
				ret_val = issolvable(stack, own_stackheights, print);
				if(ret_val != FALSE){
					if(print == TRUE)
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

	/*zeroes are left empty;
	  the loop iterates over the face values*/
	for (i = 1; i < STACK_COUNT; i++)
	{
		for (j = 0; j < STACK_HEIGHT; j++)
		{
			/*r is the random position where the face value is saved*/
			do {
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
		if((i + 1) % STACK_HEIGHT == 0)
			printf("%i\n", stack[i]);
		else
			printf("%i, ", stack[i]);
	}
}