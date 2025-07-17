#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int choice;
    do {
        printf("1. Add new order\n");
        printf("2. Printf all order\n");
        printf("3. Delete a order\n");
        printf("4. Update new order\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                break;
            case 2:
               break;
            case 3:
                break;
            case 4:

                break;
            case 5:
                printf("Exit\n");
                break;
            default:
                printf("Invalid choice\n");

        };
    }while (choice != 8);
    return 0;
}