#include <iostream>
#include <memory>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

class BillingError : public std::runtime_error { public: using std::runtime_error::runtime_error; };
class ClaimError : public BillingError { public: using BillingError::BillingError; };
class UnknownPackageError : public BillingError { public: using BillingError::BillingError; };

class Bill {
protected:
    std::string patient;
    static void valid(double x) { if (x < 0) throw std::invalid_argument("negative charge"); }
public:
    explicit Bill(std::string p) : patient(std::move(p)) {}
    virtual ~Bill() noexcept = default;
    virtual double total() const = 0;
    virtual std::string type() const = 0;
    virtual void print() const { std::cout << type() << ' ' << patient << ": " << total() << '\n'; }
};
class OutPatient final : public Bill {
    double consultation, tests;
public:
    OutPatient(std::string p,double c,double t):Bill(std::move(p)),consultation(c),tests(t){valid(c);valid(t);}
    double total() const override { return consultation+tests; }
    std::string type() const override { return "OP"; }
};
class InPatient final : public Bill {
    int days; double perDay, surgery;
public:
    InPatient(std::string p,int d,double rate,double s):Bill(std::move(p)),days(d),perDay(rate),surgery(s){if(d<0)throw std::invalid_argument("negative days");valid(rate);valid(s);}
    double total() const override { return days*perDay+surgery; }
    std::string type() const override { return "IP"; }
};
class DayCareBill final : public Bill {
    double package;
public:
    DayCareBill(std::string p,double x):Bill(std::move(p)),package(x){valid(x);}
    double total() const override{return package;}
    std::string type() const override{return "DAYCARE";}
};
class EmergencyBill final : public Bill {
    double base, perHour; int hours;
public:
    EmergencyBill(std::string p,double b,int h,double r):Bill(std::move(p)),base(b),perHour(r),hours(h){valid(b);valid(r);if(h<0)throw std::invalid_argument("negative hours");}
    double total() const override{return base+hours*perHour;}
    std::string type() const override{return "EMERGENCY";}
};

class Payer {
public: virtual ~Payer() noexcept=default; virtual double amountCovered(const Bill&) const=0; virtual std::string name() const=0;
};
class SelfPay final:public Payer { public: double amountCovered(const Bill& b)const override{return 0.0;} std::string name()const override{return "SelfPay";} };
class Insurance final:public Payer {
    double limit, copay;
public:
    Insurance(double l,double c):limit(l),copay(c){if(l<0||c<0||c>100)throw std::invalid_argument("invalid insurance policy");}
    double amountCovered(const Bill& b)const override { if(b.total()>limit)throw ClaimError("exceeds cover"); return b.total()*(1.0-copay/100.0); }
    std::string name()const override{return "Insurance";}
};
class GovernmentScheme final:public Payer {
    double packageRate;
public:
    explicit GovernmentScheme(double r):packageRate(r){if(r<0)throw std::invalid_argument("negative package rate");}
    double amountCovered(const Bill& b)const override { if(b.type()!="DAYCARE")throw UnknownPackageError("unknown package for bill type"); return std::min(b.total(),packageRate); }
    std::string name()const override{return "GovernmentScheme";}
};
class CorporatePayer final:public Payer {
    double percent;
public:
    explicit CorporatePayer(double p):percent(p){if(p<0||p>100)throw std::invalid_argument("invalid corporate percentage");}
    double amountCovered(const Bill& b)const override{return b.total()*percent/100.0;}
    std::string name()const override{return "Corporate";}
};

int main(){
    std::cout<<std::fixed<<std::setprecision(2);
    std::vector<std::unique_ptr<Bill>> bills;
    bills.emplace_back(std::make_unique<OutPatient>("Ravi",500,1200));
    bills.emplace_back(std::make_unique<InPatient>("Meena",3,2500,40000));
    bills.emplace_back(std::make_unique<DayCareBill>("Arun",18000));
    bills.emplace_back(std::make_unique<EmergencyBill>("Sara",2000,3,750));
    double grand=0;
    for(const auto& b:bills){b->print();grand+=b->total();}
    std::cout<<"Grand total: "<<grand<<"\n";
    Insurance insurer(60000,20); CorporatePayer corporate(30); SelfPay self;
    std::cout<<"Insurance cover for OP: "<<insurer.amountCovered(*bills[0])<<"\n";
    std::cout<<"Corporate cover for IP: "<<corporate.amountCovered(*bills[1])<<"\n";
    std::cout<<"Self-pay cover: "<<self.amountCovered(*bills[0])<<"\n";
    try { Insurance small(1000,10); (void)small.amountCovered(*bills[0]); }
    catch(const ClaimError& e){std::cout<<"Claim rejected: "<<e.what()<<"\n";}
    try { OutPatient bad("Bad",-1,20); }
    catch(const std::invalid_argument& e){std::cout<<"Invalid bill: "<<e.what()<<"\n";}
}
