#include <stdio.h>
#include <stdlib.h>
#include "endpoints.h"

void updateCakeData(Cake **cakeData, int *cakeCount)
{
   *cakeData = getCakes("cakedata.txt", cakeCount);
}

void displayMenu(Cake *cakeData, int cakeCount)
{
   printf("No. \t| Cake Code \t| Cake name\t\t| Available\t| Price\n");
   printf("---------------------------------------------------------------------------\n");
   for (int i = 0; i < cakeCount; i++)
   {
      printf("%d. \t| %s\t\t| %s\t| %d\t\t| Rp. %d\n", i + 1, cakeData[i].cakeCode, cakeData[i].cakeName, cakeData[i].available, cakeData[i].price);
   }
   printf("---------------------------------------------------------------------------\n");
}

int main()
{
   int cakeCount = 0;

   Cake *cakeData = getCakes("cakedata.txt", &cakeCount);

   int input;
   char cakeCode[5];
   int qty;
   do
   {
      displayMenu(cakeData, cakeCount);

      printf("\n\nMenu :\n1.Sell\n2.Add Stock\n3.Exit\n\nInput :>");
      scanf("%i", &input);

      switch (input)
      {
      case 1:
         printf("Input Cake Code\t>");
         scanf("%s", &cakeCode);
         printf("Input Quantity \t>");
         scanf("%d", &qty);
         getchar();
         printf("\n");
         sellStock(cakeData, cakeCount, cakeCode, qty);
         getchar();
         break;
      case 2:
         printf("Input Cake Code\t>");
         scanf("%s", &cakeCode);
         printf("Input Quantity \t>");
         scanf("%d", &qty);
         getchar();
         printf("\n");
         addStock(cakeData, cakeCount, cakeCode, qty);
         getchar();
         break;
      }
      updateCakeData(&cakeData, &cakeCount);
      system("cls");
   } while (input != 3);

   free(cakeData);
   return 0;
}