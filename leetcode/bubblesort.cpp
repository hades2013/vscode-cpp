#include <iostream>
#include <vector>
#include <utility> // std::swap

// A: Input elements, typically list.
void bubble_sort(std::vector<int>& A) {
    for(int idx = 0; idx <= A.size() - 1; idx++) {
        for(int i = 0; i <= A.size() - 2; i++) {
            if(A[i] > A[i + 1]) {
                std::swap(A[i], A[i + 1]);
             }
          }
     }
}
// end bubble_sort

int main() {
    std::vector<int> A {5, 3, 6, 7, 1}; // C++11 syntax
    bubble_sort(A);
    std::cout << "after bubble sort..." << std::endl;
    // C++11 range-based for loop
    for(const auto &elem : A) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
}