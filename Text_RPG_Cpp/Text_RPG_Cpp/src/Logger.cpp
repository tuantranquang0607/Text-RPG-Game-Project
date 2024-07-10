// Disable warnings about unsafe C Runtime Library functions
#define _CRT_SECURE_NO_WARNINGS

#include "Logger.h"
#include "utilities/Colors.h"

#include <chrono>
#include <ctime>
#include <Windows.h>
#include <iostream>

// Function to get the current date and time in the format "yy-mm-dd HH:MM:SS".
std::string Logger::CurrentDate()
{
    // Get the current time.
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    // Initialize an output string of size 30.
    std::string output(30, '\0');

    // Format the time into the output string.
    std::strftime(&output[0], output.size(), "%y-%m-%d %H:%M:%S", std::localtime(&now));

    // Return the formatted time.
    return output;
}

// Function to log a message with the current date and time.
void Logger::Log(const std::string_view message)
{
    // Get the standard output handle.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set the console text color to green.
    SetConsoleTextAttribute(hConsole, GREEN);
    
    // Output the log message with the current date and time.
    std::cout << "LOG: " << CurrentDate() << " - " << message << "\n";

    // Reset the console text color to white.
    SetConsoleTextAttribute(hConsole, WHITE);
}

// Function to log an error message with the current date and time and the source location of the error.
void Logger::Error(const std::string_view message, std::source_location location)
{
    // Get the standard output handle.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set the console text color to red.
    SetConsoleTextAttribute(hConsole, RED);

    // Output the error message with the current date and time and the source location.
    std::cout << "ERROR: " << CurrentDate() << " - " << message << "FILE: " << location.file_name() << "FUNC: " << location.function_name() << "LINE: " << location.line() << "\n";

    // Reset the console text color to white.
    SetConsoleTextAttribute(hConsole, WHITE);
}
