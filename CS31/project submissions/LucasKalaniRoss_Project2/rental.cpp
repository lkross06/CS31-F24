#include <iostream>
#include <string>
using namespace std;

int main() {
    
    //declare constants
    const int BASE_CHARGE_NORMAL = 45;
    const int BASE_CHARGE_LUXURY = 75;
    const int CPM_LOW_THRESHOLD = 100;
    const int CPM_MEDIUM_THRESHOLD = 600;
    const double CPM_LOW = 0.33;
    const double CPM_MEDIUM = 0.27;
    const double CPM_MEDIUM_WINTER = 0.33;
    const double CPM_HIGH = 0.21;
    
    //gather inputs
    int odo_start;
    int odo_end;
    int days;
    string name;
    bool is_luxury = true;
    int month;
    
    /*
     * Error types:
     * 0 = no error :)
     * 1 = odometer start is negative
     * 2 = odometer end is less than odometer start
     * 3 = rental days not positive
     * 4 = empty string for customer name
     * 5 = luxury status not "y" or "n"
     * 6 = month is not between 1 (inclusive) and 12 (inclusive)
     */
    
    int error_type = 0;
    
    cout << "Odometer at start: ";
    cin >> odo_start;
    
    cout << "Odometer at end: ";
    cin >> odo_end;
    
    cout << "Rental days: ";
    cin >> days;
    
    cin.ignore(10000, '\n'); //clear input stream
    cout << "Customer name: ";
    getline(cin, name);
    
    string temp_luxury;
    cout << "Luxury car? (y/n): ";
    getline(cin, temp_luxury);
    
    cout << "Starting month (1=Jan, 2=Feb, etc.): ";
    cin >> month;
    
    //look for input errors in the opposite order that we gathered them
    
    if (month < 1 || month > 12) error_type = 6;
    
    if (temp_luxury == "n")
        is_luxury = false; //automatically set to true
    else if (temp_luxury != "y")
        error_type = 5;
    
    if (name == "") error_type = 4;
    
    if (days < 0) error_type = 3;
    
    if (odo_end < odo_start) error_type = 2;
    
    if (odo_start < 0) error_type = 1;
    
    //finish collecting/processing inputs
    cout << "---" << endl;
    
    // if any errors were triggered, send the appropriate message and exit the program
    if (error_type != 0){
        switch (error_type){
            case 1:
                cout << "The starting odometer reading must not be negative." << endl;
                break;
            case 2:
                cout << "The ending odometer reading must be at least as large as the starting reading." << endl;
                break;
            case 3:
                cout << "The number of rental days must be positive." << endl;
                break;
            case 4:
                cout << "You must enter a customer name." << endl;
                break;
            case 5:
                cout << "You must enter y or n." << endl;
                break;
            case 6:
                cout << "The month number must be in the range 1 through 12." << endl;
                break;
        }
        return 0;
    }
    
    int miles_driven = odo_end - odo_start;
    bool is_winter = month <= 3 || month >= 12;
    double charge = 0.0;
    
    //base charge
    if (!is_luxury)
        charge += (BASE_CHARGE_NORMAL * days);
    else if (is_luxury)
        charge += (BASE_CHARGE_LUXURY * days);
    
    // charge per mile
    if (miles_driven > CPM_LOW_THRESHOLD){
        charge += (CPM_LOW_THRESHOLD * CPM_LOW);
    } else {
        charge += (miles_driven * CPM_LOW);
    }
    
    if (miles_driven > CPM_LOW_THRESHOLD && miles_driven <= CPM_MEDIUM_THRESHOLD){
        int medium_miles_driven = miles_driven - CPM_LOW_THRESHOLD;
        if (is_winter)
            charge += (medium_miles_driven * CPM_MEDIUM_WINTER);
        else
            charge += (medium_miles_driven * CPM_MEDIUM);
    }
    
    if (miles_driven > CPM_MEDIUM_THRESHOLD){
        int high_miles_driven = miles_driven - CPM_MEDIUM_THRESHOLD;
        charge += (high_miles_driven * CPM_HIGH);
    }
    
    //set cout to format doubles to 2 decimal points (money)
    cout.setf(ios::fixed);
    cout.precision(2);
    
    //print final result
    cout << "The rental charge for " << name << " is $" << charge << endl;
    
    return 0;
}
