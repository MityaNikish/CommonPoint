#pragma once
#include <exception>

class UserException : public std::exception {};


class IsWrongSize : public UserException {
    const char* what() const noexcept override
    {
        return "Not the correct size";
    }
};