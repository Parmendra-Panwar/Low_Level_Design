#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// --- 1. Strategy Pattern: Discount Types ---
class DiscountStrategy {
public:
    virtual double applyDiscount(double amount) = 0;
    virtual ~DiscountStrategy() = default;
};

class FlatDiscount : public DiscountStrategy {
    double off;
public:
    FlatDiscount(double amount) : off(amount) {}
    double applyDiscount(double amount) override { return amount - off; }
};

class PercentDiscount : public DiscountStrategy {
    double percent;
public:
    PercentDiscount(double p) : percent(p) {}
    double applyDiscount(double amount) override { return amount * (1 - percent / 100.0); }
};

// --- 2. Chain of Responsibility: Coupon Validators ---
struct Context { double cartAmount; bool isFirstOrder; };

class CouponValidator {
protected:
    shared_ptr<CouponValidator> next;
public:
    void setNext(shared_ptr<CouponValidator> n) { next = n; }
    virtual bool validate(Context& ctx) = 0;
};

class MinAmountValidator : public CouponValidator {
    double minAmount;
public:
    MinAmountValidator(double m) : minAmount(m) {}
    bool validate(Context& ctx) override {
        if (ctx.cartAmount < minAmount) return false;
        return next ? next->validate(ctx) : true;
    }
};

class FirstOrderValidator : public CouponValidator {
public:
    bool validate(Context& ctx) override {
        if (!ctx.isFirstOrder) return false;
        return next ? next->validate(ctx) : true;
    }
};

// --- 3. Coupon Model ---
class Coupon {
public:
    string code;
    unique_ptr<DiscountStrategy> strategy;
    shared_ptr<CouponValidator> chainHead;

    Coupon(string c, unique_ptr<DiscountStrategy> s, shared_ptr<CouponValidator> v) 
        : code(c), strategy(move(s)), chainHead(v) {}
};

// --- 4. Singleton: Coupon Manager ---
class CouponManager {
    vector<shared_ptr<Coupon>> coupons;
    static CouponManager* instance;
    CouponManager() {}

public:
    static CouponManager* getInstance() {
        if (!instance) instance = new CouponManager();
        return instance;
    }

    void addCoupon(shared_ptr<Coupon> c) { coupons.push_back(c); }

    double applyCoupon(string code, Context& ctx) {
        for (auto& c : coupons) {
            if (c->code == code) {
                if (c->chainHead->validate(ctx)) {
                    return c->strategy->applyDiscount(ctx.cartAmount);
                }
            }
        }
        return ctx.cartAmount; // No discount applied
    }
};
CouponManager* CouponManager::instance = nullptr;

// --- Happy Flow ---
int main() {
    // 1. Setup Validators (Chain)
    auto minAmt = make_shared<MinAmountValidator>(500);
    auto firstOrder = make_shared<FirstOrderValidator>();
    minAmt->setNext(firstOrder);

    // 2. Setup Coupon with Strategy
    auto promoCoupon = make_shared<Coupon>(
        "WELCOME100", 
        make_unique<PercentDiscount>(20), // 20% Off
        minAmt
    );

    CouponManager::getInstance()->addCoupon(promoCoupon);

    // 3. User Context (Happy Flow)
    Context userCtx = { 1000.0, true }; // Above 500 and is first order

    double finalPrice = CouponManager::getInstance()->applyCoupon("WELCOME100", userCtx);

    cout << "Original Price: ₹1000\n";
    if (finalPrice < 1000) {
        cout << "Coupon Applied! Final Price: ₹" << finalPrice << endl;
    } else {
        cout << "Coupon Invalid for current cart." << endl;
    }

    return 0;
}