#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Staff {
protected:
    std::string name_;
    int id_;
    double basic_;
public:
    Staff(std::string name, int id, double basic)
        : name_(std::move(name)), id_(id), basic_(basic) {
        if (basic_ < 0) throw std::invalid_argument("basic salary cannot be negative");
    }
    virtual ~Staff() = default;
    virtual double pay() const = 0;
    virtual std::string category() const = 0;
    void print() const {
        std::cout << category() << " | " << name_ << " | " << id_
                  << " | Rs." << std::fixed << std::setprecision(2) << pay() << '\n';
    }
};

class Professor : public Staff {
    double research_;
public:
    Professor(std::string n, int id, double basic, double research)
        : Staff(std::move(n), id, basic), research_(research) {
        if (research_ < 0) throw std::invalid_argument("research allowance cannot be negative");
    }
    double pay() const override { return basic_ * 1.42 + research_; }
    std::string category() const override { return "Professor"; }
};

class LabAssistant : public Staff {
public:
    using Staff::Staff;
    double pay() const override { return basic_ * 1.42; }
    std::string category() const override { return "LabAssistant"; }
};

class GuestFaculty : public Staff {
    double hours_, rate_;
public:
    GuestFaculty(std::string n, int id, double hours, double rate)
        : Staff(std::move(n), id, 0), hours_(hours), rate_(rate) {
        if (hours_ < 0 || rate_ < 0) throw std::invalid_argument("hours and rate must be non-negative");
    }
    double pay() const override { return hours_ * rate_; }
    std::string category() const override { return "GuestFaculty"; }
};

class ResearchFellow : public Staff {
    double fellowship_;
public:
    ResearchFellow(std::string n, int id, double fellowship)
        : Staff(std::move(n), id, 0), fellowship_(fellowship) {
        if (fellowship_ < 0) throw std::invalid_argument("fellowship cannot be negative");
    }
    double pay() const override { return fellowship_; }
    std::string category() const override { return "ResearchFellow"; }
};

int main() {
    std::vector<std::unique_ptr<Staff>> payroll;
    payroll.push_back(std::make_unique<Professor>("Anita", 101, 50000, 8000));
    payroll.push_back(std::make_unique<LabAssistant>("Bala", 102, 30000));
    payroll.push_back(std::make_unique<GuestFaculty>("Charan", 103, 20, 900));
    payroll.push_back(std::make_unique<ResearchFellow>("Divya", 104, 25000));
    double total = 0;
    for (const auto& person : payroll) { person->print(); total += person->pay(); }
    std::cout << "Payroll total | Rs." << std::fixed << std::setprecision(2) << total << '\n';
}
