//	stbi_img_file_loader.cpp		-*- C++20 -*-
//
//
//----------------------------content begins----------------------------

#include <stbi_img_file_loader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_origin/stb_image.h>
#include <stbi_resizer.h>




namespace stbi {


	ImgFileLoader::~ImgFileLoader()
	{
		if(buff_ != nullptr) stbi_image_free(buff_);
	}

	ImgFileLoader& ImgFileLoader::operator=(ImgFileLoader&& Other) noexcept
	{
		if (buff_ != nullptr) stbi_image_free(buff_);
		buff_ = Other.buff_;
		hgt_ = Other.hgt_;
		wid_ = Other.wid_;
		nch_ = Other.nch_;
		Other.buff_ = nullptr;
		Other.hgt_ = 0;
		Other.wid_ = 0;
		Other.nch_ = 0;
		return *this;
	}

	bool ImgFileLoader::load(const char* Path, Load_Option Option)
	{
		if (buff_ != nullptr) stbi_image_free(buff_);
		uint8_t* rbuff = stbi_load(Path, &wid_, &hgt_, &nch_, Option);
		if (Option != 0) nch_ = Option;
		return buff_ != nullptr;
	}

	bool ImgFileLoader::loadResized(const char* Path, Load_Option Option, const Resizer& Reszr)
	{
		if (buff_ != nullptr) stbi_image_free(buff_);
		buff_ = stbi_load(Path, &wid_, &hgt_, &nch_, Option);
		if (Option != 0) nch_ = Option;
		if (buff_ == nullptr) return false;

		uint8_t* rsz_buff = (uint8_t*)STBI_MALLOC(Reszr.toHeight() * Reszr.toWidth() * nch_);
		if (rsz_buff == nullptr) return false;

		Reszr.resize(buff_, wid_, hgt_, nch_, rsz_buff);
		stbi_image_free(buff_);
		buff_ = rsz_buff;
		wid_ = Reszr.toWidth();
		hgt_ = Reszr.toHeight();
		return true;
	}



}//namespace stbi end