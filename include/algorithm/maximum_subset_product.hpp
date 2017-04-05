#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

namespace mk {

int min(int x, int y) {
  return (x < y) ? x : y;
}

// Function to return maximum product of a subset of given array
int maximum_subset_product(int arr[], int n) {
  // base case
  if (n == 0) return 0;

  // if array contains only one element
  if (n == 1) return arr[0];

  int product = 1; // to store maximum product subset

  // stores the negative element having minimum absolute value in the set
  int abs_min_so_far = INT_MAX;

  int negative = 0; // maintain count of negative elements in the set
  int positive = 0; // maintain count of positive elements in the set

  int contains_zero = 0;

  // traverse the given array
  for (int i = 0; i < n; i++) {
    // if current element is negative
    if (arr[i] < 0) {
      negative++;
      abs_min_so_far = min(abs_min_so_far, abs(arr[i]));
    }
    // if current element is positive
    else if (arr[i] > 0) {
      positive++;
    }

    // if current element is zero
    if (arr[i] == 0)
      contains_zero = 1;
    else
      product = product * arr[i];
  }

  // if odd number of negative elements are present, exclude the negative
  // element having minimum absolute value from the subset
  if (negative & 1) product = product / -abs_min_so_far;

  // special case - set contains one negative element and one or more zeroes
  if (negative == 1 && !positive && contains_zero) product = 0;

  // return maximum product
  return product;
}

} // namespace mk

int main() {
  int arr[] = {-6, 4, -5, 8, -10, 0, 8};

  int n = sizeof(arr) / sizeof(arr[0]);

  printf("The maximum product of a subset is %d",
         maximum_subset_product(arr, n));

  return 0;
}
