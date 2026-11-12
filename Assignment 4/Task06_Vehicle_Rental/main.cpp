#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class Vehicle {
    std::string registration_;
    double dailyRate_;
    bool rented_ = false;
public:
    Vehicle(std::string registration, double dailyRate)
        : registration_(std::move(registration)), dailyRate_(dailyRate) {
        if (dailyRate_ < 0) throw std::invalid_argument("daily rate cannot be negative");
    }
    virtual ~Vehicle() = default;
    virtual std::string type() const = 0;
    virtual double energyCharge() const = 0;
    virtual void printDetails() const = 0;
    const std::string& registration() const { return registration_; }
    double dailyRate() const { return dailyRate_; }
    bool rented() const { return rented_; }
    void rent() {
        if (rented_) throw std::logic_error("vehicle already rented");
        rented_ = true;
    }
    double returnVehicle(int daysUsed, int lateDays) {
        if (!rented_) throw std::logic_error("vehicle is not currently rented");
        if (daysUsed < 1 || lateDays < 0) throw std::invalid_argument("invalid rental days");
        rented_ = false;
        return daysUsed * dailyRate_ + lateDays * dailyRate_ * 1.5 + energyCharge();
    }
};

class Bicycle : public Vehicle {
public:
    Bicycle(std::string reg, double rate) : Vehicle(std::move(reg), rate) {}
    std::string type() const override { return "Bicycle"; }
    double energyCharge() const override { return 0; }
    void printDetails() const override { std::cout << type() << " " << registration() << " daily Rs." << dailyRate() << '\n'; }
};

class TwoWheeler : public Vehicle {
    double fuelLitres_;
public:
    TwoWheeler(std::string reg, double rate, double fuel)
        : Vehicle(std::move(reg), rate), fuelLitres_(fuel) {}
    std::string type() const override { return "TwoWheeler"; }
    double energyCharge() const override { return fuelLitres_ * 105.0; }
    void printDetails() const override { std::cout << type() << " " << registration() << " fuel " << fuelLitres_ << " L\n"; }
};

class Car : public Vehicle {
    int seats_;
    double fuelLitres_;
public:
    Car(std::string reg, double rate, int seats, double fuel)
        : Vehicle(std::move(reg), rate), seats_(seats), fuelLitres_(fuel) {}
    std::string type() const override { return "Car"; }
    double energyCharge() const override { return fuelLitres_ * 105.0; }
    void printDetails() const override { std::cout << type() << " " << registration() << " seats " << seats_ << '\n'; }
};

class ElectricCar : public Vehicle {
    int seats_;
    double batteryKwh_;
public:
    ElectricCar(std::string reg, double rate, int seats, double kwh)
        : Vehicle(std::move(reg), rate), seats_(seats), batteryKwh_(kwh) {}
    std::string type() const override { return "ElectricCar"; }
    double energyCharge() const override { return batteryKwh_ * 8.0; }
    void printDetails() const override { std::cout << type() << " " << registration() << " seats " << seats_ << " battery " << batteryKwh_ << " kWh\n"; }
};

// Extension: new type added without editing Vehicle or existing derived classes.
class ElectricBus : public Vehicle {
    int capacity_;
    double kwh_;
public:
    ElectricBus(std::string reg, double rate, int capacity, double kwh)
        : Vehicle(std::move(reg), rate), capacity_(capacity), kwh_(kwh) {}
    std::string type() const override { return "ElectricBus"; }
    double energyCharge() const override { return kwh_ * 8.0; }
    void printDetails() const override { std::cout << type() << " " << registration() << " capacity " << capacity_ << '\n'; }
};

int main() {
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Bicycle>("CYC-101", 100));
    fleet.push_back(std::make_unique<TwoWheeler>("TN-01-BB-2020", 350, 2));
    fleet.push_back(std::make_unique<Car>("TN-09-CC-3030", 1800, 5, 5));
    fleet.push_back(std::make_unique<ElectricCar>("TN-10-EE-4040", 2200, 5, 20));
    fleet.push_back(std::make_unique<ElectricBus>("TN-11-EB-5050", 5000, 30, 60));

    for (auto& vehicle : fleet) {
        vehicle->printDetails();
        vehicle->rent();
        const double charge = vehicle->returnVehicle(2, 1);
        std::cout << "Returned " << vehicle->registration() << " total Rs."
                  << std::fixed << std::setprecision(2) << charge << '\n';
    }
}
