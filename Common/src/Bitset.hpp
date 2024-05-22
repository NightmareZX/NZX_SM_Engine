#pragma once
#include "IntTypes.h"
#include <bitset>
/// <summary>
/// A class that represents a fixed size of bits
/// </summary>
/// <typeparam name="Enum">The enumerator that holds elements which represent each bit within the bitset</typeparam>
/// <typeparam name="BitType">The integer that is used to store the bits in, by default the bits are stored in a unsigned 32-bit integer</typeparam>
template<typename Enum, typename BitType = uint32>
class Bitset
{
private:
	BitType mBits;
public:
	Bitset(): mBits(0) {}
	Bitset(BitType bits) : mBits(bits) {}
	BitType GetInteger() { return mBits; }
	inline bool CheckBit(Enum bit) { return mBits & static_cast<BitType>(bit); }
	inline void ToggleBit(Enum bit) { mBits ^= static_cast<BitType>(bit); }
	inline void SetBit(Enum bit) { mBits |= static_cast<BitType>(bit); }
	inline void ResetBit(Enum bit) { mBits &= ~static_cast<BitType>(bit); }
};