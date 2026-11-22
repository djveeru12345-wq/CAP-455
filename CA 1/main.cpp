#include <iostream> 
#include <string> 
using namespace std; 
  
class FoodTruck { 
private: 
    int id; 
    string name; 
    string location; 
    float price; 
    char type; 
    string status; 
    static int cnt; 
  
public: 
    void setData(int &x, string &n, string &l, float &p, 
                 char &t, string &s) { 
        this->id = x; 
        this->name = n; 
        this->location = l; 
        this->price = p; 
        this->type = t; 
        this->status = s; 
        cnt++; 
    } 
  
    void showData() { 
        cout << "\nID: " << id; 
        cout << "\nName: " << name; 
        cout << "\nLocation: " << location; 
        cout << "\nAverage Price: " << price; 
        cout << "\nFood Type: " << type; 
        cout << "\nStatus: " << status << "\n"; 
    } 
 
 
  
    inline int getId() { 
        return id; 
    } 
  
    static int getCount() { 
        return cnt; 
    } 
  
    static void showCount() { 
        cout << "\nTotal Food Trucks: " << cnt << "\n"; 
    } 
  
    friend void checkPrice(FoodTruck &f); 
}; 
  
int FoodTruck::cnt = 0; 
  
void checkPrice(FoodTruck &f) { 
    cout << "\nPrice Check for ID " << f.id << ": "; 
  
    if (f.price <= 200) { 
        cout << "Affordable"; 
    } else { 
        cout << "Premium"; 
    } 
  
    cout << "\n"; 
} 
  
int main() { 
    FoodTruck arr[50]; 
    FoodTruck *ptr = arr; 
  
    int choice, id, flag, found; 
    int i; 
    float price; 
    char type; 
    string name, location, status; 
 
 
  
    do { 
        cout << "\n===== FOOD TRUCK PLANNER =====\n"; 
        cout << "1. Add Food Truck\n"; 
        cout << "2. Display All Food Trucks\n"; 
        cout << "3. Search Food Truck by ID\n"; 
        cout << "4. Show Total Records\n"; 
        cout << "5. Exit\n"; 
        cout << "Enter choice: "; 
  
        if (!(cin >> choice)) { 
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            choice = -1; 
        } 
  
        switch (choice) { 
        case 1: 
            if (FoodTruck::getCount() >= 50) { 
                cout << "\nArray is full. Cannot add more 
records.\n"; 
                break; 
            } 
  
            do { 
                cout << "\nEnter Food Truck ID: "; 
  
                if (!(cin >> id)) { 
                    cin.clear(); 
                    cin.ignore(1000, '\n'); 
                    id = -1; 
                } 
  
                if (id <= 0) { 
                    cout << "ID must be a positive 
number.\n"; 
                } 
            } while (id <= 0); 
  
 
 
            flag = 0; 
  
            for (i = 0; i < FoodTruck::getCount(); i++) { 
                if (id == arr[i].getId()) { 
                    flag = 1; 
                    break; 
                } 
            } 
  
            if (flag == 1) { 
                cout << "\nDuplicate ID not allowed.\n"; 
                break; 
            } 
  
            cin.ignore(); 
  
            do { 
                cout << "Enter Food Truck Name: "; 
                getline(cin, name); 
  
                if (name == "") { 
                    cout << "Name cannot be empty.\n"; 
                } 
            } while (name == ""); 
  
            do { 
                cout << "Enter Location: "; 
                getline(cin, location); 
  
                if (location == "") { 
                    cout << "Location cannot be empty.\n"; 
                } 
            } while (location == ""); 
  
            do { 
                cout << "Enter Average Menu Price: "; 
  
                if (!(cin >> price)) { 
                    cin.clear(); 
 
 
                    cin.ignore(1000, '\n'); 
                    price = -1; 
                } 
  
                if (price <= 0 || price > 10000) { 
                    cout << "Enter price between 1 and 
10000.\n"; 
                } 
            } while (price <= 0 || price > 10000); 
  
            do { 
                cout << "Enter Food Type (V/N): "; 
                cin >> type; 
  
                if (type >= 'a' && type <= 'z') { 
                    type = type - 32; 
                } 
  
                if (type != 'V' && type != 'N') { 
                    cout << "Enter only V or N.\n"; 
                } 
            } while (type != 'V' && type != 'N'); 
  
            cin.ignore(); 
  
            do { 
                cout << "Enter Status (Available/Busy): "; 
                getline(cin, status); 
  
                if (status != "Available" && status != 
"Busy") { 
                    cout << "Enter Available or Busy.\n"; 
                } 
            } while (status != "Available" && status != 
"Busy"); 
  
            arr[FoodTruck::getCount()].setData( 
                id, name, location, price, type, status 
            ); 
 
 
  
            cout << "\nFood Truck added successfully.\n"; 
            checkPrice(arr[FoodTruck::getCount() - 1]); 
            break; 
  
        case 2: 
            if (FoodTruck::getCount() == 0) { 
                cout << "\nNo Food Truck records 
available.\n"; 
            } else { 
                cout << "\n----- FOOD TRUCK RECORDS ----
\n"; 
  
                for (i = 0; i < FoodTruck::getCount(); 
i++) { 
                    (ptr + i)->showData(); 
                } 
            } 
            break; 
  
        case 3: 
            if (FoodTruck::getCount() == 0) { 
                cout << "\nNo records available for 
searching.\n"; 
                break; 
            } 
  
            do { 
                cout << "\nEnter ID to search: "; 
  
                if (!(cin >> id)) { 
                    cin.clear(); 
                    cin.ignore(1000, '\n'); 
                    id = -1; 
                } 
  
                if (id <= 0) { 
                    cout << "Enter a valid positive 
ID.\n"; 
 
 
                } 
            } while (id <= 0); 
  
            found = 0; 
  
            for (i = 0; i < FoodTruck::getCount(); i++) { 
                if ((ptr + i)->getId() == id) { 
                    cout << "\nFood Truck Found:\n"; 
                    (ptr + i)->showData(); 
                    found = 1; 
                    break; 
                } 
            } 
  
            if (found == 0) { 
                cout << "\nFood Truck not found.\n"; 
            } 
            break; 
  
        case 4: 
            FoodTruck::showCount(); 
            break; 
  
        case 5: 
            cout << "\nThank you for using Food Truck 
Planner.\n"; 
            break; 
  
        default: 
            cout << "\nInvalid choice. Please try 
again.\n"; 
        } 
  
    } while (choice != 5); 
  
    return 0; 
}