#ifndef VALIDATION_HANDLER_HPP
#define VALIDATION_HANDLER_HPP

#include <string>
#include "LanguageManager.hpp"
#include "IValidation.hpp"

/**
 * Contexto del Patrón Strategy
 * Maneja el flujo de validaciones y delega la ejecución en los objetos IValidation.
 */
class ValidationHandler {
private:
    LanguageManager* languageManager;
    std::string target;

public:
    ValidationHandler();

    // Retorna true o false directamente delegando en validationObject.evaluate()
    bool isValid(const std::string& target, IValidation& validationObject);

    // Guarda el objetivo para encadenar llamadas (Fluent Interface)
    ValidationHandler& validateThis(const std::string& target);

    // Conecta el validador, inyecta la referencia (Visitor / Inyección) y ejecuta la validación
    ValidationHandler& with(IValidation& validationObject);

    LanguageManager* getLanguageManager() const;
};

#endif // VALIDATION_HANDLER_HPP
