//	stbi_img_file_writer.h		-*- C++20 -*-
#pragma once
//@brief: image file writer header
//
//@classes:
//	stbi::ImgFileWriter
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
		virtual void writeToThisFormat(std::string Path_No_Suffix_, int Width_, int Height_, int Num_of_Channls_, const void* Data_) = 0;

	public:
		friend class ImgFileWriter;
	};


	class PngStrategy : public FormatStrategy {
	private:
		void writeToThisFormat(std::string Path_No_Suffix_, int Width_, int Height_, int Num_of_Channls_, const void* Data_) override;
	};

	class BmpStrategy : public FormatStrategy {
	private:
		void writeToThisFormat(std::string Path_No_Suffix_, int Width_, int Height_, int Num_of_Channls_, const void* Data_) override;
	};

	class TgaStrategy : public FormatStrategy {
	private:
		void writeToThisFormat(std::string Path_No_Suffix_, int Width_, int Height_, int Num_of_Channls_, const void* Data_) override;
	};

	class JpgStrategy : public FormatStrategy {
	private:
		void writeToThisFormat(std::string Path_No_Suffix_, int Width_, int Height_, int Num_of_Channls_, const void* Data_) override;
	};





	enum class Format {
		PNG, BMP, TGA, JPG
	};

	class ImgFileWriter
	{
	private:
		std::unique_ptr<FormatStrategy> format_;

	public:
		ImgFileWriter(Format Dest_Format)
			:format_()
		{
			switch (Dest_Format)
			{
			case Format::PNG:
				format_ = std::make_unique<PngStrategy>();
				break;
			case Format::BMP:
				format_ = std::make_unique<BmpStrategy>();
				break;
			case Format::TGA:
				format_ = std::make_unique<TgaStrategy>();
				break;
			case Format::JPG:
				format_ = std::make_unique<JpgStrategy>();
				break;
			}
		}

		template<class InIt>
		void writeInto(std::string Path_No_Suffix, InIt Src, size_t Width, size_t Height)
		{
			using Userdef_Pixel_T = std::decay_t<decltype(*Src)>;
			static_assert(Pixel_type<Userdef_Pixel_T>, "Invalid pixel type");

			std::allocator<Userdef_Pixel_T> allocator = std::allocator< Userdef_Pixel_T>();
			size_t n = (size_t)Width * (size_t)Height;
			Userdef_Pixel_T* buffer = allocator.allocate(n);
			Userdef_Pixel_T* iter = buffer;
			for (size_t i = 0; i < n; ++i)
			{
				*iter++ = *Src++;
			}
			format_->writeToThisFormat(Path_No_Suffix, (int)Width, (int)Height, sizeof(Userdef_Pixel_T), (const void*)buffer);
			allocator.deallocate(buffer, n);
		}

		template<Pixel_type Userdef_Pixel_T, class InIt>
		void writeInto(std::string Path_No_Suffix, InIt Src, size_t Width, size_t Height)
		{
			std::allocator<Userdef_Pixel_T> allocator = std::allocator< Userdef_Pixel_T>();
			size_t n = (size_t)Width * (size_t)Height;
			Userdef_Pixel_T* buffer = allocator.allocate(n);
			for (size_t i = 0; i < n; ++i)
			{
				buffer[i] = *Src++;
			}
			format_->writeToThisFormat(Path_No_Suffix, (int)Width, (int)Height, sizeof(Userdef_Pixel_T), (const void*)buffer);
			allocator.deallocate(buffer, n);
		}

		template<Pixel_type Userdef_Pixel_T>
		void writeInto(std::string Path_No_Suffix, Userdef_Pixel_T* Src, size_t Width, size_t Height)
		{
			format_->writeToThisFormat(Path_No_Suffix, (int)Width, (int)Height, sizeof(Userdef_Pixel_T), (const void*)Src);
		}

		template<Pixel_type Userdef_Pixel_T>
		void writeInto(std::string Path_No_Suffix, const Userdef_Pixel_T* Src, size_t Width, size_t Height)
		{
			format_->writeToThisFormat(Path_No_Suffix, (int)Width, (int)Height, sizeof(Userdef_Pixel_T), (const void*)Src);
		}



		template<class InIt>
		void writeResizedInto(std::string Path_No_Suffix, InIt Src, size_t Width, size_t Height, const Resizer& Reszr)
		{
			using Userdef_Pixel_T = std::decay_t<decltype(*Src)>;
			static_assert(Pixel_type<Userdef_Pixel_T>, "Invalid pixel type");

			std::allocator<Userdef_Pixel_T> allocator = std::allocator< Userdef_Pixel_T>();
			size_t n = (size_t)Width * (size_t)Height;
			Userdef_Pixel_T* buffer = allocator.allocate(n);
			Userdef_Pixel_T* iter = buffer;
			for (size_t i = 0; i < n; ++i)
			{
				*iter++ = *Src++;
			}
			
			Userdef_Pixel_T* rsz_buffer = allocator.allocate(Reszr.toWidth() * Reszr.toHeight());
			Reszr.resize((const void*)buffer, Width, Height, sizeof(Userdef_Pixel_T), rsz_buffer);

			format_->writeToThisFormat(Path_No_Suffix, (int)Reszr.toWidth(), (int)Reszr.toHeight(), sizeof(Userdef_Pixel_T), (const void*)rsz_buffer);
			allocator.deallocate(rsz_buffer, Reszr.toWidth() * Reszr.toHeight());
			allocator.deallocate(buffer, n);
		}

		template<Pixel_type Userdef_Pixel_T, class InIt>
		void writeResizedInto(std::string Path_No_Suffix, InIt Src, size_t Width, size_t Height, const Resizer& Reszr)
		{
			std::allocator<Userdef_Pixel_T> allocator = std::allocator< Userdef_Pixel_T>();
			size_t n = (size_t)Width * (size_t)Height;
			Userdef_Pixel_T* buffer = allocator.allocate(n);
			for (size_t i = 0; i < n; ++i)
			{
				buffer[i] = *Src++;
			}

			Userdef_Pixel_T* rsz_buffer = allocator.allocate(Reszr.toWidth() * Reszr.toHeight());
			Reszr.resize((const void*)buffer, Width, Height, sizeof(Userdef_Pixel_T), rsz_buffer);

			format_->writeToThisFormat(Path_No_Suffix, (int)Reszr.toWidth(), (int)Reszr.toHeight(), sizeof(Userdef_Pixel_T), (const void*)rsz_buffer);
			allocator.deallocate(rsz_buffer, Reszr.toWidth() * Reszr.toHeight());
			allocator.deallocate(buffer, n);
		}

		template<Pixel_type Userdef_Pixel_T>
		void writeResizedInto(std::string Path_No_Suffix, Userdef_Pixel_T* Src, size_t Width, size_t Height, const Resizer& Reszr)
		{
			std::allocator<Userdef_Pixel_T> allocator = std::allocator< Userdef_Pixel_T>();
			Userdef_Pixel_T* rsz_buffer = allocator.allocate(Reszr.toWidth() * Reszr.toHeight());
			Reszr.resize((const void*)Src, Width, Height, sizeof(Userdef_Pixel_T), rsz_buffer);

			format_->writeToThisFormat(Path_No_Suffix, (int)Reszr.toWidth(), (int)Reszr.toHeight(), sizeof(Userdef_Pixel_T), (const void*)rsz_buffer);
			allocator.deallocate(rsz_buffer, Reszr.toWidth() * Reszr.toHeight());
		}

		template<Pixel_type Userdef_Pixel_T>
		void writeResizedInto(std::string Path_No_Suffix, const Userdef_Pixel_T* Src, size_t Width, size_t Height, const Resizer& Reszr)
		{
			std::allocator<Userdef_Pixel_T> allocator = std::allocator< Userdef_Pixel_T>();
			Userdef_Pixel_T* rsz_buffer = allocator.allocate(Reszr.toWidth() * Reszr.toHeight());
			Reszr.resize((const void*)Src, Width, Height, sizeof(Userdef_Pixel_T), rsz_buffer);

			format_->writeToThisFormat(Path_No_Suffix, (int)Reszr.toWidth(), (int)Reszr.toHeight(), sizeof(Userdef_Pixel_T), (const void*)rsz_buffer);
			allocator.deallocate(rsz_buffer, Reszr.toWidth() * Reszr.toHeight());
		}

		
	};


}//namespace stbi end

