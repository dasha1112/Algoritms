
#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : maxPower(mp), BitField (mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : maxPower(s.maxPower), BitField (s.BitField)
{

}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : maxPower (bf.GetLength()), BitField (bf)
{
}

TSet::operator TBitField()
{
    TBitField temp(this->BitField);
    return temp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return maxPower;
}

int TSet::IsMember(const int elem) const // элемент множества?
{
    if (elem < 0 || elem >= maxPower)
    {
        throw ("Ошибка");
    }
    return BitField.GetBit(elem);
}

void TSet::InsElem(const int elem) // включение элемента множества
{
    if (elem < 0 || elem >= maxPower)
    {
        throw ("Ошибка");
    }
    return BitField.SetBit(elem);
}

void TSet::DelElem(const int elem) // исключение элемента множества
{
    if (elem < 0 || elem >= maxPower)
    {
        throw ("Ошибка");
    }
    return BitField.ClrBit(elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    BitField = s.BitField;
    maxPower = s.GetMaxPower();
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet temp(BitField | s.BitField);
    return temp;
}

TSet TSet::operator+(const int elem) // объединение с элементом
{
    TSet resultSet(*this);
    resultSet.BitField.SetBit(elem);
    return resultSet;
}

TSet TSet::operator-(const int elem) // разность с элементом
{
    TSet resultSet(*this);
    resultSet.BitField.ClrBit(elem);
    return resultSet;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet temp(BitField & s.BitField);
    return temp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet temp(~BitField);
    return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int element;
    istr >> element;
    while (element >= 0) {
        s.InsElem(element);
        istr >> element;
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    for (int i = 0; i < s.GetMaxPower(); i++) {
        if (s.IsMember(i)) {
            ostr << i << " ";
        }
    }
    return ostr;
}
