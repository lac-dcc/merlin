void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void bubble_sort(int n, int b, int *arr) {
  int i = 0;
  while (i < n) {
    int j = i + 1;
    while (j < n) {
      if (arr[j] < arr[i]) // compare
        swap(&arr[i], &arr[j]);
      j++;
    }
    i++;
  }
}

int main() {
  return 0;
}