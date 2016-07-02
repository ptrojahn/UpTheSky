#pragma once

template<typename T>
class Vector3
{
public:
	Vector3<T>(T x, T y, T z) : x(x), y(y), z(z) {}
	Vector3<T>() : x(0), y(0), z(0) {}
	Vector3<T> operator+(Vector3<T> vec) {
		return Vector3<T>(x + vec.x, y + vec.y, z + vec.z);
	}
	Vector3<T> operator+=(Vector3<T> vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}
	Vector3<T> operator-(Vector3<T> vec) {
		return Vector3<T>(x - vec.x, y - vec.y, z - vec.z);
	}
	Vector3<T> operator-=(Vector3<T> vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}
	Vector3<T> operator*(Vector3<T> vec) {
		return Vector3<T>(x * vec.x, y * vec.y, z * vec.z);
	}
	Vector3<T> operator*=(Vector3<T> vec) {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		return *this;
	}
	Vector3<T> operator/(Vector3<T> vec) {
		return Vector3<T>(x / vec.x, y / vec.y, z / vec.z);
	}
	Vector3<T> operator/=(Vector3<T> vec) {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		return *this;
	}
	Vector3<T> operator+(T type) {
		return Vector3<T>(x + type, y + type, z + type.z);
	}
	Vector3<T> operator+=(T type) {
		x += type;
		y += type;
		z += type;
		return *this;
	}
	Vector3<T> operator-(T type) {
		return Vector2<T>(x - type, y - type, z - type);
	}
	Vector3<T> operator-=(T type) {
		x -= type;
		y -= type;
		z -= type;
		return *this;
	}
	Vector3<T> operator*(T type) {
		return Vector2<T>(x * type, y * type, z * type);
	}
	Vector3<T> operator*=(T type) {
		x *= type;
		y *= type;
		z *= type;
		return *this;
	}
	Vector3<T> operator/(T type) {
		return Vector3<T>(x / type, y / type, z / type);
	}
	Vector3<T> operator/=(T type) {
		x /= type;
		y /= type;
		z /= type;
		return *this;
	}
	T x;
	T y;
	T z;
};