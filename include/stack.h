// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������

// ��������� ����� �����
#pragma once
#include "vector.h"

template <typename T>
class TStack {
 private:
    TVector<T> vec;

 public:
    void push(const T& value) { vec.push_back(value); }
    T pop() { return vec.pop_back(); }
    T top() { return vec.back(); }
    bool empty() const { return vec.empty(); }
    size_t size() const { return vec.get_size(); }
    void clear() { vec.clear(); }
};

