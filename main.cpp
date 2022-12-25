#include <iostream>
#include <string>

#include "Game.h"

int main() {
  
  Game g("answer_list.txt", "guess_list.txt");

  std::string guess;
  while (g.get_state()) {
    g.print(std::cout);
    std::cout << std::endl << "GUESS: ";
    std::cin >> guess;
    if (guess.length() != 5) {
      std::cout << "Guesses must be length 5." << std::endl;
      std::cout << "-------------------" << std::endl;
      continue;
    }
    if (!g.valid_guess(guess)) {
      std::cout << "Guess not in word list." << std::endl;
      std::cout << "-------------------" << std::endl;
      continue;
    }
    g.guess(guess);
    std::cout << "-------------------" << std::endl;
  }
  g.print(std::cout);
  std::cout << "ANSWER: " << g.get_answer() << std::endl;

  return 0;
}