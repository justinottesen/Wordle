#include "Game.h"

Game::Game(const std::string& f_ans, const std::string& f_guess) {
  srand(time(NULL));
  set_answer(f_ans);
  for (char c : answer) {
    if (ans_counts.count(c)) { ans_counts[c]++; }
    else { ans_counts[c] = 1; }
  }
  populate_guesses(f_guess);
  guesses.clear();
  display = "";
}

void Game::guess(const std::string& guess) {
  guesses.push_back(guess);
  std::map<char, int> g_counts(ans_counts);
  for (int i = 0; i < 5; i++) {
    if (guess[i] == answer[i]) { --g_counts[guess[i]]; }
  }
  display += "       ";
  for (int i = 0; i < 5; i++) {
    if (guess[i] == answer[i]) { 
      display += "\033[42m";
      keyboard.set_color(guess[i], GREEN);
    }
    else if (g_counts[guess[i]]) {
      display += "\033[43m";
      keyboard.set_color(guess[i], YELLOW);
      --g_counts[guess[i]];
    } else {
      keyboard.set_color(guess[i], BLACK);
    }
    display += guess[i];
    display += "\033[0m";
  }
  display += "\n";
}

void Game::print(std::ostream& ostr) const {
  std::cout << display << std::endl;
  keyboard.print(ostr);
}

bool Game::get_state() const {
  if (guesses.size() == 0) { return true; }
  if (guesses[guesses.size()-1] != answer && guesses.size() < 6) { return true; }
  return false;
}

void Game::set_answer(const std::string& f_name) {
  std::ifstream f_in(f_name);
  assert(f_in.good() && "ANSWER LIST FILE NOT FOUND");

  std::vector<std::string> answers;
  std::string temp;
  while (f_in >> temp) { answers.push_back(temp); }
  f_in.close();

  answer = answers[rand() % answers.size()];
}

void Game::populate_guesses(const std::string& guess_list) {
  std::ifstream f_in(guess_list);
  assert(f_in.good() && "GUESS LIST FILE NOT FOUND");
  std::string temp;
  while (f_in >> temp) { valid_guesses.push_back(temp); }
  f_in.close();
}