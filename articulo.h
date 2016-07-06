#ifndef ARTICULO_H_
#define ARTICULO_H_

#include <iostream>
#include <set>
#include "cadena.h"
#include "fecha.h"

class Autor;

//Declaración de la clase Articulo
class Articulo {
public:
    class Autores_vacios {};
    typedef std::set<Autor*> Autores;
    Articulo (const Autores&, const Cadena&, const Cadena&, const Fecha&, double);
    const Autores& autores() const;
    Cadena referencia() const;
    Cadena titulo() const;
    Fecha f_publi() const;
    double precio() const;
    double& precio();
    virtual void imp_esp (std::ostream&) const = 0;
    virtual ~Articulo();
private:
    Autores autores_;
    Cadena referencia_;
    Cadena titulo_;
    Fecha f_publi_;
    double precio_;
};

//Declaración de la clase ArticuloAlmacenable
class ArticuloAlmacenable : public Articulo {
public:
    ArticuloAlmacenable (const Autores&, const Cadena&, const Cadena&, const Fecha&, double, unsigned);
    unsigned& stock ();
    unsigned stock () const;
    virtual ~ArticuloAlmacenable();
private:
    unsigned stock_;
};

//Declaración de la clase Libro
class Libro : public ArticuloAlmacenable {
public:
    Libro (const Autores&, const Cadena&, const Cadena&, const Fecha&, double, unsigned, unsigned);
    unsigned n_pag() const;
    void imp_esp (std::ostream&) const;
    ~Libro();
private:
    const unsigned n_pag_;
};

//Declaración de la clase Cederron
class Cederron : public ArticuloAlmacenable {
public:
    Cederron (const Autores&, const Cadena&, const Cadena&, const Fecha&, double, unsigned, unsigned);
    double tam() const;
    void imp_esp (std::ostream&) const;
    ~Cederron();
private:
    const unsigned tam_;
};

//Declaración de la clase LibroDigital
class LibroDigital : public Articulo {
public:
    LibroDigital (const Autores&, const Cadena&, const Cadena&, const Fecha&, double, const Fecha&);
    const Fecha& f_expir() const;
    void imp_esp (std::ostream&) const;
    ~LibroDigital();
private:
    Fecha f_expir_;
};

//Declaración de las funciones externas
std::ostream& operator << (std::ostream&, const Articulo&);

//Definición de los métodos inline
inline const Articulo::Autores& Articulo::autores() const {
    return autores_;
}

inline Cadena Articulo::referencia() const {
    return referencia_;
}

inline Cadena Articulo::titulo() const {
    return titulo_;
}

inline Fecha Articulo::f_publi() const {
    return f_publi_;
}

inline double Articulo::precio() const {
    return precio_;
}

inline double& Articulo::precio() {
    return precio_;
}

inline Articulo::~Articulo() {}

inline unsigned& ArticuloAlmacenable::stock () {
    return stock_;
}

inline unsigned ArticuloAlmacenable::stock () const {
    return stock_;
}

inline ArticuloAlmacenable::~ArticuloAlmacenable() {}

inline void Libro::imp_esp (std::ostream& os) const {
    os << "\t" << n_pag_ << " págs., " << stock() << " unidades.";
}

inline unsigned Libro::n_pag() const {
    return n_pag_;
}

inline Libro::~Libro() {}

inline void Cederron::imp_esp (std::ostream& os) const {
    os << "\t" << tam_ << " MB, " << stock() << " unidades.";
}

inline double Cederron::tam() const {
    return tam_;
}

inline Cederron::~Cederron() {}

inline void LibroDigital::imp_esp (std::ostream& os) const {
    os << "\tA la venta hasta el " << f_expir_ <<".";
}

inline const Fecha& LibroDigital::f_expir() const {
    return f_expir_;
}

inline LibroDigital::~LibroDigital() {}

#endif
