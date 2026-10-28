#include "LanguageManager.hpp"

LanguageManager::LanguageManager() : currentLanguage("es") {
    loadLocales();
}

void LanguageManager::loadLocales() {
    // Recursos en español (es.json)
    resources["es"]["CT_INVALID_EMAIL"] = "El formato de correo electrónico no es válido";
    resources["es"]["CT_INVALID_RESOURCE_CONSTANT"] = "Recurso de lenguaje inválido o clave inexistente";

    // Recursos en inglés (en.json)
    resources["en"]["CT_INVALID_EMAIL"] = "Invalid email address format";
    resources["en"]["CT_INVALID_RESOURCE_CONSTANT"] = "Invalid language resource or missing key";
}

LanguageManager& LanguageManager::getInstance() {
    // En C++11 en adelante, la inicialización de variables locales estáticas es thread-safe
    static LanguageManager instance;
    return instance;
}

void LanguageManager::setLanguage(const std::string& lang) {
    if (resources.find(lang) != resources.end()) {
        currentLanguage = lang;
    } else {
        std::cerr << "⚠️ Idioma '" << lang << "' no soportado. Se mantiene '" << currentLanguage << "'." << std::endl;
    }
}

std::string LanguageManager::getLanguage() const {
    return currentLanguage;
}

std::string LanguageManager::getThisMessage(const std::string& messageName) const {
    // Buscar idioma actual, fallback a 'es'
    auto langIt = resources.find(currentLanguage);
    if (langIt == resources.end()) {
        langIt = resources.find("es");
    }

    if (langIt != resources.end()) {
        auto msgIt = langIt->second.find(messageName);
        if (msgIt != langIt->second.end()) {
            return msgIt->second;
        }
    }

    // Manejo de error con fallback igual que en JavaScript
    auto fallbackLang = resources.find("es");
    std::string fallbackMsg = "Clave de recurso no encontrada";
    if (fallbackLang != resources.end()) {
        auto fbMsgIt = fallbackLang->second.find("CT_INVALID_RESOURCE_CONSTANT");
        if (fbMsgIt != fallbackLang->second.end()) {
            fallbackMsg = fbMsgIt->second;
        }
    }

    throw std::runtime_error(fallbackMsg + ". La clave '" + messageName + "' no existe en '" + currentLanguage + "'.");
}
