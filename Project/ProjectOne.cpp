#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;

/*
* This program displays a clock and offers user options to update the clock.
* Author: Asia Peters
* Date:   March 19, 2023
* Version: 1.0
*/

// A clock that runs by hours, minutes, and seconds.
class Clock 
{
private:                
    int hours;        
    int minutes;        
    int seconds;        
    vector<string> menuChoices{ "Add One Hour", "Add One Minute", "Add One Second", "Exit Program" };

    /**
    * Adds one hour
    */
    void AddHour() {
        // If current minute is less than 23 hours, one hour will be added
        if (GetHour() >= 0 && GetHour() <= 22) {
            SetHour(GetHour() + 1);
        }
        // If current minute is equal to 23, it will reset to 0
        else if (GetHour() == 23) {
            SetHour(0);
        }
    }

    /**
    * Adds one minute
    */
    void AddMinute() {
        // If current minute is less than 59 minutes, one minute will be added
        if (GetMinute() >= 0 && GetMinute() <= 58) {
            SetMinute(GetMinute() + 1);
        }
        // If current minute is equal to 59 minutes it will reset to 0 and one hour will be added
        else if (GetMinute() == 59) {
            SetMinute(0);
            AddHour();
        }
    }

    /**
    * Adds one second
    */
    void AddSecond() { 
        // If current second is less than 59 seconds, one second will be added
        if (GetSecond() >= 0 && GetSecond() <= 58) {
            SetSecond(GetSecond() + 1);
        }
        // If current second is equal to 59 seconds it will reset to 0 and one minute will be added
        else if (GetSecond() == 59) {
            SetSecond(0);
            AddMinute();
        }
    }

    /**
    * Returns a string of length num, each character.
    *
    * @param character character that will be duplicated
    * @param num string length, >=0
    * @return string of num characters's
    */
    string PrintCharacters(char character, unsigned int num) {
        string newString = "";
        unsigned int i;

        for (i = 0; i < num; ++i) {
            newString += character;
        }

        return newString;
    }

    /**
     * Formats a number as 2 digits, with a leading 0 if needed
     *
     * @param n number to format, assumed between 0 and 59, inclusive
     * 
     * @return two digit string representation of number
     */
    string TwoDigitString(unsigned int n) {
        string digitString = "";

        // Numbers between 10 and 59 just need to be converted to a string
        // Numbers from 0 to 9 need a "O" tacked onto the front of the string representation of the number
        if (n >= 0) {
            if (n >= 0 && n <= 9) {
                digitString += '0';
            }
            digitString += to_string(n);
        }

        return digitString;

        // Return the two digit string representation of n
    }

    /**
    * Formats the time in military format
    *
    * @param h, hours 0 to 23
    * @param m, minutes 0 to 59
    * @param s, seconds 0 to 59
    *
    * @return HH:MM:SS
    */
    string FormatTime24(unsigned int h, unsigned int m, unsigned int s) {
        string formattedTime;

        formattedTime += TwoDigitString(h) + ':' + TwoDigitString(m) + ':' + TwoDigitString(s);

        return formattedTime;
    }
    
    /**
    * Formats the time in 12-hour format

    *
    * @param h, hours 0 to 23
    * @param m, minutes 0 to 59
    * @param s, seconds 0 to 59
    *
    * @return HH:MM:SS AM/PM
    */
    string FormatTime12(unsigned int h, unsigned int m, unsigned int s) {
        string dayType;
        string formattedString = "";
        if (h >= 12) {
            if (h != 12) {
                h -= 12;
            }
            dayType = " P M";
        }
        else {
            if (h == 0) {
                h = 12;
            }

            dayType = " A M";
        }

        formattedString += TwoDigitString(h) + ":" + TwoDigitString(m) + ":" + TwoDigitString(s) + dayType;

        return formattedString;
    }

    /**
    * Displays the 12-hour and 24-hour clocks surrounded by border
    */
    void DisplayTime() { 
        cout << PrintCharacters('*', 27) << PrintCharacters(' ', 3) << PrintCharacters('*', 27) << endl; // Top Border

        // Displays clocks
        cout << PrintCharacters('*', 1) << PrintCharacters(' ', 6) << "12-HOUR CLOCK" << PrintCharacters(' ', 6) << PrintCharacters('*', 1) << PrintCharacters(' ', 3); 
        cout << PrintCharacters('*', 1) << PrintCharacters(' ', 6) << "24-HOUR CLOCK" << PrintCharacters(' ', 6) << PrintCharacters('*', 1) << endl;
        cout << endl;
        cout << PrintCharacters('*', 1) << PrintCharacters(' ', 6) << FormatTime12(GetHour(), GetMinute(), GetSecond()) << PrintCharacters(' ', 7) << PrintCharacters('*', 1) << PrintCharacters(' ', 3);
        cout << PrintCharacters('*', 1) << PrintCharacters(' ', 8) << FormatTime24(GetHour(), GetMinute(), GetSecond()) << PrintCharacters(' ', 9) << PrintCharacters('*', 1) << endl;
        
        cout << PrintCharacters('*', 27) << PrintCharacters(' ', 3) << PrintCharacters('*', 27) << endl; // Bottom border
    }
    
    /**
    * Prints menu
    *
    * @param menuItems, nonempty vector of choices
    * @param width, width of each line, will be comfortably bigger than the longest string
    *
    */
    void DisplayMenu(vector<string> menuItems, int numStrings, int width) {
        cout << PrintCharacters('*', width) << endl;

        for (int i = 0; i < numStrings; ++i) {
            int remainingSpaces = width - 7;
            remainingSpaces -= static_cast<unsigned int>(menuItems.at(i).size());
            
            if (remainingSpaces < 0) {
                break;
            }

            cout << "* " << i + 1 << " - ";
            cout << menuItems.at(i);
            cout << PrintCharacters(' ', remainingSpaces) << "*" << endl;
        }

        cout << PrintCharacters('*', width) << endl;
    }



public:
    Clock();
    Clock(int s, int m, int h);

    // Getter / Setter Methods
    /**
    * Gets current list of choices available to user
    */
    vector<string> GetMenuChoices() {
        return menuChoices;
    }

    /**
    * Gets current hour of clock
    */
    int GetHour() {
        return hours;
    }
    
    /**
    * Gets current minute of clock
    */
    int GetMinute() {
        return minutes;
    }
    
    /**
    * Gets current second of clock
    */
    int GetSecond() {
        return seconds;
    }

    /**
    * Sets hours for clock
    * @param hour, hours (0-23)
    */
    void SetHour(int h) {
        hours = h;
    }

    /**
    * Sets minutes for clock
    * @param m, minutes (0-59)
    */
    void SetMinute(int m) {
        minutes = m;
    }

    /**
    * Sets seconds for clock
    * @param s, seconds (0-59)
    */
    void SetSecond(int s) {
        seconds = s;
    }

    /*
    * Clears screen
    */
    void ClearScreen() { 
        system("CLS");
    }

    /*
    * Displays clocks and menu
    */
    void Display() { 
        DisplayTime();
        cout << endl;
        DisplayMenu(menuChoices, static_cast<unsigned int>(GetMenuChoices().size()), 26);
        cout << endl;
    };      
    
    /*
    * Selects option for user based on input
    * 
    * @param input, number that user selected from options
    */
    void InputAction(int input) {
        switch (input) {
        case 1:
            AddHour();
            break;
        case 2:
            AddMinute();
            break;
        case 3:
            AddSecond();
            break;
        }
    }
    
    /*
    * Requests user for input and validates if input is in range
    * 
    * @param maxSize, maximum number of choices for user (0 - maxSize)
    * 
    * @return validated number 
    */
    int ReadUserInput(int maxSize) { 
        int userChoice = 0;

        // Loop to ensure user enters a number within range
        do {
            cout << "Enter Selection:" << endl;
            cin >> userChoice;
            cout << endl;

            if (userChoice < 1 || userChoice > maxSize) { // Reminds user to enter a number within range
                cout << "Entered value is not in range. Please select options 1 - " << maxSize << endl << endl;
            }
        } while (userChoice < 1 || userChoice > maxSize);

        return userChoice;
    };

    /*
    * Activates clock and allows user to make changes to time
    */
    bool Start() {
        int userInput = 0;

        // Loop that will only break if user decides to exit the program
        // Will display updated time after each new loop
        do {
            ClearScreen();
            Display();
            userInput = ReadUserInput(static_cast<unsigned int>(GetMenuChoices().size()));
            InputAction(userInput);
        } while (userInput != GetMenuChoices().size());

        return false;
    }
};

// Constructors
Clock::Clock() {
    SetHour(0);
    SetMinute(0);
    SetSecond(0);
}

Clock::Clock(int s, int m, int h) {
    SetHour(h);
    SetMinute(m);
    SetSecond(s);
}

/**
* verifies if number is valid (0 to max number)
* 
* @param type, type number validated is being used for
* @param maxVal, possible max number that validated number can be
* 
* @return, returns valid number
* 
*/
int verifyNum(string type, int maxVal) {
    int val = 0;

    // Loop to ensure that inputted number is within range
    do {
        if (val < 0) {
            cout << "Value too low. Please enter " << type << " (0 - " << maxVal << " ) : ";
        }
        else if (val > maxVal) {
            cout << "Value too high. Please enter " << type << " (0 - " << maxVal << " ) : ";
        }
        else {
            cout << "Please enter " << type << " (0 - " << maxVal << " ) : ";
        }
        
        cin >> val;
        cout << endl;
        system("CLS");
    } while (val < 0 || val > maxVal);
    
    return val;
}

/*
* User intializes clock settings and starts the clock
*/
int main() {
    Clock clock(verifyNum("second", 59), verifyNum("minute", 59), verifyNum("hour", 23));

    while (true) {
        if (clock.Start() == false) {
            break;
        }
    }
   
    return 0;
}