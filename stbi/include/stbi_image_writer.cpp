//	stbi_image_writer.cpp		-*- C++20 -*-
//
//
//----------------------------content begins----------------------------

#include <stbi_image_writer.h>


#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_origin/stb_image_write.h>




namespace stbi {
	

	void format::PNG::writeToThisFormat_(std::string Path_No_Suffix_, int Width_, int Height_, int Num_of_Channls_, const void* Data_) {
		Path_No_Suffix_ += ".png";
		stbi_write_png(Path_No_Suffix_.c_str(), Width_, Height_, Num_of_Channls_, Data_, Width_ * Num_of_Channls_);
	}

	void format::BMP::writeToThisFormat_(std::string Path_No_Suffix_, int Width_, int Height_, int Num_of_Channls_, const void* Data_) {
		Path_No_Suffix_ += ".bmp";
		stbi_write_bmp(Path_No_Suffix_.c_str(), Width_, Height_, Num_of_Channls_, Data_);
	}

	void format::TGA::writeToThisFormat_(std::string Path_No_Suffix_, int Width_, int Height_, int Num_of_Channls_, const void* Data_) {
		Path_No_Suffix_ += ".tga";
		stbi_write_tga(Path_No_Suffix_.c_str(), Width_, Height_, Num_of_Channls_, Data_);
	}

	void format::JPG::writeToThisFormat_(std::string Path_No_Suffix_, int Width_, int Height_, int Num_of_Channls_, const void* Data_) {
		Path_No_Suffix_ += ".jpg";
		stbi_write_jpg(Path_No_Suffix_.c_str(), Width_, Height_, Num_of_Channls_, Data_, 100);
	}




}//namespace stbi end


