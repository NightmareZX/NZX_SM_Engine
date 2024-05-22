#pragma once
#include "IntTypes.h"

template <typename Number>
class Vector2
{
public:
	Number x;
	Number y;
	Vector2() : x(0), y(0) {}
	Vector2(Number x, Number y): x(x), y(y) {}
	inline Vector2 operator+(const Vector2& vectorOther){ return Vector2(x + vectorOther.x, y + vectorOther.y); }
	inline Vector2 operator-(const Vector2& vectorOther){ return Vector2(x - vectorOther.x, y - vectorOther.y); }
	inline Vector2 operator*(const Vector2& vectorOther){ return Vector2(x * vectorOther.x, y * vectorOther.y); }
	inline Vector2 operator/(const Vector2& vectorOther){ return Vector2(x / vectorOther.x, y / vectorOther.y); }
	inline Vector2 operator*(const float scalar){ return Vector2(static_cast<Number>(x * scalar), static_cast<Number>(y * scalar)); }
	inline Vector2& operator+=(const Vector2& vectorOther){ x += vectorOther.x; y += vectorOther.y; return *this; }
	inline Vector2& operator-=(const Vector2& vectorOther){ x -= vectorOther.x; y -= vectorOther.y; return *this; }
	inline Vector2& operator*=(const Vector2& vectorOther){ x *= vectorOther.x; y *= vectorOther.y; return *this; }
	inline Vector2& operator/=(const Vector2& vectorOther){ x /= vectorOther.x; y /= vectorOther.y; return *this; }
	inline bool operator==(const Vector2& vectorOther){ if (vectorOther.x == x && vectorOther.y == y) return true; else return false; }
	inline bool operator!=(const Vector2& vectorOther){ if (vectorOther.x != x || vectorOther.y != y) return true; else return false; }
};