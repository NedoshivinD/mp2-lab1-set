// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
    MaxPower = BitField.GetLength();
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if ((Elem < 0) || (Elem >= MaxPower))
        throw "Incorrect element";
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if ((Elem < 0) || (Elem >= MaxPower))
        throw "Incorrect element";
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if ((Elem < 0) || (Elem >= MaxPower))
        throw "Incorrect element";
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this != &s)
    {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower)
        return 0;
    else
        if (BitField != s.BitField)
            return 0;
    return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (*this == s)
        return 0;
    return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int len = MaxPower;
    if (s.MaxPower >= MaxPower)
        len = s.MaxPower;
    TSet temp(len);
    temp.BitField = BitField | s.BitField;
    return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if ((Elem < 0) || (Elem >= MaxPower))
        throw "Incorrect element";
    TSet temp(MaxPower);
    temp = *this;
    if (temp.BitField.GetBit(Elem) != 1)
        temp.BitField.SetBit(Elem);
    return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if ((Elem < 0) || (Elem >= MaxPower))
        throw "Incorrect element";
    TSet temp(MaxPower);
    temp = *this;
    if (temp.BitField.GetBit(Elem) == 1)
        temp.BitField.ClrBit(Elem);
    return temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    int len = MaxPower;
    if (s.MaxPower >= MaxPower)
        len = s.MaxPower;
    TSet temp(len);
    temp.BitField = BitField & s.BitField;
    return temp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet temp = *this;
    temp.BitField = ~temp.BitField;
    return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int l;
    istr >> l;
    for (int i = 0; i < s.MaxPower; i++) 
    {
        istr >> l;
        s.InsElem(l);
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    for (int i = 0; i < s.MaxPower; i++)
    {
        if (s.BitField.GetBit(i))
            ostr << i << endl;
    }
    return ostr;
}