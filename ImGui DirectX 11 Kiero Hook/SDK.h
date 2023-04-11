#pragma once

#include "memory.h"
#include <math.h>
#include <corecrt_math_defines.h>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <vector>
#include <stringapiset.h>
#define RAD(degs) float(degs) * PI / 180.0f
#define DEG(rads) float(rads) * 180.0f / PI

struct UWorld
{

};

struct UGameInstance
{

};

struct ULocalPlayer
{

};

struct FVector
{
	float X, Y, Z;

	FVector() : X(0.f), Y(0.f), Z(0.f) {}

	FVector(float x, float y, float z) : X(x), Y(y), Z(z) {}

	FVector(float InF) : X(InF), Y(InF), Z(InF) { }


	inline float Dot(const FVector& b) const { return (X * b.X) + (Y * b.Y) + (Z * b.Z); }

	inline float MagnitudeSqr() const { return Dot(*this); }

	inline float Magnitude() const { return std::sqrtf(MagnitudeSqr()); }

	float Size() const { return sqrtf(X * X + Y * Y + Z * Z); }

	float Sum() const { return X + Y + Z; }

	float Size2D() const { return sqrtf(X * X + Y * Y); }

	float SizeSquared() const { return X * X + Y * Y + Z * Z; }

	float DistTo(const FVector& V) const { return (*this - V).Size(); }

	FVector operator+(const FVector& other) const { return FVector(X + other.X, Y + other.Y, Z + other.Z); }

	FVector operator-(const FVector& other) const { return FVector(X - other.X, Y - other.Y, Z - other.Z); }

	FVector operator*(const FVector& V) const { return FVector(X * V.X, Y * V.Y, Z * V.Z); }

	FVector operator/(const FVector& V) const { return FVector(X / V.X, Y / V.Y, Z / V.Z); }

	bool operator==(const FVector& V) const { return X == V.X && Y == V.Y && Z == V.Z; }

	bool operator!=(const FVector& V) const { return X != V.X || Y != V.Y || Z != V.Z; }

	FVector operator-() const { return FVector(-X, -Y, -Z); }

	FVector operator+(float Bias) const { return FVector(X + Bias, Y + Bias, Z + Bias); }

	FVector operator-(float Bias) const { return FVector(X - Bias, Y - Bias, Z - Bias); }

	FVector operator*(float Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); } const

		FVector operator/(float Scale) const { const float RScale = 1.f / Scale; return FVector(X * RScale, Y * RScale, Z * RScale); }

	FVector operator=(const FVector& V) { X = V.X; Y = V.Y; Z = V.Z; return *this; }

	FVector operator+=(const FVector& V) { X += V.X; Y += V.Y; Z += V.Z; return *this; }

	FVector operator-=(const FVector& V) { X -= V.X; Y -= V.Y; Z -= V.Z; return *this; }

	FVector operator*=(const FVector& V) { X *= V.X; Y *= V.Y; Z *= V.Z; return *this; }

	FVector operator/=(const FVector& V) { X /= V.X; Y /= V.Y; Z /= V.Z; return *this; }

	FVector operator*=(float Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }

	FVector operator/=(float V) { const float RV = 1.f / V; X *= RV; Y *= RV; Z *= RV; return *this; }

	float operator|(const FVector& V) const { return X * V.X + Y * V.Y + Z * V.Z; }

	FVector operator^(const FVector& V) const { return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X); }
	inline float Distance(FVector v) {
		return float(sqrtf(powf(v.X - X, 2.0) + powf(v.Y - Y, 2.0) + powf(v.Z - Z, 2.0)));
	}
	bool IsValid()
	{
		if (X == 0 || Y == 0 || Z == 0)
			return false;
		else
			return true;
	}
	static const FVector ZeroVector;

	static const FVector OneVector;
};

struct FVector2D
{
	float X, Y;

	FVector2D() : X(0), Y(0) {}

	FVector2D(float x, float y) : X(x), Y(y) {}

	float Size() const;

	FVector2D operator + (const FVector2D& other) const { return FVector2D(X + other.X, Y + other.Y); }

	FVector2D operator- (const FVector2D& other) const { return FVector2D(X - other.X, Y - other.Y); }

	FVector2D operator* (float scalar) const { return FVector2D(X * scalar, Y * scalar); }

	FVector2D& operator=  (const FVector2D& other) { X = other.X; Y = other.Y; return *this; }

	FVector2D& operator+= (const FVector2D& other) { X += other.X; Y += other.Y; return *this; }

	FVector2D& operator-= (const FVector2D& other) { X -= other.X; Y -= other.Y; return *this; }

	FVector2D& operator*= (const float other) { X *= other; Y *= other; return *this; }

	friend bool operator==(const FVector2D& one, const FVector2D& two) { return one.X == two.X && one.Y == two.Y; }

	friend bool operator!=(const FVector2D& one, const FVector2D& two) { return !(one == two); }

	friend bool operator>(const FVector2D& one, const FVector2D& two) { return one.X > two.X && one.Y > two.Y; }

	friend bool operator<(const FVector2D& one, const FVector2D& two) { return one.X < two.X && one.Y < two.Y; }
	bool IsValid()
	{
		if (X == 0 || Y == 0)
			return false;
		else
			return true;
	}
};

struct FQuat
{
public:

	float X, Y, Z, W;

	FQuat() : X(0.f), Y(0.f), Z(0.f), W(0.f) {};

	FQuat(float InX, float InY, float InZ, float InW) : X(InX), Y(InY), Z(InZ), W(InW) {}

	FQuat(struct FRotator& R);

	FVector RotateVector(const struct FVector& V) const;
};
struct FRotator
{
	float Pitch, Yaw, Roll;

	FRotator()
		: Pitch(0), Yaw(0), Roll(0)
	{ }

	FRotator(float pitch, float yaw, float roll) : Pitch(pitch), Yaw(yaw), Roll(roll) {}

	FRotator operator+ (const FRotator& other) const { return FRotator(Pitch + other.Pitch, Yaw + other.Yaw, Roll + other.Roll); }

	FRotator operator- (const FRotator& other) const { return FRotator(Pitch - other.Pitch, Yaw - other.Yaw, Roll - other.Roll); }

	FRotator operator* (float scalar) const { return FRotator(Pitch * scalar, Yaw * scalar, Roll * scalar); }

	FRotator& operator=  (const FRotator& other) { Pitch = other.Pitch; Yaw = other.Yaw; Roll = other.Roll; return *this; }

	FRotator& operator+= (const FRotator& other) { Pitch += other.Pitch; Yaw += other.Yaw; Roll += other.Roll; return *this; }

	FRotator& operator-= (const FRotator& other) { Pitch -= other.Pitch; Yaw -= other.Yaw; Roll -= other.Roll; return *this; }

	FRotator& operator*= (const float other) { Yaw *= other; Pitch *= other; Roll *= other; return *this; }

	struct FQuat Quaternion() const;
};

template<class T>
struct TArray
{
	friend class FString;

public:
	TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	}

	TArray(T* data, int32_t count, int32_t max)
		: Data(data),
		Count(count),
		Max(max)
	{
	}

	int Num() const
	{
		return Count;
	}

	T& operator[](int i)
	{
		return Data[i];
	}

	const T& operator[](int i) const
	{
		return Data[i];
	}

	bool IsValidIndex(int i) const
	{
		return i < Num();
	}



private:
	T* Data;
	int32_t Count;
	int32_t Max;
};
class FString : public TArray<wchar_t>
{
public:
	inline FString()
	{
	};

	FString(const wchar_t* other)
	{
		Max = Count = *other ? static_cast<int>(std::wcslen(other)) + 1 : 0;

		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	};
	FString(const wchar_t* other, int count)
	{
		Data = const_cast<wchar_t*>(other);;
		Max = Count = count;
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* wide() const
	{
		return Data;
	}

	int multi(char* name, int size) const
	{
		return WideCharToMultiByte(CP_UTF8, 0, Data, Count, name, size, nullptr, nullptr) - 1;
	}

	std::string ToString() const
	{
		auto length = std::wcslen(Data);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

		return str;
	}
};

class FLinearColor
{
public:
	float R, G, B, A;
};

enum class EAresOutlineMode : uint8_t {
	None = 0,
	Outline = 1,
	Block = 2,
	Enemy = 3,
	AlwaysOutline = 4,
	AlwaysEnemy = 5,
	EAresOutlineMode_MAX = 6
};

class UObject
{
public:
	char padding_01[0x18];
	int32_t ComparisonIndex;
	static UObject* StaticFindObject(UObject* Class, UObject* InOuter, const wchar_t* Name, bool ExactClass)
	{
		static uintptr_t StaticFindObjectAddress = TEST::Obama + Offsets::StaticFindObject;

		auto StaticFindObjectFN = reinterpret_cast<UObject * (__fastcall*)(UObject*, UObject*, const wchar_t*, bool)>(StaticFindObjectAddress);

		return StaticFindObjectFN(Class, InOuter, Name, ExactClass);
	}
	static void ProcessEvent(void* class_, UObject* function, void* params)
	{
		reinterpret_cast<void (*)(void*, UObject*, void*)>(TEST::Obama + Offsets::ProcessEvent)(class_, function, params);
	}
};


//This is here if you want to use it but I wouldn't use functions since they make the cheat 10,000,000,000% detected
struct APlayerState
{
	
};

struct USkeletalMeshComponent
{

};

struct APlayerController : UObject
{
	
};

struct AAresEquippable : UObject
{
	
};

struct UAresInventory : UObject
{
	
};

struct UAresOutlineComponent {

	
};

struct AShooterCharacter : UObject
{
	
};