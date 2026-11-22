#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <limits>
using namespace std;

struct TruckRecord {
    int id;
    char name[40];
    char location[40];
    char menu[40];
    float price;
    char status;
};

void copyText(char dest[], const string &src, int size) {
    int i = 0;
    while (i < size - 1 && i < (int)src.size()) { dest[i] = src[i]; i++; }
    dest[i] = '\0';
}

class FoodTruck {
protected:
    int id;
    string name, location, menu;
    float price;
    char status;
    static int cnt;
public:
    FoodTruck() : id(0), price(0), status('C') {}
    FoodTruck(int i, string n, string l, string m, float p, char s)
        : id(i), name(n), location(l), menu(m), price(p), status(s) {}
    FoodTruck(const FoodTruck &obj)
        : id(obj.id), name(obj.name), location(obj.location), menu(obj.menu),
          price(obj.price), status(obj.status) {}
    virtual ~FoodTruck() {}
    virtual void display() const {
        cout << "ID: " << id << "\nName: " << name << "\nLocation: " << location
             << "\nMenu: " << menu << "\nPrice: " << price
             << "\nStatus: " << status << '\n';
    }
    int getId() const { return id; }
    static int getCount() { return cnt; }
    static void setCount(int n) { cnt = n; }
    operator int() const { return id; } // Type conversion: FoodTruck to ID
    bool operator==(const FoodTruck &other) const { return id == other.id; }
    bool operator<(const FoodTruck &other) const { return price < other.price; }
    FoodTruck operator+(float extra) const {
        FoodTruck result(*this);
        if (extra >= 0) result.price += extra;
        return result;
    }
    friend ostream &operator<<(ostream &out, const FoodTruck &t) {
        out << "ID: " << t.id << ", Name: " << t.name << ", Location: " << t.location
            << ", Menu: " << t.menu << ", Price: " << t.price << ", Status: " << t.status;
        return out;
    }
    friend istream &operator>>(istream &in, FoodTruck &t) {
        cout << "Enter Truck ID: "; in >> t.id;
        if (!in) return in;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Truck Name: "; getline(in, t.name);
        cout << "Enter Location: "; getline(in, t.location);
        cout << "Enter Menu Item: "; getline(in, t.menu);
        cout << "Enter Price: "; in >> t.price;
        if (!in) return in;
        cout << "Enter Status (A/C): "; in >> t.status;
        return in;
    }
    bool valid() const {
        return id > 0 && !name.empty() && !location.empty() && !menu.empty()
            && name.size() < 40 && location.size() < 40 && menu.size() < 40
            && price >= 0 && price <= 1000000 && (status == 'A' || status == 'C');
    }
    TruckRecord toRecord() const {
        TruckRecord r = {};
        r.id = id;
        copyText(r.name, name, 40); copyText(r.location, location, 40);
        copyText(r.menu, menu, 40); r.price = price; r.status = status;
        return r;
    }
    void setFromRecord(const TruckRecord &r) {
        id = r.id;
        name = string(r.name, strnlenSafe(r.name, 40));
        location = string(r.location, strnlenSafe(r.location, 40));
        menu = string(r.menu, strnlenSafe(r.menu, 40));
        price = r.price; status = r.status;
    }
    static int strnlenSafe(const char *s, int maxlen) {
        int n = 0; while (n < maxlen && s[n]) n++; return n;
    }
};
int FoodTruck::cnt = 0;

class VegTruck : public FoodTruck {
public:
    VegTruck(const FoodTruck &t) : FoodTruck(t) {}
    void display() const override { cout << "[Vegetarian truck]\n"; FoodTruck::display(); }
};
class NonVegTruck : public FoodTruck {
public:
    NonVegTruck(const FoodTruck &t) : FoodTruck(t) {}
    void display() const override { cout << "[Non-vegetarian truck]\n"; FoodTruck::display(); }
};

const char *DATA_FILE = "foodtruck.dat";
int countRecords() {
    ifstream f(DATA_FILE, ios::binary);
    TruckRecord r; int n = 0;
    while (f.read(reinterpret_cast<char *>(&r), sizeof(r))) n++;
    return n;
}
int searchRecord(int id, FoodTruck &truck, streamoff &position) {
    ifstream f(DATA_FILE, ios::binary);
    if (!f) return 0;
    TruckRecord r;
    f.seekg(0, ios::beg);
    while (true) {
        streampos p = f.tellg();
        if (!f.read(reinterpret_cast<char *>(&r), sizeof(r))) break;
        if (r.id == id) {
            position = static_cast<streamoff>(p);
            truck.setFromRecord(r);
            return 1;
        }
    }
    return 0;
}
void resetInput() {
    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void addRecord() {
    FoodTruck *t = new FoodTruck;
    cin >> *t;
    if (!cin) { cout << "Invalid numeric input.\n"; resetInput(); delete t; return; }
    if (!t->valid()) { cout << "Invalid details. Record not saved.\n"; delete t; return; }
    FoodTruck existing; streamoff pos = 0;
    if (searchRecord(t->getId(), existing, pos)) {
        cout << "Duplicate ID. Record not added.\n"; delete t; return;
    }
    ofstream f(DATA_FILE, ios::binary | ios::app);
    TruckRecord r = t->toRecord();
    if (f.write(reinterpret_cast<const char *>(&r), sizeof(r))) {
        cout << "Record saved successfully.\n";
    } else cout << "File write failed.\n";
    f.close(); FoodTruck::setCount(countRecords()); delete t;
}
void displayAll() {
    ifstream f(DATA_FILE, ios::binary);
    TruckRecord r; int n = 0;
    while (f.read(reinterpret_cast<char *>(&r), sizeof(r))) {
        FoodTruck t; t.setFromRecord(r); cout << t << "\n--------------------\n"; n++;
    }
    if (n == 0) cout << "No records available.\n";
    FoodTruck::setCount(n);
}
void searchMenu() {
    int id; cout << "Enter Truck ID to search: ";
    if (!(cin >> id)) { cout << "Invalid ID.\n"; resetInput(); return; }
    FoodTruck t; streamoff pos = 0;
    if (searchRecord(id, t, pos)) t.display();
    else cout << "Record not found.\n";
}
void updateRecord() {
    int id; cout << "Enter Truck ID to update: ";
    if (!(cin >> id)) { cout << "Invalid ID.\n"; resetInput(); return; }
    FoodTruck old; streamoff pos = 0;
    if (!searchRecord(id, old, pos)) { cout << "Record not found.\n"; return; }
    cout << "Current record:\n" << old << "\nConfirm update (Y/N): ";
    char yes; cin >> yes;
    if (yes != 'Y' && yes != 'y') { cout << "Update cancelled.\n"; return; }
    FoodTruck replacement;
    cout << "Enter replacement details (same ID required):\n";
    cin >> replacement;
    if (!cin) { cout << "Invalid numeric input.\n"; resetInput(); return; }
    if (!replacement.valid() || replacement.getId() != id) {
        cout << "Invalid details or changed ID. Update cancelled.\n"; return;
    }
    fstream f(DATA_FILE, ios::in | ios::out | ios::binary);
    if (!f) { cout << "Unable to open file.\n"; return; }
    TruckRecord r = replacement.toRecord();
    f.seekp(pos, ios::beg);
    if (f.write(reinterpret_cast<const char *>(&r), sizeof(r)))
        cout << "Record updated successfully.\n";
    else cout << "Update failed.\n";
}
void deleteRecord() {
    int id; cout << "Enter Truck ID to delete: ";
    if (!(cin >> id)) { cout << "Invalid ID.\n"; resetInput(); return; }
    FoodTruck target; streamoff pos = 0;
    if (!searchRecord(id, target, pos)) { cout << "Record not found.\n"; return; }
    cout << "Record to delete:\n" << target << "\nConfirm DELETE (Y/N): ";
    char yes; cin >> yes;
    if (yes != 'Y' && yes != 'y') { cout << "Delete cancelled.\n"; return; }
    ifstream in(DATA_FILE, ios::binary);
    ofstream out("foodtruck.tmp", ios::binary | ios::trunc);
    if (!in || !out) { cout << "Unable to prepare temporary file.\n"; return; }
    TruckRecord r; int removed = 0; bool ok = true;
    while (in.read(reinterpret_cast<char *>(&r), sizeof(r))) {
        if (r.id == id) { removed++; continue; }
        if (!out.write(reinterpret_cast<const char *>(&r), sizeof(r))) { ok = false; break; }
    }
    if (!in.eof()) ok = false;
    in.close(); out.close();
    if (!ok || removed != 1 || !out) {
        remove("foodtruck.tmp"); cout << "Delete failed; original file kept.\n"; return;
    }
    // Keep original until a backup exists; restore it if replacement fails.
    remove("foodtruck.bak");
    if (rename(DATA_FILE, "foodtruck.bak") != 0) {
        remove("foodtruck.tmp"); cout << "Unable to back up data file.\n"; return;
    }
    if (rename("foodtruck.tmp", DATA_FILE) != 0) {
        rename("foodtruck.bak", DATA_FILE);
        cout << "Delete failed; attempted to restore original.\n"; return;
    }
    remove("foodtruck.bak");
    FoodTruck::setCount(countRecords());
    cout << "Record deleted successfully.\n";
}
void conceptDemo() {
    FoodTruck sample(700, "Sample Truck", "Campus", "Sandwich", 50, 'A');
    FoodTruck copy(sample);
    VegTruck veg(sample);
    NonVegTruck nonveg(sample);
    FoodTruck *p = new VegTruck(sample);
    cout << "Virtual display through base pointer:\n"; p->display(); delete p;
    cout << "Second derived class:\n"; nonveg.display();
    cout << "Veg class:\n"; veg.display();
    cout << "<< operator: " << sample << '\n';
    cout << "== operator (sample/copy): " << (sample == copy) << '\n';
    cout << "< operator (sample/sample+10): " << (sample < sample + 10.0f) << '\n';
    cout << "+ operator (price + 10): " << sample + 10.0f << '\n';
    int convertedId = static_cast<int>(sample);
    cout << "Type conversion FoodTruck to int: " << convertedId << '\n';
    cout << ">> operator is used when adding/updating records.\n";
}
int main() {
    FoodTruck::setCount(countRecords());
    int choice = 0;
    do {
        cout << "\n===== FOOD TRUCK PLANNER CA3 =====\n"
             << "1. Add Food Truck\n2. Display All Food Trucks\n"
             << "3. Search Food Truck\n4. Update Food Truck\n"
             << "5. Delete Food Truck\n6. OOP Concept Demo\n7. Exit\nEnter choice: ";
        if (!(cin >> choice)) { cout << "Invalid choice.\n"; resetInput(); continue; }
        switch (choice) {
            case 1: addRecord(); break;
            case 2: displayAll(); break;
            case 3: searchMenu(); break;
            case 4: updateRecord(); break;
            case 5: deleteRecord(); break;
            case 6: conceptDemo(); break;
            case 7: cout << "Program closed.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 7);
}
