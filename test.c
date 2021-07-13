#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
char **sortStrings(char **arr, int n)
{
    char *temp;
  
    // Sorting strings using bubble sort
    for (int j=0; j<n-1; j++)
    {
        for (int i=j+1; i<n; i++)
        {
            if (strcmp(arr[j], arr[i]) > 0)
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
	return (arr);
}

int main()
{
	char **car = calloc(4, sizeof(char *));
	car[0] = strdup("ZZZZ");
	car[1] = strdup("CCCC");
	car[2] = strdup("BBBB");
	car[3] = strdup("AAAA");
	char **arr = sortStrings(car, 4);
	int i = 0;
	while(arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}