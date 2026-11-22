#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct TruckRecord
{
    int id;
    char name[40];
    char location[40];
    char menu[40];
    float price;
    char status;
};

void copyText(char dest[], string source, int size)
{
    int i;
    for (i = 0; i < size - 1 && i < (int)source.length(); i++)
        dest[i] = source[i];
    dest[i] = '\0';
}

class FoodTruck
{
private:
    int id;
    string name, location, menu;
    float price;
    char status;
    static int cnt;

public:
    FoodTruck()
    {
        id = 0;
        name = "";
        location = "";
        menu = "";
        price = 0;
        status = 'C';
    }

    FoodTruck(int id, string name, string location,
              string menu, float price, char status)
    {
        this->id = id;
        this->name = name;
        this->location = location;
        this->menu = menu;
        this->price = price;
        this->status = status;
    }

    FoodTruck(const FoodTruck &obj)
    {
        id = obj.id;
        name = obj.name;
        location = obj.location;
        menu = obj.menu;
        price = obj.price;
        status = obj.status;
    }

    ~FoodTruck()
    {
    }

    void setFromRecord(const TruckRecord &record)
    {
        id = record.id;
        name = record.name;
        location = record.location;
        menu = record.menu;
        price = record.price;
        status = record.status;
    }

    TruckRecord toRecord() const
    {
        TruckRecord record = {};
        record.id = id;
        copyText(record.name, name, 40);
        copyText(record.location, location, 40);
        copyText(record.menu, menu, 40);
        record.price = price;
        record.status = status;
        return record;
    }

    void display() const
    {
        cout << "\nID: " << id
             << "\nName: " << name
             << "\nLocation: " << location
             << "\nMenu: " << menu
             << "\nPrice: " << price
             << "\nStatus: " << status << endl;
    }

    int getId() const
    {
        return id;
    }

    static int getCount()
    {
        return cnt;
    }

    static void setCount(int value)
    {
        cnt = value;
    }

    friend void showRecord(FoodTruck &obj);
};

int FoodTruck::cnt = 0;

void showRecord(FoodTruck &obj)
{
    obj.display();
}

int countRecords()
{
    ifstream file("foodtruck.dat", ios::binary);
    TruckRecord record;
    int count = 0;

    if (!file)
        return 0;

    while (file.read(reinterpret_cast<char *>(&record), sizeof(record)))
        count++;

    file.close();
    return count;
}

int searchRecord(int id, FoodTruck &truck, streamoff &position)
{
    ifstream file("foodtruck.dat", ios::binary);
    TruckRecord record;

    if (!file)
        return 0;

    file.seekg(0, ios::beg);

    while (true)
    {
        streampos current = file.tellg();

        if (!file.read(reinterpret_cast<char *>(&record), sizeof(record)))
            break;

        if (record.id == id)
        {
            position = static_cast<streamoff>(current);
            truck.setFromRecord(record);
            file.close();
            return 1;
        }
    }

    file.close();
    return 0;
}

void addRecord()
{
    int id;
    string name, location, menu;
    float price;
    char status;
    FoodTruck existing;
    streamoff position = 0;

    cout << "\nEnter Truck ID: ";
    cin >> id;

    if (id <= 0)
    {
        cout << "ID must be positive.\n";
        return;
    }

    if (searchRecord(id, existing, position))
    {
        cout << "Duplicate ID. Record not added.\n";
        return;
    }

    cin.ignore();

    cout << "Enter Truck Name: ";
    getline(cin, name);
    cout << "Enter Location: ";
    getline(cin, location);
    cout << "Enter Menu Item: ";
    getline(cin, menu);
    cout << "Enter Price: ";
    cin >> price;
    cout << "Enter Status (A/C): ";
    cin >> status;

    if (name.empty() || location.empty() || menu.empty() ||
        price < 0 || (status != 'A' && status != 'C'))
    {
        cout << "Invalid input. Record not saved.\n";
        return;
    }

    FoodTruck truck(id, name, location, menu, price, status);
    FoodTruck copiedTruck(truck);
    TruckRecord record = copiedTruck.toRecord();

    ofstream file("foodtruck.dat", ios::binary | ios::app);

    if (!file)
    {
        cout << "Unable to open data file.\n";
        return;
    }

    file.write(reinterpret_cast<char *>(&record), sizeof(record));

    if (file)
    {
        FoodTruck::setCount(countRecords());
        cout << "Record saved successfully.\n";
    }
    else
        cout << "Record could not be saved.\n";

    file.close();
}

void displayAll()
{
    ifstream file("foodtruck.dat", ios::binary);
    TruckRecord record;
    FoodTruck truck;

    if (!file)
    {
        cout << "No records available.\n";
        return;
    }

    file.seekg(0, ios::beg);
    int count = 0;

    while (file.read(reinterpret_cast<char *>(&record), sizeof(record)))
    {
        truck.setFromRecord(record);
        showRecord(truck);
        cout << "----------------------\n";
        count++;
    }

    if (count == 0)
        cout << "No records available.\n";

    FoodTruck::setCount(count);
    file.close();
}

void searchMenu()
{
    int id;
    FoodTruck truck;
    streamoff position = 0;

    cout << "\nEnter Truck ID to search: ";
    cin >> id;

    if (searchRecord(id, truck, position))
        showRecord(truck);
    else
        cout << "Record not found.\n";
}

void updateRecord()
{
    int id;
    FoodTruck truck;
    streamoff position = 0;

    cout << "\nEnter Truck ID to update: ";
    cin >> id;

    if (!searchRecord(id, truck, position))
    {
        cout << "Record not found.\n";
        return;
    }

    string name, location, menu;
    float price;
    char status;

    cin.ignore();
    cout << "Enter New Truck Name: ";
    getline(cin, name);
    cout << "Enter New Location: ";
    getline(cin, location);
    cout << "Enter New Menu Item: ";
    getline(cin, menu);
    cout << "Enter New Price: ";
    cin >> price;
    cout << "Enter Status (A/C): ";
    cin >> status;

    if (name.empty() || location.empty() || menu.empty() ||
        price < 0 || (status != 'A' && status != 'C'))
    {
        cout << "Invalid input. Update cancelled.\n";
        return;
    }

    FoodTruck updated(id, name, location, menu, price, status);
    TruckRecord record = updated.toRecord();

    fstream file("foodtruck.dat", ios::in | ios::out | ios::binary);

    if (!file)
    {
        cout << "Unable to open data file.\n";
        return;
    }

    file.seekp(position, ios::beg);
    file.write(reinterpret_cast<char *>(&record), sizeof(record));

    if (file)
        cout << "Record updated successfully.\n";
    else
        cout << "Update failed.\n";

    file.close();
}

int main()
{
    int choice;
    FoodTruck::setCount(countRecords());

    do
    {
        cout << "\n===== FOOD TRUCK PLANNER =====";
        cout << "\n1. Add Food Truck";
        cout << "\n2. Display All Food Trucks";
        cout << "\n3. Search Food Truck";
        cout << "\n4. Update Food Truck";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Enter a number.\n";
            choice = 0;
            continue;
        }

        switch (choice)
        {
        case 1:
            addRecord();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            searchMenu();
            break;
        case 4:
            updateRecord();
            break;
        case 5:
            cout << "Program closed.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
