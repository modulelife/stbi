//	stbi_image_loader.cpp		-*- C++20 -*-
//
//
//----------------------------content begins----------------------------

#include <stbi_image_loader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_origin/stb_image.h>
#include <stbi_resizer.h>




namespace stbi {


	ImageLoader::~ImageLoader()
	{
		if(buff_ != nullptr) stbi_image_free(buff_);
	}

	ImageLoader& ImageLoader::operator=(ImageLoader&& Other_) noexcept
	{
		if (buff_ != nullptr) stbi_image_free(buff_);
		buff_ = Other_.buff_;
		hgt_ = Other_.hgt_;
		wid_ = Other_.wid_;
		nch_ = Other_.nch_;
		Other_.buff_ = nullptr;
		Other_.hgt_ = 0;
		Other_.wid_ = 0;
		Other_.nch_ = 0;
		return *this;
	}

	bool ImageLoader::load(const char* Path_, LOAD_OPTION Option_)
	{
		if (buff_ != nullptr) stbi_image_free(buff_);
		buff_ = stbi_load(Path_, &wid_, &hgt_, &nch_, Option_);
		if (Option_ != 0) nch_ = Option_;
		return buff_ != nullptr;
	}

	bool ImageLoader::loadResized(const char* Path_, LOAD_OPTION Option_, const Resizer& Resizer_)
	{
		if (buff_ != nullptr) stbi_image_free(buff_);
		buff_ = stbi_load(Path_, &wid_, &hgt_, &nch_, Option_);
		if (Option_ != 0) nch_ = Option_;
		if (buff_ == nullptr) return false;

		uint8_t* rsz_buff = (uint8_t*)STBI_MALLOC(Resizer_.toHeight() * Resizer_.toWidth() * nch_);
		if (rsz_buff == nullptr) return false;

		Resizer_.resize_(buff_, wid_, hgt_, nch_, rsz_buff);
		stbi_image_free(buff_);
		buff_ = rsz_buff;
		wid_ = Resizer_.toWidth();
		hgt_ = Resizer_.toHeight();
		return true;
	}



}//namespace stbi end