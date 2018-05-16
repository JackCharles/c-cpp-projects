#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "md5.h"

int main(int argc ,char **argv)
{
  char *query;
  char *query_md5;
  int query_len=10;

  query_md5 =(char *)malloc(33);
  if(query_md5 == NULL)
    {
      return -1;
    }
  md5_hash("1234567890",query_len,query_md5);
  printf("%s\n",query_md5);
  printf("dchdushfu");

  return 0;
}

