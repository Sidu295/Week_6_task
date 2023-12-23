#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>    

using namespace std;

// Function prototypes
bool checkSingleSack(string& contents, double& weight);
void checkCustomerOrder(int& cementCount, int& gravelCount, int& sandCount);
double calculateOrderPrice(int cementCount, int gravelCount, int sandCount);

int main() {
    // Task 1 - Check the contents and weight of a single sack
    string sackContents;
    double sackWeight;

    if (checkSingleSack(sackContents, sackWeight)) {
        cout << "Accepted Sack: Contents - " << sackContents << ", Weight - " << fixed << setprecision(2) << sackWeight << " kg\n\n";

        // Task 2 - Check a customer’s order for delivery
        int cementCount = 0, gravelCount = 0, sandCount = 0;
        checkCustomerOrder(cementCount, gravelCount, sandCount);

        // Task 3 - Calculate the price for a customer’s order
        double totalPrice = calculateOrderPrice(cementCount, gravelCount, sandCount);
        cout << "\nTotal Order Price: $" << totalPrice << endl;
    }

    return 0;
}

bool checkSingleSack(string& contents, double& weight) {
    cout << "Enter the contents of sack (C for Cement, G for Gravel, S for Sand): ";
    cin >> contents;

    transform(contents.begin(), contents.end(), contents.begin(), ::toupper);

    if (contents != "C" && contents != "G" && contents != "S") {
        cout << "Rejected: Invalid contents\n";
        return false;
    }

    cout << "Enter the weight of sack between([C>24.9kg<25.1kg] [S,G>49.9kg<50.1kg]): ";
    cin >> weight;

    if (cin.fail() || (contents == "C" && (weight < 24.9 || weight > 25.1)) ||
        ((contents == "G" || contents == "S") && (weight < 49.9 || weight > 50.1))) {
        cout << "Rejected: Invalid weight\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    return true;
}

void checkCustomerOrder(int& cementCount, int& gravelCount, int& sandCount) {
   
    int orderSize;

    cout << "Enter the number of sacks in the order: ";
    cin >> orderSize;

    if (orderSize < 0) {
        cout << "Invalid order size. Please enter a non-negative value.\n";
        // You might want to handle this case appropriately, possibly by asking for input again.
        return;
    }

    for (int i = 0; i < orderSize; ++i) {
        string contents;
        double weight;

        cout << "\nSack " << i + 1 << ":\n";
        if (checkSingleSack(contents, weight)) {
            if (contents == "C") {
                cementCount++;
            } else if (contents == "G") {
                gravelCount++;
            } else if (contents == "S") {
                sandCount++;
            }
        }
    }

    cout << "\nTotal Weight of the Order: " << fixed << setprecision(2) << (cementCount * 25 + gravelCount * 50 + sandCount * 50) << " kg\n";
}

double calculateOrderPrice(int cementCount, int gravelCount, int sandCount) {
    const double CEMENT_PRICE = 3.0;
    const double GRAVEL_PRICE = 2.0;
    const double SAND_PRICE = 2.0;
    const double DISCOUNT_PRICE = 10.0;

    double totalPrice = cementCount * CEMENT_PRICE + gravelCount * GRAVEL_PRICE + sandCount * SAND_PRICE;

    int specialPacks = min({cementCount, sandCount / 2, gravelCount / 2});

    if (specialPacks > 0) {
        totalPrice -= specialPacks * (CEMENT_PRICE + 2 * SAND_PRICE + 2 * GRAVEL_PRICE - DISCOUNT_PRICE);
        cout << "Discount Applied: $" << DISCOUNT_PRICE << " per special pack\n";
        cout << "Amount Saved: $" << specialPacks * DISCOUNT_PRICE << endl;
    }

    return totalPrice;
}
