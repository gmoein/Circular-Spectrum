//   Acomplex.h - declaration of class
//   of Acomplex number
//
//   The code is property of LIBROW
//   You can use it on your own
//   When utilizing credit LIBROW site

#ifndef _ACOMPLEX_H_
#define _ACOMPLEX_H_

class Acomplex
{
protected:
	//   Internal presentation - real and imaginary parts
	double m_re;
	double m_im;

public:
	//   Imaginary unity
    static const Acomplex i;
    static const Acomplex j;

	//   Constructors
    Acomplex(): m_re(0.), m_im(0.) {}
    Acomplex(double re, double im): m_re(re), m_im(im) {}
    Acomplex(double val): m_re(val), m_im(0.) {}

	//   Assignment
    Acomplex& operator= (const double val)
	{
		m_re = val;
		m_im = 0.;
		return *this;
	}

	//   Basic operations - taking parts
	double re() const { return m_re; }
	double im() const { return m_im; }

	//   Conjugate number
    Acomplex conjugate() const
	{
        return Acomplex(m_re, -m_im);
	}

	//   Norm   
	double norm() const
	{
		return m_re * m_re + m_im * m_im;
	}

	//   Arithmetic operations
    Acomplex operator+ (const Acomplex& other) const
	{
        return Acomplex(m_re + other.m_re, m_im + other.m_im);
	}

    Acomplex operator- (const Acomplex& other) const
	{
        return Acomplex(m_re - other.m_re, m_im - other.m_im);
	}

    Acomplex operator* (const Acomplex& other) const
	{
        return Acomplex(m_re * other.m_re - m_im * other.m_im,
			m_re * other.m_im + m_im * other.m_re);
	}

    Acomplex operator/ (const Acomplex& other) const
	{
		const double denominator = other.m_re * other.m_re + other.m_im * other.m_im;
        return Acomplex((m_re * other.m_re + m_im * other.m_im) / denominator,
			(m_im * other.m_re - m_re * other.m_im) / denominator);
	}

    Acomplex& operator+= (const Acomplex& other)
	{
		m_re += other.m_re;
		m_im += other.m_im;
		return *this;
	}

    Acomplex& operator-= (const Acomplex& other)
	{
		m_re -= other.m_re;
		m_im -= other.m_im;
		return *this;
	}

    Acomplex& operator*= (const Acomplex& other)
	{
		const double temp = m_re;
		m_re = m_re * other.m_re - m_im * other.m_im;
		m_im = m_im * other.m_re + temp * other.m_im;
		return *this;
	}

    Acomplex& operator/= (const Acomplex& other)
	{
		const double denominator = other.m_re * other.m_re + other.m_im * other.m_im;
		const double temp = m_re;
		m_re = (m_re * other.m_re + m_im * other.m_im) / denominator;
		m_im = (m_im * other.m_re - temp * other.m_im) / denominator;
		return *this;
	}

    Acomplex& operator++ ()
	{
		++m_re;
		return *this;
	}

    Acomplex operator++ (int)
	{
        Acomplex temp(*this);
		++m_re;
		return temp;
	}

    Acomplex& operator-- ()
	{
		--m_re;
		return *this;
	}

    Acomplex operator-- (int)
	{
        Acomplex temp(*this);
		--m_re;
		return temp;
	}

    Acomplex operator+ (const double val) const
	{
        return Acomplex(m_re + val, m_im);
	}

    Acomplex operator- (const double val) const
	{
        return Acomplex(m_re - val, m_im);
	}

    Acomplex operator* (const double val) const
	{
        return Acomplex(m_re * val, m_im * val);
	}

    Acomplex operator/ (const double val) const
	{
        return Acomplex(m_re / val, m_im / val);
	}

    Acomplex& operator+= (const double val)
	{
		m_re += val;
		return *this;
	}

    Acomplex& operator-= (const double val)
	{
		m_re -= val;
		return *this;
	}

    Acomplex& operator*= (const double val)
	{
		m_re *= val;
		m_im *= val;
		return *this;
	}

    Acomplex& operator/= (const double val)
	{
		m_re /= val;
		m_im /= val;
		return *this;
	}

    friend Acomplex operator+ (const double left, const Acomplex& right)
	{
        return Acomplex(left + right.m_re, right.m_im);
	}

    friend Acomplex operator- (const double left, const Acomplex& right)
	{
        return Acomplex(left - right.m_re, -right.m_im);
	}

    friend Acomplex operator* (const double left, const Acomplex& right)
	{
        return Acomplex(left * right.m_re, left * right.m_im);
	}

    friend Acomplex operator/ (const double left, const Acomplex& right)
	{
		const double denominator = right.m_re * right.m_re + right.m_im * right.m_im;
        return Acomplex(left * right.m_re / denominator,
			-left * right.m_im / denominator);
	}

	//   Boolean operators
    bool operator== (const Acomplex &other) const
	{
		return m_re == other.m_re && m_im == other.m_im;
	}

    bool operator!= (const Acomplex &other) const
	{
		return m_re != other.m_re || m_im != other.m_im;
	}

	bool operator== (const double val) const
	{
		return m_re == val && m_im == 0.;
	}

	bool operator!= (const double val) const
	{
		return m_re != val || m_im != 0.;
	}

    friend bool operator== (const double left, const Acomplex& right)
	{
		return left == right.m_re && right.m_im == 0.;
	}

    friend bool operator!= (const double left, const Acomplex& right)
	{
		return left != right.m_re || right.m_im != 0.;
	}
};

#endif
