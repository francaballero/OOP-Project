#ifndef AUTOR_H_
#define AUTOR_H_

class Cadena;

//Declaración de la clase Autor
class Autor {
public:
    Autor (const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion);
    const Cadena& nombre() const;
    const Cadena& apellidos() const;
    const Cadena& direccion() const;
private:
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
};

//Definición de los métodos inline
inline Autor::Autor (const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion) : nombre_(nombre), apellidos_(apellidos), direccion_(direccion) {}

inline const Cadena& Autor::nombre() const {
    return nombre_;
}

inline const Cadena& Autor::apellidos() const {
    return apellidos_;
}

inline const Cadena& Autor::direccion() const {
    return direccion_;
}

#endif
