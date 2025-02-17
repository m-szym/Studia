#include <iostream>
//#include "Vektor3d.h"
#include "Vector.h"
#include "Envelope.h"

using namespace std;

/*std::ostream& operator<<(std::ostream& ostr, const Vektor3d& v) {
    ostr << "Vector3d{"; for(std::size_t i = 0; i < 3; i++) {
        if(i > 0)
            ostr << ',';
        ostr << v[i];
    }
    ostr << '}';
    return ostr;
}*/

std::ostream& operator<<(std::ostream& ostr, const Vector& v){ ostr << "Vector{";
    for(std::size_t i = 0; i < v.GetSize(); i++)
    {
        if(i > 0)
            ostr << ',';
        ostr << v[i];
    }
    ostr << '}';
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const Envelope& e) {
    ostr << "Envelope{vector: " << e.vector << '}';
    return ostr;
}

    int main() {
        std::cout << "Konstruktor z r-referencją" << std::endl;
        Envelope e1{Vector{1,2,3}};
        std::cout << "e1: " << e1 << std::endl;

        std::cout << "Konstrukor przenoszący" << std::endl;
        Envelope e2 = std::move(e1);
        std::cout << "e1: " << e1 << std::endl;
        std::cout << "e2: " << e2 << std::endl;
        std::cout << "Przenoszący operator przypisania" << std::endl; e1 = std::move(e2);
        std::cout << "e1: " << e1 << std::endl;
        std::cout << "e2: " << e2 << std::endl;
        std::cout << "operator przypisania copy-swap początek" << std::endl;
        e2 = e1;
        std::cout << "operator przypisania copy-swap koniec" << std::endl;
        std::cout << "e1: " << e1 << std::endl;
        std::cout << "e2: " << e2 << std::endl;

        return 0;
}
