#include <stdio.h>
#include <string.h>

const char* itemName(int choice) {
    switch (choice) {
        case 1: return "Bread";
        case 2: return "Milk";
        case 3: return "Eggs";
        case 4: return "Rice";
        case 5: return "Hand Wash";
        case 6: return "Shampoo";
        default: return "Invalid Item";
    }
}

typedef struct Product {
    char name[20];
    float price;
    int quantity;
} Product;

typedef struct Customer {
    char name[50];
    int mobile;
    float total;
    char payment_mode[25];
    Product items[100];
    int item_count;
} Cu;

void saveCustomer(int *index, char name[], int number, int payment, Cu pe[]) {
    if (*index < 500) {
        for (int i = 0; i < 500; i++) {
            if (strcmp(name, pe[i].name) == 0) {
                printf("This Username Already Not Available\n");
                return;
            }
        }

        strcpy(pe[*index].name, name);
        pe[*index].mobile = number;
        pe[*index].total = 0.0;

        switch (payment) {
            case 1:
                strcpy(pe[*index].payment_mode, "Online");
                break;
            case 2:
                strcpy(pe[*index].payment_mode, "Card");
                break;
            case 3:
                strcpy(pe[*index].payment_mode, "Cash");
                break;
            case 4:
                strcpy(pe[*index].payment_mode, "Gift Cards/Vouchers");
                break;
            default:
                printf("Wrong Payment Method Selected\n");
                return;
        }

        pe[*index].item_count = 0;
        printf("The User Created Successfully\n");
        (*index)++;
    }
}

void productListSave(char new_name[], int n, Cu pe[]) {
    for (int i = 0; i < 500; i++) {
        if (strcmp(pe[i].name, new_name) == 0) {
            for (int j = 0; j < pe[i].item_count; j++) {
                if (strcmp(pe[i].items[j].name, itemName(n)) == 0) {
                    pe[i].items[j].quantity++;
                    printf("Quantity updated in the cart.\n");
                    return;
                }
            }

            strcpy(pe[i].items[pe[i].item_count].name, itemName(n));
            pe[i].items[pe[i].item_count].quantity = 1;
            pe[i].items[pe[i].item_count].price = 100.00;
            pe[i].item_count++;

            printf("Item added to the cart.\n");
            return;
        }
    }
    printf("User not found.\n");
}

void productListShow(char new_name[], Cu pe[]) {
    for (int i = 0; i < 500; i++) {
        if (strcmp(new_name, pe[i].name) == 0) {
            printf("\n");
            printf("===== Your Products =====\n");
            printf("Item\t\tQuantity\tPrice\n");
            printf("--------------------------\n");

            float total = 0.0;
            float gst = 0.0;  

            pe[i].total = 0.0;

            for (int j = 0; j < pe[i].item_count; j++) {
                printf("%-15s\t%-8d\t%.2f\n", pe[i].items[j].name, pe[i].items[j].quantity, pe[i].items[j].price);
                total += pe[i].items[j].quantity * pe[i].items[j].price;
            }

            gst = (total) * 0.18;
            pe[i].total = total + gst;

            printf("\n--------------------------\n");
            printf("GST\t\t\t\t18%%\n");
            printf("Total\t\t\t\t%.2f\n", pe[i].total);
            printf("==========================\n");
            return;
        }
    }
    printf("User not found.\n");
}

void customerInfo(char new_name[], Cu pe[]) {
    for (int i = 0; i < 500; i++) {
        if (strcmp(pe[i].name, new_name) == 0) {
            printf("\n");
            printf("===== Customer Details =====\n");
            printf("Customer Name:           %s\n", pe[i].name);
            printf("Customer Mobile Number:  %d\n", pe[i].mobile);
            printf("Customer Payment Mode:   %s\n", pe[i].payment_mode);
            printf("Customer Total:          %.2f\n", pe[i].total);
            printf("Customer Items:\n");

            for (int j = 0; j < pe[i].item_count; j++) {
                printf("   %-15s\t%-8d\t%.2f\n", pe[i].items[j].name, pe[i].items[j].quantity, pe[i].items[j].price);
            }
            return;
        }
        }
}



int main() {
    int index = 0;
    char new_name[50];
    int mobile;
    int payment;
    int op;
    int op2;

    Cu pe[500];

    do {
        printf("\n    Billing System\n");
        printf("1. Add To Cart\n");
        printf("2. Customer Details\n");
        printf("3. Exit\n");

        printf("Enter your choice (1-3): ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("Enter Customer Name: ");
                scanf("%49s", new_name);
                printf("Enter Mobile Number: ");
                scanf("%d", &mobile);
                printf("\n");
                printf("Choose The Payment Mode ->\n");
                printf("1 - Online\n");
                printf("2 - Card\n");
                printf("3 - Cash\n");
                printf("4 - Gift Cards/Vouchers\n");
                printf("Enter The Mode : ");
                scanf("%d", &payment);
                saveCustomer(&index, new_name, mobile, payment, pe);

                do {
                    printf("\nAdd Item To Cart\n");
                    printf("1 -> Bread\n");
                    printf("2 -> Milk\n");
                    printf("3 -> Eggs\n");
                    printf("4 -> Rice\n");
                    printf("5 -> Hand Wash\n");
                    printf("6 -> Shampoo\n");
                    printf("\n");
                    printf("7 -> DONE\n");
                    printf("Enter your choice: ");
                    scanf("%d", &op2);

                    if (op2 >= 1 && op2 <= 6) {
                        productListSave(new_name, op2, pe);
                        productListShow(new_name, pe);
                    } else if (op2 != 7) {
                        printf("Invalid choice.\n");
                    }

                } while (op2 != 7);

                break;

            case 2:
            printf("Enter The Name : ");
            scanf("%s",new_name);
            customerInfo(new_name, pe);

            break;    

            default:
            printf("Wrong Opction Selectet\n");
                break;
        }

    } while (op != 3);

    return 0;
}
