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

