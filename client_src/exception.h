#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class Exception : public std::exception{ 
	private:
		std::string error_message;

	public:
		explicit Exception(const char* message);

	    virtual const char* what() const noexcept override;
};
#endif
