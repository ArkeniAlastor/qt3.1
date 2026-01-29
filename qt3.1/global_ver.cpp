#include <iostream>
#include <atomic>
#include <thread>
using namespace std;

/*
* Глобальный массив инициализировать случайными числами от -20 +20. Вывести на консоль
* При помощи атомарных операции реализовать следующие функции:
* 1) Функция считает количество четных элементов.
* 2) Функция считает количество отрицательных элементов
* Все функции используют 1 счетчик (atomic<int> counter ={0};)
*/

const int SIZE = 100;

int arr[SIZE];

void initializeArray() {
	for (int i = 0; i < SIZE; ++i) {
		arr[i] = rand() % 41 - 20; // Случайные числа от -20 до +20
	}
}

void printArray() {
	for (int i = 0; i < SIZE; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void countEvenElements(atomic<int>& counter) {
	for (int i = 0; i < SIZE; ++i) {
		if (arr[i] % 2 == 0) {
			counter.fetch_add(1, memory_order_relaxed);
		}
	}
}

void countNegativeElements(atomic<int>& counter) {
	for (int i = 0; i < SIZE; ++i) {
		if (arr[i] < 0) {
			counter.fetch_add(1, memory_order_relaxed);
		}
	}
}

int main() {
	srand(static_cast<unsigned int>(time(0)));
	initializeArray();
	printArray();

	atomic<int> counterEven{ 0 };
	atomic<int> counterNegative{ 0 };

	thread t1(countEvenElements, ref(counterEven));
	thread t2(countNegativeElements, ref(counterNegative));

	t1.join();
	t2.join();

	cout << "Number of even elements: " << counterEven.load() << endl;
	cout << "Number of negative elements: " << counterNegative.load() << endl;

	return 0;
}
