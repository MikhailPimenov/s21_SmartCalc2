#include "parcer.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <array>

namespace s21 {

class ParcerBase {
public:
public:
  virtual bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const = 0;
  virtual ~ParcerBase() {}
};
//================================================================================================================
class ParcerOpenBracket : public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerOpenBracket::Run(std::vector<Model::Token>& tokens, 
                            const std::string& string,
                            std::size_t& s) const {
  if (string[s] != '(')
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::OpenBracket, 0));
  ++s;
  return true;
}
//================================================================================================================
class ParcerCloseBracket : public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerCloseBracket::Run(std::vector<Model::Token>& tokens, 
                            const std::string& string,
                            std::size_t& s) const {
  if (string[s] != ')')
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::CloseBracket, 0));
  ++s;
  return true;
}
//================================================================================================================
class ParcerSum : public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerSum::Run(std::vector<Model::Token>& tokens, 
                    const std::string& string,
                    std::size_t& s) const {
  if (string[s] != '+')
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::Sum, 6));
  ++s;
  return true;
}
//================================================================================================================
class ParcerMinus : public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerMinus::Run(std::vector<Model::Token>& tokens, 
                      const std::string& string,
                      std::size_t& s) const {
  if (string[s] != '-')
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::Minus, 6));
  ++s;
  return true;
}
//================================================================================================================
class ParcerDivision : public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerDivision::Run(std::vector<Model::Token>& tokens, 
                         const std::string& string,
                         std::size_t& s) const {
  if (string[s] != '/')
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::Div, 8));
  ++s;
  return true;
}
//================================================================================================================
class ParcerMultiplication : public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerMultiplication::Run(std::vector<Model::Token>& tokens, 
                         const std::string& string,
                         std::size_t& s) const {
  if (string[s] != '*')
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::Mult, 8));
  ++s;
  return true;
}
//================================================================================================================
class ParcerPower : public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerPower::Run(std::vector<Model::Token>& tokens, 
                         const std::string& string,
                         std::size_t& s) const {
  if (string[s] != '^')
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::Power, 9));
  ++s;
  return true;
}
//================================================================================================================
class ParcerPlaceholderX : public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerPlaceholderX::Run(std::vector<Model::Token>& tokens, 
                         const std::string& string,
                         std::size_t& s) const {
  if (string[s] != 'x')
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::X, 1));
  ++s;
  return true;
}
//================================================================================================================
class ParcerCos : public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerCos::Run(std::vector<Model::Token>& tokens, 
                         const std::string& string,
                         std::size_t& s) const {
  if (0 != string.compare(s, 3, "cos"))
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::Cos, 8));
  s += 3;
  return true;
}
//================================================================================================================
class ParcerSin : public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerSin::Run(std::vector<Model::Token>& tokens, 
                         const std::string& string,
                         std::size_t& s) const {
  if (0 != string.compare(s, 3, "sin"))
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::Sin, 8));
  s += 3;
  return true;
}
//================================================================================================================
class ParcerMod : public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerMod::Run(std::vector<Model::Token>& tokens, 
                         const std::string& string,
                         std::size_t& s) const {
  if (0 != string.compare(s, 3, "mod"))
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::Mod, 8));
  s += 3;
  return true;
}
//================================================================================================================
class ParcerTan : public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerTan::Run(std::vector<Model::Token>& tokens, 
                         const std::string& string,
                         std::size_t& s) const {
  if (0 != string.compare(s, 3, "tan"))
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::Tan, 8));
  s += 3;
  return true;
}
//================================================================================================================
class ParcerAcos : public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerAcos::Run(std::vector<Model::Token>& tokens, 
                         const std::string& string,
                         std::size_t& s) const {
  if (0 != string.compare(s, 4, "acos"))
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::Acos, 8));
  s += 4;
  return true;
}
//================================================================================================================
class ParcerAsin: public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerAsin::Run(std::vector<Model::Token>& tokens, 
                         const std::string& string,
                         std::size_t& s) const {
  if (0 != string.compare(s, 4, "asin"))
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::Asin, 8));
  s += 4;
  return true;
}
//================================================================================================================
class ParcerAtan: public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerAtan::Run(std::vector<Model::Token>& tokens, 
                         const std::string& string,
                         std::size_t& s) const {
  if (0 != string.compare(s, 4, "atan"))
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::Atan, 8));
  s += 4;
  return true;
}
//================================================================================================================
class ParcerSquareRoot: public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerSquareRoot::Run(std::vector<Model::Token>& tokens, 
                         const std::string& string,
                         std::size_t& s) const {
  if (0 != string.compare(s, 4, "sqrt"))
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::Sqrt, 8));
  s += 4;
  return true;
}
//================================================================================================================
class ParcerLn: public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerLn::Run(std::vector<Model::Token>& tokens, 
                         const std::string& string,
                         std::size_t& s) const {
  if (0 != string.compare(s, 2, "ln"))
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::Ln, 8));
  s += 2;
  return true;
}
//================================================================================================================
class ParcerLog: public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;
};
bool ParcerLog::Run(std::vector<Model::Token>& tokens, 
                         const std::string& string,
                         std::size_t& s) const {
  if (0 != string.compare(s, 3, "log"))
    return false;

  tokens.push_back(Model::Token(0.0, Model::Type::Log, 8));
  s += 3;
  return true;
}
//================================================================================================================
class ParcerNumber: public ParcerBase {
public:
  bool Run(std::vector<Model::Token>& tokens, const std::string& string, std::size_t& s) const override;

private:
  std::pair<double, std::size_t> number(const std::string& string, std::size_t s) const;
};

bool ParcerNumber::Run(std::vector<Model::Token>& tokens, 
                         const std::string& string,
                         std::size_t& s) const {
  if (const auto& [n, shifted_s] = number(string, s); shifted_s > s) {
    tokens.push_back(Model::Token(n, Model::Type::Number, 1));
    // s = (shifted_s - 1);
    s = (shifted_s);  // or  s = (shifted_s - 1) ???
    return true; 
  }
  return false;
}
std::pair<double, std::size_t> ParcerNumber::number(const std::string& string, std::size_t s) const {
  if (string[s] == '.')
    return std::make_pair(0.0, s);

  std::istringstream iss(string);
  iss.seekg(s);
  double result = 0.0;
  iss >> result;

  if (iss.eof())
    s = static_cast<int>(string.size());
  else if (!iss.fail())
    s = static_cast<int>(iss.tellg());

  return std::make_pair(result, s);
}

// static initParcers() {
  static ParcerOpenBracket                 p1;
  static ParcerCloseBracket                p2;
  static ParcerSum                         p3;
  static ParcerMinus                       p4;
  static ParcerDivision                    p5;
  static ParcerMultiplication              p6;
  static ParcerPower                       p7;
  static ParcerPlaceholderX                p8;
  static ParcerCos                         p9;
  static ParcerSin                        p10;
  static ParcerMod                        p11;
  static ParcerTan                        p12;
  static ParcerAcos                       p13;
  static ParcerAsin                       p14;
  static ParcerAtan                       p15;
  static ParcerSquareRoot                 p16;
  static ParcerLn                         p17;
  static ParcerLog                        p18; 
  static ParcerNumber                     p19;
// }

static std::array<ParcerBase*, 19> s_parcers {
  &p1,
  &p2,
  &p3,
  &p4,
  &p5,
  &p6,
  &p7,
  &p8,
  &p9,
  &p10,
  &p11,
  &p12,
  &p13,
  &p14,
  &p15,
  &p16,
  &p17,
  &p18,
  &p19,
};

Parcer::Parcer(const std::string& input) : input_{input} {}

std::optional<std::vector<Model::Token> > Parcer::Run() const {
  std::vector<Model::Token> result;
  result.reserve(input_.size());
  
  std::size_t s = 0;
  while (s < input_.size()) { // iterating through symbols

    bool found = false;
    for (std::size_t p = 0; p < s_parcers.size(); ++p) { // iterating through parcers
      if (s_parcers[p]->Run(result, input_, s)) {
        found = true;
        break;
      }
    }
    if (!found)
      return std::nullopt;
  }

  //
  // for(std::size_t i = 0; i < input_.size(); i++) {
  //   const char s = input_[i];
  //   if (s == '(') {
  //     result.push_back(Model::Token(0.0, Model::Type::OpenBracket, 0));
  //   } else if(s == ')') {
  //     result.push_back(Model::Token(0.0, Model::Type::CloseBracket, 0));
  //   } else if (s == '+') {
  //     result.push_back(Model::Token(0.0, Model::Type::Sum, 6));
  //   } else if (s == '-') {
  //     result.push_back(Model::Token(0.0, Model::Type::Minus, 6));
  //   } else if (s == '/') {
  //     result.push_back(Model::Token(0.0, Model::Type::Div, 8));
  //   } else if (s == '*') {
  //     result.push_back(Model::Token(0.0, Model::Type::Mult, 8));
  //   } else if (s == '^') {
  //     result.push_back(Model::Token(0.0, Model::Type::Power, 9));
  //   } else if (s == 'x') {
  //     result.push_back(Model::Token(0.0, Model::Type::X, 1));
  //   } else if (input_.compare(i, 3, "cos") == 0) {
  //     result.push_back(Model::Token(0.0, Model::Type::Cos, 8));
  //     i += 2;
  //   } else if (input_.compare(i, 3, "sin") == 0) {
  //     result.push_back(Model::Token(0.0, Model::Type::Sin, 8));
  //     i += 2;
  //   } else if (input_.compare(i, 3, "mod") == 0) {
  //     result.push_back(Model::Token(0.0, Model::Type::Mod, 8));
  //     i += 2;
  //   } else if (input_.compare(i, 3, "tan") == 0) {
  //     result.push_back(Model::Token(0.0, Model::Type::Tan, 8));
  //     i += 2;
  //   } else if (input_.compare(i, 4, "acos") == 0) {
  //     result.push_back(Model::Token(0.0, Model::Type::Acos, 8));
  //     i += 3;
  //   } else if (input_.compare(i, 4, "asin") == 0) {
  //     result.push_back(Model::Token(0.0, Model::Type::Asin, 8));
  //     i += 3;
  //   } else if (input_.compare(i, 4, "atan") == 0) {
  //     result.push_back(Model::Token(0.0, Model::Type::Atan, 8));
  //     i += 3;
  //   } else if (input_.compare(i, 4, "sqrt") == 0) {
  //     result.push_back(Model::Token(0.0, Model::Type::Sqrt, 8));
  //     i += 3;
  //   } else if (input_.compare(i, 2, "ln") == 0) {
  //     result.push_back(Model::Token(0.0, Model::Type::Ln, 8));
  //     i += 1;
  //   } else if (input_.compare(i, 3, "log") == 0) {
  //     result.push_back(Model::Token(0.0, Model::Type::Log, 8));
  //     i += 2;
  //   } else if (const auto& [n, index] = number(i); index > i) {
  //     result.push_back(Model::Token(n, Model::Type::Number, 1));
  //     i = (index - 1);
  //   } else {
  //     return std::nullopt;
  //   }
  // } 
  return std::optional<std::vector<Model::Token>>(result);  
}

// std::pair<double, std::size_t> Parcer::number(std::size_t index) const {
//   if (input_[index] == '.')
//     return std::make_pair(0.0, index);

//   std::istringstream iss(input_);
//   iss.seekg(index);
//   double result = 0.0;
//   iss >> result;

//   if (iss.eof())
//     index = static_cast<int>(input_.size());
//   else if (!iss.fail())
//     index = static_cast<int>(iss.tellg());

//   return std::make_pair(result, index);
// }

}   // namespace s21