#include <iostream>
#include <string>

class Address {
private:
    std::string city;
    int pin;

public:
    Address(const std::string& c, int p) : city(c), pin(p) {
        std::cout << "Address constructed ";
    }
    ~Address() { std::cout << "Address destroyed "; }

    std::string str() const {
        return city + "-" + std::to_string(pin);
    }
};

class Course {
private:
    std::string title;
    int credits;

public:
    Course(const std::string& t, int c) : title(t), credits(c) {
        std::cout << "Course constructed ";
    }
    ~Course() { std::cout << "Course destroyed "; }
};

class Person {
protected:
    std::string name;
    int age;
    Address address;

public:
    Person(const std::string& n, int a, const std::string& city, int pin)
        : name(n), age(a), address(city, pin) {
        std::cout << "Person constructed ";
    }
    virtual ~Person() { std::cout << "Person destroyed "; }
};

class Student : virtual public Person {
protected:
    long long regNo;
    Course course;

public:
    Student(const std::string& n, int a, long long r,
            const std::string& city, int pin,
            const std::string& courseName, int credits)
        : Person(n, a, city, pin), regNo(r),
          course(courseName, credits) {
        std::cout << "Student constructed ";
    }
    ~Student() override { std::cout << "Student destroyed "; }

    void print() const {
        std::cout << regNo << ' ' << name << " (" << age << ") "
                  << address.str() << '\n';
    }
};

class Staff : virtual public Person {
protected:
    std::string department;

public:
    Staff(const std::string& n, int a, const std::string& city, int pin,
          const std::string& dept)
        : Person(n, a, city, pin), department(dept) {
        std::cout << "Staff constructed ";
    }
    ~Staff() override { std::cout << "Staff destroyed "; }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& n, int a, long long r,
                      const std::string& city, int pin,
                      const std::string& courseName, int credits,
                      const std::string& dept)
        : Person(n, a, city, pin),
          Student(n, a, r, city, pin, courseName, credits),
          Staff(n, a, city, pin, dept) {
        std::cout << "TeachingAssistant constructed ";
    }
    ~TeachingAssistant() override {
        std::cout << "TeachingAssistant destroyed ";
    }
};

class Engine {
public:
    Engine() { std::cout << "Engine "; }
    ~Engine() { std::cout << "~Engine "; }
};

class Vehicle {
public:
    Vehicle() { std::cout << "Vehicle "; }
    virtual ~Vehicle() { std::cout << "~Vehicle "; }
};

class Car : public Vehicle {
private:
    Engine engine;
public:
    Car() { std::cout << "Car "; }
    ~Car() override { std::cout << "~Car "; }
};

int main() {
    std::cout << "Student object:\n";
    {
        Student s("Kavya", 19, 192311001, "Salem", 636001,
                  "C++ Programming", 4);
        std::cout << '\n';
        s.print();
        std::cout << "Leaving Student scope:\n";
    }
    std::cout << "\n\nTeachingAssistant object:\n";
    {
        TeachingAssistant ta("Riya", 20, 192311002, "Chennai", 600001,
                             "OOP", 4, "CSE");
        std::cout << "\nLeaving TeachingAssistant scope:\n";
    }
    std::cout << "\n\nCar construction/destruction trace:\n";
    {
        Car car;
        std::cout << "| ";
    }
    std::cout << '\n';
    return 0;
}
