#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Order {
    int id;
    char customer[50];
    int total;
    int status; // 0: chưa giao, 1: đã giao
} Order;

typedef struct DoubleNode {
    Order order;
    struct DoubleNode *next;
    struct DoubleNode *prev;
} DoubleNode;

DoubleNode *headDouble = NULL;

// Tạo node mới
DoubleNode *createDoubleNode(Order order) {
    DoubleNode *newNode = (DoubleNode *)malloc(sizeof(DoubleNode));
    newNode->order = order;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Thêm đơn hàng vào cuối danh sách
DoubleNode *insertOrder(DoubleNode *head, Order order) {
    DoubleNode *newNode = createDoubleNode(order);
    if (head == NULL) return newNode;
    DoubleNode *current = head;
    while (current->next != NULL) current = current->next;
    current->next = newNode;
    newNode->prev = current;
    return head;
}

// In toàn bộ đơn hàng
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

// Xóa đơn hàng theo ID
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

// Cập nhật đơn hàng theo ID
DoubleNode* updateOrder(DoubleNode *head, int id) {
    DoubleNode* current = head;
    while (current != NULL) {
        if (current->order.id == id) {
            printf("Enter new customer: ");
            fgets(current->order.customer, 50, stdin);
            current->order.customer[strcspn(current->order.customer, "\n")] = '\0'; // Xoá '\n'

            printf("Enter new total: ");
            scanf("%d", &current->order.total);
            getchar(); // clear buffer

            printf("Update succeeded.\n");
            return head;
        }
        current = current->next;
    }
    printf("Order not found.\n");
    return head;
}

// Đánh dấu đã giao
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

// Sắp xếp theo tổng tiền (tăng dần)
DoubleNode* sortOrdersByTotal(DoubleNode *head) {
    if (head == NULL || head->next == NULL) return head;
    int swapped;
    DoubleNode *ptr1;
    do {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != NULL) {
            if (ptr1->order.total > ptr1->next->order.total) {
                Order temp = ptr1->order;
                ptr1->order = ptr1->next->order;
                ptr1->next->order = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
    } while (swapped);
    printf("Sorted by total.\n");
    return head;
}

// Tìm kiếm đơn hàng theo ID
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

// Main menu
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
        getchar(); // clear buffer

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
                headDouble = sortOrdersByTotal(headDouble);
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
