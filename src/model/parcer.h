#ifndef SRC_MODEL_PARCER_PARCER_H
#define SRC_MODEL_PARCER_PARCER_H

#include <optional>
#include <string>
#include <vector>
// #include "model.h"
#include "token.h"


namespace s21 {

class Parcer {
private:
    const std::string& input_;

public:
    Parcer(const std::string& input);
    std::optional<std::vector<Model::Token> > Run() const;


private:
    std::pair<double, std::size_t> number(std::size_t index) const;

};

}   // namespace s21

#endif  //  SRC_MODEL_PARCER_PARCER_H