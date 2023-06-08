#include <stdexcept>
#include <string>

class InvalidDificultyValue : public std::exception {
private:
  std::string msg = "Valor inválido para dificuldade!";
public:
  InvalidDificultyValue() {}
  virtual std::string what() {
    return msg.c_str(); 
  }
};