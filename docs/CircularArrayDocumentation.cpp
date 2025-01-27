#include "CircularArray.h"

using std::cout, std::endl;

int main() {
    // To declare, give a TYPE of value contained in the array and a size, the maximum number of elements that can be contained in the array
    CircularArray<double> arr(5);

    // To add elements, use the push function
    arr.push(0.0);
    arr.push(1.0);
    arr.push(2.0);
    arr.push(3.0);
    arr.push(4.0); // Current array contents: [0, 1, 2, 3, 4]

    // Array elements can be accessed using brackets ([]) or .at(), just like a normal array. The oldest element is at index 0
    arr[0]; // returns 0
    arr.at(2); // returns 2
    arr[-1]; // negative indices wrap around (just like in Python), so -1 returns the newest elements (here, 4)

    arr.push(5.0); // After size is hit, oldest element is overwritten. Current array contents: [1, 2, 3, 4, 5]

    arr.pop(); // Removes and returns the oldest element (1). Current array contents: [2, 3, 4, 5]

    arr.median(); // Finds and returns the median element, 3.5
    double* arrDoublePrime = arr.doubleDerivative(1); // Finds and returns the running double derivative of the array's values given the separation in seconds between each each value's time of collection. The first 2 values from the start and end are removed during computation


    delete[] arrDoublePrime; // created dynamically, so make sure to delete!
}
