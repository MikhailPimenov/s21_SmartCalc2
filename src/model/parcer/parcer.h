#ifndef SRC_MODEL_PARCER_PARCER_H
#define SRC_MODEL_PARCER_PARCER_H

#include <optional>
#include <string>
#include <vector>

#include "token.h"

namespace s21 {

/**
 * @brief Parcer
 *
 * Converts a string into tokens and adds tockens into std::vector
 * 
 * @param parameters Input parameters
 */

class Parcer {
private:
    const std::string& input_;

public:
    Parcer(const std::string& input);
    std::optional<std::vector<Model::Token> > Run() const;

};

}   // namespace s21

#endif  //  SRC_MODEL_PARCER_PARCER_H