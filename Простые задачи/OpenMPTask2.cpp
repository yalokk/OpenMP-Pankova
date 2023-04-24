#include <omp.h>
#include <iostream>


int main() {
	//�������� ������ �� 16000 ���������
	int size = 16000;
	double* a = new double[size];
	double* b = new double[size];

	//�������� �������� ������� ����� ��� ����������� ������
	for (int i = 0; i < size; i++) {
		a[i] = i;
	}

	//�������������� ������
	//��� ���������� ����� ������� �������� ��������� �������, �� ����������� �������

	//�����������, �������� �������� ������� ����� ��������
	double start = omp_get_wtime();
#pragma omp parallel for schedule(static), num_threads(8)
	for (int i = 1; i < size - 1; i++) {
		b[i] = (a[i - 1] + a[i + 1] + a[i]) / 3.0;
	}
	double end = omp_get_wtime();

	std::cout << "Static finished in " << end - start << " sec" << std::endl;

	//�����������, 8 �������� �� �����
	start = omp_get_wtime();
#pragma omp parallel for schedule(static, 8), num_threads(8)
	for (int i = 1; i < size - 1; i++) {
		b[i] = (a[i - 1] + a[i + 1] + a[i]) / 3.0;
	}

	end = omp_get_wtime();

	std::cout << "Static (8 iterations per thread) finished in " << end - start << " sec" << std::endl;

	//������������, �� ��������� 1 ��������
	start = omp_get_wtime();
#pragma omp parallel for schedule(dynamic), num_threads(8)
	for (int i = 1; i < size - 1; i++) {
		b[i] = (a[i - 1] + a[i + 1] + a[i]) / 3.0;
	}

	end = omp_get_wtime();

	std::cout << "Dynamic finished in " << end - start<< " sec" << std::endl;

	//������������, 8 ��������
	start = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 8), num_threads(8)
	for (int i = 1; i < size - 1; i++) {
		b[i] = (a[i - 1] + a[i + 1] + a[i]) / 3.0;
	}

	end = omp_get_wtime();

	std::cout << "Dynami� (8 iterations per thread) finished in " << end - start << " sec" << std::endl;


	//guided, �� ��������� 1 ��������
	start = omp_get_wtime();
#pragma omp parallel for schedule(guided), num_threads(8)
	for (int i = 1; i < size - 1; i++) {
		b[i] = (a[i - 1] + a[i + 1] + a[i]) / 3.0;
	}

	end = omp_get_wtime();

	std::cout << "Guided finished in " << end - start << " sec" << std::endl;

	delete[] a, b;
}