#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Customer {
    int customerID;
    char customerName[100];
    char productName[100];
    int productNumber;
    int productQuality;
    int productRating;
    int serviceRating;
    char suggestions[200];
};

double calculateOverallRating(int productRating, int serviceRating) {
    return (double)(productRating + serviceRating) / 2.0;
}

int main() {
    FILE *file;
    struct Customer customer;

    char continueAdding;
    int numCustomers = 0;

    file = fopen("customer_data.txt", "a"); // Open the file for appending

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    do {
        int id, quality, prodRating, servRating, prodNumber;
        char name[100], product[100], suggestions[200];

        printf("Enter customer ID: ");
        scanf("%d", &id);

        printf("Enter customer name: ");
        getchar(); // Clear the newline character from the previous input
        fgets(name, sizeof(name), stdin);
        name[strlen(name) - 1] = '\0'; // Remove the newline character

        printf("Enter product name: ");
        fgets(product, sizeof(product), stdin);
        product[strlen(product) - 1] = '\0'; // Remove the newline character

        printf("Enter product number: ");
        scanf("%d", &prodNumber);

        printf("Enter product quality (1 to 5): ");
        scanf("%d", &quality);

        printf("Enter product rating (1 to 5): ");
        scanf("%d", &prodRating);

        printf("Enter service rating (1 to 5): ");
        scanf("%d", &servRating);

        printf("Enter customer suggestions: ");
        getchar(); // Clear the newline character from the previous input
        fgets(suggestions, sizeof(suggestions), stdin);
        suggestions[strlen(suggestions) - 1] = '\0'; // Remove the newline character

        // Validate ratings
        if (quality < 1 || quality > 5 || prodRating < 1 || prodRating > 5 || servRating < 1 || servRating > 5) {
            printf("Invalid ratings. Please enter ratings between 1 and 5.\n");
        } else {
            customer.customerID = id;
            strcpy(customer.customerName, name);
            strcpy(customer.productName, product);
            customer.productNumber = prodNumber;
            customer.productQuality = quality;
            customer.productRating = prodRating;
            customer.serviceRating = servRating;
            strcpy(customer.suggestions, suggestions);

            fwrite(&customer, sizeof(struct Customer), 1, file);

            numCustomers++;

            printf("Do you want to continue adding customers? (y/n): ");
            scanf(" %c", &continueAdding);
        }

    } while (continueAdding == 'y' || continueAdding == 'Y');

    fclose(file); // Close the file

    // Display customer data and overall ratings from the file
    file = fopen("customer_data.txt", "r"); // Open the file for reading

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    printf("\nCustomer Data:\n");

    while (fread(&customer, sizeof(struct Customer), 1, file) == 1) {
        printf("Customer ID: %d\n", customer.customerID);
        printf("Customer Name: %s\n", customer.customerName);
        printf("Product Name: %s\n", customer.productName);
        printf("Product Number: %d\n", customer.productNumber);
        printf("Product Quality: %d\n", customer.productQuality);
        printf("Product Rating: %d\n", customer.productRating);
        printf("Service Rating: %d\n", customer.serviceRating);
        printf("Suggestions: %s\n", customer.suggestions);
        printf("Overall Rating: %.2lf\n", calculateOverallRating(customer.productRating, customer.serviceRating));
        printf("\n");
    }

    fclose(file); // Close the file

    return 0;
}

