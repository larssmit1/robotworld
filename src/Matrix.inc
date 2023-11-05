#include <cassert>
#include <stdexcept>
#include <numeric>
#include <cmath>
#include <utility>
#include <iomanip>

/**
 *
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N >::Matrix( T value)
{
	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column)
		{
			matrix.at( row).at( column) = value;
		}
	}
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N >::Matrix( const std::initializer_list< T >& aList)
{
	// Check the arguments
	assert( aList.size() == M * N);

	auto row_iter = aList.begin();
	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column, ++row_iter)
		{
			matrix.at( row).at( column) = *row_iter;
		}
	}
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N >::Matrix( const std::initializer_list< std::initializer_list< T > >& aList)
{
	// Check the arguments, the static assert assures that there is at least 1 M and 1 N!
	assert( aList.size() == M && (*aList.begin()).size() == N);

	auto row_iter = aList.begin();
	for (std::size_t row = 0; row < aList.size(); ++row, ++row_iter)
	{
		auto column_iter = (*row_iter).begin();
		for (std::size_t column = 0; column < (*row_iter).size(); ++column, ++column_iter)
		{
			matrix.at( row).at( column) = *column_iter;
		}
	}
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N >::Matrix( const Matrix< T, M, N >& aMatrix) :
				matrix( aMatrix.matrix)
{
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
std::array< T, N >& Matrix< T, M, N >::at( std::size_t aRowIndex)
{
	return matrix.at( aRowIndex);
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
const std::array< T, N >& Matrix< T, M, N >::at( std::size_t aRowIndex) const
{
	return matrix.at( aRowIndex);
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
T& Matrix< T, M, N >::at( 	std::size_t aRowIndex,
							std::size_t aColumnIndex)
{
	return matrix.at( aRowIndex).at( aColumnIndex);
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
const T& Matrix< T, M, N >::at( std::size_t aRowIndex,
								std::size_t aColumnIndex) const
{
	return matrix.at( aRowIndex).at( aColumnIndex);
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
std::array< T, N >& Matrix< T, M, N >::operator[]( std::size_t aRowIndex)
{
	return matrix[aRowIndex];
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
const std::array< T, N >& Matrix< T, M, N >::operator[]( std::size_t aRowIndex) const
{
	return matrix[aRowIndex];
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N >& Matrix< T, M, N >::operator=( const Matrix< T, M, N >& rhs)
{
	if (this != &rhs)
	{
		matrix = rhs.matrix;
	}
	return *this;
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
bool Matrix< T, M, N >::operator==( const Matrix< T, M, N >& rhs) const
{
	return matrix == rhs.matrix;
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
template< class T2 >
Matrix< T, M, N >& Matrix< T, M, N >::operator*=( const T2& scalar)
{
	static_assert( std::is_arithmetic<T2>::value, "Value T2 must be arithmetic, see http://en.cppreference.com/w/cpp/types/is_arithmetic");

	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column)
		{
			matrix.at( row).at( column) *= scalar;
		}
	}
	return *this;
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
template< class T2 >
Matrix< T, M, N > Matrix< T, M, N >::operator*( const T2& scalar) const
{
	static_assert( std::is_arithmetic<T2>::value, "Value T2 must be arithmetic, see http://en.cppreference.com/w/cpp/types/is_arithmetic");

	Matrix< T, M, N > result( *this);
	return result *= scalar;
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
template< class T2 >
Matrix< T, M, N >& Matrix< T, M, N >::operator/=( const T2& aScalar)
{
	static_assert( std::is_arithmetic<T2>::value, "Value T2 must be arithmetic, see http://en.cppreference.com/w/cpp/types/is_arithmetic");

	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column)
		{
			matrix.at( row).at( column) /= aScalar;
		}
	}
	return *this;
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
template< class T2 >
Matrix< T, M, N > Matrix< T, M, N >::operator/( const T2& aScalar) const
{
	static_assert( std::is_arithmetic<T2>::value, "Value T2 must be arithmetic, see http://en.cppreference.com/w/cpp/types/is_arithmetic");

	Matrix< T, M, N > result( *this);
	return result /= aScalar;
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N >& Matrix< T, M, N >::operator+=( const Matrix< T, M, N >& rhs)
{
	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column)
		{
			matrix[row][column] += rhs.at( row, column);
		}
	}
	return *this;
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N > Matrix< T, M, N >::operator+( const Matrix< T, M, N >& rhs) const
{
	Matrix< T, M, N > result( *this);
	return result += rhs;
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N >& Matrix< T, M, N >::operator-=( const Matrix< T, M, N >& rhs)
{
	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column)
		{
			matrix[row][column] -= rhs.at( row, column);
		}
	}
	return *this;
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N > Matrix< T, M, N >::operator-( const Matrix< T, M, N >& rhs) const
{
	Matrix< T, M, N > result( *this);
	return result -= rhs;
}
/**
 * (M, N) * (N, P) -> (M, P)
 */
template< typename T, std::size_t M, std::size_t N >
template< std::size_t columns >
Matrix< T, M, columns > Matrix< T, M, N >::operator*( const Matrix< T, N, columns >& rhs) const
{
    Matrix< T, M, columns > result;
	for(uint8_t i = 0; i < M; ++i)
    {
	    for(uint8_t j = 0; j < rhs.getColumns(); ++j)
        {
	        for(uint8_t k = 0; k < N; ++k)
            {
	            result.at(i,j) += matrix[i][k] * rhs.at(k, j);
            }
	    }
    }
	return result;
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, N, M > Matrix< T, M, N >::transpose() const
{
    Matrix< T, N, M > result;

    for(uint8_t i = 0; i < M; ++i)
    {
	    for(uint8_t j = 0; j < N; ++j)
        {
	        result.at(j, i) = matrix[i][j];
        }
    }
	return result;
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N > Matrix< T, M, N >::identity() const
{
	Matrix< T, N, M > result;
    for(uint8_t i = 0; i < M; ++i)
    {
        for(uint8_t j = 0; j < N; ++j)
        {
            if(i == j)
                result.at(i,j) = 1;
            else
                result.at(i,j) = 0;
        }
    }
	return result;
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N > Matrix< T, M, N >::gauss() const
{
    Matrix< T, M, N > result = *this;
    std::size_t pivotRow = 0;
    std::size_t pivotCol = 0;

    while (pivotRow < M && pivotCol < N)
    {
        T rowMax = 0;
        std::size_t largestIndex;

        /* zoek de index van de rij dat de hoogste waarde bevat */
        for (std::size_t i = pivotRow; i < M; ++i)
        {
            if (std::abs(result.at(i, pivotCol)) > rowMax)
            {
                rowMax = result.at(i, pivotCol);
                largestIndex = i;
            }
        }

        if (rowMax == 0)
        {
            ++pivotCol;
        }
        else
        {
            /* swap de rij met hoogste waarde naar pivot point */
            result.at(pivotRow).swap(result.at(largestIndex));

            /* Voor elke rij onder de pivot point */
            for (std::size_t i = pivotRow + 1; i < M; ++i)
            {
                double f = static_cast<double>(result.at(i, pivotCol))
                           / static_cast<double>(result.at(pivotRow, pivotCol));

                result.at(i, pivotCol) = 0;

                /* Voor alle overgebleven elemented in de huidige rij */
                for (std::size_t j = pivotCol + 1; j < N; ++j)
                {
                    result.at(i, j) = static_cast<T>( static_cast<double>(result.at(i, j)) -
                                                      static_cast<double>(result.at(pivotRow, j)) * f );
                }
            }
            /* Deel elk getal in de pivot-rij door de pivot waarde */
            double k = 1.0 / static_cast<double>(result.at(pivotRow, pivotCol));
            for (std::size_t i = pivotCol; i < N; ++i)
            {
                result.at(pivotRow, i) = static_cast<T>( static_cast<double>(result.at(pivotRow, i)) * k );
            }
            ++pivotRow;
            ++pivotCol;
        }
    }
    return result;
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N > Matrix< T, M, N >::gaussJordan() const
{
    Matrix < T, M, N > result = this->gauss();

    std::size_t pivotRow = 1;
    std::size_t pivotCol = 1;

    while (pivotRow < M && pivotCol < N)
    {
        /* Voor elke rij boven de pivot point */
        for (std::size_t i = 0; i < pivotRow; ++i)
        {
            double multiplier = static_cast<double>(result.at(i, pivotCol));

            result.at(i, pivotCol) = 0;

            /* Voor alle elementen in die rij */
            for (std::size_t j = pivotCol + 1; j < N; ++j)
            {
                result.at(i, j) = static_cast<T>( static_cast<double>(result.at(i, j)) - static_cast<double>(result.at(pivotRow, j)) * multiplier );
            }
        }
        ++pivotRow;
        ++pivotCol;
    }
    return result;
}

template< class T, std::size_t M, std::size_t N >
Matrix< T, M, 1 > Matrix< T, M, N >::solve() const
{
    Matrix < T, M, 1 > result;
    Matrix < T, M, N> solved = this->gaussJordan();

    for (std::size_t i = 0; i < M; ++i)
    {
        result.at(i, 0) = solved.at(i, N - 1);
    }

    return result;
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N > Matrix< T, M, N >::inverse() const
{
    Matrix< T, N, M > result;
    Matrix< T, M, N*2 > solved;
    Matrix< T, M, N > identity = this->identity();

    for (std::size_t row = 0; row < M; ++row)
    {
        for (std::size_t col = 0; col < N*2; ++col)
        {
            if (col < N)
            {
                solved.at(row, col) = this->at(row, col);
            }
            else
            {
                solved.at(row, col) = identity.at(row, col % N);
            }
        }
    }

    solved = solved.gaussJordan();

    for (std::size_t row = 0; row < N; ++row)
    {
        for (std::size_t col = 0; col < M; ++col)
        {
            result.at(row, col) = solved.at(row, M + col);
        }
    }

    return result;
}
/**
 *
 */
template< class T, std::size_t M, std::size_t N >
std::string Matrix< T, M, N >::to_string() const
{
	std::string result = "Matrix<" + std::to_string( N) + "," + std::to_string( M) + ">\n{\n";
	for (std::size_t i = 0; i < M; ++i)
	{
		for (std::size_t j = 0; j < N; ++j)
		{
			result += std::to_string( matrix[i][j]) + ",";
		}
		result += "\n";
	}
	result += "}";
	return result;
}
/**
 *
 */
template< typename T, const std::size_t N >
bool equals(	const Matrix< T, 1, N >& lhs,
				const Matrix< T, 1, N >& rhs,
				const T aPrecision /*= std::numeric_limits<T>::epsilon()*/,
				const unsigned long aFactor /*= 1*/)
{
	for(std::size_t i = 0; i < N; ++i)
	{
		T absDiff = std::abs(lhs.at(0, i) - rhs.at(0, i));
		bool isCloseEnough = absDiff  <= aPrecision * aFactor;

		if(!isCloseEnough)
			return false;
	}
	return true;
}
/**
 *
 */
template< typename T, const std::size_t M >
bool equals(	const Matrix< T, M, 1 >& lhs,
				const Matrix< T, M, 1 >& rhs,
				const T aPrecision /*= std::numeric_limits<T>::epsilon()*/,
				const unsigned long aFactor /*= 1*/)
{
	for(std::size_t i = 0; i < M; ++i)
	{
		T absDiff = std::abs(lhs.at(i, 0) - rhs.at(i, 0));
		bool isCloseEnough = absDiff <= aPrecision * aFactor;

		if(!isCloseEnough)
			return false;
	}

	return true;
}
/**
 *
 */
template< typename T, const std::size_t M, const std::size_t N >
bool equals(	const Matrix< T, M, N >& lhs,
				const Matrix< T, M, N >& rhs,
				const T aPrecision /*= std::numeric_limits<T>::epsilon()*/,
				const unsigned long aFactor /*= 1*/)
{
	for(std::size_t i = 0; i < M; ++i)
		for(std::size_t j = 0; j < N; ++j)
		{
			T absDiff = std::abs(lhs.at(i, j) - rhs.at(i, j));
			bool isCloseEnough = absDiff <= aPrecision * aFactor;

			if(!isCloseEnough)
				return false;
		}

	return true;
}
