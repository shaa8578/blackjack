#include <gtest/gtest.h>

#include <clocale>
#include <iostream>
#include <stdexcept>

//------------------------------------------------------------------------------
void createUnexpectedException() {
  std::cerr << "Вызвано необрабатываемое исключение" << std::endl;
  throw;
}

//------------------------------------------------------------------------------
int main(int argc, char** argv) {
  setlocale(LC_ALL, "Russian");
  std::set_unexpected(&createUnexpectedException);

  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
