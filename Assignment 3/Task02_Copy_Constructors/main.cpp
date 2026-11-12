#include <chrono>
#include <iostream>
#include <string>
#include <vector>

class Prescription {
    int n{};
    std::string* medicines{};
public:
    explicit Prescription(int count) : n(count), medicines(count > 0 ? new std::string[count] : nullptr) {
        if (count < 0) throw std::invalid_argument("negative medicine count");
    }
    Prescription(const Prescription& other) : n(other.n), medicines(n ? new std::string[n] : nullptr) {
        for (int i=0; i<n; ++i) medicines[i]=other.medicines[i];
        std::cout << "[deep copy] ";
    }
    Prescription& operator=(const Prescription& other) {
        if (this != &other) {
            std::string* fresh = other.n ? new std::string[other.n] : nullptr;
            for (int i=0; i<other.n; ++i) fresh[i]=other.medicines[i];
            delete[] medicines; medicines=fresh; n=other.n;
        }
        return *this;
    }
    ~Prescription() { delete[] medicines; }
    void set(int i,const std::string& m) { if(i<0||i>=n) throw std::out_of_range("medicine index"); medicines[i]=m; }
    std::string get(int i) const { if(i<0||i>=n) throw std::out_of_range("medicine index"); return medicines[i]; }
    int size() const { return n; }
};
void byValue(Prescription p) { (void)p; }
void byReference(const Prescription& p) { (void)p; }
int main() {
    Prescription p(2); p.set(0,"Paracetamol"); p.set(1,"ORS");
    Prescription q=p; q.set(1,"Cetirizine");
    Prescription r(1); r=p; p.set(0,"Ibuprofen"); r=r;
    std::cout << p.get(0)<<' '<<p.get(1)<<" | "<<q.get(0)<<' '<<q.get(1)<<" | "<<r.get(0)<<' '<<r.get(1)<<'\n';
    byValue(p); byReference(p);
    for(int n : {10,1000,100000}) {
        Prescription source(n); auto start=std::chrono::steady_clock::now();
        for(int k=0;k<10;++k) { Prescription copy(source); (void)copy; }
        auto us=std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()-start).count();
        std::cout << "10 deep copies of "<<n<<" medicines: "<<us<<" us\n";
    }
}
