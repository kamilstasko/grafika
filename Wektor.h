#pragma once

template <unsigned size>
class Wektor
{
private:
	float coordinates[size];
public:
	Wektor(void);
	Wektor(float x);
	Wektor(float x, float y, float z);
	Wektor(float x, float y, float z, float w);
	Wektor(float* tab);
	Wektor(float tab[size]);
	~Wektor(void);

	Wektor<size>& operator=(Wektor<size> other);
	Wektor<size> operator+(Wektor<size>& other);
	Wektor<size> operator+=(Wektor<size>& other);
	Wektor<size> operator-(Wektor<size>& other);
	Wektor<size> operator-=(Wektor<size>& other);
	Wektor<size> operator*(const int val);
	Wektor<size> operator*=(const int val);
	friend std::ostream& operator<<(std::ostream& os, Wektor<size>& data)
	{
		os << '<' << data.getX() << ',' << data.getY() << ',' << data.getZ();

		if (size == 4)
		{
			os << ',' << data.getW();
		}

		return os << '>';
	}

	void setX(float x);
	float getX(void);
	void setY(float y);
	float getY(void);
	void setZ(float z);
	float getZ(void);
	void setW(float w);
	float getW(void);

	Wektor<size> normalize(void);
	float scalarProd(Wektor<size>& other);
	Wektor<size> vectorProd(Wektor<size>& other);
};

template <unsigned size>
Wektor<size>::Wektor(void)
{
	for (unsigned i = 0; i < size; ++i)
	{
		this->coordinates[i] = 0;
	}
}

template <unsigned size>
Wektor<size>::Wektor(float x)
{
	for (unsigned i = 0; i < size; ++i)
	{
		this->coordinates[i] = x;
	}
}

template <unsigned size>
Wektor<size>::Wektor(float x, float y, float z)
{
	this->coordinates[0] = x;
	this->coordinates[1] = y;
	this->coordinates[2] = z;
}

template <unsigned size>
Wektor<size>::Wektor(float x, float y, float z, float w)
{
	this->coordinates[0] = x;
	this->coordinates[1] = y;
	this->coordinates[2] = z;
	this->coordinates[3] = w;
}

template <unsigned size>
Wektor<size>::Wektor(float* tab)
{
	for (unsigned i = 0; i < size; ++i)
	{
		this->coordinates[i] = tab[i];
	}
}

template<unsigned size>
inline Wektor<size>::Wektor(float tab[size])
{
	for (unsigned i = 0; i < size; ++i)
	{
		this->coordinates[i] = tab[i];
	}
}

template <unsigned size>
Wektor<size>::~Wektor(void)
{

}

template<unsigned size>
Wektor<size>& Wektor<size>::operator=(Wektor<size> other)
{
	if (this != &other)
	{
		this->setX(other.getX());
		this->setY(other.getY());
		this->setZ(other.getZ());

		if (size == 4)
		{
			this->setW(other.getW());
		}
	}

	return *this;
}

template<unsigned size>
Wektor<size> Wektor<size>::operator+(Wektor<size>& other)
{
	if (size == 3)
	{
		return Wektor<size>(
				this->getX() + other.getX(),
				this->getY() + other.getY(),
				this->getZ() + other.getZ()
			);
	}
	else
	{
		return Wektor<size>(
				this->getX() + other.getX(),
				this->getY() + other.getY(),
				this->getZ() + other.getZ(),
				this->getW() + other.getW()
			);
	}
}

template<unsigned size>
Wektor<size> Wektor<size>::operator+=(Wektor<size>& other)
{
	this->setX(this->getX() + other.getX());
	this->setY(this->getY() + other.getY());
	this->setZ(this->getZ() + other.getZ());

	if (size == 4)
	{
		this->setW(this->getW() + other.getW());
	}

	return *this;
}

template<unsigned size>
Wektor<size> Wektor<size>::operator-(Wektor<size>& other)
{
	if (size == 3)
	{
		return Wektor<size>(
			this->getX() - other.getX(),
			this->getY() - other.getY(),
			this->getZ() - other.getZ()
			);
	}
	else
	{
		return Wektor<size>(
			this->getX() - other.getX(),
			this->getY() - other.getY(),
			this->getZ() - other.getZ(),
			this->getW() - other.getW()
			);
	}
}

template<unsigned size>
Wektor<size> Wektor<size>::operator-=(Wektor<size>& other)
{
	this->setX(this->getX() - other.getX());
	this->setY(this->getY() - other.getY());
	this->setZ(this->getZ() - other.getZ());

	if (size == 4)
	{
		this->setW(this->getW() - other.getW());
	}

	return *this;
}

template<unsigned size>
Wektor<size> Wektor<size>::operator*(const int val)
{
	if (size == 3)
	{
		return Wektor<size>(
			this->getX() * val,
			this->getY() * val,
			this->getZ() * val
			);
	}
	else
	{
		return Wektor<size>(
			this->getX() * val,
			this->getY() * val,
			this->getZ() * val,
			this->getW() * val
			);
	}
}

template<unsigned size>
Wektor<size> Wektor<size>::operator*=(const int val)
{
	this->setX(this->getX() * val);
	this->setY(this->getY() * val);
	this->setZ(this->getZ() * val);

	if (size == 4)
	{
		this->setW(this->getW() * val);
	}

	return *this;
}

template <unsigned size>
void Wektor<size>::setX(float x)
{
	this->coordinates[0] = x;
}

template <unsigned size>
float Wektor<size>::getX(void)
{
	return this->coordinates[0];
}

template <unsigned size>
void Wektor<size>::setY(float y)
{
	this->coordinates[1] = y;
}

template <unsigned size>
float Wektor<size>::getY(void)
{
	return this->coordinates[1];
}

template <unsigned size>
void Wektor<size>::setZ(float z)
{
	this->coordinates[2] = z;
}

template <unsigned size>
float Wektor<size>::getZ(void)
{
	return this->coordinates[2];
}

template <unsigned size>
void Wektor<size>::setW(float w)
{
	this->coordinates[3] = w;
}

template <unsigned size>
float Wektor<size>::getW(void)
{
	return this->coordinates[3];
}

template<unsigned size>
Wektor<size> Wektor<size>::normalize(void)
{
	float d = pow(this->getX(), 2) + pow(this->getY(), 2) + pow(this->getZ(), 2);
	if (size == 4)
	{
		d += pow(this->getW(), 2);
	}

	d = sqrt(d);
	
	if (d > 0)
	{
		if (size == 3)
		{
			return Wektor<size>(
					this->getX() / d,
					this->getY() / d,
					this->getZ() / d
				);
		}

		return Wektor<size>(
				this->getX() / d,
				this->getY() / d,
				this->getZ() / d,
				this->getW() / d
			);
	}
	
	return *this;
}

template<unsigned size>
float Wektor<size>::scalarProd(Wektor<size>& other)
{
	float val = this->getX() * other.getX() + this->getY() * other.getY() + this->getZ() * other.getZ();

	if (size == 4)
	{
		val += this->getW() * other.getW();
	}

	return val;
}

template<unsigned size>
Wektor<size> Wektor<size>::vectorProd(Wektor<size>& other)
{
	return Wektor<size>(
			this->getY() * other.getZ() - this->getZ() * other.getY(),
			this->getZ() * other.getX() - this->getX() * other.getZ(),
			this->getX() * other.getY() - this->getY() * other.getX()
		);
}