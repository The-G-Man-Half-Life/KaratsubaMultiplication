#include <iostream>
#include <string>
#include <limits>
#include "KaratsubaMult.hpp"

void printSeparator() {
    std::cout << "\n============================================\n";
}

void displayMenu() {
    printSeparator();
    std::cout << "  Multiplicador por metodo Karatsuba\n";
    printSeparator();
    std::cout << "1. Multiplicar (2 numeros)\n";
    std::cout << "2. Salir\n";
    printSeparator();
    std::cout << "Seleccione una opcion (1-2): ";
}

BigInt getValidBigIntInput(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;
        
        try {
            return stringToBigInt(input);
        } 
        catch (const std::invalid_argument& e) {
            std::cout <<" Solo ingrese digitos (0-9).\n\n";
        }
    }
}

void handleInvalidCin() {
    std::cout << "\nEntrada no valida. Por favor ingrese un numero.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int option = 0;
    bool running = true;

    while (running) {
        displayMenu();
        
        if (!(std::cin >> option)) {
            handleInvalidCin();
            continue; 
        }

        switch (option) {
            case 1: {
                std::cout << "\n    Multiplicacion por metodo Karatsuba \n";
                
                BigInt num1 = getValidBigIntInput("Ingrese el multiplicando: ");
                BigInt num2 = getValidBigIntInput("Ingrese el multiplicador: ");
                
                BigInt result = karatsuba(num1, num2);
                
                printSeparator();
                std::cout << "Resultado:\n";
                std::cout << "   " << bigIntToString(num1) << "\n";
                std::cout << " * " << bigIntToString(num2) << "\n";
                std::cout << " = " << bigIntToString(result) << "\n";
                printSeparator();
                break;
            }
            case 2: {
                std::cout << "\nAdios\n";
                running = false; 
                break;
            }
            default: {
                std::cout << "\nOpcion fuera de rango. Elija un numero entre el 1 y el 2.\n";
                break;
            }
        }
    }

    return 0;
}