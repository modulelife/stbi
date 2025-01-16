//	stbi_image_loader.h		-*- C++20 -*-
#pragma once
//@brief: imagefile loader  class header
//
//@classes:
//	stbi::ImageLoader
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


	enum LOAD_OPTION {
		LOAD_ORIGINAL = 0, LOAD_GRY, LOAD_GRYA, LOAD_RGB, LOAD_RGBA
	};


	class ImageLoader {
	private:
		uint8_t* buff_;
		int hgt_;
		int wid_;
		int nch_;

	public:
		ImageLoader()
			: buff_(nullptr), hgt_(0), wid_(0), nch_(0)
		{}
		ImageLoader(const ImageLoader& Other_) = delete;
		ImageLoader(ImageLoader&& Other_) noexcept
			: buff_(Other_.buff_), hgt_(Other_.hgt_), wid_(Other_.wid_), nch_(Other_.nch_)
		{
			Other_.buff_ = nullptr;
			Other_.hgt_ = 0;
			Other_.wid_ = 0;
			Other_.nch_ = 0;
		}
		~ImageLoader();
		ImageLoader& operator=(const ImageLoader& Other_) = delete;
		ImageLoader& operator=(ImageLoader&& Other_) noexcept;

		constexpr bool operator==(const ImageLoader& Other_) { return true; }

		constexpr size_t height() const { return (size_t)hgt_; }
		constexpr size_t width() const { return (size_t)wid_; }
		constexpr size_t numberOfChannls() const { return (size_t)nch_; }

		bool load(const char* Path_, LOAD_OPTION Option_);
		bool loadResized(const char* Path_, LOAD_OPTION Option_, const Resizer& Resizer_);

		template<class OutIt>
		void putInto(OutIt Dest_) noexcept(false)
		{
			using Userdef_Pixel_T = std::decay_t<decltype(*Dest_)>;
			static_assert(Pixel_type<Userdef_Pixel_T>, "Invalid pixel type");

			if (sizeof(Userdef_Pixel_T) != nch_) throw std::domain_error("Userdef_Pixel_T mismatches with loaded image, probably wrong channle number");

			Userdef_Pixel_T* iter = (Userdef_Pixel_T*)buff_;
			size_t n = (size_t)hgt_ * (size_t)wid_;
			for (size_t i = 0; i < n; ++i) {
				*Dest_++ = *iter++;
			}
		}

		template<Pixel_type Userdef_Pixel_T, class OutIt>
		void putInto(OutIt Dest_) noexcept(false)
		{
			if (sizeof(Userdef_Pixel_T) != nch_) throw std::domain_error("Userdef_Pixel_T mismatches with loaded image, probably wrong channle number");

			Userdef_Pixel_T* iter = (Userdef_Pixel_T*)buff_;
			size_t n = (size_t)hgt_ * (size_t)wid_;
			for (size_t i = 0; i < n; ++i) {
				*Dest_++ = *iter++;
			}
		}

	};


}//namespace stbi end