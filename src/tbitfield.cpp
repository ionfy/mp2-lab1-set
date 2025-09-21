// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

size_t power_of_two_sizeof(size_t tsize)
{
  size_t digit = 0;
  tsize = tsize * 8;

  while(tsize >>= 1) {
    digit += 1;
  }

  return digit;
}

TBitField::TBitField(int len)
{
  if (len <= 0) throw length_error("Length should be positive");

  BitLen = len;
  MemLen = (BitLen + sizeof(TELEM)*8 - 1) >> (power_of_two_sizeof(sizeof(TELEM)));
  pMem = new TELEM[MemLen]();
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;

  pMem = new TELEM[MemLen];

  for (size_t i = 0; i < MemLen; i++)
  {
    pMem[i] = bf.pMem[i];
  }
}

TBitField::~TBitField()
{
  delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n >> (power_of_two_sizeof(sizeof(TELEM)));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n & (sizeof(TELEM)*8 - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n >= BitLen || n < 0) throw out_of_range("Value outside TBitField");

  pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n >= BitLen || n < 0) throw out_of_range("Value outside TBitField");

  pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n >= BitLen || n < 0) throw out_of_range("Value outside TBitField");

  return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;  
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this == &bf) return *this;

  BitLen = bf.BitLen;
  MemLen = bf.MemLen;

  delete[] pMem;
  pMem = new TELEM[MemLen];

  for (size_t i = 0; i < MemLen; i++)
  {
    pMem[i] = bf.pMem[i];
  }

  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (BitLen != bf.BitLen) return 0;

  for (size_t i = 0; i < MemLen; i++)
  {
    if (pMem[i] != bf.pMem[i])
    {
      return 0;
    }
  }

  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (BitLen != bf.BitLen)  return 1;

  for (size_t i = 0; i < MemLen; i++)
  {
    if (pMem[i] != bf.pMem[i])
    {
      return 1;
    }
  }

  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  TBitField rbf(max(BitLen, bf.BitLen));

  for (size_t i = 0; i < bf.MemLen; i++)
  {
    rbf.pMem[i] |= bf.pMem[i];
  }
  for (size_t i = 0; i < MemLen; i++)
  {
    rbf.pMem[i] |= pMem[i];
  }

  return rbf;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  TBitField rbf(max(BitLen, bf.BitLen));

  for (size_t i = 0; i < min(BitLen, bf.BitLen); i++)
  {
    rbf.pMem[i] = pMem[i] & bf.pMem[i];
  }

  return rbf;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField rbf(BitLen);

  for (size_t i = 0; i < MemLen; i++)
  {
    rbf.pMem[i] = ~pMem[i];
  }
  
  rbf.pMem[MemLen - 1] &= ((TELEM)1 << (BitLen & (sizeof(TELEM)*8 - 1))) - 1;

  return rbf;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  char ch;
  int i = 0;
  
  while ((ch = getchar()) != EOF && ch != '\n')
  {
    switch (ch)
    {
      case '0':
      bf.ClrBit(i);
      break;
      case '1':
      bf.SetBit(i);
      break;
      default:
      throw runtime_error("Incorrect input");
      break;
    }
    
    i++;
  }

  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.GetLength(); i++) {
    ostr << bf.GetBit(i);
  }

  return ostr;
}
