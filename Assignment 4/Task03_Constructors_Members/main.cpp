#include <iostream>
#include <string>

class Address {
    std::string city_;
    int pin_;
public:
    Address(std::string city, int pin) : city_(std::move(city)), pin_(pin) {
        std::cout << "Address constructed\n";
    }
    ~Address() { std::cout << "Address destroyed\n"; }
    std::string str() const { return city_ + "-" + std::to_string(pin_); }
};

class Person {
protected:
    std::string name_;
    int age_;
    Address address_;
public:
    Person(std::string name, int age, std::string city, int pin)
        : name_(std::move(name)), age_(age), address_(std::move(city), pin) {
        std::cout << "Person constructed\n";
    }
    virtual ~Person() { std::cout << "Person destroyed\n"; }
};

class Course {
    std::string code_;
public:
    explicit Course(std::string code) : code_(std::move(code)) {
        std::cout << "Course constructed\n";
    }
    ~Course() { std::cout << "Course destroyed\n"; }
    const std::string& code() const { return code_; }
};

class Student : virtual public Person {
    long long regNo_;
    Course course_;
public:
    Student(std::string name, int age, std::string city, int pin,
            long long regNo, std::string course)
        : Person(std::move(name), age, std::move(city), pin),
          regNo_(regNo), course_(std::move(course)) {
        std::cout << "Student constructed\n";
    }
    ~Student() override { std::cout << "Student destroyed\n"; }
};

class Staff : virtual public Person {
    std::string department_;
public:
    Staff(std::string name, int age, std::string city, int pin, std::string department)
        : Person(std::move(name), age, std::move(city), pin), department_(std::move(department)) {
        std::cout << "Staff constructed\n";
    }
    ~Staff() override { std::cout << "Staff destroyed\n"; }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(std::string name, int age, std::string city, int pin,
                      long long regNo, std::string course, std::string department)
        : Person(name, age, city, pin),
          Student(name, age, city, pin, regNo, course),
          Staff(name, age, city, pin, department) {
        std::cout << "TeachingAssistant constructed\n";
    }
    ~TeachingAssistant() override { std::cout << "TeachingAssistant destroyed\n"; }
};

int main() {
    std::cout << "-- Student lifetime --\n";
    { Student s("Kavya", 19, "Salem", 636001, 192311001, "DSA01"); }
    std::cout << "-- Staff lifetime --\n";
    { Staff t("Ravi", 42, "Chennai", 600001, "IT"); }
    std::cout << "-- TeachingAssistant lifetime (virtual diamond) --\n";
    { TeachingAssistant ta("Mira", 21, "Madurai", 625001, 192311003, "DSA01", "IT"); }
}
