#include <iostream>
#include <string>
#include "src/front/interface.h"

int main(int argc, char **argv) {
  int exitCode = 0;
  
  Interface* ui = new Interface();
  exitCode = ui->runInterface();
  return exitCode;
}
