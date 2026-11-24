#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Staff {
private:
    std::string name_;
    int id_;
    double basic_;

protected:
    double basicPay() const { return basic_; }

public:
    Staff(const std::string& name, int id, double basic)
        : name_(name), id_(id), basic_(basic) {}

    virtual double pay() const = 0;

    virtual void display() const {
        std::cout << name_ << " (" << id_ << "): ";
    }

    virtual ~Staff() = default;
};

class Professor : public Staff {
private:
    double researchAllowance_;

public:
    Professor(const std::string& name, int id, double basic,
              double researchAllowance)
        : Staff(name, id, basic),
          researchAllowance_(researchAllowance) {}

    double pay() const override {
        return basicPay() + basicPay() * 0.42 + researchAllowance_;
    }
};

class LabAssistant : public Staff {
public:
    LabAssistant(const std::string& name, int id, double basic)
        : Staff(name, id, basic) {}

    double pay() const override {
        return basicPay() + basicPay() * 0.42;
    }
};

class GuestFaculty : public Staff {
private:
    double hours_;
    double rate_;

public:
    GuestFaculty(const std::string& name, int id,
                 double hours, double rate)
        : Staff(name, id, 0.0), hours_(hours), rate_(rate) {}

    double pay() const override {
        return hours_ * rate_;
    }
};

int main() {
    std::vector<std::unique_ptr<Staff>> payroll;
    payroll.push_back(std::make_unique<Professor>("Anita", 101, 50000, 8000));
    payroll.push_back(std::make_unique<LabAssistant>("Ravi", 102, 30000));
    payroll.push_back(std::make_unique<GuestFaculty>("Meera", 103, 40, 500));

    for (const auto& member : payroll) {
        member->display();
        std::cout << std::fixed << std::setprecision(2)
                  << member->pay() << '\n';
    }
    return 0;
}
