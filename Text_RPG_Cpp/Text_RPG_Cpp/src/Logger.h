#pragma once

#include <string_view>
#include <source_location>

// Define macros for logging and error reporting.
#define TRPG_LOG(x) Logger::Log(x);
#define TRPG_ERROR(x) Logger::Error(x);

class Logger
{
private:
	// A private method to get the current date.
	static std::string CurrentDate();

public:
	// The constructor for the Logger class.
	Logger() {};
	// The destructor for the Logger class. Defined as default.
	~Logger() = default;

	// A public method to log a message.
	static void Log(const std::string_view message);
	// A public method to log an error message with the source location of the error.
	static void Error(const std::string_view message, std::source_location location = std::source_location::current());
};
