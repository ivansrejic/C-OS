#include <stdio.h>
#include <stdlib.h>
int main(int argc, char * argv[])
{
  int i;
  /*U petlji se stampaju svi ulazni argumenti programa*/
  for (i = 0; i < argc; i++)
    printf("argv[%d] = %s\n", i, argv[i]);
  return 0;
}
