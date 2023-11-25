#include "parcer.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <array>

namespace s21 {

namespace {

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
    s = (shifted_s);
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

// singleton
class ParcerChain {
private:
  std::array<ParcerBase*, 19> _parcers;
public:
  static const ParcerChain& Get();

  std::size_t Size() const;
  const ParcerBase* operator[](std::size_t index) const;

private:
  ParcerChain();
  ParcerChain(const ParcerChain&) = delete;
  ParcerChain(ParcerChain&&) = delete;

  ParcerChain& operator=(const ParcerChain&) = delete;
  ParcerChain& operator=(ParcerChain&&) = delete;
};

const ParcerChain& ParcerChain::Get() {
  static ParcerChain instance;
  return instance;
}

std::size_t ParcerChain::Size() const {
  return _parcers.size();
}
const ParcerBase* ParcerChain::operator[](std::size_t index) const {
  return _parcers[index];
}

ParcerChain::ParcerChain() {
  static ParcerOpenBracket      p0;
  static ParcerCloseBracket     p1;
  static ParcerSum              p2;
  static ParcerMinus            p3;
  static ParcerDivision         p4;
  static ParcerMultiplication   p5;
  static ParcerPower            p6;
  static ParcerPlaceholderX     p7;
  static ParcerCos              p8;
  static ParcerSin              p9;
  static ParcerMod             p10;
  static ParcerTan             p11;
  static ParcerAcos            p12;
  static ParcerAsin            p13;
  static ParcerAtan            p14;
  static ParcerSquareRoot      p15;
  static ParcerLn              p16;
  static ParcerLog             p17;
  static ParcerNumber          p18;

  _parcers[0]  =  &p0;
  _parcers[1]  =  &p1;
  _parcers[2]  =  &p2;
  _parcers[3]  =  &p3;
  _parcers[4]  =  &p4;
  _parcers[5]  =  &p5;
  _parcers[6]  =  &p6;
  _parcers[7]  =  &p7;
  _parcers[8]  =  &p8;
  _parcers[9]  =  &p9;
  _parcers[10] = &p10;
  _parcers[11] = &p11;
  _parcers[12] = &p12;
  _parcers[13] = &p13;
  _parcers[14] = &p14;
  _parcers[15] = &p15;
  _parcers[16] = &p16;
  _parcers[17] = &p17;
  _parcers[18] = &p18;
}

} // namespace

Parcer::Parcer(const std::string& input) : input_{input} {}

std::optional<std::vector<Model::Token> > Parcer::Run() const {
  std::vector<Model::Token> result;
  result.reserve(input_.size());
  
  std::size_t s = 0;
  while (s < input_.size()) {                                         // iterating through symbols

    bool recognised = false;
    for (std::size_t p = 0; p < ParcerChain::Get().Size(); ++p) {     // iterating through parcers
      if (ParcerChain::Get()[p]->Run(result, input_, s)) {
        recognised = true;
        break;
      }
    }
    if (!recognised)
      return std::nullopt;
  }

  return std::optional<std::vector<Model::Token>>(result);  
}

}   // namespace s21