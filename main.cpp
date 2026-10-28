#include <iostream>
#include "ValidationHandler.hpp"
#include "Email.hpp"
#include "LanguageManager.hpp"

int main() {
    std::cout << "====================================================\n";
    std::cout << "  DEMO: ValidationHandler + Strategy + Singleton    \n";
    std::cout << "====================================================\n\n";

    ValidationHandler validator;
    Email emailValidator;

    // ----------------------------------------------------
    // Caso 1: Uso directo con isValid (devuelve booleano)
    // ----------------------------------------------------
    std::cout << "--- 1. Evaluacion booleana con isValid() ---\n";
    std::string testEmail1 = "usuario@empresa.com";
    std::string testEmail2 = "correo_invalido_sin_arroba";

    std::cout << "Evaluar '" << testEmail1 << "': " 
              << (validator.isValid(testEmail1, emailValidator) ? "VALIDO [OK]" : "INVALIDO [FAIL]") 
              << "\n";
    std::cout << "Evaluar '" << testEmail2 << "': " 
              << (validator.isValid(testEmail2, emailValidator) ? "VALIDO [OK]" : "INVALIDO [FAIL]") 
              << "\n\n";

    // ----------------------------------------------------
    // Caso 2: Fluent Interface con validateThis().with() (Correo Valido)
    // ----------------------------------------------------
    std::cout << "--- 2. Fluent Interface con correo valido ---\n";
    try {
        validator.validateThis("contacto@ejemplo.com").with(emailValidator);
        std::cout << "[OK] 'contacto@ejemplo.com' paso la validacion sin excepciones.\n\n";
    } catch (const std::exception& e) {
        std::cout << "[FAIL] Error inesperado: " << e.what() << "\n\n";
    }

    // ----------------------------------------------------
    // Caso 3: Validacion fallida con mensaje en Espanol (es)
    // ----------------------------------------------------
    std::cout << "--- 3. Excepcion en Espanol (Idioma actual: " 
              << LanguageManager::getInstance().getLanguage() << ") ---\n";
    try {
        validator.validateThis("correo_invalido").with(emailValidator);
    } catch (const std::exception& e) {
        std::cout << "[EXCEPCION CAPTURADA]: " << e.what() << "\n\n";
    }

    // ----------------------------------------------------
    // Caso 4: Cambio de idioma a Ingles (en) y validacion fallida
    // ----------------------------------------------------
    std::cout << "--- 4. Cambiando idioma a 'en' (Ingles) ---\n";
    LanguageManager::getInstance().setLanguage("en");
    std::cout << "Idioma actual: " << LanguageManager::getInstance().getLanguage() << "\n";

    try {
        validator.validateThis("bad_email_format").with(emailValidator);
    } catch (const std::exception& e) {
        std::cout << "[EXCEPCION CAPTURADA]: " << e.what() << "\n\n";
    }

    std::cout << "====================================================\n";
    std::cout << "  Ejecucion finalizada con exito                    \n";
    std::cout << "====================================================\n";

    return 0;
}
