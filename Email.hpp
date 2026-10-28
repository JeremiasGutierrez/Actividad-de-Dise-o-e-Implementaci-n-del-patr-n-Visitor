#ifndef EMAIL_HPP
#define EMAIL_HPP

#include <string>
#include "IValidation.hpp"

/**
 * Estrategia Concreta (Concrete Strategy)
 * Implementa la validación específica para formato de correo electrónico.
 */
class Email : public IValidation {
private:
    std::string messageName;

public:
    Email(const std::string& messageName = "CT_INVALID_EMAIL");

    void setMessageName(const std::string& name);
    std::string getMessageName() const;

    bool evaluate(const std::string& target) override;
    void validate(const std::string& target) override;
};

#endif // EMAIL_HPP
