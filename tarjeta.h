#ifndef TARJETA_H_
#define TARJETA_H_

#include <iostream>
#include "../P1/Fecha/fecha.h"
#include "../P1/Cadena/cadena.h"

class Usuario;

//Declaración de la clase Numero
class Numero {
public:
    enum Razon { LONGITUD, DIGITOS, NO_VALIDO };
    class Incorrecto {
        Razon r_;
    public:
        Incorrecto (const Razon& r) : r_(r) {}
        Razon razon() const { return r_; }
    };
    Numero (const Cadena& num);
    operator const char* () const;
private:
    Cadena num_;
};

//Declaración de la clase Tarjeta
class Tarjeta {
public:
    class Caducada {
        Fecha caducidad_;
    public:
        Caducada (const Fecha&);
        Fecha cuando() const;
    };
    Tarjeta (const Numero& n, Usuario& u, const Fecha& f);
    Tarjeta (const Tarjeta&) = delete;
    Tarjeta& operator = (const Tarjeta&) = delete;
    Numero numero() const;
    Fecha caducidad() const;
    Cadena titular_facial() const;
    const Usuario* titular() const;
    void anula_titular();
    ~Tarjeta();
private:
    Numero numero_;
    const Usuario* titular_;
    Fecha caducidad_;
    Cadena titular_facial_;
};

//Declaración de las funciones externas
std::ostream& operator << (std::ostream&, const Tarjeta&);
bool operator < (const Tarjeta& t1, const Tarjeta& t2);

//Definición de los métodos inline de la clase Numero
inline Numero::operator const char* () const {
    return num_.c_str();
}

//Definición de los métodos inline de la clase Tarjeta
inline Tarjeta::Caducada::Caducada (const Fecha& f) : caducidad_(f) {}

inline Fecha Tarjeta::Caducada::cuando () const {
    return caducidad_;
}

inline Numero Tarjeta::numero() const {
    return numero_;
}

inline Fecha Tarjeta::caducidad() const {
    return caducidad_;
}

inline Cadena Tarjeta::titular_facial() const {
    return titular_facial_;
}

inline const Usuario* Tarjeta::titular() const {
    return titular_;
}

inline void Tarjeta::anula_titular() {
    titular_ = nullptr;
}

//Definición de las funciones externas inline
inline bool operator < (const Numero& n1, const Numero& n2) {
    return std::strcmp(n1, n2) < 0;
}

inline bool operator < (const Tarjeta& t1, const Tarjeta& t2) {
    return t1.numero() < t2.numero();
}

#endif
