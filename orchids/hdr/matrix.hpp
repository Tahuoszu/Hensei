/**
 *
 *  @file			matrix.hpp
 *  @brief          Matrix class
 *  @version        0.04
 *  @author			Antoine Bouchereau
 *	@date			16-12-2013
 *
 */

#ifndef __Orchids__matrix__
#define __Orchids__matrix__

#include "Orchids.h"

/**
 *  @class Matrix
 */
template<typename T>
class TArray2
{
public:
    
    // Typedefs
    typedef T value_type;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    
    /**
     *  @brief Constructor
     */
    TArray2(int rows=0, int cols=0)
    : m_Rows(0),
    m_Cols(0),
    m_OwnsData(true),
    p_Data(0)
    {
        if (rows * cols != 0)
        {
            p_Data = (T *)calloc(rows * cols, sizeof(T));
            //memset(p_Data, 0, sizeof(T) * rows * cols);
        }
        m_Rows = rows;
        m_Cols = cols;
    }
    
    /**
     *  @brief Construct given external data
     */
    TArray2(T* pAry, bool ownsData, int rows=1, int cols=1)
    : m_Rows(rows),
    m_Cols(cols),
    m_OwnsData(ownsData),
    p_Data(pAry)
    {
        //assert(0 != p_Data);
    }
    
    /**
     *  @brief Copy constructor
     */
    TArray2(const TArray2<T>& a)
    {
        p_Data = (T *)malloc(a.rows() * a.cols() * sizeof(T));
        std::copy(a.begin(), a.end(), p_Data);
        m_Rows = a.rows();
        m_Cols = a.cols();
        m_OwnsData = true;
    }
    
    /**
     *  @brief Assignmant operation
     */
    TArray2& operator = (const TArray2<T>& a)
    {
        p_Data = (T *)malloc(a.rows() * a.cols() * sizeof(T));
        m_Rows = a.rows();
        m_Cols = a.cols();
        std::copy(a.begin(), a.end(), p_Data);
        m_OwnsData = true;
        return *this;
    }
    
    /**
     *  @brief Destructor
     */
    ~TArray2()
    {
        if (m_OwnsData) { free(p_Data); }
    }
    
    /**
     *  @brief Deallocation of p_data
     */
    void deallocate()
    {
        delete [] p_Data;
        p_Data = NULL;
    }
    
    /**
     *  @brief Set number of rows
     */
    inline void setRows(int rows) { m_Rows = rows; }
    /**
     *  @brief Set number of cols
     */
    inline void setCols(int cols) { m_Cols = cols; }
    /**
     *  @brief Set data
     */
    void setData(float *data, int size)
    {
        p_Data = (T *)malloc(size * sizeof(float));
        std::copy(&data[0], &data[size], p_Data);
    }
    /**
     *  @brief Set ownsData
     */
    inline void setOwnsData(bool ownsData) { m_OwnsData = ownsData; }

    
    /**
     *  @brief Number of rows retrieval
     */
    inline int rows() const { return m_Rows; }
    /**
     *  @brief Number of cols retrieval
     */
    inline int cols() const { return m_Cols; }
    /**
     *  @brief Size retrieval
     */
    inline int size() const { return rows()*cols(); }
    /**
     *  @brief Bytes retrieval
     */
    inline int bytes() const { return size()*sizeof(value_type); }
    
    /**
     *  @brief Check if empty matrix
     */
    inline bool isEmpty() { return size() == 0; }
    
    /**
     *  @brief Fill matrix with a value
     */
    void fill(value_type val)
    {
        std::uninitialized_fill_n( p_Data, size(), val );
    }
    
    /**
     *  @brief Swap contents with another matrix
     */
    void swap(TArray2<T>& ary)
    {
        std::swap( m_Rows, ary.m_Rows );
        std::swap( m_Cols, ary.m_Cols );
        std::swap( m_OwnsData, ary.m_OwnsData );
        std::swap( p_Data, ary.p_Data );
    }

    /**
     *  @brief Resize data bank
     */
    void resizeTo(int rows, int cols, bool keepData)
    {
        // Sanity check
        int nElements = rows * cols;
        //assert( nElements > 0 );
        
        // No change, return
        if (rows == m_Rows && cols == m_Cols)
            return;
        
        // If we want to keep existing data
        if (keepData)
        {
            p_Data = (T *)realloc(p_Data, nElements * sizeof(T)); // Reallocate data bank
        }
        else
        {
            deallocate();
            p_Data = (T *)malloc(nElements * sizeof(T)); // Allocate data bank
        }
        
        m_Rows = rows;
        m_Cols = cols;
    }
    
    /**
     *  @brief Return the kth row
     */
    inline T* getRow(int k)
    {
        //assert(k < rows());
        T *arr1d = (T *)malloc(m_Cols * sizeof(T));
        
        for(int i = 0; i < m_Cols; i++)
            arr1d[i] = p_Data[ m_Cols * k + i ];
        
        return arr1d;
    }
    
    /**
     *  @brief Return the kth column
     */
    T* getCol(int k)
    {
        //assert(k < cols());
        T *arr1d = (T *)malloc(m_Rows * sizeof(T));
        
        for(int i = 0; i < m_Rows; i++)
            arr1d[i] = p_Data[ m_Cols * i + k ];
        
        return arr1d;
    }
    
    /**
     *  @brief Return values between row1 and row2 at the kth column
     */
    T* getCol(int k, int row1, int row2)
    {
        //assert(k < cols());
        //assert(row2 < rows());
        //assert(row2 >= row1);
        
        T *arr1d = (T *)malloc((row2 - row1 + 1) * sizeof(T));
        
        int index = 0;
        for(int i = row1; i <= row2; i++)
        {
            arr1d[index] = p_Data[ m_Cols * i + k ];
            index++;
        }
        
        return arr1d;
    }
    
    /**
     *  @brief Delete the ith row
     */
    void delRow(int irow)
    {
        assert(irow < m_Rows);
        
        int n = rows();
        int m = cols() ;
        
        if ( n <= 1 || m == 0 ) return ;
        
        TArray2<T> B(n - 1, m) ;
        for ( int i = 0; i < irow; i++ )
            for ( int j = 0; j < m; j++)
                B(i, j) = p_Data[ m_Cols * i + j ] ;
        for ( int i = irow+1; i < n; i++ )
            for ( int j = 0; j < m; j++)
                B(i - 1, j) = p_Data[ m_Cols * i + j ] ;
        
        resizeTo(n-1, m, false);
        for ( int i = 0; i < n-1; i++ )
            for ( int j = 0; j < m; j++)
                p_Data[ m_Cols * i + j ] = B(i, j) ;
    }
    
    /**
     *  @brief Delete the ith column
     */
    void delCol(int icol)
    {
        assert(icol < m_Cols);
        
        int n = rows();
        int m = cols() ;
        
        if ( n == 0 || m <= 1 ) return ;
        
        TArray2<T> B(n, m - 1) ;
        for ( int i = 0; i < n; i++ )
            for ( int j = 0; j < icol; j++)
                B(i, j) = p_Data[ m_Cols * i + j ] ;
        for ( int i = 0; i < n; i++ )
            for ( int j = icol+1; j < m; j++)
                B(i, j - 1) = p_Data[ m_Cols * i + j ] ;
        
        resizeTo(n, m-1, false);
        for ( int i = 0; i < n; i++ )
            for ( int j = 0; j < m-1; j++)
                p_Data[ m_Cols * i + j ] = B(i, j) ;
    }
    
    /**
     *  @brief Optimized version of merge
     */
    void merge2(TArray2<T>& y)
    {
        if (isEmpty())
            swap(y);
        else
        {
            if (y.rows() > 1)
            {
                //Merging a column Nx1
                //Current matrix NxM
                TArray2<T> res;
                res.resizeTo(y.rows(), cols() + y.cols(), false);
                
                //Copy current matrix into res
                for (int i = 0; i < rows(); i++)
                    for (int j = 0; j < cols(); j++)
                        res(i, j) = p_Data[ m_Cols * i + j ];
                
                //Copy matrix to merge into res
                for (int i = 0; i < y.rows(); i++)
                    for (int j = cols(); j < res.cols(); j++)
                        res(i, j) = y(i, j - cols());
                
                swap(res);
            }
            else
            {
                //Merging a row 1xN or 1x1
                //Current matrix MxN
                resizeTo(rows() + 1, y.cols(), true);
                
                //Add the row under the matrix
                for (int i = rows() - 1; i < rows(); i++)
                    for (int j = 0; j < cols(); j++)
                        p_Data[ m_Cols * i + j ] = y(i - rows() + 1, j);
            }
        }
    }
    
    /**
     *  @brief Add a row under the matrix
     */
    void quickmerge(float *y)
    {
        resizeTo(rows() + 1, cols(), true);
                
        //Add the row under the matrix
        for (int j = 0; j < cols(); j++)
            p_Data[ m_Cols * (rows() - 1) + j ] = y[j];
        
        free(y);
    }
    
    /**
     *  @brief Return the transposed current matrix
     */
    void transpose()
    {
        TArray2<T> t(cols(), rows());
        
        for (int i = 0; i < cols(); i++)
            for (int j = 0; j < rows(); j++)
                t(i, j) =  p_Data[ m_Cols * j + i ];

        deallocate();
        swap(t);
    }
    
    /**
     *  @brief Retrieve cols between col1 and col2 of the current matrix
     */
    void resizeMatrixByCol(int col1, int col2)
    {
        //assert(col1 <= col2);
        //assert(col2 <= cols());
        
        TArray2<T> savedValues(rows(), col2 - col1 + 1);
        int j;
        
        for (int i = 0; i < rows(); i++) {
            j = 0;
            do {
                savedValues(i, j) = p_Data[ m_Cols * i + col1 + j - 1 ];
                j++;
            } while (j <= col2 - col1);
        }
        
        deallocate();
        swap(savedValues);
    }
    
    /**
     *  @brief Retrieve rows between row1 and row2 of the current matrix
     */
    TArray2 resizeMatrixByRow(int row1, int row2)
    {
        assert( row2 < rows() );
        
        TArray2<T> savedValues(row2 - row1 + 1, cols());
        
        for (int i = row1; i <= row2; i++)
            for (int j = 0; j < cols(); j++)
                savedValues(i - row1, j) = p_Data[ m_Cols * i + j ];
        
        return savedValues;
    }
    
    /**
     *  @brief Print datas as a matrix
     */
    void print()
    {
        for (int i = 0; i < rows(); ++i)
        {
            for (int j = 0; j < cols(); ++j)
                cout << p_Data[ m_Cols * i + j ] << " ";
            cout << endl;
        }
    }
    
    //Mathematicals functions
    /**
     *  @brief Return the sum values for elements along the dimension dim
     *  dim = 1 -> vector containing the sum value of each column
     *  dim = 2 -> vector containing the sum value of each row
     */
    T* getSum(int dim)
    {
        T*  res;
        T   sum;
        
        switch (dim) {
            case 1:
                res = (T *)malloc(cols() * sizeof(T));
                for (int i = 0; i < cols(); i++)
                {
                    sum = 0;
                    for (int j = 0; j < rows(); j++)
                        sum += p_Data[ m_Cols * j + i ];
                    res[i] = sum;
                }
                break;
                
            case 2:
                res = (T *)malloc(rows() * sizeof(T));
                for (int i = 0; i < rows(); i++)
                {
                    sum = 0;
                    for (int j = 0; j < cols(); j++)
                        sum += p_Data[ m_Cols * i + j ];
                    res[i] = sum;
                }
                break;
                
            default:
                return 0;
                break;
        }

        return res;
    }
    
    /**
     *  @brief Return the norm of the current matrix
     */
    float norm()
    {
        int     i, j;
        float   sum = 0.0, nrm;
        
        for(i = 0; i < m_Rows; i++)
            for(j = 0; j < m_Cols; j++)
                sum += p_Data[ m_Cols * i + j ] * p_Data[ m_Cols * i + j ];

        //sqrt(parameter) function for square root
        nrm = sqrt(sum);
        
        // return float value to function call
        return nrm;
    }
    
    
    /**
     *  @brief Return the mean values for elements along the dimension dim
     *  dim = 1 -> vector containing the mean value of each column
     *  dim = 2 -> vector containing the mean value of each row
     */
    T*  getMean(int dim)
    {
        T*  res;
        T sum;
        
        switch (dim) {
            case 1:
                res = (T *)malloc(cols() * sizeof(T));
                for (int i = 0; i < cols(); i++)
                {
                    sum = 0;
                    for (int j = 0; j < rows(); j++)
                        sum += p_Data[ m_Cols * j + i ];
                    res[i] = sum / rows();
                }
                break;
                
            case 2:
                res = (T *)malloc(rows() * sizeof(T));
                for (int i = 0; i < rows(); i++)
                {
                    sum = 0;
                    for (int j = 0; j < cols(); j++)
                        sum += p_Data[ m_Cols * i + j ];
                    res[i] = sum / cols();
                }
                break;
                
            default:
                return 0;
                break;
        }
        
        return res;
    }
    
    /**
     *  @brief Operator -
     */
    void operator - (float n)
    {
        for (int i = 0; i < rows(); i++)
            for (int j = 0; j < cols(); j++)
                p_Data[ m_Cols * i + j ] = p_Data[ m_Cols * i + j ] - n;
    }
    
    /**
     *  @brief Operator +
     */
    void operator + (float n)
    {
        for (int i = 0; i < rows(); i++)
            for (int j = 0; j < cols(); j++)
                p_Data[ m_Cols * i + j ] = p_Data[ m_Cols * i + j ] + n;
    }
    
    /**
     *  @brief Operator /
     */
    void operator / (float n)
    {
        for (int i = 0; i < rows(); i++)
            for (int j = 0; j < cols(); j++)
                p_Data[ m_Cols * i + j ] = p_Data[ m_Cols * i + j ] / n;
    }
    
    /**
     *  @brief Operator *
     */
    void operator * (float n)
    {
        for (int i = 0; i < rows(); i++)
            for (int j = 0; j < cols(); j++)
                p_Data[ m_Cols * i + j ] = p_Data[ m_Cols * i + j ] * n;
    }
    
    /**
     *  @brief Operator ^
     */
    void operator ^ (float n)
    {
        for (int i = 0; i < rows(); i++)
            for (int j = 0; j < cols(); j++)
                p_Data[ m_Cols * i + j ] = std::pow(p_Data[ m_Cols * i + j ], n);
    }

    
    // STL style iterators
    /**
     *  @brief Const iterator begin
     */
    inline const_iterator begin() const { return p_Data; }
    /**
     *  @brief Const iterator end
     */
    inline const_iterator end() const { return p_Data + size(); }
    /**
     *  @brief Iterator begin
     */
    inline iterator begin() { return p_Data; }
    /**
     *  @brief Iterator end
     */
    inline iterator end() { return p_Data + size(); }
    
    // Array indexing operators
    /**
     *  @brief Array indexing const operator, matrix(i)
     */
    inline const T& operator () ( int i ) const { return p_Data[ i ]; }
    /**
     *  @brief Array indexing const operator, matrix(i, j)
     */
    inline const T& operator () ( int i, int j ) const { return p_Data[  m_Cols * i + j ]; }
    /**
     *  @brief Array indexing operator, matrix(i)
     */
    inline T& operator () ( int i ) { return p_Data[ i ]; }
    /**
     *  @brief Array indexing operator, matrix(i, j)
     */
    inline T& operator () ( int i, int j ) { return p_Data[ m_Cols * i + j ]; }
    
    // Get pointers to internal data
    /**
     *  @brief Get const pointer to internal data
     */
    inline const T* c_data() const { return p_Data; }
    /**
     *  @brief Get pointer to internal data
     */
    inline T* c_data() { return p_Data; }
    
private:
    
    inline int checkedIndex(int indx) const
    {
        assert( indx < size() );
        return indx;
    }
    
    inline int checkedIndex(int iRow, int jCol) const
    {
        int k = m_Cols*iRow + jCol;
        assert( k < size() );
        return k;
    }
    
private:
    int     m_Rows;
    int     m_Cols;
    bool    m_OwnsData;
    T       *p_Data;
    
}; // class TArray2

#endif // #if !defined(TARRAY2_INCLUDED)
