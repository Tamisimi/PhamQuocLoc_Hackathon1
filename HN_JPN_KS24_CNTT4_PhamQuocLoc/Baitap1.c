#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Order {
    int id;
    char customer[50];
    int total;
    int status;
}Order;

typedef struct SingleNode {
    Order order;
    struct SingleNode *next;
}SingleNode;

typedef struct DoubleNode {
    Order order;
    struct DoubleNode *next;
    struct DoubleNode *prev;
}DoubleNode;

SingleNode *head = NULL;
DoubleNode *headDouble = NULL;

SingleNode *createSingleNode(Order order) {
    SingleNode *newNode = (SingleNode *)malloc(sizeof(SingleNode));
    newNode->order = order;
    newNode->next = NULL;
    return newNode;
}

DoubleNode *createDoubleNode(Order order) {
    DoubleNode *newNode = (DoubleNode *)malloc(sizeof(DoubleNode));
    newNode->order = order;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

DoubleNode *insertOrder(DoubleNode *head,Order order) {
    DoubleNode *newNode = createDoubleNode(order);
    if (head == NULL) {
        head = newNode;
        return head;
    }
    DoubleNode *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
    return head;
}

void printfOrder(DoubleNode *head) {
    DoubleNode *current = head;
    while (current != NULL) {
        printf("ID: %d\n",current->order.id);
        printf("Customer: %s\n",current->order.customer);
        printf("Total: %d\n",current->order.total);
        printf("Status: %d\n",current->order.status);
        printf("\n");
        current = current->next;
    }

}

DoubleNode* deleteOrder(DoubleNode *head,int id) {
    DoubleNode* current = head;
    if (head == NULL) {
        return NULL;
    }
    while (current != NULL) {
        if (current->order.id == id) {
            if (current-> prev == NULL) {
                head = current->next;
                if (head == NULL) {
                    head -> prev = NULL;
                }
            }else if (current->next == NULL) {
                current->prev->next = NULL;
            }else{
            current -> prev -> next = current->next;
            current -> next -> prev = current->prev;
            }
        }
        free(current);
        printf("Detele Succeed");
        return head;
    }

    return head;
}

DoubleNode* updateOrder(DoubleNode *head,int id) {
    Order order;
    DoubleNode* current = head;
    while (current != NULL) {
        if (current->order.id == id) {
            printf("Enter new customer: ");
            fgets(current->order.customer, 50, stdin);
            fflush(stdin);
            order.customer[strlen(current->order.customer) - 1] = '\0';
            printf("Enter new total: ");
            scanf("%d", &current->order.total);
            printf("Update succeed");
            return head;
        }
        current = current->next;
    }
    return head;
}

DoubleNode sortOrder(DoubleNode *head) {
    DoubleNode *current = head;
    Order order;
    int swapped;

}



int main(){
    int choice;
    do {
        printf("1. Add new order\n");
        printf("2. Printf all order\n");
        printf("3. Delete a order\n");
        printf("4. Update new order\n");
        printf("5. Mark order type\n");
        printf("6. Sort all order\n");
        printf("7. Find a order\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                Order order;
                printf("Enter order id: ");
                scanf("%d", &order.id);
                getchar();
                printf("Enter order customer: ");
                fgets(order.customer, 50, stdin);
                fflush(stdin);
                printf("Enter order total: ");
                scanf("%d", &order.total);
                getchar();
                printf("Enter order status: ");
                scanf("%d", &order.status);
                getchar();
                headDouble = insertOrder(headDouble, order);
                break;
            case 2:
                printfOrder(headDouble);
                break;
            case 3:
                int IdDelete;
                printf("Enter id to detele: ");
                scanf("%d", &IdDelete);
                headDouble = deleteOrder(headDouble, IdDelete);

                break;
            case 4:
                int IdUpdate;
                printf("Enter id to update order: ");
                scanf("%d", &IdUpdate);
                headDouble = updateOrder(headDouble, IdUpdate);
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                printf("Exit\n");
                break;
            default:
                printf("Invalid choice\n");

        };
    }while (choice != 8);
    return 0;
}