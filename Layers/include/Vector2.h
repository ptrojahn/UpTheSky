#pragma once

template<typename T>
class Vector2
{
public:
	Vector2<T>(T x, T y) : x(x), y(y){
	}
	Vector2<T>() {
		x = 0;
		y = 0;
	}
	Vector2<T> operator+(Vector2<T> vec) {
		return Vector2<T>(x + vec.x, y + vec.y);
	}
	Vector2<T> operator+=(Vector2<T> vec) {
		x += vec.x;
		y += vec.y;
		return *this;
	}
	Vector2<T> operator-(Vector2<T> vec) {
		return Vector2<T>(x - vec.x, y - vec.y);
	}
	Vector2<T> operator-=(Vector2<T> vec) {
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	Vector2<T> operator*(Vector2<T> type) {
		return Vector2<T>(x * type.x, y * type.y);
	}
	Vector2<T> operator*=(Vector2<T> type) {
		x *= type;
		y *= type;
		return *this;
	}
	Vector2<T> operator/(Vector2<T> vec) {
		return Vector2<T>(x / vec.x, y / vec.y);
	}
	Vector2<T> operator/=(Vector2<T> vec) {
		x /= vec.x;
		y /= vec.y;
		return *this;
	}
	Vector2<T> operator+(T type) {
		return Vector2<T>(x + type, y + type);
	}
	Vector2<T> operator+=(T type) {
		x += type;
		y += type;
		return *this;
	}
	Vector2<T> operator-(T type) {
		return Vector2<T>(x - type, y - type);
	}
	Vector2<T> operator-=(T type) {
		x -= type;
		y -= type;
		return *this;
	}
	Vector2<T> operator*(T type) {
		return Vector2<T>(x * type, y * type);
	}
	Vector2<T> operator*=(T type) {
		x *= type;
		y *= type;
		return *this;
	}
	Vector2<T> operator/(T type) {
		return Vector2<T>(x / type, y / type);
	}
	Vector2<T> operator/=(T type) {
		x /= type;
		y /= type;
		return *this;
	}
	T x;
	T y;
};