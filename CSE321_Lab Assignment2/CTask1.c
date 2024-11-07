#include <stdio.h>

struct Item {
    int quantity;
    float unit_price;
};

int main() {
    struct Item paratha, vegetable, water;
    int num_people;
    float total_bill, individual_payment;
    
    printf("Quantity of Paratha: ");
    scanf("%d", &paratha.quantity);
    printf("Unit price of Paratha: ");
    scanf("%f", &paratha.unit_price);
    printf("Quantity of Vegetables: ");
    scanf("%d", &vegetable.quantity);
    printf("Unit price of Vegetables: ");
    scanf("%f", &vegetable.unit_price);
    printf("Quantity of Mineral Water: ");
    scanf("%d", &water.quantity);
    printf("Unit price of Mineral Water: ");
    scanf("%f", &water.unit_price);

    total_bill = (paratha.quantity * paratha.unit_price) + (vegetable.quantity * vegetable.unit_price) + (water.quantity * water.unit_price);
    printf("Enter the number of people: ");
    scanf("%d", &num_people);
    individual_payment = total_bill / num_people;
    printf("Each person will pay: %.2f tk\n", individual_payment);

    return 0;
}
