
#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 10
#define MAX_SALES 20

struct Date {
    int day, month, year;
};

enum ItemType {
    PACKAGED,
    COOKED,
    COMBO
};

struct Item {
    int id;
    char name[30];
    int stock;
    float price;
    enum ItemType type;

    union {
        struct Date expiry;
        char preparedTime[10];
        int components[3];
    } detail;
};

struct Sale {
    int id;
    int quantity;
    float revenue;
};

int findItem(struct Item items[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (items[i].id == id)
            return i;
    }
    return -1;
}

void recordSale(struct Item items[], int n,
                struct Sale sales[], int *count,
                int id, int quantity) {

    int index = findItem(items, n, id);

    if (index == -1) {
        printf("Item not found\n");
        return;
    }

    if (quantity <= 0 || items[index].stock < quantity) {
        printf("Insufficient stock for %s\n",
               items[index].name);
        return;
    }

    items[index].stock -= quantity;

    sales[*count].id = id;
    sales[*count].quantity = quantity;
    sales[*count].revenue =
        items[index].price * quantity;

    (*count)++;

    printf("Sale recorded: %s x %d = Rs. %.2f\n",
           items[index].name,
           quantity,
           items[index].price * quantity);
}

void expiryWarning(struct Item items[], int n,
                   struct Date today) {
    for (int i = 0; i < n; i++) {
        if (items[i].type == PACKAGED) {
            int days =
                (items[i].detail.expiry.year - today.year) * 365 +
                (items[i].detail.expiry.month - today.month) * 30 +
                items[i].detail.expiry.day - today.day;

            if (days >= 0 && days <= 2) {
                printf("Expiry Warning: %s\n",
                       items[i].name);
            }
        }
    }
}

void revenueSummary(struct Item items[], int n,
                    struct Sale sales[], int count) {
    float revenue[MAX_ITEMS] = {0};

    for (int i = 0; i < count; i++) {
        int index = findItem(items, n, sales[i].id);

        if (index != -1)
            revenue[index] += sales[i].revenue;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (revenue[j] > revenue[i]) {
                float temp = revenue[i];
                revenue[i] = revenue[j];
                revenue[j] = temp;

                struct Item tempItem = items[i];
                items[i] = items[j];
                items[j] = tempItem;
            }
        }
    }

    printf("\nRevenue Summary:\n");

    for (int i = 0; i < n; i++) {
        if (revenue[i] > 0) {
            printf("%s: Rs. %.2f\n",
                   items[i].name, revenue[i]);
        }
    }
}

int main(void) {
    struct Item items[3] = {
        {1, "Milk", 10, 30, PACKAGED,
            {.expiry = {20, 11, 2026}}},

        {2, "Sandwich", 8, 50, COOKED,
            {.preparedTime = "09:30"}},

        {3, "Combo Meal", 5, 100, COMBO,
            {.components = {1, 2, 0}}}
    };

    struct Sale sales[MAX_SALES];
    int count = 0;

    struct Date today = {19, 11, 2026};

    recordSale(items, 3, sales, &count, 1, 2);
    recordSale(items, 3, sales, &count, 2, 20);
    recordSale(items, 3, sales, &count, 3, 1);

    expiryWarning(items, 3, today);

    revenueSummary(items, 3, sales, count);

    return 0;
}
