//	stbi_img_file_loader.h		-*- C++20 -*-
#pragma once
//@brief: imagefile loader  class header
//
//@classes:
//	stbi::ImgFileLoader
//								------------ " image file loader class "
//	
//@description:
//	class packaging of stb_image
//	
//
//@usage:
//
//----------------------------content begins----------------------------

#include <stbi_pixel_type.h>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace stbi { class Resizer; }




namespace stbi {


	enum Load_Option {
		Load_Original = 0, Load_Gry, Load_GryA, Load_RGB, Load_RGBA
	};


	class ImgFileLoader {
	private:
		uint8_t* buff_;
		int hgt_;
		int wid_;
		int nch_;

	public:
		ImgFileLoader()
			: buff_(nullptr), hgt_(0), wid_(0), nch_(0)
		{}
		ImgFileLoader(const ImgFileLoader& Other) = delete;
		ImgFileLoader(ImgFileLoader&& Other) noexcept
			: buff_(Other.buff_), hgt_(Other.hgt_), wid_(Other.wid_), nch_(Other.nch_)
		{
			Other.buff_ = nullptr;
			Other.hgt_ = 0;
			Other.wid_ = 0;
			Other.nch_ = 0;
		}
		~ImgFileLoader();
		ImgFileLoader& operator=(const ImgFileLoader& Other) = delete;
		ImgFileLoader& operator=(ImgFileLoader&& Other) noexcept;

		constexpr bool operator==(const ImgFileLoader& Other) { return true; }

		constexpr size_t height() const { return (size_t)hgt_; }
		constexpr size_t width() const { return (size_t)wid_; }
		constexpr size_t numberOfChannls() const { return (size_t)nch_; }

		bool load(const char* Path, Load_Option Option);
		bool loadResized(const char* Path, Load_Option Option, const Resizer& Reszr);

		template<class OutIt>
		void putInto(OutIt Dest) noexcept(false)
		{
			using Userdef_Pixel_T = std::decay_t<decltype(*Dest)>;
			static_assert(Pixel_type<Userdef_Pixel_T>, "Invalid pixel type");

			if (sizeof(Userdef_Pixel_T) != nch_) throw std::domain_error("Userdef_Pixel_T mismatches with decltype(*OutIt), probably wrong channle number");

			Userdef_Pixel_T* iter = (Userdef_Pixel_T*)buff_;
			size_t n = (size_t)hgt_ * (size_t)wid_;
			for (size_t i = 0; i < n; ++i) {
				*Dest++ = *iter++;
			}
		}

		template<Pixel_type Userdef_Pixel_T, class OutIt>
		void putInto(OutIt Dest) noexcept(false)
		{
			if (sizeof(Userdef_Pixel_T) != nch_) throw std::domain_error("Userdef_Pixel_T mismatches with decltype(*OutIt), probably wrong channle number");

			Userdef_Pixel_T* iter = (Userdef_Pixel_T*)buff_;
			size_t n = (size_t)hgt_ * (size_t)wid_;
			for (size_t i = 0; i < n; ++i) {
				*Dest++ = *iter++;
			}
		}

	};


}//namespace stbi end