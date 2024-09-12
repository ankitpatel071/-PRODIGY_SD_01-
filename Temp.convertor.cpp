#include <iostream>
#include <iomanip> // For setting precision

using namespace std;

// Function to convert Celsius to Fahrenheit
double celsiusToFahrenheit(double celsius) {
    return (celsius * 9 / 5) + 32;
}

// Function to convert Celsius to Kelvin
double celsiusToKelvin(double celsius) {
    return celsius + 273.15;
}

// Function to convert Fahrenheit to Celsius
double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32) * 5 / 9;
}

// Function to convert Fahrenheit to Kelvin
double fahrenheitToKelvin(double fahrenheit) {
    return (fahrenheit - 32) * 5 / 9 + 273.15;
}

// Function to convert Kelvin to Celsius
double kelvinToCelsius(double kelvin) {
    return kelvin - 273.15;
}

// Function to convert Kelvin to Fahrenheit
double kelvinToFahrenheit(double kelvin) {
    return (kelvin - 273.15) * 9 / 5 + 32;
}

// Function to display the converted values in a user-friendly format
void displayConversions(double originalTemp, char originalUnit) {
    cout << fixed << setprecision(2); // Set precision for decimal output

    if (originalUnit == 'C' || originalUnit == 'c') {
        cout << "\nConversion Results for " << originalTemp << "° Celsius:\n";
        cout << "------------------------------------------\n";
        cout << "Fahrenheit: " << celsiusToFahrenheit(originalTemp) << "°F\n";
        cout << "Kelvin    : " << celsiusToKelvin(originalTemp) << " K\n";
    } else if (originalUnit == 'F' || originalUnit == 'f') {
        cout << "\nConversion Results for " << originalTemp << "° Fahrenheit:\n";
        cout << "------------------------------------------\n";
        cout << "Celsius   : " << fahrenheitToCelsius(originalTemp) << "°C\n";
        cout << "Kelvin    : " << fahrenheitToKelvin(originalTemp) << " K\n";
    } else if (originalUnit == 'K' || originalUnit == 'k') {
        cout << "\nConversion Results for " << originalTemp << " Kelvin:\n";
        cout << "------------------------------------------\n";
        cout << "Celsius   : " << kelvinToCelsius(originalTemp) << "°C\n";
        cout << "Fahrenheit: " << kelvinToFahrenheit(originalTemp) << "°F\n";
    } else {
        cout << "\nInvalid input. Please enter a valid unit (C, F, or K).\n";
    }
}

int main() {
    double temperature;
    char unit;

    // Ask user to input the temperature and its unit
    cout << "Enter the temperature: ";
    cin >> temperature;
    cout << "Enter the unit (C for Celsius, F for Fahrenheit, K for Kelvin): ";
    cin >> unit;

    // Convert and display the temperature in other units
    displayConversions(temperature, unit);

    return 0;
}
