#include "calculator.h"
#include "parcer.h"

namespace s21 {

Calculator::Calculator(const std::string& input, double x) : input_{input}, x_{x} {

}

std::optional<double> Calculator::Run() const {
    Parcer parcer(input_);
    const std::optional<std::vector<Model::Token>> tokens = parcer.Run();
    if (!tokens.has_value())
        return std::nullopt;
    

    
}


}