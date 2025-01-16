//	stbi_image_writer.h		-*- C++20 -*-
#pragma once
//@brief: image file writer header
//
//@classes:
//	stbi::ImageWriter
//								------------ " image file writer class "
//	
//@description:
//	class packaging of stb_image_write
//	
//
//@usage:
//
//----------------------------content begins----------------------------

#include <stbi_pixel_type.h>
#include <string>
#include <memory>
#include <stbi_resizer.h>




namespace stbi {


	class FormatStrategy {
	private:
		virtual void writeToThisFormat_(std::string Path_No_Suffix_, int Width_, int Height_, int Num_of_Channls_, const void* Data_) = 0;

	public:
		friend class ImageWriter;
	};


	class PngStrategy : public FormatStrategy {
	private:
		void writeToThisFormat_(std::string Path_No_Suffix_, int Width_, int Height_, int Num_of_Channls_, const void* Data_) override;
	};

	class BmpStrategy : public FormatStrategy {
	private:
		void writeToThisFormat_(std::string Path_No_Suffix_, int Width_, int Height_, int Num_of_Channls_, const void* Data_) override;
	};

	class TgaStrategy : public FormatStrategy {
	private:
		void writeToThisFormat_(std::string Path_No_Suffix_, int Width_, int Height_, int Num_of_Channls_, const void* Data_) override;
	};

	class JpgStrategy : public FormatStrategy {
	private:
		void writeToThisFormat_(std::string Path_No_Suffix_, int Width_, int Height_, int Num_of_Channls_, const void* Data_) override;
	};





	enum class FORMAT {
		PNG, BMP, TGA, JPG
	};

	class ImageWriter
	{
	private:
		std::unique_ptr<FormatStrategy> format_;

	public:
		ImageWriter(FORMAT Dest_Format_)
			:format_()
		{
			switch (Dest_Format_)
			{
			case FORMAT::PNG:
				format_ = std::make_unique<PngStrategy>();
				break;
			case FORMAT::BMP:
				format_ = std::make_unique<BmpStrategy>();
				break;
			case FORMAT::TGA:
				format_ = std::make_unique<TgaStrategy>();
				break;
			case FORMAT::JPG:
				format_ = std::make_unique<JpgStrategy>();
				break;
			}
		}

		template<class InIt>
		void writeInto(std::string Path_No_Suffix_, InIt Src_, size_t Width_, size_t Height_)
		{
			using Userdef_Pixel_T = std::decay_t<decltype(*Src_)>;
			static_assert(Pixel_type<Userdef_Pixel_T>, "Invalid pixel type");

			std::allocator<Userdef_Pixel_T> allocator = std::allocator< Userdef_Pixel_T>();
			size_t n = Width_ * Height_;
			Userdef_Pixel_T* buffer = allocator.allocate(n);
			Userdef_Pixel_T* iter = buffer;
			for (size_t i = 0; i < n; ++i)
			{
				*iter++ = *Src_++;
			}
			format_->writeToThisFormat_(Path_No_Suffix_, (int)Width_, (int)Height_, sizeof(Userdef_Pixel_T), (const void*)buffer);
			allocator.deallocate(buffer, n);
		}

		template<Pixel_type Userdef_Pixel_T, class InIt>
		void writeInto(std::string Path_No_Suffix_, InIt Src_, size_t Width_, size_t Height_)
		{
			std::allocator<Userdef_Pixel_T> allocator = std::allocator< Userdef_Pixel_T>();
			size_t n = Width_ * Height_;
			Userdef_Pixel_T* buffer = allocator.allocate(n);
			for (size_t i = 0; i < n; ++i)
			{
				buffer[i] = *Src_++;
			}
			format_->writeToThisFormat_(Path_No_Suffix_, (int)Width_, (int)Height_, sizeof(Userdef_Pixel_T), (const void*)buffer);
			allocator.deallocate(buffer, n);
		}

		template<Pixel_type Userdef_Pixel_T>
		void writeInto(std::string Path_No_Suffix_, Userdef_Pixel_T* Src_, size_t Width_, size_t Height_)
		{
			format_->writeToThisFormat_(Path_No_Suffix_, (int)Width_, (int)Height_, sizeof(Userdef_Pixel_T), (const void*)Src_);
		}

		template<Pixel_type Userdef_Pixel_T>
		void writeInto(std::string Path_No_Suffix_, const Userdef_Pixel_T* Src_, size_t Width_, size_t Height_)
		{
			format_->writeToThisFormat_(Path_No_Suffix_, (int)Width_, (int)Height_, sizeof(Userdef_Pixel_T), (const void*)Src_);
		}



		template<class InIt>
		void writeResizedInto(std::string Path_No_Suffix_, InIt Src_, size_t Width_, size_t Height_, const Resizer& Resizer_)
		{
			using Userdef_Pixel_T = std::decay_t<decltype(*Src_)>;
			static_assert(Pixel_type<Userdef_Pixel_T>, "Invalid pixel type");

			std::allocator<Userdef_Pixel_T> allocator = std::allocator< Userdef_Pixel_T>();
			size_t n = Width_ * Height_;
			Userdef_Pixel_T* buffer = allocator.allocate(n);
			Userdef_Pixel_T* iter = buffer;
			for (size_t i = 0; i < n; ++i)
			{
				*iter++ = *Src_++;
			}
			
			Userdef_Pixel_T* rsz_buffer = allocator.allocate(Resizer_.toWidth() * Resizer_.toHeight());
			Resizer_.resize_((const void*)buffer, Width_, Height_, sizeof(Userdef_Pixel_T), rsz_buffer);

			format_->writeToThisFormat_(Path_No_Suffix_, (int)Resizer_.toWidth(), (int)Resizer_.toHeight(), sizeof(Userdef_Pixel_T), (const void*)rsz_buffer);
			allocator.deallocate(rsz_buffer, Resizer_.toWidth() * Resizer_.toHeight());
			allocator.deallocate(buffer, n);
		}

		template<Pixel_type Userdef_Pixel_T, class InIt>
		void writeResizedInto(std::string Path_No_Suffix_, InIt Src_, size_t Width_, size_t Height_, const Resizer& Resizer_)
		{
			std::allocator<Userdef_Pixel_T> allocator = std::allocator< Userdef_Pixel_T>();
			size_t n = Width_ * Height_;
			Userdef_Pixel_T* buffer = allocator.allocate(n);
			for (size_t i = 0; i < n; ++i)
			{
				buffer[i] = *Src_++;
			}

			Userdef_Pixel_T* rsz_buffer = allocator.allocate(Resizer_.toWidth() * Resizer_.toHeight());
			Resizer_.resize_((const void*)buffer, Width_, Height_, sizeof(Userdef_Pixel_T), rsz_buffer);

			format_->writeToThisFormat_(Path_No_Suffix_, (int)Resizer_.toWidth(), (int)Resizer_.toHeight(), sizeof(Userdef_Pixel_T), (const void*)rsz_buffer);
			allocator.deallocate(rsz_buffer, Resizer_.toWidth() * Resizer_.toHeight());
			allocator.deallocate(buffer, n);
		}

		template<Pixel_type Userdef_Pixel_T>
		void writeResizedInto(std::string Path_No_Suffix_, Userdef_Pixel_T* Src_, size_t Width_, size_t Height_, const Resizer& Resizer_)
		{
			std::allocator<Userdef_Pixel_T> allocator = std::allocator< Userdef_Pixel_T>();
			Userdef_Pixel_T* rsz_buffer = allocator.allocate(Resizer_.toWidth() * Resizer_.toHeight());
			Resizer_.resize_((const void*)Src_, Width_, Height_, sizeof(Userdef_Pixel_T), rsz_buffer);

			format_->writeToThisFormat_(Path_No_Suffix_, (int)Resizer_.toWidth(), (int)Resizer_.toHeight(), sizeof(Userdef_Pixel_T), (const void*)rsz_buffer);
			allocator.deallocate(rsz_buffer, Resizer_.toWidth() * Resizer_.toHeight());
		}

		template<Pixel_type Userdef_Pixel_T>
		void writeResizedInto(std::string Path_No_Suffix_, const Userdef_Pixel_T* Src_, size_t Width_, size_t Height_, const Resizer& Resizer_)
		{
			std::allocator<Userdef_Pixel_T> allocator = std::allocator< Userdef_Pixel_T>();
			Userdef_Pixel_T* rsz_buffer = allocator.allocate(Resizer_.toWidth() * Resizer_.toHeight());
			Resizer_.resize_((const void*)Src_, Width_, Height_, sizeof(Userdef_Pixel_T), rsz_buffer);

			format_->writeToThisFormat_(Path_No_Suffix_, (int)Resizer_.toWidth(), (int)Resizer_.toHeight(), sizeof(Userdef_Pixel_T), (const void*)rsz_buffer);
			allocator.deallocate(rsz_buffer, Resizer_.toWidth() * Resizer_.toHeight());
		}

		
	};


}//namespace stbi end

