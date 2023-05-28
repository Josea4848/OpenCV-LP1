#include <unistd.h>
#include <iostream>

void clearTerminal() {
  //Limpa terminal
  system("clear");  
}

void exibeMenu() {
  clearTerminal();
  
  std::cout << "=========================================\n";
  std::cout << "\t\tFruit Tinta\n";
  std::cout << "=========================================\n";

  std::cout << "1 - Jogar\n2 - Selecionar Dificuldade\n3 - Sair\n";
}

void menuDificuldade() {
  clearTerminal();
  
  std::cout << "=========================================\n";
  std::cout << "\t\tMenu de dificuldade\n";
  std::cout << "=========================================\n";

  std::cout << "1 - Fácil\n2 - Intermediária\n3 - Difícil\n4 - Impossível\n";
}

