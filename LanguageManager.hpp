#ifndef LANGUAGE_MANAGER_HPP
#define LANGUAGE_MANAGER_HPP

#include <string>
#include <unordered_map>
#include <stdexcept>
#include <iostream>

/**
 * Patrón Singleton (según Refactoring Guru)
 * Garantiza una única instancia y acceso global a los recursos de idiomas.
 */
class LanguageManager {
private:
    std::string currentLanguage;
    // Mapa: [idioma][clave] -> mensaje
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> resources;

    // Constructor privado para evitar instanciación directa
    LanguageManager();

    // Eliminar constructor de copia y operador de asignación
    LanguageManager(const LanguageManager&) = delete;
    LanguageManager& operator=(const LanguageManager&) = delete;

    void loadLocales();

public:
    // Punto de acceso global (Meyers' Singleton, seguro para hilos)
    static LanguageManager& getInstance();

    void setLanguage(const std::string& lang);
    std::string getLanguage() const;

    // Obtiene el mensaje traducido según la clave
    std::string getThisMessage(const std::string& messageName) const;
};

#endif // LANGUAGE_MANAGER_HPP
