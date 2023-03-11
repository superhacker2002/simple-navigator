#include "interface/interface.h"

int main() {
    s21::Interface& interface = s21::Interface::getIfaceInstance();
    interface.start();
}