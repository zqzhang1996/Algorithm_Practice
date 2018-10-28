// 函数命名, 变量命名, 文件命名要有描述性; 少用缩写.
// 文件名全部小写, 不包含下划线.
// 类型名称每个单词首字母均大写, 不包含下划线.
// 常规函数使用大小写混合, 取值和设值函数则要求与变量名匹配.
// 变量 (包括函数参数)和数据成员名一律小写, 单词之间用下划线连接.
// 类的成员变量以下划线结尾, 但结构体的就不用.
// 声明为 constexpr 或 const 的变量, 或在程序运行期间其值始终保持不变的,
// 命名时以 “k” 开头, 大小写混合.

#include <iomanip>
#include <iostream>
#include <random>

//随机数生成器
int RandNum(int num_min = 0, int num_max = 1024, int seed = time(nullptr)) {
  static std::default_random_engine e(seed);
  std::uniform_int_distribution<> u(num_min, num_max);
  return u(e);
}

//随机数组生成器
int RandArray(int arr[], int arr_length) {
  for (int i = 0; i < arr_length; i++) {
    arr[i] = RandNum();
  }
  return 0;
}

//打印数组
int PrintArray(int arr[], int arr_length, int width = 4) {
  for (int i = 0; i < arr_length; i++) {
    std::cout << std::setw(width) << arr[i] << ' ';
    if (i % 10 == 9 && arr_length > 9) std::cout << std::endl;
  }
  std::cout << std::endl;
  return 0;
}

//交换数组元素
int Exchange(int arr[], int i, int j) {
  int temp;
  temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
  return 0;
}

//模板实现
template <typename T> class Heap{
  public:
};

int main() {
  int arr[19];
  int i = 0;
  int length = std::end(arr) - std::begin(arr);
  std::cout << length << std::endl;
  for(auto &c : arr){
    c = i;
    i++;
    std::cout << c << std::endl;
  }
  std::cout << "end" << std::endl;
  return 0;
}
