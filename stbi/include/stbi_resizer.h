//	stbi_resizer.h		-*- C++20 -*-
#pragma once
//@brief: image handler header
//
//@classes:
//	stbi::Resizer
//								------------ " image resizer plugin class "
//	
//@description:
//	class packaging of stb_image_resize2
//	
//
//@usage:
//
//----------------------------content begins----------------------------

#include <cstdint>

namespace stbi { class ImgFileLoader; }
namespace stbi { class ImgFileWriter; }




namespace stbi {


	enum Edge_Option {
		Clamp_Edge, Reflect_Edge, Wrap_Edge, Zero_Edge
	};

	enum Filter_Option {
		Default_Filt,
		Box_Filt,
		Triangle_Filt,
		CubicBSpline_Filt,
		CatmullRom_Filt,
		Mitchell_Filt,
		PointSample_Filt
	};
	
	
	class Resizer
	{
	private:
		int to_hgt_;
		int to_wid_;
		Edge_Option edge_;
		Filter_Option filter_;

		void resize(const void* In_Pixels_, int Width_, int Heigt_, int Num_of_Channls_,void* Out_pixels_) const;

	public:
		Resizer(size_t New_Height, size_t New_Width, Edge_Option Edg_Op = Clamp_Edge, Filter_Option Filtr_Op = Default_Filt)
			: to_hgt_((size_t)New_Height), to_wid_((size_t)New_Width), edge_(Edg_Op), filter_(Filtr_Op)
		{}

		constexpr size_t toHeight() const { return (size_t)to_hgt_; }
		constexpr size_t toWidth() const { return (size_t)to_wid_; }

		friend class ImgFileLoader;
		friend class ImgFileWriter;
	};


}//namespace stbi end

