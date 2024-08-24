#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int a = 3;
	int b = 5;
	pid_t ppid;

	
	int sum = a + b;
	printf("sum is %d\n", sum);

	ppid = getppid();
	printf("ppid is %u\n", ppid);

	return 0;
}
