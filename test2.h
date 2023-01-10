#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ITEM_NAME_LEN 50
#define ITEM_QUANTITY_LEN 20
#define ITEM_FILE "items.txt"

// struct form{
//   int rNum;
//   int qty;
//   char availability[20];
//   char firstName[30];
//   char lastName[30];
//   char username[30];
//   char password[20];
//   char status[10];
//   char roles[10];
// };

void print_menu() {
  printf("\nBorrow and Return System\n");
  printf("1. Borrow item\n");
  printf("2. Return item\n");
  printf("3. View items\n");
  printf("4. Exit\n\n");
}

void borrow_item(struct form *items, int num_items) {
  char name[ITEM_NAME_LEN];
  int quantity;

  printf("Enter item name: ");
  scanf("%s", name);

  for (int i = 0; i < num_items; i++) {
    if (strcmp(name, items[i].firstName) == 0) {
      printf("Enter quantity: ");
      scanf("%d", &quantity);
      if (quantity > items[i].qty) {
        printf("Error: Not enough items in stock.\n");
      } else {
        items[i].qty -= quantity;
        printf("Successfully borrowed %d %s.\n", quantity, name);
      }
      return;
    }
  }

  printf("Error: Item not found.\n");
}

void return_item(struct form *items, int num_items) {
  char name[ITEM_NAME_LEN];
  int quantity;

  printf("Enter item name: ");
  scanf("%s", name);

  for (int i = 0; i < num_items; i++) {
    if (strcmp(name, items[i].firstName) == 0) {
      printf("Enter quantity: ");
      scanf("%d", &quantity);
      items[i].qty += quantity;
      printf("Successfully returned %d %s.\n", quantity, name);
      return;
    }
  }

  printf("Error: Item not found.\n");
}

void view_items(struct form *items, int num_items) {
  printf("\nName\tQuantity\n");
  for (int i = 0; i < num_items; i++) {
    printf("%s\t%d\n", items[i].firstName, items[i].qty);
  }
}

int OUsersPage() {
  struct form *items;
  int num_items = 0;

  // Load items from file
  FILE *fp = fopen(ITEM_FILE, "r");
  if (fp) {
    char name[ITEM_NAME_LEN];
    int quantity;
    while (fscanf(fp, "%s %d", name, &quantity) == 2) {
      num_items++;
      items = realloc(&items, num_items * sizeof(struct form));
    strcpy(items[num_items - 1].firstName, name);
    items[num_items - 1].qty = quantity;
    }
    fclose(fp);
    }

    int choice;
    do {
    print_menu();
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        borrow_item(items, num_items);
        break;
      case 2:
        return_item(items, num_items);
        break;
      case 3:
        view_items(items, num_items);
        break;
      case 4:
        break;
      default:
        printf("Invalid choice.\n");
        break;
    }
    } while (choice != 4);

// Save items to file
fp = fopen(ITEM_FILE, "w");
if (fp) {
for (int i = 0; i < num_items; i++) {
fprintf(fp, "%s %d\n", items[i].firstName, items[i].qty);
}
fclose(fp);
}

free(items);
return 0;
}

