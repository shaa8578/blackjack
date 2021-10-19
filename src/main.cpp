#include <getopt.h>
#include <string.h>

#include <clocale>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <vector>

#include "blackjack/player.h"
#include "game.h"

#if defined(USING_SRAND)
#include <ctime>
#endif /* USING_SRAND */

//------------------------------------------------------------------------------
#if !defined(TARGET)
#error TARGET not defined
#endif /* TARGET */

//------------------------------------------------------------------------------
void createUnexpectException() {
  std::cerr << "Вызвано необрабатываемое исключение" << std::endl;
  throw;
}

//------------------------------------------------------------------------------
// clang-format off
/** Список "длинных" опций программы */
static const struct option LONG_OPTIONS[] = {
    {"help", 0, NULL, 'h'}
};
// clang-format on

/** Описание коротких опций программы */
static const char* const SHORT_OPTIONS = "h";

//------------------------------------------------------------------------------
/* Сообщение о том, как правильно использовать программу. */
void printUsage(bool isError) {
  static const char* const usage_template =
      "Использование: %s { ОПЦИИ }\n"
      " -h, --help    Вывести текущую информацию.\n"
      "\n";
  fprintf(isError ? stderr : stdout, usage_template, TARGET);
}

//------------------------------------------------------------------------------
StringList splitString(const std::string& text) {
  std::istringstream iss(text);
  std::vector<std::string> result(std::istream_iterator<std::string>{iss},
                                  std::istream_iterator<std::string>());
  return result;
}

//------------------------------------------------------------------------------
void clearCinStream() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//------------------------------------------------------------------------------
StringList promtPlayerNames() {
  clearCinStream();

  std::cout << "Введите через пробел имена игроков: ";
  std::string player_names_str;
  std::getline(std::cin, player_names_str, '\n');

  return splitString(player_names_str);
}

//------------------------------------------------------------------------------
bool promtPlayAgain() {
  char user_answer(0);
  while (true) {
    std::cout << "Повторить игру (y/n)? " << std::ends;
    std::cin >> user_answer;
    if (std::cin.fail()) {
      clearCinStream();
    } else {
      if (user_answer == 'y' || user_answer == 'n') {
        break;
      }
    }
    std::cerr << "Необходимо ввести символы 'y', или 'n'" << std::endl;
  }
  return (user_answer == 'y');
}

//------------------------------------------------------------------------------
int main(int argc, char** argv) {
  setlocale(LC_ALL, "Russian");
  std::set_unexpected(createUnexpectException);

  int next_option(-1);
  do {
    next_option = getopt_long(argc, argv, SHORT_OPTIONS, LONG_OPTIONS, NULL);
    switch (next_option) {
      case 'h':
        printUsage(/* isError = */ false);
        return EXIT_SUCCESS;
      case '?':
        printUsage(/* isError = */ true);
        return EXIT_FAILURE;
      case -1:
        /* Обработка опций завершена. */
        break;
      default:
        abort();
    }
  } while (next_option != -1);
  if (optind != argc) {
    printUsage(/* isError = */ true);
    return EXIT_FAILURE;
  }

#if defined(USING_SRAND)
  srand(static_cast<unsigned int>(time(0)));
#endif /* USING_SRAND */

  std::cout << "Для начала игры введите Enter";

  do {
    auto player_names = promtPlayerNames();

    Game game;
    game.init(player_names);

    game.play();

    if (promtPlayAgain() == false) break;

  } while (true);

  return EXIT_SUCCESS;
}
