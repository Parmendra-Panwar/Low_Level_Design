#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// --- Models ---
class Product {
public:
    int sku;
    string name;
    double price;
    Product(int id, string n, double p) : sku(id), name(n), price(p) {}
};

// --- Strategy Pattern for Replenishment ---
class InventoryManager; 
class ReplenishStrategy {
public:
    virtual void replenish(InventoryManager* mgr, int sku) = 0;
    virtual ~ReplenishStrategy() {}
};

class ThresholdStrategy : public ReplenishStrategy {
    int threshold;
public:
    ThresholdStrategy(int t) : threshold(t) {}
    void replenish(InventoryManager* mgr, int sku) override {
        // Logic to trigger restock if stock < threshold
    }
};

// --- Inventory Management (Interface Segregation) ---
class InventoryStore {
public:
    virtual void updateStock(int sku, int qty) = 0;
    virtual int getStock(int sku) = 0;
    virtual ~InventoryStore() {}
};

class InMemInventoryStore : public InventoryStore {
    map<int, int> stock; // SKU -> Quantity
public:
    void updateStock(int sku, int qty) override { stock[sku] += qty; }
    int getStock(int sku) override { return stock.count(sku) ? stock[sku] : 0; }
};

// --- Dark Store (Local Hub) ---
class DarkStore {
public:
    string id;
    double x, y;
    InventoryStore* store;
    ReplenishStrategy* strategy;

    DarkStore(string i, double x_id, double y_id) : id(i), x(x_id), y(y_id) {
        store = new InMemInventoryStore();
    }

    double getDistance(double ux, double uy) {
        return sqrt(pow(x - ux, 2) + pow(y - uy, 2));
    }
};

// --- Singleton Manager for Stores ---
class DarkStoreManager {
    vector<DarkStore*> stores;
    static DarkStoreManager* instance;
    DarkStoreManager() {}

public:
    static DarkStoreManager* getInstance() {
        if (!instance) instance = new DarkStoreManager();
        return instance;
    }

    void addStore(DarkStore* ds) { stores.push_back(ds); }

    vector<DarkStore*> getNearbyStores(double ux, double uy, double maxDist) {
        vector<DarkStore*> nearby;
        for (auto s : stores) {
            if (s->getDistance(ux, uy) <= maxDist) nearby.push_back(s);
        }
        sort(nearby.begin(), nearby.end(), [&](DarkStore* a, DarkStore* b) {
            return a->getDistance(ux, uy) < b->getDistance(ux, uy);
        });
        return nearby;
    }
};
DarkStoreManager* DarkStoreManager::instance = nullptr;

// --- The Core: Order Fulfillment Logic ---
class OrderManager {
public:
    void fulfillOrder(string userName, double ux, double uy, map<int, int> requirements) {
        auto nearbyStores = DarkStoreManager::getInstance()->getNearbyStores(ux, uy, 5.0);
        map<int, int> remaining = requirements;
        
        cout << "Fulfilling order for " << userName << "...\n";

        for (auto* ds : nearbyStores) {
            if (remaining.empty()) break;

            for (auto it = remaining.begin(); it != remaining.end(); ) {
                int sku = it->first;
                int qtyNeeded = it->second;
                int available = ds->store->getStock(sku);

                if (available > 0) {
                    int taken = min(available, qtyNeeded);
                    ds->store->updateStock(sku, -taken);
                    remaining[sku] -= taken;
                    
                    cout << " - Store " << ds->id << " provides SKU " << sku << " x " << taken << "\n";
                    
                    if (remaining[sku] <= 0) it = remaining.erase(it);
                    else ++it;
                } else ++it;
            }
        }

        if (!remaining.empty()) {
            cout << "Order partially unfulfilled for SKUs:\n";
            for (auto const& [sku, qty] : remaining) cout << " SKU " << sku << " Qty " << qty << "\n";
        }
    }
};