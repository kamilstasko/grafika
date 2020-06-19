#pragma once

#include <iostream>
#include <math.h>

#define M_PI 3.14159265358979323846

float naStopnie(float radiany)
{
	return 180 * radiany / M_PI;
}

float naRadiany(float stopnie)
{
	return M_PI * stopnie / 180;
}

template <unsigned size>
class Macierz
{
private:
	float data[size][size];
	float detLaplacea(unsigned n, float** macierz);
	Macierz<size> algebraicComplementMatrix(void);
public:
	Macierz(void);
	Macierz(float val);
	Macierz(float **tab);
	Macierz(float tab[][size]);

	Macierz<size>& operator=(Macierz<size> other);
	Macierz<size> operator+(Macierz<size>& other);
	Macierz<size> operator+=(Macierz<size>& other);
	Macierz<size> operator-(Macierz<size>& other);
	Macierz<size> operator-=(Macierz<size>& other);
	Macierz<size> operator*(const int value);
	Macierz<size> operator*=(const int value);
	Macierz<size> operator*(Macierz<size>& other);
	Macierz<size> operator*=(Macierz<size>& other);
	float* operator*(float tab[size]);
	friend std::ostream& operator<<(std::ostream& os, Macierz<size>& data)
	{
		for (unsigned i = 0; i < size; ++i)
		{
			os << '[';

			for (unsigned j = 0; j < size; ++j)
			{
				os << data.getData(i, j);

				if (j != size - 1)
				{
					os << ',';
				}
			}

			os << ']';
		}

		return os;
	}

	void setData(unsigned i, unsigned j, float val);
	float getData(unsigned i, unsigned j);
	float** getTab(void);
	Macierz<size> identityMatrix(void);
	Macierz<size> transposeMatrix(void);
	Macierz<size> invertibleMatrix(void);
};

template<unsigned size>
Macierz<size>::Macierz(void)
{
	for (unsigned i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < size; ++j)
		{
			this->data[i][j] = 0;
		}
	}
}

template<unsigned size>
Macierz<size>::Macierz(float val)
{
	for (unsigned i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < size; ++j)
		{
			this->data[i][j] = val;
		}
	}
}

template<unsigned size>
Macierz<size>::Macierz(float ** tab)
{
	for (unsigned i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < size; ++j)
		{
			this->data[i][j] = tab[i][j];
		}
	}
}

template<unsigned size>
Macierz<size>::Macierz(float tab[][size])
{
	for (unsigned i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < size; ++j)
		{
			this->data[i][j] = tab[i][j];
		}
	}
}

template<unsigned size>
Macierz<size>& Macierz<size>::operator=(Macierz<size> other)
{
	if (this != &other)
	{
		for (unsigned i = 0; i < size; ++i)
		{
			for (unsigned j = 0; j < size; ++j)
			{
				this->setData(i, j, other.getData(i, j));
			}
		}
	}

	return *this;
}

template<unsigned size>
Macierz<size> Macierz<size>::operator+(Macierz<size>& other)
{
	Macierz<size> tmp;

	for (unsigned i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < size; ++j)
		{
			tmp.setData(i, j, this->getData(i, j) + other.getData(i, j));
		}
	}

	return tmp;
}

template<unsigned size>
Macierz<size> Macierz<size>::operator+=(Macierz<size>& other)
{
	for (unsigned i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < size; ++j)
		{
			this->setData(i, j, this->getData(i, j) + other.getData(i, j));
		}
	}

	return *this;
}

template<unsigned size>
Macierz<size> Macierz<size>::operator-(Macierz<size>& other)
{
	Macierz<size> tmp;

	for (unsigned i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < size; ++j)
		{
			tmp.setData(i, j, this->getData(i, j) - other.getData(i, j));
		}
	}

	return tmp;
}

template<unsigned size>
Macierz<size> Macierz<size>::operator-=(Macierz<size>& other)
{
	for (unsigned i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < size; ++j)
		{
			this->setData(i, j, this->getData(i, j) - other.getData(i, j));
		}
	}

	return *this;
}

template<unsigned size>
Macierz<size> Macierz<size>::operator*(const int value)
{
	Macierz<size> tmp;

	for (unsigned i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < size; ++j)
		{
			tmp.setData(i, j, this->getData(i, j) * value);
		}
	}

	return tmp;
}

template<unsigned size>
Macierz<size> Macierz<size>::operator*=(const int value)
{
	for (unsigned i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < size; ++j)
		{
			this->setData(i, j, this->getData(i, j) * value);
		}
	}

	return *this;
}

template<unsigned size>
Macierz<size> Macierz<size>::operator*(Macierz<size>& other)
{
	Macierz<size> tmp;

	for (unsigned i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < size; ++j)
		{
			float value = 0;
			unsigned tmp2 = 0;

			while (tmp2 < size)
			{
				value += this->getData(i, tmp2) * other.getData(tmp2, j);
				++tmp2;
			}

			tmp.setData(i, j, value);
		}
	}

	return tmp;
}

template<unsigned size>
Macierz<size> Macierz<size>::operator*=(Macierz<size>& other)
{
	Macierz<size> tmp;

	for (unsigned i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < size; ++j)
		{
			float value = 0;
			unsigned tmp2 = 0;

			while (tmp2 < size)
			{
				value += this->getData(i, tmp2) * other.getData(tmp2, j);
				++tmp2;
			}

			tmp.setData(i, j, value);
		}
	}

	return *this = tmp;
}

template<unsigned size>
float* Macierz<size>::operator*(float tab[size])
{
	float* tmp = new float[size];

	for (unsigned i = 0; i < size; ++i)
	{
		float value = 0;

		for (unsigned j = 0; j < size; ++j)
		{
			value += this->getData(i, j) * tab[j];
		}

		tmp[i] = value;
	}

	return tmp;
}

template<unsigned size>
void Macierz<size>::setData(unsigned i, unsigned j, float val)
{
	this->data[i][j] = val;
}

template<unsigned size>
float Macierz<size>::getData(unsigned i, unsigned j)
{
	return this->data[i][j];
}

template<unsigned size>
inline float ** Macierz<size>::getTab(void)
{
	float** tmp = new float *[size];

	for (unsigned i = 0; i < size; ++i)
	{
		tmp[i] = new float[size];

		for (unsigned j = 0; j < size; ++j)
		{
			tmp[i][j] = this->getData(i, j);
		}
	}

	return tmp;
}

template<unsigned size>
Macierz<size> Macierz<size>::identityMatrix(void)
{
	Macierz<size> tmp;

	unsigned tmp2 = 0;
	while (tmp2 < size)
	{
		tmp.setData(tmp2, tmp2, 1);
		++tmp2;
	}

	return tmp;
}

template<unsigned size>
Macierz<size> Macierz<size>::transposeMatrix(void)
{
	Macierz<size> tmp;

	for (unsigned i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < size; ++j)
		{
			tmp.setData(i, j, this->getData(j, i));
		}
	}

	return tmp;
}

template<unsigned size>
float Macierz<size>::detLaplacea(unsigned n, float** matrix)
{
	float sum = 0;

	if (n == 1)
	{
		return matrix[0][0];
	}
	else
	{
		for (int i = 0; i < n; ++i)
		{
			float** tmpMatrix = new float*[n - 1];

			int a = 1, b = 0;
			for (int x = 0; x < n - 1; ++x)
			{
				tmpMatrix[x] = new float[n - 1];

				for (int y = 0; y < n - 1; ++y)
				{
					if (b == i)
						++b;

					tmpMatrix[x][y] = matrix[a][b++];
				}

				++a;
				b = 0;
			}

			sum += pow(-1, (i + 2)) * matrix[0][i] * detLaplacea(n - 1, tmpMatrix);
		}

		return sum;
	}
}

template<unsigned size>
Macierz<size> Macierz<size>::algebraicComplementMatrix(void)
{
	Macierz<size> tmp;

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			float** tmpMatrix = new float*[size - 1];

			int a = 0, b = 0;
			for (int x = 0; x < size - 1; ++x)
			{
				tmpMatrix[x] = new float[size - 1];
				for (int y = 0; y < size - 1; ++y)
				{
					if (a == i)
						++a;

					if (b == j)
						++b;

					tmpMatrix[x][y] = this->getData(a, b++);
				}
				++a;
				b = 0;
			}

			tmp.setData(i, j, (pow(-1, (i + j + 2)) * this->detLaplacea(size - 1, tmpMatrix)));
		}
	}

	return tmp;
}

template<unsigned size>
Macierz<size> Macierz<size>::invertibleMatrix(void)
{
	Macierz<size> tmp;

	float det = this->detLaplacea(size, this->getTab());
	std::cout << "Det = " << det << '\n';

	if (det != 0)
	{
		tmp = this->algebraicComplementMatrix();
		std::cout << "A^D: " << tmp << '\n';

		tmp = tmp.transposeMatrix();
		std::cout << "(A^D)^T: " << tmp << '\n';

		for (unsigned i = 0; i < size; ++i)
		{
			for (unsigned j = 0; j < size; ++j)
			{
				tmp.setData(i, j, tmp.getData(i, j) / det);
			}
		}
	}

	return tmp;
}