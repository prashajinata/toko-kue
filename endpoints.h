#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Cake
{
  int id;
  char cakeCode[5];
  char *cakeName;
  int available;
  int price;
} Cake;

void sellStock(Cake *cakes, int count, char *cakeCode, int quantity)
{
  int flag = 0;
  int onStock = 0;
  int price = 0;

  for (int i = 0; i < count; i++)
  {
    if (strcmp(cakeCode, cakes[i].cakeCode) == 0)
    {
      flag = 1;
      if (cakes[i].available >= quantity)
      {
        onStock = 1;
        cakes[i].available -= quantity;
        price = cakes[i].price;
        break;
      }
    }
  }

  if(onStock == 0) {
    printf("Not Enough Stock");
    return;
  }

  if (flag == 0)
  {
    printf("Invalid Code");
    return;
  }

  FILE *fp = fopen("cakedata.txt", "w");
  if (fp == NULL)
  {
    printf("Error: cannot open file %s\n", "cakedata.txt");
    return;
  }

  for (int i = 0; i < count; i++)
  {
    fprintf(fp, "%d|%s|%s|%d|%d\n", cakes[i].id, cakes[i].cakeCode, cakes[i].cakeName, cakes[i].available, cakes[i].price);
  }

  printf("\n\nSuccess!\n\nTotal : Rp.%.3f", price * quantity);

  fclose(fp);
}

void addStock(Cake *cakes, int count, char *cakeCode, int quantity)
{

  int flag = 0;
  for (int i = 0; i < count; i++)
  {
    if (strcmp(cakeCode, cakes[i].cakeCode) == 0)
    {
      flag = 1;
      cakes[i].available += quantity;
      break;
    }
  }

  if (flag == 0)
  {
    printf("Invalid Code");
    return;
  }

  FILE *fp = fopen("cakedata.txt", "w");
  if (fp == NULL)
  {
    printf("Error: cannot open file %s\n", "cakedata.txt");
    return;
  }

  for (int i = 0; i < count; i++)
  {
    fprintf(fp, "%d|%s|%s|%d|%d\n", cakes[i].id, cakes[i].cakeCode, cakes[i].cakeName, cakes[i].available, cakes[i].price);
  }
  printf("Success!");

  fclose(fp);
}

Cake *getCakes(char *filename, int *count)
{
  char line[300];

  FILE *fp;
  fp = fopen(filename, "r");

  if (fp == NULL)
  {
    printf("Cannot Open File\n");
  }

  int cakeCount = 0;

  while (fgets(line, sizeof(line), fp))
    cakeCount++;

  rewind(fp);

  Cake *cakes = (Cake *)malloc(cakeCount * sizeof(Cake));

  *count = cakeCount;

  char *token;
  int id;
  char *cakeCode;
  char *cakeName;
  int available;
  int price;

  for (int i = 0; i < cakeCount; i++)
  {
    if (fgets(line, sizeof(line), fp))
    {
      token = strtok(line, "|");
      cakes[i].id = atoi(token);

      token = strtok(NULL, "|");
      if (token != NULL)
      {
        strcpy(cakes[i].cakeCode, token);
        cakes[i].cakeCode[strlen(token)] = '\0';
      }
      else
      {
        cakes[i].cakeCode[5] = '\0';
      }

      token = strtok(NULL, "|");
      if (token != NULL)
      {
        cakes[i].cakeName = (char *)malloc(strlen(token) + 1);
        strcpy(cakes[i].cakeName, token);
        cakes[i].cakeName[strlen(token)] = '\0';
      }
      else
      {
        cakes[i].cakeName[279] = '\0';
      }

      token = strtok(NULL, "|");
      cakes[i].available = atoi(token);

      token = strtok(NULL, "|");
      cakes[i].price = atoi(token);
    }
  }
  fclose(fp);
  return cakes;
}