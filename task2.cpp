#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int id;
    std::string phone;

public:
    Person(const std::string& n, int i, const std::string& p)
        : name(n), id(i), phone(p) {
        std::cout << "Person ";
    }

    const std::string& getName() const { return name; }
    virtual ~Person() = default;
};

class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;

public:
    Student(const std::string& n, int i, const std::string& p,
            const std::string& prog, double c)
        : Person(n, i, p), programme(prog), cgpa(c) {
        std::cout << "Student ";
    }
};

class Staff : virtual public Person {
protected:
    std::string department;
    double salary;

public:
    Staff(const std::string& n, int i, const std::string& p,
          const std::string& dept, double s)
        : Person(n, i, p), department(dept), salary(s) {
        std::cout << "Staff ";
    }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& n, int i, const std::string& p,
                      const std::string& prog, double c,
                      const std::string& dept, double s)
        : Person(n, i, p),
          Student(n, i, p, prog, c),
          Staff(n, i, p, dept, s) {
        std::cout << "TA ";
    }
};

class ResearchScholar : public Student {
private:
    double fellowship;

public:
    ResearchScholar(const std::string& n, int i, const std::string& p,
                    const std::string& prog, double c, double f)
        : Person(n, i, p), Student(n, i, p, prog, c),
          fellowship(f) {}
};

int main() {
    std::cout << "Constructing TeachingAssistant:\n";
    TeachingAssistant ta("Kavya", 1001, "9876543210",
                         "CSE", 8.7, "Computer Science", 25000);
    std::cout << "\n";

    std::cout << "Person name through shared virtual base: "
              << ta.getName() << '\n';

    std::cout << "\nConstructing ResearchScholar:\n";
    ResearchScholar scholar("Arun", 1002, "9876500000",
                            "ECE", 9.1, 12000);
    (void)scholar;
    std::cout << '\n';
    return 0;
}
