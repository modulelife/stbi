//	stbi_pixel_type.h		-*- C++20 -*-
#pragma once
//@brief: pixel type defs
//
//	
//@description:
//	pixel types surpported
//	
//
//@usage:
//
//----------------------------content begins----------------------------

#include <cstdint>
#include <concepts>




namespace stbi {


	using Gry = uint8_t;
	struct GryA { uint8_t Y; uint8_t A; };
	struct RGB{ uint8_t R; uint8_t G; uint8_t B; };
	struct RGBA { uint8_t R; uint8_t G; uint8_t B; uint8_t A; };



	template<typename T>
	concept Gry_type = sizeof(T) == 1 && std::is_trivially_copyable_v<T>;

	template<typename T>
	concept GryA_struct = sizeof(T) == 2 && std::is_trivially_copyable_v<T>;

	template<typename T>
	concept RGB_struct = sizeof(T) == 3 && std::is_trivially_copyable_v<T>;

	template<typename T>
	concept RGBA_struct = sizeof(T) == 4 && std::is_trivially_copyable_v<T>;

	template<typename T>
	concept Pixel_type = Gry_type<T> || GryA_struct<T> || RGB_struct<T> || RGBA_struct<T>;

}//namespace stbi end