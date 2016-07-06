#include <ctype.h>
#include <iomanip>
#include <algorithm>
#include "tarjeta.h"
#include "usuario.h"
#include "articulo.h"

bool luhn(const Cadena& numero, size_t n);

//Definición de los métodos de la clase Numero
Numero::Numero (const Cadena& num) {
    Cadena aux = num;
    auto n1 = std::remove_if (aux.begin(), aux.end(), [](char c) { return isspace(c); });
    *n1= '\0';
    auto n2 = std::find_if (aux.begin(), aux.end(), [](char c) { return !isdigit(c); });
    if (n1 != n2) throw Numero::Incorrecto(DIGITOS);
    num_ = Cadena(aux.c_str());
    if (num_.length()<13 || num_.length()>19) throw Numero::Incorrecto(LONGITUD);
    if (!luhn (num_, num_.length())) throw Numero::Incorrecto(NO_VALIDO);
}

//Definición de los métodos de la clase Tarjeta
Tarjeta::Tarjeta (const Numero& n, Usuario& u, const Fecha& f) : numero_(n), titular_(&u), caducidad_(f), titular_facial_(titular_->nombre() + " " + titular_->apellidos()) {
    if (caducidad_ < Fecha()) throw Tarjeta::Caducada (caducidad_);
    for(auto& i : titular_facial_) i = toupper(i);
    u.es_titular_de(*this);
}
                                                                                                                                
Tarjeta::~Tarjeta() {
    if (Usuario* u = const_cast<Usuario*>(titular_)) {
        u->no_es_titular_de(*this);
    }
}

//Definición de las funciones externas
std::ostream& operator << (std::ostream& os, const Tarjeta& t) {
    os << t.numero() << std::endl;
    os << t.titular_facial() << std::endl;
    os << "Caduca: " << std::setfill('0') << std::setw(2) << t.caducidad().mes() << "/" << std::setw(2) << t.caducidad().anno()%100;
    return os;
}
