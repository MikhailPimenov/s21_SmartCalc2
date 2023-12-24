#ifndef SRC_MODEL_UNARYREPLACER_H
#define SRC_MODEL_UNARYREPLACER_H

#include <optional>
#include <vector>
// #include "model.h"
#include "token.h"

namespace s21 {

/**
 * @brief Unary Replacer
 *
 * Defins the sign of a number in brackets
 *
 * @param input_ Input parameters
 */

class UnaryReplacer {
 private:
  const std::vector<Model::Token>& input_;

 public:
  UnaryReplacer(const std::vector<Model::Token>& input);
  std::vector<Model::Token> Run() const;
};

}  // namespace s21

#endif  //  SRC_MODEL_UNARYREPLACER_H