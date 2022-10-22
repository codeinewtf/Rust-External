#pragma once
#include "common.hpp"
class Vector3
{
public:
	float x, y, z;

	inline Vector3() {
		x = y = z = 0.0f;
	}

	inline Vector3(float X, float Y, float Z) {
		x = X; y = Y; z = Z;
	}

	inline Vector3(const Vector3& in)
	{
		x = in.x;
		y = in.y;
		z = in.z;
	}

	inline float operator[](int i) const {
		return ((float*)this)[i];
	}

	inline Vector3& operator-=(float v) {
		x -= v; y -= v; z -= v; return *this;
	}

	inline Vector3 operator*(float v) const {
		return Vector3(x * v, y * v, z * v);
	}

	inline Vector3 operator/(float v) const
	{
		return Vector3(x / v, y / v, z / v);
	}

	inline Vector3& operator+=(const Vector3& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}

	inline Vector3& operator-=(const Vector3& v)
	{
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	inline bool operator==(const Vector3& v) const {
		if (this->x == v.x && this->y == v.y && this->z == v.z)
			return true;
		else
			return false;
	}

	inline Vector3 operator-(const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	inline Vector3 operator+(const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	inline bool empty()
	{
		return x == 0.f && y == 0.f && z == 0.f;
	}

	float Magnitude()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	inline Vector3 normalized()
	{
		float num = Magnitude();
		if (num > 9.99999974737875E-06)
			return { x / num, y / num, z / num };

		return Vector3(x, y, z);
	}

	inline float Length() {
		return sqrtf(x * x + y * y + z * z);
	}



	static float UnityClamp(float value)
	{
		float result;
		if (value < 0.f)
		{
			result = 0.f;
		}
		else if (value > 1.f)
		{
			result = 1.f;
		}
		else
		{
			result = value;
		}
		return result;
	}

	float Lerp()
	{
		return x + (y - x) * Vector3::UnityClamp(z);
	}
};

class Vector2 {
public:
	float x, y;

	inline Vector2() {
		x = y = 0.0f;
	}

	inline Vector2 operator/(float v) const {
		return Vector2(x / v, y / v);
	}
	inline Vector2(float X, float Y) {
		x = X; y = Y;
	}

	inline Vector2 operator-(const Vector2& v) const {
		return Vector2(x - v.x, y - v.y);
	}

	inline Vector2 operator+(const Vector2& v) const {
		return Vector2(x + v.x, y + v.y);
	}

	inline Vector2& operator+=(const Vector2& v) {
		x += v.x; y += v.y; return *this;
	}

	inline Vector2& operator*=(float input)
	{
		x *= input;
		y *= input;
		return *this;
	}

	inline bool Zero() const {
		return (x > -0.1f && x < 0.1f && y > -0.1f && y < 0.1f);
	}

	inline float length() const
	{
		return std::sqrt((x * x) + (y * y));
	}

	inline Vector2 normalized() const
	{
		return { x / length(), y / length() };
	}
};

class Vector4 {
public:
	float x, y, z, w;
};

struct Matrix4x4 {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		}; float m[4][4];
	};
};


__forceinline float Magnitude2(Vector3 vector)
{
	return static_cast<float>(std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
}

__forceinline Vector3 monkey_normalize2(Vector3 value)
{
	float mag = Magnitude2(value);
	if (mag > 0.00001F)
	{
		return Vector3(value.x / mag, value.y / mag, value.z / mag);
	}
	else
	{
		return Vector3(0, 0, 0);
	}

}

__forceinline Vector3 Cross2(Vector3 lhs, Vector3 rhs)
{
	return Vector3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
}

namespace Math
{
#define M_PI 3.14159265358979323846f
#define M_RADPI	57.295779513082f
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))
#define DEG2RAD(x) ((float)(x) * (float)(M_PI_F / 180.f))
#define atan2(a, b) ((float)atan2((double)(a), (double)(b)))
	static volatile const double Infinity = INFINITY;
	typedef struct { double d0, d1; } double2;


	static inline double2 Add212RightSmaller(double2 a, double b)
	{
		double
			c0 = a.d0 + b,
			c1 = a.d0 - c0 + b + a.d1,
			d0 = c0 + c1,
			d1 = c0 - d0 + c1;
		return double2{ d0, d1 };
	}

	static inline double Add221RightSmaller(double2 a, double2 b)
	{
		double
			c0 = a.d0 + b.d0,
			c1 = a.d0 - c0 + b.d0 + b.d1 + a.d1,
			d0 = c0 + c1;
		return d0;
	}

	//float abs(float a) {
	//	if (a < 0.f) return -a;
	//	else return a;
	//}

	//float asin(float x) {
	//	float negate = float(x < 0);
	//	x = abs(x);
	//	float ret = -0.0187293;
	//	ret *= x;
	//	ret += 0.0742610;
	//	ret *= x;
	//	ret -= 0.2121144;
	//	ret *= x;
	//	ret += 1.5707288;
	//	ret = 3.14159265358979 * 0.5 - sqrt(1.0 - x) * ret;
	//	return ret - 2 * negate * ret;
	//}

	__forceinline float Dot(const Vector3& Vec1, const Vector3& Vec2) {
		return Vec1[0] * Vec2[0] + Vec1[1] * Vec2[1] + Vec1[2] * Vec2[2];
	}

	__forceinline float Distance(const Vector3* value1, const Vector3* value2)
	{
		float num1 = value1->x - value2->x;
		float num2 = value1->y - value2->y;
		float num3 = value1->z - value2->z;

		return (float)sqrt(num1 * num1 + num2 * num2 + num3 * num3);
	}

	__forceinline float Calc3D_Dist(const Vector3& Src, const Vector3& Dst) {
		return sqrtf(pow((Src.x - Dst.x), 2) + pow((Src.y - Dst.y), 2) + pow((Src.z - Dst.z), 2));
	}

	__forceinline float Calc2D_Dist(const Vector2& Src, const Vector2& Dst) {
		return sqrt(powf(Src.x - Dst.x, 2) + powf(Src.y - Dst.y, 2));
	}

	__forceinline Vector2 CalcAngle(const Vector3& Src, const Vector3& Dst) {
		Vector3 dir = Src - Dst;
		return Vector2{ RAD2DEG(asin(dir.y / dir.Length())), RAD2DEG(-atan2(dir.x, -dir.z)) };
	}



	__forceinline Vector4 QuaternionLookRotation(Vector3 forward, Vector3 up)
	{
		monkey_normalize2(forward);

		Vector3 vector = monkey_normalize2(forward);
		Vector3 vector2 = monkey_normalize2(Cross2(up, vector));
		Vector3 vector3 = Cross2(vector, vector2);
		auto m00 = vector2.x;
		auto m01 = vector2.y;
		auto m02 = vector2.z;
		auto m10 = vector3.x;
		auto m11 = vector3.y;
		auto m12 = vector3.z;
		auto m20 = vector.x;
		auto m21 = vector.y;
		auto m22 = vector.z;


		float num8 = (m00 + m11) + m22;
		auto quaternion = Vector4();
		if (num8 > 0.0f)
		{
			auto num = static_cast<float>(std::sqrt(num8 + 1.0f));
			quaternion.w = num * 0.5f;
			num = 0.5f / num;
			quaternion.x = (m12 - m21) * num;
			quaternion.y = (m20 - m02) * num;
			quaternion.z = (m01 - m10) * num;

			return quaternion;
		}
		if ((m00 >= m11) && (m00 >= m22))
		{
			auto num7 = static_cast<float>(std::sqrt(((1.0f + m00) - m11) - m22));
			auto num4 = 0.5f / num7;
			quaternion.w = 0.5f * num7;
			quaternion.y = (m01 + m10) * num4;
			quaternion.z = (m02 + m20) * num4;
			quaternion.w = (m12 - m21) * num4;

			return quaternion;
		}
		if (m11 > m22)
		{
			auto num6 = static_cast<float>(std::sqrt(((1.0f + m11) - m00) - m22));
			auto num3 = 0.5f / num6;
			quaternion.x = (m10 + m01) * num3;
			quaternion.y = 0.5f * num6;
			quaternion.z = (m21 + m12) * num3;
			quaternion.w = (m20 - m02) * num3;

			return quaternion;
		}
		auto num5 = static_cast<float>(std::sqrt(((1.0f + m22) - m00) - m11));
		auto num2 = 0.5f / num5;
		quaternion.x = (m20 + m02) * num2;
		quaternion.y = (m21 + m12) * num2;
		quaternion.z = 0.5f * num5;
		quaternion.w = (m01 - m10) * num2;

		return quaternion;
	}


}

//class Vector3
//{
//public:
//	float x, y, z;
//
//	inline Vector3() {
//		x = y = z = 0.0f;
//	}
//
//	inline Vector3(float X, float Y, float Z) {
//		x = X; y = Y; z = Z;
//	}
//
//	inline float operator[](int i) const {
//		return ((float*)this)[i];
//	}
//
//	inline Vector3& operator-=(float v) {
//		x -= v; y -= v; z -= v; return *this;
//	}
//
//	inline Vector3 operator*(float v) const {
//		return Vector3(x * v, y * v, z * v);
//	}
//
//	inline Vector3 operator/(float v) const
//	{
//		return Vector3(x / v, y / v, z / v);
//	}
//
//	inline Vector3& operator+=(const Vector3& v) {
//		x += v.x; y += v.y; z += v.z; return *this;
//	}
//
//	inline Vector3 operator-(const Vector3& v) const {
//		return Vector3(x - v.x, y - v.y, z - v.z);
//	}
//
//	inline Vector3 operator+(const Vector3& v) const {
//		return Vector3(x + v.x, y + v.y, z + v.z);
//	}
//
//	inline float Length() {
//		return sqrtf(x * x + y * y + z * z);
//	}
//};
//
//class Vector2 {
//public:
//	float x, y;
//
//	inline Vector2() {
//		x = y = 0.0f;
//	}
//
//	inline Vector2 operator/(float v) const {
//		return Vector2(x / v, y / v);
//	}
//	inline Vector2(float X, float Y) {
//		x = X; y = Y;
//	}
//
//	inline Vector2 operator-(const Vector2& v) const {
//		return Vector2(x - v.x, y - v.y);
//	}
//
//	inline Vector2 operator+(const Vector2& v) const {
//		return Vector2(x + v.x, y + v.y);
//	}
//
//	inline Vector2& operator+=(const Vector2& v) {
//		x += v.x; y += v.y; return *this;
//	}
//
//	inline bool Zero() const {
//		return (x > -0.1f && x < 0.1f && y > -0.1f && y < 0.1f);
//	}
//};
//
//class Vector4 {
//public:
//	float x, y, z, w;
//};
//
//struct Matrix4x4 {
//	union {
//		struct {
//			float        _11, _12, _13, _14;
//			float        _21, _22, _23, _24;
//			float        _31, _32, _33, _34;
//			float        _41, _42, _43, _44;
//
//		}; float m[4][4];
//	};
//};
//
//namespace Math
//{
//#define M_PI 3.14159265358979323846f
//#define M_RADPI	57.295779513082f
//#define M_PI_F ((float)(M_PI))
//#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))
//#define DEG2RAD(x) ((float)(x) * (float)(M_PI_F / 180.f))
//#define atan2(a, b) ((float)atan2((double)(a), (double)(b)))
//	static volatile const double Infinity = INFINITY;
//	typedef struct { double d0, d1; } double2;
//
//
//	static inline double2 Add212RightSmaller(double2 a, double b)
//	{
//		double
//			c0 = a.d0 + b,
//			c1 = a.d0 - c0 + b + a.d1,
//			d0 = c0 + c1,
//			d1 = c0 - d0 + c1;
//		return double2{ d0, d1 };
//	}
//
//	static inline double Add221RightSmaller(double2 a, double2 b)
//	{
//		double
//			c0 = a.d0 + b.d0,
//			c1 = a.d0 - c0 + b.d0 + b.d1 + a.d1,
//			d0 = c0 + c1;
//		return d0;
//	}
//
//	float abs(float a) {
//		if (a < 0.f) return -a;
//		else return a;
//	}
//
//	float asin(float x) {
//		float negate = float(x < 0);
//		x = abs(x);
//		float ret = -0.0187293;
//		ret *= x;
//		ret += 0.0742610;
//		ret *= x;
//		ret -= 0.2121144;
//		ret *= x;
//		ret += 1.5707288;
//		ret = 3.14159265358979 * 0.5 - sqrt(1.0 - x) * ret;
//		return ret - 2 * negate * ret;
//	}
//
//	__forceinline float Dot(const Vector3& Vec1, const Vector3& Vec2) {
//		return Vec1[0] * Vec2[0] + Vec1[1] * Vec2[1] + Vec1[2] * Vec2[2];
//	}
//
//	__forceinline float Calc3D_Dist(const Vector3& Src, const Vector3& Dst) {
//		return sqrtf(pow((Src.x - Dst.x), 2) + pow((Src.y - Dst.y), 2) + pow((Src.z - Dst.z), 2));
//	}
//
//	__forceinline float Calc2D_Dist(const Vector2& Src, const Vector2& Dst) {
//		return sqrt(powf(Src.x - Dst.x, 2) + powf(Src.y - Dst.y, 2));
//	}
//
//	__forceinline Vector2 CalcAngle(const Vector3& Src, const Vector3& Dst) {
//		Vector3 dir = Src - Dst;
//		return Vector2{ RAD2DEG(asin(dir.y / dir.Length())), RAD2DEG(-atan2(dir.x, -dir.z)) };
//	}
//
//
//}