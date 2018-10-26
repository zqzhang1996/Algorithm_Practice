#include <conio.h>  //Windows only  //getch()
#include <iomanip>
#include <iostream>
#include <random>
#define kLevel 4

int RandNum(int num_min = 0, int num_max = 1024, int seed = time(nullptr)) {
  static std::default_random_engine e(seed);
  std::uniform_int_distribution<> u(num_min, num_max);
  return u(e);
}

class Cube {
  int block[kLevel * kLevel];
  int free_block = kLevel * kLevel;
  int score = 0;
  bool moved = false;
  bool exit = false;
  bool fail = false;
  void Format();
  void Display();
  void ShowNum(int *key);
  void PrintLine(int *key);
  void PrintLine();
  void PutNum();
  bool IsFail();
  void Merge(int *key, int way, int i);
  void Move(int *key, int way);
  void Move(char c);

 public:
  void Run();
};

void Cube::Format() {
  for (int &i : block) {
    i = -1;
  }
  free_block = kLevel * kLevel;
  score = 0;
  fail = false;
  moved = false;
  PutNum();
  PutNum();
}

bool Cube::IsFail() {
  for (int i = 0; i != kLevel * kLevel; i++) {
    if (i / kLevel != 0 && *(block + i - kLevel) == *(block + i)) {
      return false;
    } else if (i % kLevel != 0 && *(block + i - 1) == *(block + i)) {
      return false;
    }
  }
  return true;
}

void Cube::ShowNum(int *key) {
  if ((*key) == -1) {
    std::cout << "    |";
    return;
  }
  std::cout << std::setw(4) << (1 << (*key)) << '|';
}

void Cube::PrintLine(int *key) {
  std::cout << '|';
  for (int i = 0; i != kLevel; i++) {
    ShowNum(key + i);
  }
  std::cout << std::endl;
}

void Cube::PrintLine() {
  std::cout << '+';
  for (int i = 0; i != kLevel; i++) {
    std::cout << "----+";
  }
  std::cout << std::endl;
}

void Cube::Display() {
  system("cls");
  std::cout << "score: " << score << std::endl;
  PrintLine();
  for (int i = 0; i != kLevel; i++) {
    PrintLine(block + i * kLevel);
    PrintLine();
  }
  std::cout << "\n[wasd] to move, \n[r] to restart, \n[e] to exit."
            << std::endl;
  if (fail) {
    std::cout << "\nGame Over \nPress [r] to restart." << std::endl;
  }
}

void Cube::PutNum() {
  int *key = block;
  while (*key != -1) {
    key++;
  }
  for (int i = RandNum(0, free_block - 1); i != 0; i--) {
    key++;
    while (*key != -1) {
      key++;
    }
  }
  *key = RandNum(0, 1);
  free_block--;
  if (free_block == 0) {
    fail = IsFail();
  }
}

void Cube::Merge(int *key, int way, int i = 0) {
  if (i == kLevel - 1) {
    return;
  }
  int *kez = key + way;
  for (int j = i + 1; j != kLevel - 1; j++) {
    if (*kez != -1) {
      break;
    }
    kez += way;
  }
  if (*kez == -1) {
    return;
  }
  if (*key == -1) {
    *key = *kez;
    *kez = -1;
    moved = true;
    Merge(key, way, i);
    return;
  } else if (*key == *kez) {
    (*key)++;
    *kez = -1;
    moved = true;
    score += (1 << (*key));
    free_block++;
  }
  Merge(key + way, way, i + 1);
}

void Cube::Move(int *key, int way) {
  for (int i = 0; i != kLevel; i++) {
    Merge(key + i * (kLevel / way), way);
  }
  if (moved) {
    moved = false;
    PutNum();
    Display();
  }
}

void Cube::Move(char c) {
  if (fail) {
    return;
  }
  switch (c) {
    case 'w':
      Move(block, kLevel);
      break;
    case 's':
      Move(block + kLevel * kLevel - 1, -kLevel);
      break;
    case 'a':
      Move(block, 1);
      break;
    case 'd':
      Move(block + kLevel * kLevel - 1, -1);
      break;
    default:;
  }
}

void Cube::Run() {
  Format();
  Display();
  char c;
  while (!exit) {
    c = getch();
    switch (c) {
      case 'w':
      case 'a':
      case 's':
      case 'd':
        Move(c);
        break;
      case 'r':
        Format();
        Display();
        break;
      case 'e':
        exit = true;
        std::cout << "\nPress any key to close." << std::endl;
        getch();
        break;
      default:
        Display();
        break;
    }
  }
}

int main() {
  Cube cube;
  cube.Run();
  return 0;
}