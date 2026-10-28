#include "Email.hpp"
#include "ValidationHandler.hpp"
#include "LanguageManager.hpp"
#include <regex>
#include <stdexcept>

Email::Email(const std::string& messageName) : messageName(messageName) {
}

void Email::setMessageName(const std::string& name) {
    this->messageName = name;
}

std::string Email::getMessageName() const {
    return this->messageName;
}

bool Email::evaluate(const std::string& target) {
    if (target.empty()) {
        return false;
    }
    // Expresión regular equivalente a la del código JS
    // [a-z0-9][a-z0-9_\.-]*[a-z0-9]@[a-z0-9][a-z0-9_\.-]*[a-z0-9]\.[a-z0-9]{2,4}
    static const std::regex emailRegex(
        R"(^[a-zA-Z0-9][a-zA-Z0-9_\.-]*[a-zA-Z0-9]@[a-zA-Z0-9][a-zA-Z0-9_\.-]*[a-zA-Z0-9]\.[a-zA-Z0-9]{2,4}$)"
    );
    return std::regex_match(target, emailRegex);
}

void Email::validate(const std::string& target) {
    if (!evaluate(target)) {
        std::string message;
        // Se obtiene el LanguageManager a través del ValidationHandler (o de la instancia Singleton)
        if (validationHandler && validationHandler->getLanguageManager()) {
            message = validationHandler->getLanguageManager()->getThisMessage(messageName);
        } else {
            message = LanguageManager::getInstance().getThisMessage(messageName);
        }
        throw std::runtime_error(message + ": " + target);
    }
}
