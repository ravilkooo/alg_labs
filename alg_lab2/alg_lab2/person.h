#pragma once

#include <string>
#include <iostream>

class Person {
private:
    std::string name_;
    int age_;

public:
    Person() : name_("Unknown"), age_(0) {}
    Person(const std::string& name, int age) : name_(name), age_(age) {}

    Person(const Person& other) : name_(other.name_), age_(other.age_) {}

    Person& operator=(const Person& other) {
        if (this != &other) {
            name_ = other.name_;
            age_ = other.age_;
        }
        return *this;
    }

    const std::string& getName() const { return name_; }
    int getAge() const { return age_; }

    void print() const {
        std::cout << "Person(Name: " << name_ << ", Age: " << age_ << ")\n";
    }
};
