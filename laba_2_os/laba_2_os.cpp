#include <iostream>
#include <Windows.h>

typedef struct {
    int* array;
    int size;
    int* max;
    int* min;
    double* average;
} MyData;

DWORD WINAPI min_max(LPVOID lpParam) {
    std::cout << "------------------------------" << std::endl;
    std::cout << "Thread min_max is started" << std::endl;
    MyData* data = (MyData*)lpParam;
    int* array = data->array;
    int size = data->size;

    *data->max = array[0];
    *data->min = array[0];

    for (int i = 0; i < size; ++i) {
        if (array[i] > *data->max) {
            *data->max = array[i];
            Sleep(7);
        }
        if (array[i] < *data->min) {
            *data->min = array[i];
            Sleep(7);
        }
    }
    std::cout << "Maximum array element found : " << *data->max << std::endl;
    std::cout << "Minimum array element found : " << *data->min << std::endl;
    std::cout << "Thread min_max is finished" << std::endl;
    std::cout << "------------------------------" << std::endl;
    return 0;
}

DWORD WINAPI average(LPVOID lpParam) {
    std::cout << "------------------------------" << std::endl;
    std::cout << "Thread average is started" << std::endl;
    MyData* data = (MyData*)lpParam;
    int* array = data->array;
    int size = data->size;
    double sum = 0, averageNumber;

    for (int i = 0; i < size; i++) {
        sum += array[i]; // Используем правильный индекс i
    }

    averageNumber = sum / size;
    std::cout << "Average number of array : " << averageNumber << std::endl;
    *data->average = averageNumber;
    std::cout << "Thread average is finished" << std::endl;
    std::cout << "------------------------------" << std::endl;
    return 0;
}

int main() {
    int n;
    HANDLE hMinMax;
    HANDLE hAverage;
    DWORD IDMinMax;
    DWORD IDAverage;
    std::cout << "Enter array dimension : " << std::endl;
    std::cin >> n;
    int* arrayOfIntegers = new int[n];
    int max, min;
    double averageValue;
    MyData data;
    data.array = arrayOfIntegers;
    data.size = n;
    data.max = &max;
    data.min = &min;
    data.average = &averageValue;
    std::cout << "Enter " << n << " array elements : ";
    for (int i = 0; i < n; i++) {
        std::cin >> arrayOfIntegers[i];
    }

    hMinMax = CreateThread(NULL, 0, min_max, &data, 0, &IDMinMax);
    if (hMinMax == NULL) {
        return GetLastError();
    }
    WaitForSingleObject(hMinMax, INFINITE);
    CloseHandle(hMinMax);

    hAverage = CreateThread(NULL, 0, average, &data, 0, &IDAverage);
    if (hAverage == NULL) {
        return GetLastError();
    }
    WaitForSingleObject(hAverage, INFINITE);
    CloseHandle(hAverage);

    for (int i = 0; i < n; i++) {
        if (arrayOfIntegers[i] == max || arrayOfIntegers[i] == min) {
            arrayOfIntegers[i] = static_cast<int>(averageValue);
        }
    }

    std::cout << "Modified array elements: ";
    for (int i = 0; i < n; i++) {
        std::cout << arrayOfIntegers[i] << " ";
    }
    std::cout << std::endl;

    delete[] arrayOfIntegers;
    return 0;
}

