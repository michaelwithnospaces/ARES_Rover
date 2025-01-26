template <typename T>
class CircularArray {
public:
    int capacity; // capacity (space allocated in memory) of array

    CircularArray(int capacity) {
        this->capacity = capacity;
        this->arr = new T[capacity];
        this->start = 0;
        this->size = 0;
    }

    ~CircularArray() {
        delete[] this->arr;
    }

    void push(T element) {
        // if space remaining for element, put it at the end
        if (this->size < this->capacity) {
            int index = (this->start + this->size) % this->capacity;
            this->arr[index] = element;
            this->size += 1;
        } else { // otherwise, put it at the start (erasing the oldest element) and make it the new start
            this->arr[this->start] = element;
            this->start = (this->start + 1 + this->capacity) % this->capacity;
        }
    }

    T pop() {
        if (this->size == 0) {
            throw "Cant' pop from an empty circular array";
        }

        // Acccess and return element at the "start", decrease size
        T el = this->arr[this->start];
        this->size -= 1;
        this->start = (this->start + 1) % this->capacity;
        return el;
    }

    // Allows access like a normal array
    T& operator[](const int _i) {
        int i = _i;
        if (i < 0) { // allows for python-style negative indexing
            i += this->capacity;
        }
        
        int j = (i + this->start) % this->capacity;
        return this->arr[j];
    }

    const T& operator[](const int _i) const {
        int i = _i;
        if (i < 0) {
            i += this->capacity;
        }

        int j = (i + this->start) % this->capacity;
        return this->arr[j];
    }

    T* getArray() {
        T* arr = new T[this->size];
        for (int i = 0; i < this->size; i++) {
            arr[i] = this->arr[(this->start + i) % this->capacity];
        }
        return arr;
    }

    double median() {
        T* arr = this->sorted();

        double median;
        if (this->size % 2 == 0) {
            median = (arr[this->size / 2 - 1] + arr[this->size / 2]) / 2.0;
        } else {
            median = arr[this->size / 2];
        }

        delete[] arr;

        return median;
    }

    int start;
    int size;

private:
    T* arr; // internal array that actually holds data

    void sort(T*& arr) {
        // insertion sort
        for (int i = 1; i < this->size; i++) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }

    T* sorted() {
        T* arr = this->getArray();
        this->sort(arr);
        return arr;
    }
};
