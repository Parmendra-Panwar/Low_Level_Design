#include <vector>
#include <iostream>

using namespace std;

class Product{
    public:
    string name;
    string category;
    double price;
};

class CartItem{
    public:
    Product* p;
    int q; //quentity
    CartItem(Product* p, int q){
        this->p = p;
        this->q = q;
    }

    double getTotal(){
        return p->price*q;
    };
};

class Cart{
    public:
    vector<CartItem*> items;
    bool loyalityMem;
    double initPrice;
    double finalPrice;

    void addProduct(Product* p, int q = 1){
        items.push_back(new CartItem(p, q));
    }
    void applyDisc(double disAmount){
        finalPrice -= disAmount;
        if(finalPrice < 0) finalPrice = 0;
    }
};

class DiscountStrategy{
    public:
    double calculate(double amt){};
};

class FlatDisStrategy : public DiscountStrategy{
    public:
    double amt;
    FlatDisStrategy(double amt){
        this->amt = amt;
    }
    double calculate(double d){
        return min(d, amt);
    }
};

class ParcentDisStrategy : public DiscountStrategy{
    public:
    double amt;
    ParcentDisStrategy(double amt){
        this->amt = amt;
    }
    double calculate(double d){
        return (d*amt)/100;
    }
};

class ParcentWithCapDisStrategy : public DiscountStrategy{
    public:
    double percent;
    double amt;
    ParcentWithCapDisStrategy(double percent,double amt){
        this->amt = amt;
        this->percent = percent;
    }
    double calculate(double d){
        return ((d*percent)/100 > amt) ? amt : (d*percent)/100 > amt;
    }
};

enum SType{
    FLAT, 
    PER,
    PERWITHCAP
};

class DisStrategyManager{
    private:
    static DisStrategyManager* instance;
    DisStrategyManager() {}
    DisStrategyManager(const DisStrategyManager&) = delete;
    DisStrategyManager& operator=(const DisStrategyManager&) = delete;
    public:
    static DisStrategyManager* getInstance(){
        if (!instance) {
            instance = new DisStrategyManager();
        }
        return instance;
    }
    DiscountStrategy* getStragey(SType t, int amt, int precent = 1){
        if(t == SType::FLAT){
            return new FlatDisStrategy(amt);
        }
        if(t == SType::PER){
            return new ParcentDisStrategy(amt);
        }
        if(t == SType::PERWITHCAP){
            return new ParcentWithCapDisStrategy(precent, amt);
        }

        return nullptr;
    }
};

DisStrategyManager* DisStrategyManager::instance = nullptr; 

class Coupon{
    public:
    Coupon* next;
    
};

int main(){


    return 0;
}