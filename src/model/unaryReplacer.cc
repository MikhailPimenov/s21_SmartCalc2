#include "unaryReplacer.h"

namespace s21 {

UnaryReplacer::UnaryReplacer(const std::vector<Model::Token>& input) : input_{input} {}

std::vector<Model::Token> UnaryReplacer::Run() const {
  std::vector<Model::Token> result;
  result.reserve(4ull * input_.size());

  if (!input_.front().isUnaryLeftFunction()) {
    result.push_back(input_.front());
  } else if (input_.front().type_ == Model::Type::Minus) {
    result.emplace_back( 0.0, Model::Type::OpenBracket,   0);
    result.emplace_back(-1.0, Model::Type::Number,        1);
    result.emplace_back( 0.0, Model::Type::CloseBracket,  0);
    result.emplace_back( 0.0, Model::Type::Mult,          8);
  }

  for (int i = 1; i < input_.size(); ++i) {
    if (input_[i].type_ == Model::Type::Sum && input_[i - 1].isOpeningBrace())
      continue;

    if (input_[i].type_ == Model::Type::Minus && input_[i - 1].isOpeningBrace()) {
      result.emplace_back( 0.0, Model::Type::OpenBracket,   0);
      result.emplace_back(-1.0, Model::Type::Number,        1);
      result.emplace_back( 0.0, Model::Type::CloseBracket,  0);
      result.emplace_back( 0.0, Model::Type::Mult,          8);
      continue;
    }
    result.push_back(input_[i]);
  }

  return result;
}

}   // namespace s21