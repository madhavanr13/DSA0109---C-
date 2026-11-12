#include <iostream>
#include <string>

class Person {
protected:
    std::string name_;
    int id_;
    std::string phone_;
public:
    Person(std::string name, int id, std::string phone)
        : name_(std::move(name)), id_(id), phone_(std::move(phone)) {
        std::cout << "Person constructed\n";
    }
    virtual ~Person() = default;
    void printPerson() const { std::cout << name_ << " | " << id_ << " | " << phone_; }
};

class Student : virtual public Person {
protected:
    std::string programme_;
    double cgpa_;
public:
    Student(std::string n, int id, std::string ph, std::string prog, double cgpa)
        : Person(std::move(n), id, std::move(ph)), programme_(std::move(prog)), cgpa_(cgpa) {
        std::cout << "Student constructed\n";
    }
};

class Staff : virtual public Person {
protected:
    std::string department_;
    double salary_;
public:
    Staff(std::string n, int id, std::string ph, std::string dept, double salary)
        : Person(std::move(n), id, std::move(ph)), department_(std::move(dept)), salary_(salary) {
        std::cout << "Staff constructed\n";
    }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(std::string n, int id, std::string ph, std::string prog,
                      double cgpa, std::string dept, double salary)
        : Person(std::move(n), id, std::move(ph)),
          Student(name_, id_, phone_, std::move(prog), cgpa),
          Staff(name_, id_, phone_, std::move(dept), salary) {
        std::cout << "TeachingAssistant constructed\n";
    }
    void print() const {
        printPerson();
        std::cout << " | " << programme_ << " | CGPA " << cgpa_
                  << " | " << department_ << " | Rs." << salary_ << '\n';
    }
};

class ResearchScholar : public Student {
    double fellowship_;
public:
    ResearchScholar(std::string n, int id, std::string ph, std::string prog,
                    double cgpa, double fellowship)
        : Person(std::move(n), id, std::move(ph)),
          Student(name_, id_, phone_, std::move(prog), cgpa), fellowship_(fellowship) {}
    void print() const {
        printPerson(); std::cout << " | " << programme_ << " | fellowship Rs." << fellowship_ << '\n';
    }
};

int main() {
    TeachingAssistant ta("Kavya", 192311001, "9876543210", "B.Tech IT", 8.7, "IT", 24000);
    ta.print();
    ResearchScholar scholar("Arun", 192311002, "9876500000", "M.Tech", 9.1, 18000);
    scholar.print();
}
