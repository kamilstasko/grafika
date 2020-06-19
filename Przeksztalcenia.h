#pragma once

#include "Macierz.h"

template <unsigned size>
class Przeksztalcenia
{
private:
	Macierz<size> matrix;
public:
	Przeksztalcenia(void);

	Macierz<3> macierzSkalowania2d(float x);
	Macierz<3> macierzSkalowania2d(float x, float y);
	Macierz<3> macierzSkalowania2d(float* tab);
	Macierz<3> macierzObrotu2d(float angle);
	Macierz<3> macierzTranslacji2d(float x);
	Macierz<3> macierzTranslacji2d(float x, float y);
	Macierz<3> macierzTranslacji2d(float* tab);

	Macierz<4> macierzSkalowania3d(float x);
	Macierz<4> macierzSkalowania3d(float x, float y, float z);
	Macierz<4> macierzSkalowania3d(float* tab);
	Macierz<4> macierzObrotu3d(float angle, unsigned type);
	Macierz<4> macierzObrotu3d(float angle, float* vec);
	Macierz<4> macierzTranslacji3d(float x);
	Macierz<4> macierzTranslacji3d(float x, float y, float z);
	Macierz<4> macierzTranslacji3d(float* tab);

	Macierz<size> getMatrix(void);
	void setMatrix(float val);
	void setMatrix(Macierz<size> other);

	Macierz<size> operacje(unsigned n, ...);
	Macierz<size> macierzPerspektyw(float angle, float height, float width, float nearZ, float farZ);

	Macierz<size> kierunekKamery(float* eye, float* top);
	Macierz<size> polozenieKamery(float x, float y, float z);
};

template<unsigned size>
inline Przeksztalcenia<size>::Przeksztalcenia(void)
{

}

template<unsigned size>
inline Macierz<3> Przeksztalcenia<size>::macierzSkalowania2d(float x)
{
	this->setMatrix(0);

	this->matrix.setData(0, 0, x);
	this->matrix.setData(1, 1, x);
	this->matrix.setData(2, 2, 1);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<3> Przeksztalcenia<size>::macierzSkalowania2d(float x, float y)
{
	this->setMatrix(0);

	this->matrix.setData(0, 0, x);
	this->matrix.setData(1, 1, y);
	this->matrix.setData(2, 2, 1);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<3> Przeksztalcenia<size>::macierzSkalowania2d(float* tab)
{
	this->setMatrix(0);

	this->matrix.setData(0, 0, tab[0]);
	this->matrix.setData(1, 1, tab[1]);
	this->matrix.setData(2, 2, 1);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<3> Przeksztalcenia<size>::macierzObrotu2d(float angle)
{
	this->setMatrix(0);

	this->matrix.setData(0, 0, cos(naRadiany(angle)));
	this->matrix.setData(0, 1, -sin(naRadiany(angle)));
	this->matrix.setData(1, 0, sin(naRadiany(angle)));
	this->matrix.setData(1, 1, cos(naRadiany(angle)));
	this->matrix.setData(2, 2, 1);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<3> Przeksztalcenia<size>::macierzTranslacji2d(float x)
{
	this->setMatrix(0);

	this->matrix.setData(0, 0, 1);
	this->matrix.setData(0, 2, x);
	this->matrix.setData(1, 1, 1);
	this->matrix.setData(1, 2, x);
	this->matrix.setData(2, 2, 1);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<3> Przeksztalcenia<size>::macierzTranslacji2d(float x, float y)
{
	this->setMatrix(0);

	this->matrix.setData(0, 0, 1);
	this->matrix.setData(0, 2, x);
	this->matrix.setData(1, 1, 1);
	this->matrix.setData(1, 2, y);
	this->matrix.setData(2, 2, 1);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<3> Przeksztalcenia<size>::macierzTranslacji2d(float * tab)
{
	this->setMatrix(0);

	this->matrix.setData(0, 0, 1);
	this->matrix.setData(0, 2, tab[0]);
	this->matrix.setData(1, 1, 1);
	this->matrix.setData(1, 2, tab[1]);
	this->matrix.setData(2, 2, 1);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<4> Przeksztalcenia<size>::macierzSkalowania3d(float x)
{
	this->setMatrix(0);

	this->matrix.setData(0, 0, x);
	this->matrix.setData(1, 1, x);
	this->matrix.setData(2, 2, x);
	this->matrix.setData(3, 3, 1);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<4> Przeksztalcenia<size>::macierzSkalowania3d(float x, float y, float z)
{
	this->setMatrix(0);

	this->matrix.setData(0, 0, x);
	this->matrix.setData(1, 1, y);
	this->matrix.setData(2, 2, z);
	this->matrix.setData(3, 3, 1);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<4> Przeksztalcenia<size>::macierzSkalowania3d(float * tab)
{
	this->setMatrix(0);

	this->matrix.setData(0, 0, tab[0]);
	this->matrix.setData(1, 1, tab[1]);
	this->matrix.setData(2, 2, tab[2]);
	this->matrix.setData(3, 3, 1);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<4> Przeksztalcenia<size>::macierzObrotu3d(float angle, unsigned type)
{
	this->setMatrix(0);

	if (type == 1)  //x
	{
		this->matrix.setData(0, 0, 1);
		this->matrix.setData(1, 1, cos(naRadiany(angle)));
		this->matrix.setData(1, 2, -sin(naRadiany(angle)));
		this->matrix.setData(2, 1, sin(naRadiany(angle)));
		this->matrix.setData(2, 2, cos(naRadiany(angle)));
		this->matrix.setData(3, 3, 1);
	}
	else if (type == 2) //y
	{
		this->matrix.setData(0, 0, cos(naRadiany(angle)));
		this->matrix.setData(0, 2, sin(naRadiany(angle)));
		this->matrix.setData(1, 1, 1);
		this->matrix.setData(2, 0, -sin(naRadiany(angle)));
		this->matrix.setData(2, 2, cos(naRadiany(angle)));
		this->matrix.setData(3, 3, 1);
	}
	else if (type == 3) //z
	{
		this->matrix.setData(0, 0, cos(naRadiany(angle)));
		this->matrix.setData(0, 1, -sin(naRadiany(angle)));
		this->matrix.setData(1, 0, sin(naRadiany(angle)));
		this->matrix.setData(1, 1, cos(naRadiany(angle)));
		this->matrix.setData(2, 2, 1);
		this->matrix.setData(3, 3, 1);
	}

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<4> Przeksztalcenia<size>::macierzObrotu3d(float angle, float * vec)
{
	this->setMatrix(0);

	this->matrix.setData(0, 0, pow(vec[0], 2) * (1 - cos(naRadiany(angle))) + cos(naRadiany(angle)));
	this->matrix.setData(0, 1, vec[0] * vec[1] * (1 - cos(naRadiany(angle))) - vec[2] * sin(naRadiany(angle)));
	this->matrix.setData(0, 2, vec[0] * vec[2] * (1 - cos(naRadiany(angle))) + vec[1] * sin(naRadiany(angle)));

	this->matrix.setData(1, 0, vec[0] * vec[1] * (1 - cos(naRadiany(angle))) + vec[2] * sin(naRadiany(angle)));
	this->matrix.setData(1, 1, pow(vec[1], 2) * (1 - cos(naRadiany(angle))) + cos(naRadiany(angle)));
	this->matrix.setData(1, 2, vec[1] * vec[2] * (1 - cos(naRadiany(angle))) - vec[0] * sin(naRadiany(angle)));

	this->matrix.setData(2, 0, vec[0] * vec[2] * (1 - cos(naRadiany(angle))) - vec[1] * sin(naRadiany(angle)));
	this->matrix.setData(2, 1, vec[1] * vec[2] * (1 - cos(naRadiany(angle))) + vec[0] * sin(naRadiany(angle)));
	this->matrix.setData(2, 2, pow(vec[2], 2) * (1 - cos(naRadiany(angle))) + cos(naRadiany(angle)));

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<4> Przeksztalcenia<size>::macierzTranslacji3d(float x)
{
	this->setMatrix(0);

	this->matrix.setData(0, 0, 1);
	this->matrix.setData(0, 3, x);
	this->matrix.setData(1, 1, 1);
	this->matrix.setData(1, 3, x);
	this->matrix.setData(2, 2, 1);
	this->matrix.setData(2, 3, x);
	this->matrix.setData(3, 3, 1);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<4> Przeksztalcenia<size>::macierzTranslacji3d(float x, float y, float z)
{
	this->setMatrix(0);

	this->matrix.setData(0, 0, 1);
	this->matrix.setData(0, 3, x);
	this->matrix.setData(1, 1, 1);
	this->matrix.setData(1, 3, y);
	this->matrix.setData(2, 2, 1);
	this->matrix.setData(2, 3, z);
	this->matrix.setData(3, 3, 1);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<4> Przeksztalcenia<size>::macierzTranslacji3d(float * tab)
{
	this->setMatrix(0);

	this->matrix.setData(0, 0, 1);
	this->matrix.setData(0, 3, tab[0]);
	this->matrix.setData(1, 1, 1);
	this->matrix.setData(1, 3, tab[1]);
	this->matrix.setData(2, 2, 1);
	this->matrix.setData(2, 3, tab[2]);
	this->matrix.setData(3, 3, 1);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<size> Przeksztalcenia<size>::getMatrix(void)
{
	return this->matrix;
}

template<unsigned size>
inline void Przeksztalcenia<size>::setMatrix(float val)
{
	for (unsigned i = 0; i < size; ++i)
	{
		for (unsigned j = 0; j < size; ++j)
		{
			this->matrix.setData(i, j, val);
		}
	}
}

template<unsigned size>
inline void Przeksztalcenia<size>::setMatrix(Macierz<size> other)
{
	this->matrix = other;
}

template<unsigned size>
inline Macierz<size> Przeksztalcenia<size>::operacje(unsigned n, ...)
{
	va_list list_pointer;
	va_start(list_pointer, n);

	for (unsigned i = 0; i < n; ++i)
	{
		if (i == 0)
		{
			this->setMatrix(va_arg(list_pointer, Macierz<size>));
		}
		else
		{
			this->setMatrix(this->getMatrix() * va_arg(list_pointer, Macierz<size>));
		}
	}

	va_end(list_pointer);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<size> Przeksztalcenia<size>::macierzPerspektyw(float angle, float height, float width, float nearZ, float farZ)
{
	this->setMatrix(0);

	float n = nearZ;
	float f = farZ;
	float r = -n * tan(naRadiany(angle / 2));
	float a = width / height;

	this->matrix.setData(0, 0, -n / (r*a));
	this->matrix.setData(1, 1, -n / r);
	this->matrix.setData(2, 2, (f + n) / (n - f));
	this->matrix.setData(2, 3, (2 * f*n) / (f - n));
	this->matrix.setData(3, 2, -1);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<size> Przeksztalcenia<size>::kierunekKamery(float * eye, float * top)
{
	this->setMatrix(0);
	
	if (eye[0] != 0)
	{
		eye[0] = -eye[0];
	}
	
	if (eye[1] != 0)
	{
		eye[1] = -eye[1];
	}

	if (eye[2] != 0)
	{
		eye[2] = -eye[2];
	}
	
	float F = sqrt(eye[0] * eye[0] + eye[1] * eye[1] + eye[2] * eye[2]);
	float U = sqrt(top[0] * top[0] + top[1] * top[1] + top[2] * top[2]);
	float UFx = top[1] * eye[2] - top[2] * eye[1];
	float UFy = -(top[0] * eye[2] - top[2] * eye[0]);
	float UFz = top[0] * eye[1] - top[1] * eye[0];
	float R = sqrt(UFx * UFx + UFy * UFy + UFz * UFz);

	if (F > 0)
	{
		eye[0] /= F;
		eye[1] /= F;
		eye[2] /= F;
	}

	if (U > 0)
	{
		top[0] /= U;
		top[1] /= U;
		top[2] /= U;
	}

	if (R > 0)
	{
		UFx /= R;
		UFy /= R;
		UFz /= R;
	}

	this->matrix.setData(0, 0, UFx);
	this->matrix.setData(0, 1, UFy);
	this->matrix.setData(0, 2, UFz);

	this->matrix.setData(1, 0, top[0]);
	this->matrix.setData(1, 1, top[1]);
	this->matrix.setData(1, 2, top[2]);
	
	this->matrix.setData(2, 0, eye[0]);
	this->matrix.setData(2, 1, eye[1]);
	this->matrix.setData(2, 2, eye[2]);
	
	this->matrix.setData(3, 3, 1);

	return this->getMatrix();
}

template<unsigned size>
inline Macierz<size> Przeksztalcenia<size>::polozenieKamery(float x, float y, float z)
{
	this->setMatrix(0);

	if (x != 0)
	{
		x = -x;
	}

	if (y != 0)
	{
		y = -y;
	}

	if (z != 0)
	{
		z = -z;
	}

	this->matrix.setData(0, 0, 1);
	this->matrix.setData(0, 3, x);
	this->matrix.setData(1, 1, 1);
	this->matrix.setData(1, 3, y);
	this->matrix.setData(2, 2, 1);
	this->matrix.setData(2, 3, z);
	this->matrix.setData(3, 3, 1);

	return this->getMatrix();
}