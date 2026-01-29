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

atomic <int> counter_even{ 0 };
atomic <int> counter_negative{ 0 };

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

void countEvenElements() {
	for (int i = 0; i < SIZE; ++i) {
		if (arr[i] % 2 == 0) {
			counter_even.fetch_add(1);
		}
	}
}

void countNegativeElements() {
	for (int i = 0; i < SIZE; ++i) {
		if (arr[i] < 0) {
			counter_negative.fetch_add(1);
		}
	}
}

int main() {
	srand(time(0));
	initializeArray();
	printArray();

	thread t1(countEvenElements);
	thread t2(countNegativeElements);

	t1.join();
	t2.join();

	cout << "Number of even elements: " << counter_even.load() << endl;
	cout << "Number of negative elements: " << counter_negative.load() << endl;
}
