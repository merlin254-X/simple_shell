#include <stdio.h>

/**
 * add_numbers - Function to add three numbers
 * @a: The first number
 * @b: The second number
 * @c: The third number
 * This function adds three numbers and returns the sum.
 * Returns: Sum of the three  numbers
 */
int add_numbers(int a, int b, int c)
{
	return (a + b + c);
}

/**
 * main - Entry point
 *
 * This is the entry point of the program.
 * It calls the add_numbers function and prints the result.
 * Returns: Always 0
 */
int main(void)
{
	int num1 = 3;
	int num2 = 5;
	int num3 = 7;
	int sum;

	sum = add_numbers(num1, num2, num3);

	printf("The sum of %d, %d and %d is %d\n", num1, num2, num3, sum);

	return (0);
}
