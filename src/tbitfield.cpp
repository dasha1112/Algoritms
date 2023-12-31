
#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len) // конструктор
{
    if (len <= 0)
    {
        throw ("Некорректное значение");
    }
    BitLen = len;
    MemLen = (BitLen + sizeof(int) * 8 - 1) / (sizeof(int) * 8);
    pMem = new TELEM [MemLen];
    for (int i = 0; i < MemLen; i++) 
    {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM(MemLen);
    if (pMem != NULL) 
    {
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = 0;
        }
    }
}

TBitField::~TBitField() //деструктор
{
    if (pMem != nullptr) 
    {
        delete [] pMem;
    }
    pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return (n / (sizeof(int) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n <0 || n > BitLen)
    {
        throw ("Ошибка");
    }
    int m = 1 << (n / sizeof(int) * 8);
    int j = n >> static_cast <int> (log2 (sizeof(int) * 8));
    pMem[j] |= m;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    int j = n >> static_cast <int> (log2(sizeof(int) * 8));
    int m = 1 << (n / sizeof(int) * 8);
    m = ~m;
    pMem[j] &= m;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n > BitLen) 
    {
        throw ("Ошибка");
    }
    int j = n >> static_cast <int> (log2(sizeof(int) * 8));
    int m = 1 << (n / sizeof(int) * 8);
    return (pMem[j] & m);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    BitLen = bf.BitLen;
    if (MemLen != bf.MemLen) 
    {
        MemLen = bf.MemLen;
        if (pMem != NULL) 
        {
            delete pMem;
        }
        pMem = new TELEM[MemLen];
    }
    if (pMem != NULL) 
    {
        for (int i = 0; i < MemLen; i++) 
        {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    int flag = 0;
    for (int i = 0; i < MemLen; i++) 
    {
        if (pMem == bf.pMem) 
        {
            flag = 1;
        }
    }
    return flag;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    int flag = 0;
    for (int i = 0; i < MemLen; i++)
    {
        if (pMem == bf.pMem)
        {
            flag = 1;
        }
    }
    return flag;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if (this->BitLen != bf.BitLen) 
    {
        throw ("Ошибка");
    }
    TBitField res(*this);
    for (int i = 0; i < MemLen; i++)
    {
        res.pMem[i] |= bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (this->BitLen != bf.BitLen)
    {
        throw ("Ошибка");
    }
    TBitField res(*this);
    for (int i = 0; i < MemLen; i++)
    {
        res.pMem[i] &= bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(*this);
    for (int i = 0; i < MemLen; i++)
    {
        res.pMem[i] = ~pMem[i];
    }
    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string input;
    istr >> input;

    for (int i = 0; i < bf.BitLen; i++)
    {
        if (input[i] == '0')
        {
            bf.ClrBit(i);
        }
        else if (input[i] == '1')
        {
            bf.SetBit(i);
        }
        else
        {
            throw("Ошибка");
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) 
    {
        ostr << bf.GetBit(i);
    }
    return ostr;
}
