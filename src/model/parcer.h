#ifndef SRC_MODEL_PARCER_PARCER_H
#define SRC_MODEL_PARCER_PARCER_H

#include <optional>
#include "model.h"

namespace s21 {

class Parcer {
private:
    const std::string& input_;

public:
    Parcer(const std::string& input);
    std::optional<std::vector<Model::Token> > Run() const;


private:
    std::pair<double, int> number(int index) const;

};

}   // namespace s21

#endif  //  SRC_MODEL_PARCER_PARCER_H