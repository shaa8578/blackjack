#include <getopt.h>

#include <clocale>
#include <cstdlib>
#include <iostream>

#include "blackjack/player.h"

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
static void printUsage(bool isError) {
  static const char* const usage_template =
      "Использование: %s { ОПЦИИ }\n"
      " -h, --help    Вывести текущую информацию.\n"
      "\n";
  fprintf(isError ? stderr : stdout, usage_template, TARGET);
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

  /* Точка запуска программы */
  Player p("user", 10);
  std::cout << std::boolalpha << p.isHitting() << std::endl;

  return EXIT_SUCCESS;
}
