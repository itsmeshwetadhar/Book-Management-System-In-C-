#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <limits>

struct ZodiacSign {
    std::string name;
    int startMonth;
    int startDay;
    int endMonth;
    int endDay;
    std::string luckyColor;
    int luckyNumber;
    std::string personalityTrait;
};

class FortuneTeller {
private:
    const ZodiacSign zodiacSigns[12] = {
        {"Aries", 3, 21, 4, 19, "Red", 7, "Energetic"},
        {"Taurus", 4, 20, 5, 20, "Green", 5, "Patient"},
        {"Gemini", 5, 21, 6, 20, "Yellow", 3, "Adaptable"},
        {"Cancer", 6, 21, 7, 22, "Silver", 2, "Emotional"},
        {"Leo", 7, 23, 8, 22, "Gold", 1, "Charismatic"},
        {"Virgo", 8, 23, 9, 22, "Navy Blue", 9, "Detail-oriented"},
        {"Libra", 9, 23, 10, 22, "Pink", 6, "Balanced"},
        {"Scorpio", 10, 23, 11, 21, "Maroon", 8, "Determined"},
        {"Sagittarius", 11, 22, 12, 21, "Purple", 4, "Optimistic"},
        {"Capricorn", 12, 22, 1, 19, "Brown", 10, "Ambitious"},
        {"Aquarius", 1, 20, 2, 18, "Turquoise", 11, "Innovative"},
        {"Pisces", 2, 19, 3, 20, "Sea Green", 12, "Compassionate"}
    };

    std::tm birthDate;

public:
    FortuneTeller() {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(0)));

        // Get current date
        std::time_t t = std::time(0);
        birthDate = *std::localtime(&t);
    }

    void getUserDetails() {
        std::string name;
        std::cout << "Welcome to the Fortune Teller!" << std::endl;
        std::cout << "Enter your name: ";
        std::getline(std::cin, name);
        std::cout << "Hello, " << name << "!" << std::endl;

        // User birth date input
        int day, month, year;
        std::cout << "Enter your birth date (DD MM YYYY): ";
        std::cin >> day >> month >> year;

        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        birthDate = {0, 0, 0, day, month - 1, year - 1900};
    }

    int calculateAge() {
        std::time_t currentDate = std::time(0);
        std::tm* pCurrentDate = std::localtime(&currentDate);
        int age = pCurrentDate->tm_year - birthDate.tm_year;

        if (pCurrentDate->tm_mon < birthDate.tm_mon ||
            (pCurrentDate->tm_mon == birthDate.tm_mon && pCurrentDate->tm_mday < birthDate.tm_mday)) {
            age--;
        }

        return age;
    }

    void displayAge() {
        int age = calculateAge();
        std::cout << "Your age is: " << age << " years" << std::endl;
    }

    void displayZodiacSign() {
        int month = birthDate.tm_mon + 1;
        int day = birthDate.tm_mday;

        for (const ZodiacSign& sign : zodiacSigns) {
            if ((month == sign.startMonth && day >= sign.startDay) ||
                (month == sign.endMonth && day <= sign.endDay)) {
                std::cout << "Your Zodiac Sign (Indian): " << sign.name << std::endl;
                return;
            }
        }
        std::cout << "Unable to determine your Zodiac Sign." << std::endl;
    }

    void displayFortune() {
        int randomIndex = std::rand() % 12;
        const ZodiacSign& todaySign = zodiacSigns[randomIndex];

        std::cout << "Today's Fortune: " << todaySign.name << " - " << todaySign.personalityTrait << " day." << std::endl;
        std::cout << "Lucky Number: " << todaySign.luckyNumber << std::endl;
        std::cout << "Lucky Color: " << todaySign.luckyColor << std::endl;
    }

    void displayLoveCompatibility() {
        int partnerMonth, partnerDay;
        std::cout << "Enter your partner's birth date (MM DD): ";
        std::cin >> partnerMonth >> partnerDay;

        for (const ZodiacSign& sign : zodiacSigns) {
            if ((partnerMonth == sign.startMonth && partnerDay >= sign.startDay) ||
                (partnerMonth == sign.endMonth && partnerDay <= sign.endDay)) {
                std::cout << "Your Love Compatibility with " << sign.name << ": ";
                std::cout << "You make a great match!" << std::endl;
                return;
            }
        }

        std::cout << "Unable to determine your partner's Zodiac Sign." << std::endl;
    }
};

int main() {
    FortuneTeller fortuneTeller;
    fortuneTeller.getUserDetails();

    int choice;
    do {
        std::cout << "\nOptions:" << std::endl;
        std::cout << "1. Display Age" << std::endl;
        std::cout << "2. Display Zodiac Sign (Indian)" << std::endl;
        std::cout << "3. Today's Fortune, Lucky Number, and Lucky Color" << std::endl;
        std::cout << "4. Love Compatibility" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                fortuneTeller.displayAge();
                break;
            case 2:
                fortuneTeller.displayZodiacSign();
                break;
            case 3:
                fortuneTeller.displayFortune();
                break;
            case 4:
                fortuneTeller.displayLoveCompatibility();
                break;
            case 0:
                std::cout << "Exiting the Fortune Teller program. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0);

    return 0;
}
