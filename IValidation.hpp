#ifndef IVALIDATION_HPP
#define IVALIDATION_HPP

#include <string>

// Declaración adelantada (Forward declaration) para evitar dependencia circular
class ValidationHandler;

/**
 * Interfaz Strategy (Estrategia)
 * Define los métodos comunes para todos los algoritmos de validación.
 */
class IValidation {
public:
    ValidationHandler* validationHandler = nullptr;

    virtual ~IValidation() = default;

    // Evalúa si el objetivo cumple la regla (retorna booleano)
    virtual bool evaluate(const std::string& target) = 0;

    // Valida y lanza excepción con mensaje internacionalizado si falla
    virtual void validate(const std::string& target) = 0;
};

#endif // IVALIDATION_HPP
