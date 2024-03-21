// dynamic array (vector) implementation (cpp-style)
#pragma once


// decl: Vector
template<typename T>
class Vector {
private:
    T* data_ptr;
    int _size; // same as next_index;
    int _capacity;
    const static int step = 2;

public:
    Vector();
    Vector(const Vector<T>& other);
    ~Vector();

public:
    void resize_capacity();
    void resize_capacity(int new_capacity);
    void append(const T& value);
    void print();
    void sort(void (* sort_fn)(T* ptr, int length, bool ascending), bool ascending = true);
    void clear();
    int size();
    int capacity();

    class iterator;
    iterator begin();
    iterator end();
    iterator erase(iterator& iter);

public:
    int& operator[](int index);
    Vector<T>& operator=(const Vector<T>& other);

public:
    // decl: Vector::iterator
    class iterator {
        // inner 클래스는 outter 클래스의 private 멤버에 접근 가능
        // friend 키워드: 해당 클래스에서 private 멤버에 접근 가능하도록 함
        friend class Vector;

    private:
        Vector* array_ptr;
        T* data_ptr;
        int index;
        bool is_valid;

    public:
        iterator();
        iterator(Vector* array_ptr, T* data_ptr, int index);
        ~iterator() = default;

    private:
        void validate();

    public:
        T& operator*();
        iterator& operator++(); // 전위 증가
        iterator operator++(int); // 후위 증가
        iterator& operator--(); // 전위 감소
        iterator operator--(int); // 후위 감소
        bool operator==(const iterator& other);
        bool operator!=(const iterator& other);
    };
};


// impl: Vector
template<typename T>
Vector<T>::Vector() : data_ptr(nullptr), _size(0), _capacity(step)
{
    data_ptr = new T[_capacity];
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
    data_ptr = other.data_ptr;
    _size = other._size;
    _capacity = other._capacity;
}

template<typename T>
Vector<T>::~Vector()
{
    delete[] data_ptr;
}

template<typename T>
void Vector<T>::resize_capacity(int new_capacity)
{
    int* new_ptr = new T[new_capacity];
    int* old_ptr = data_ptr;

    for (int i = 0; i < _size; ++i) {
        new_ptr[i] = old_ptr[i];
    }

    delete old_ptr;
    data_ptr = new_ptr;
    _capacity = new_capacity;
}

template<typename T>
void Vector<T>::resize_capacity()
{
    this->resize_capacity(_capacity + step);
}

template<typename T>
void Vector<T>::append(const T& value)
{
    if (_capacity <= _size) {
        this->resize_capacity();
    }
    data_ptr[_size++] = value;
}

template<typename T>
void Vector<T>::print()
{
    std::cout << "Vector(size=" << _size << ", capacity=" << _capacity << ") { ";
    for (int i = 0; i < _size; ++i) {
        std::cout << data_ptr[i] << " ";
    }
    std::cout << "}" << std::endl;
}

template<typename T>
void Vector<T>::sort(void (* sort_fn)(T* ptr, int length, bool ascending), bool ascending)
{
    sort_fn(data_ptr, _size, ascending); // 함수형 포인터 사용
}

/* 참조변수의 활용
 * return int: getter (O), setter (X)
 * return int*: getter (O), setter (O) -> 둘다 가능하지만 포인터 문법으로만 접근 가능
 * return int&: getter (O), setter(O) -> 레지스터에 저장된 참조 변수를 통해, 일반적인 array 처럼 동작 가능
 * */
template<typename T>
int& Vector<T>::operator[](int index)
{
    return data_ptr[index];
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    data_ptr = other.data_ptr;
    _size = other._size;
    _capacity = other._capacity;
    step = other.step;
    return *this;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return (_size != 0) ? iterator(this, data_ptr, 0) : end();
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end()
{
    return iterator(this, data_ptr, -1);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::erase(Vector<T>::iterator& iter)
{
    // iterator 클래스에서 Vector 클래스를 friend class 로 설정해두었기 때문에 private 멤버 접근 가능

    // 다른 배열의 iterator가 들어오는 경우
    // end iterator 인 경우
    // 배열 사이즈보다 크거나 같은 index를 가진 iterator 인 경우
    if ((this != iter.array_ptr) || (end() == iter) || (_size <= iter.index)) {
        assert(nullptr);
    }

    // 로직 부분
    for (int i = iter.index; i < _size - 1; ++i) {
        iter.data_ptr[i] = iter.data_ptr[i + 1];
    }
    --_size;

    // 배열의 경우에는 오른쪽의 원소들을 모두 왼쪽으로 한칸씩 당겨왔기 때문에 iter를 그대로 반환해도 되지만
    // 개념적으로 iterator가 가리키던 원소가 변했기 때문에 invalid iterator로 간주하여, 새로운 객체를 반환함
    iter.is_valid = false;
    return iterator(this, data_ptr, iter.index);
}

template<typename T>
int Vector<T>::size()
{
    return _size;
}

template<typename T>
int Vector<T>::capacity()
{
    return _capacity;
}

template<typename T>
void Vector<T>::clear()
{
    _size = 0;
}


// impl: Vector::iterator
template<typename T>
Vector<T>::iterator::iterator()
    : array_ptr(nullptr), data_ptr(nullptr), index(-1), is_valid(false)
{
    validate();
}

template<typename T>
Vector<T>::iterator::iterator(Vector* array_ptr, T* data_ptr, int index)
    : array_ptr(array_ptr), data_ptr(data_ptr), index(index), is_valid(false)
{
    validate();
}

template<typename T>
void Vector<T>::iterator::validate()
{
    // 가변 배열이 존재하고
    // index 값이 양수인 경우
    if (nullptr != array_ptr && 0 <= index) {
        is_valid = true;
    }
}

template<typename T>
T& Vector<T>::iterator::operator*()
{
    // iterator가 알고 있는 data 주소가 capacity 변경으로 인해 달라진 경우
    // end iterator 인 경우
    // 유효성 검사에 실패한 경우
    if ((array_ptr->data_ptr != data_ptr) || (-1 == index) || !is_valid) {
        assert(nullptr);
    }
    return data_ptr[index];
}

template<typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator++()
{
    // iterator가 알고 있는 data 주소가 capacity 변경으로 인해 달라진 경우
    // end iterator 인 경우
    if ((array_ptr->data_ptr != data_ptr) || (-1 == index)) {
        assert(nullptr);
    }
    // iterator가 마지막 원소를 가리키는 경우
    if (array_ptr->_size - 1 == index) {
        index = -1;
    } else {
        ++index;
    }
    return *this;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator++(int)
{
    iterator copy = *this;
    ++(*this);
    return copy;
}

template<typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator--()
{
    // iterator가 알고 있는 data 주소가 capacity 변경으로 인해 달라진 경우
    // begin iterator 인 경우
    if ((array_ptr->data_ptr != data_ptr) || (0 == index)) {
        assert(nullptr);
    }

    // begin operator 보다 증가할 수 없음
    if (index == 0) {
        assert(nullptr);
    }
    index -= 1;
    return *this;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator--(int)
{
    iterator clone = *this;
    --(*this);
    return clone;
}

template<typename T>
bool Vector<T>::iterator::operator==(const Vector::iterator& other)
{
    return (data_ptr == other.data_ptr) && (index == other.index);
}

template<typename T>
bool Vector<T>::iterator::operator!=(const Vector::iterator& other)
{
    return !(*this == other);
}

