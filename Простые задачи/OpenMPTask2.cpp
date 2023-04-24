#include <omp.h>
#include <iostream>


int main() {
	//объ€влен массив из 16000 элементов
	int size = 16000;
	double* a = new double[size];
	double* b = new double[size];

	//значение элемента массива равно его пор€дковому номеру
	for (int i = 0; i < size; i++) {
		a[i] = i;
	}

	//результирующий массив
	//его этементами будут средние значени€ исходного массива, за исключением крайних

	//статический, итерации поделены поровну между потоками
	double start = omp_get_wtime();
#pragma omp parallel for schedule(static), num_threads(8)
	for (int i = 1; i < size - 1; i++) {
		b[i] = (a[i - 1] + a[i + 1] + a[i]) / 3.0;
	}
	double end = omp_get_wtime();

	std::cout << "Static finished in " << end - start << " sec" << std::endl;

	//статический, 8 итераций на поток
	start = omp_get_wtime();
#pragma omp parallel for schedule(static, 8), num_threads(8)
	for (int i = 1; i < size - 1; i++) {
		b[i] = (a[i - 1] + a[i + 1] + a[i]) / 3.0;
	}

	end = omp_get_wtime();

	std::cout << "Static (8 iterations per thread) finished in " << end - start << " sec" << std::endl;

	//динамический, по умолчанию 1 итераци€
	start = omp_get_wtime();
#pragma omp parallel for schedule(dynamic), num_threads(8)
	for (int i = 1; i < size - 1; i++) {
		b[i] = (a[i - 1] + a[i + 1] + a[i]) / 3.0;
	}

	end = omp_get_wtime();

	std::cout << "Dynamic finished in " << end - start<< " sec" << std::endl;

	//динамический, 8 итераций
	start = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 8), num_threads(8)
	for (int i = 1; i < size - 1; i++) {
		b[i] = (a[i - 1] + a[i + 1] + a[i]) / 3.0;
	}

	end = omp_get_wtime();

	std::cout << "Dynamiс (8 iterations per thread) finished in " << end - start << " sec" << std::endl;


	//guided, по умолчанию 1 итераци€
	start = omp_get_wtime();
#pragma omp parallel for schedule(guided), num_threads(8)
	for (int i = 1; i < size - 1; i++) {
		b[i] = (a[i - 1] + a[i + 1] + a[i]) / 3.0;
	}

	end = omp_get_wtime();

	std::cout << "Guided finished in " << end - start << " sec" << std::endl;

	delete[] a, b;
}