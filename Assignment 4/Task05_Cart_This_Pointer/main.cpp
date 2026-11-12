#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Cart {
    std::string items_[10];
    double prices_[10]{};
    int n_ = 0;
    double discount_ = 0;
public:
    Cart& add(const std::string& item, double price) {
        if (n_ < 10 && price >= 0) { items_[n_] = item; prices_[n_] = price; ++n_; }
        return *this;
    }
    Cart& setDiscount(double discount) {
        if (discount >= 0 && discount <= 100) this->discount_ = discount;
        return *this;
    }
    double total() const {
        double sum = 0;
        for (int i = 0; i < n_; ++i) sum += prices_[i];
        return sum * (100 - discount_) / 100;
    }
    const std::string& item(int index) const { return items_[index]; }
};

int main() {
    // (a) direct object
    Cart direct; direct.add("Milk", 50);
    // (b) pointer with ->
    Cart* ptr = &direct; ptr->add("Bread", 40);
    // (c) reference
    Cart& ref = direct; ref.setDiscount(10);
    // (d) dynamically allocated object, released with delete
    Cart* dynamicCart = new Cart;
    dynamicCart->add("Rice", 60).add("Dal", 120).setDiscount(10);
    std::cout << "Direct/reference cart total: " << direct.total() << '\n';
    std::cout << "Dynamic cart total: " << dynamicCart->total() << '\n';
    delete dynamicCart;

    Cart c;
    c.add("Rice", 60).add("Dal", 120).setDiscount(10);
    Cart* p = &c;
    p->add("Oil", 180);
    std::cout << std::fixed << std::setprecision(2) << "Required chained total: " << p->total() << '\n';

    std::vector<Cart> ownedCarts(3);
    ownedCarts[0].add("A", 10);
    ownedCarts[1].add("B", 20).add("C", 30);
    ownedCarts[2].add("D", 15);
    std::vector<Cart*> cartPointers;
    for (Cart& cart : ownedCarts) cartPointers.push_back(&cart);
    Cart* highest = cartPointers[0];
    for (Cart* current : cartPointers) if (current->total() > highest->total()) highest = current;
    std::cout << "Highest total in pointer array: " << highest->total() << '\n';
}
