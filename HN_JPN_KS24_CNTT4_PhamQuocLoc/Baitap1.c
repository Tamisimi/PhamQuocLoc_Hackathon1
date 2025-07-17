#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Order {
    int id;
    char customer[50];
    int total;
    int status;
} Order;

typedef struct DoubleNode {
    Order order;
    struct DoubleNode *next;
    struct DoubleNode *prev;
} DoubleNode;

DoubleNode *headDouble = NULL;

DoubleNode *createDoubleNode(Order order) {
    DoubleNode *newNode = (DoubleNode *)malloc(sizeof(DoubleNode));
    newNode->order = order;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

DoubleNode *insertOrder(DoubleNode *head, Order order) {
    DoubleNode *newNode = createDoubleNode(order);
    if (head == NULL) return newNode;
    DoubleNode *current = head;
    while (current->next != NULL) current = current->next;
    current->next = newNode;
    newNode->prev = current;
    return head;
}

void printOrders(DoubleNode *head) {
    DoubleNode *current = head;
    while (current != NULL) {
        printf("ID: %d\n", current->order.id);
        printf("Customer: %s\n", current->order.customer);
        printf("Total: %d\n", current->order.total);
        printf("Status: %s\n", current->order.status == 1 ? "Delivered" : "Not Delivered");
        printf("---------------------\n");
        current = current->next;
    }
}

DoubleNode* deleteOrder(DoubleNode *head, int id) {
    DoubleNode* current = head;
    while (current != NULL) {
        if (current->order.id == id) {
            if (current->prev == NULL) {
                head = current->next;
                if (head != NULL) head->prev = NULL;
            } else if (current->next == NULL) {
                current->prev->next = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            free(current);
            printf("Delete succeeded.\n");
            return head;
        }
        current = current->next;
    }
    printf("Order not found.\n");
    return head;
}

DoubleNode* updateOrder(DoubleNode *head, int id) {
    DoubleNode* current = head;
    while (current != NULL) {
        if (current->order.id == id) {
            printf("Enter new customer: ");
            fgets(current->order.customer, 50, stdin);
            current->order.customer[strcspn(current->order.customer, "\n")] = '\0';

            printf("Enter new total: ");
            scanf("%d", &current->order.total);
            getchar();

            printf("Update succeeded.\n");
            return head;
        }
        current = current->next;
    }
    printf("Order not found.\n");
    return head;
}

DoubleNode* markDelivered(DoubleNode *head, int id) {
    DoubleNode* current = head;
    while (current != NULL) {
        if (current->order.id == id) {
            current->order.status = 1;
            printf("Order marked as delivered.\n");
            return head;
        }
        current = current->next;
    }
    printf("Order not found.\n");
    return head;
}


void findOrder(DoubleNode *head, int id) {
    DoubleNode *current = head;
    while (current != NULL) {
        if (current->order.id == id) {
            printf("Order found:\n");
            printf("ID: %d\n", current->order.id);
            printf("Customer: %s\n", current->order.customer);
            printf("Total: %d\n", current->order.total);
            printf("Status: %s\n", current->order.status == 1 ? "Delivered" : "Not Delivered");
            return;
        }
        current = current->next;
    }
    printf("Order not found.\n");
}

int main() {
    int choice;
    do {
        printf("\n—————— ORDER MANAGER ——————\n");
        printf("1. Add new order\n");
        printf("2. Print all orders\n");
        printf("3. Delete an order\n");
        printf("4. Update an order\n");
        printf("5. Mark order as delivered\n");
        printf("6. Sort orders by total\n");
        printf("7. Find an order by ID\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                Order order;
                printf("Enter order id: ");
                scanf("%d", &order.id);
                getchar();
                printf("Enter customer name: ");
                fgets(order.customer, 50, stdin);
                order.customer[strcspn(order.customer, "\n")] = '\0';
                printf("Enter total: ");
                scanf("%d", &order.total);
                printf("Enter status (0=Not Delivered, 1=Delivered): ");
                scanf("%d", &order.status);
                getchar();
                headDouble = insertOrder(headDouble, order);
                break;
            }
            case 2:
                printOrders(headDouble);
                break;
            case 3: {
                int id;
                printf("Enter order ID to delete: ");
                scanf("%d", &id);
                headDouble = deleteOrder(headDouble, id);
                break;
            }
            case 4: {
                int id;
                printf("Enter order ID to update: ");
                scanf("%d", &id);
                getchar();
                headDouble = updateOrder(headDouble, id);
                break;
            }
            case 5: {
                int id;
                printf("Enter order ID to mark as delivered: ");
                scanf("%d", &id);
                headDouble = markDelivered(headDouble, id);
                break;
            }
            case 6:
                break;
            case 7: {
                int id;
                printf("Enter order ID to find: ");
                scanf("%d", &id);
                findOrder(headDouble, id);
                break;
            }
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 8);

    return 0;
}
