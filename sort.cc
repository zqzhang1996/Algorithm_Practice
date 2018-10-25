// 函数命名, 变量命名, 文件命名要有描述性; 少用缩写.
// 文件名全部小写, 不包含下划线.
// 类型名称每个单词首字母均大写, 不包含下划线.
// 常规函数使用大小写混合, 取值和设值函数则要求与变量名匹配.
// 变量 (包括函数参数)和数据成员名一律小写, 单词之间用下划线连接.
// 类的成员变量以下划线结尾, 但结构体的就不用.
// 声明为 constexpr 或 const 的变量, 或在程序运行期间其值始终保持不变的,
//     命名时以 “k” 开头, 大小写混合.

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

//取对数（2为底）
int ln(int num) {
  int i = 0;
  while (num > 1) {
    num /= 2;
    i++;
  }
  return i;
}

//欧几里得算法求最大公约数
int Euclid(int p, int q);
int Euclid(int p, int q) {
  if (q == 0) return p;
  int r = p % q;
  return Euclid(q, r);
}

//二分查找
int Rank(int key, int arr[], int hi);
int Rank(int key, int arr[], int lo, int hi);

int Rank(int key, int arr[], int hi) { return Rank(key, arr, 0, hi - 1); }
int Rank(int key, int arr[], int lo, int hi) {
  if (lo > hi) return -1;
  int mid = lo + (hi - lo) / 2;
  if (key < arr[mid])
    return Rank(key, arr, lo, mid - 1);
  else if (key > arr[mid])
    return Rank(key, arr, mid + 1, hi);
  else
    return mid;
}

//插入排序
int InsertionSort(int arr[], int p, int q) {
  for (int i = p; i < q; i++) {
    int key = arr[i + 1];
    while (i >= p && arr[i] > key) {
      arr[i + 1] = arr[i];
      i--;
    }
    arr[i + 1] = key;
  }
  return 0;
}
int InsertionSort(int arr[], int arr_length) {
  InsertionSort(arr, 0, arr_length - 1);
  return 0;
}

//归并排序
int Merge(int arr[], int p, int q, int r) {
  int brray[q - p + 1], crray[r - q];
  for (int i = 0; i < q - p + 1; i++) {
    brray[i] = arr[p + i];
  }
  for (int j = 0; j < r - q; j++) {
    crray[j] = arr[q + 1 + j];
  }
  int i = 0, j = 0;
  int k = p;
  while (k <= r) {
    if (i == q - p + 1) {
      for (; j < r - q; j++) {
        arr[k] = crray[j];
        k++;
      }
    } else if (j == r - q) {
      for (; i < q - p + 1; i++) {
        arr[k] = brray[i];
        k++;
      }
    } else if (brray[i] < crray[j]) {
      arr[k] = brray[i];
      i++;
      k++;
    } else {
      arr[k] = crray[j];
      j++;
      k++;
    }
  }
  return 0;
}
int MergeSort(int arr[], int p, int r) {
  if (p < r - 4 + 1) {
    int q = (p + r) / 2;
    MergeSort(arr, p, q);
    MergeSort(arr, q + 1, r);
    Merge(arr, p, q, r);
  } else if (p > r - 4 && p < r)
    InsertionSort(arr, p, r);
  return 0;
}
int MergeSort(int arr[], int arr_length) {
  MergeSort(arr, 0, arr_length - 1);
  return 0;
}

//最大堆
int Parent(int i) { return (i - 1) / 2; }
int Left(int i) { return i * 2 + 1; }
int Right(int i) { return i * 2 + 2; }
int MaxHeapify(int arr[], int arr_length, int i) {
  int l = Left(i);
  int r = Right(i);
  int largest = i;
  if (l < arr_length && arr[l] > arr[largest]) {
    largest = l;
  }
  if (r < arr_length && arr[r] > arr[largest]) {
    largest = r;
  }
  if (largest != i) {
    Exchange(arr, i, largest);
    MaxHeapify(arr, arr_length, largest);
  }
  return 0;
}
int BuildMaxHeap(int arr[], int arr_length) {
  for (int i = (arr_length - 2) / 2; i > -1; i--) {
    MaxHeapify(arr, arr_length, i);
  }
  return 0;
}
int HeapMaximum(int arr[]) { return arr[0]; }
int HeapExtractMax(int arr[], int *arr_length) {
  int max = arr[0];
  arr[0] = arr[*arr_length - 1];
  *arr_length -= 1;
  MaxHeapify(arr, *arr_length, 0);
  return max;
}
int MaxHeapChangeKey(int arr[], int arr_length, int i, int key) {
  if (key < arr[i] && i < arr_length) {
    arr[i] = key;
    MaxHeapify(arr, arr_length, i);
  } else {
    arr[i] = key;
    while (i != 0 && arr[Parent(i)] < arr[i]) {
      Exchange(arr, i, Parent(i));
      i = Parent(i);
    }
  }
  return 0;
}
int MaxHeapInsert(int arr[], int *arr_length, int key) {
  MaxHeapChangeKey(arr, *arr_length, *arr_length, key);
  *arr_length += 1;
  return 0;
}
int MaxHeapDelete(int arr[], int *arr_length, int i) {
  *arr_length -= 1;
  arr[i] = arr[*arr_length];
  MaxHeapify(arr, *arr_length, i);
  return 0;
}

//堆排序
int HeapSort(int arr[], int arr_length) {
  BuildMaxHeap(arr, arr_length);
  for (int i = arr_length - 1; i > 0; i--) {
    Exchange(arr, 0, i);
    arr_length--;
    MaxHeapify(arr, arr_length, 0);
  }
  return 0;
}

//快速排序
int Partition(int arr[], int p, int r) {
  for (int i = p; i < r; i++) {
    if (arr[i] <= arr[r]) {
      Exchange(arr, p, i);
      p++;
    }
  }
  Exchange(arr, p, r);
  return p;
}
int RandomPartition(int arr[], int p, int r) {
  Exchange(arr, RandNum(p, r), r);
  return Partition(arr, p, r);
}
int QuickSort(int arr[], int p, int r) {
  if (p < r) {
    int q = RandomPartition(arr, p, r);
    QuickSort(arr, p, q - 1);
    QuickSort(arr, q + 1, r);
  }
  return 0;
}
int QuickSort(int arr[], int arr_length) {
  QuickSort(arr, 0, arr_length - 1);
  return 0;
}

//计数排序
int CountingSort(int arr[], int arr_length, int num_max = 1024) {
  int brray[arr_length];
  int crray[num_max + 1];
  for (int i = 0; i <= num_max; i++) {
    crray[i] = 0;
  }
  for (int i = 0; i < arr_length; i++) {
    crray[arr[i]]++;
  }
  crray[0]--;
  for (int i = 1; i <= num_max; i++) {
    crray[i] += crray[i - 1];
  }
  for (int i = arr_length - 1; i >= 0; i--) {
    brray[crray[arr[i]]] = arr[i];
    crray[arr[i]]--;
  }
  for (int i = 0; i < arr_length; i++) {
    arr[i] = brray[i];
  }
  return 0;
}

//基数排序
int RadixSort(int arr[], int arr_length, int num_max = 1024) {
  int digit = ln(num_max);
  int radix = ln(digit);
  for (int i = 0; i * radix < digit; i++) {
    int array[arr_length];
    for (int j = 0; j < arr_length; j++) {
      array[j] = (arr[j] >> (radix * i)) & ((1 << radix) - 1);
    }
    int brray[arr_length];
    int crray[1 << radix];
    for (int i = 0; i < (1 << radix); i++) {
      crray[i] = 0;
    }
    for (int i = 0; i < arr_length; i++) {
      crray[array[i]]++;
    }
    crray[0]--;
    for (int i = 1; i < (1 << radix); i++) {
      crray[i] += crray[i - 1];
    }
    for (int i = arr_length - 1; i >= 0; i--) {
      brray[crray[array[i]]] = arr[i];
      crray[array[i]]--;
    }
    for (int i = 0; i < arr_length; i++) {
      arr[i] = brray[i];
    }
  }
  return 0;
}

//随机选择算法
int RandomizedSelect(int arr[], int p, int r, int i) {
  if (p == r) {
    return arr[p];
  }
  int q = RandomPartition(arr, p, r);
  int k = q - p + 1;
  if (i == k) {
    return arr[q];
  } else if (i < k) {
    return RandomizedSelect(arr, p, q - 1, i);
  } else {
    return RandomizedSelect(arr, q + 1, r, i - k);
  }
  return 0;
}

//int main() {
//  std::random_device rd;
//  int arr_length = 100;
//  // std::cin >> arr_length;
//  int arr[arr_length];
//  RandArray(arr, arr_length);
//  PrintArray(arr, arr_length);
//  QuickSort(arr, arr_length);
//  PrintArray(arr, arr_length);
//  return 0;
//}