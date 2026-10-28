#include "ValidationHandler.hpp"

ValidationHandler::ValidationHandler() 
    : languageManager(&LanguageManager::getInstance()), target("") {
}

bool ValidationHandler::isValid(const std::string& target, IValidation& validationObject) {
    return validationObject.evaluate(target);
}

ValidationHandler& ValidationHandler::validateThis(const std::string& target) {
    this->target = target;
    return *this;
}

ValidationHandler& ValidationHandler::with(IValidation& validationObject) {
    // Inyección contextual: se enlaza con el manejador actual
    validationObject.validationHandler = this;
    validationObject.validate(this->target);
    return *this;
}

LanguageManager* ValidationHandler::getLanguageManager() const {
    return languageManager;
}
