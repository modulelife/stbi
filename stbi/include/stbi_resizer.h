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

namespace stbi { class ImageLoader; }
namespace stbi { template<class FormatImpl> class ImageWriter; }




namespace stbi {


	enum EDGE_OPTION {
		CLAMP_EDGE, REFLECT_EDGE, WRAP_EDGE, ZERO_EDGE
	};

	enum FILTER_OPTION {
		DEFAULT_FILTER,
		BOX_FILTER,
		TRIANGLE_FILTER,
		CUBICBSPLINE_FILTER,
		CATMULLROM_FILTER,
		MITCHELL_FILTER,
		POINTSAMPLE_FILTER
	};
	
	
	class Resizer
	{
	private:
		int to_hgt_;
		int to_wid_;
		EDGE_OPTION edge_;
		FILTER_OPTION filter_;

		void resize_(const void* In_Pixels_, int Width_, int Heigt_, int Num_of_Channls_,void* Out_pixels_) const;

	public:
		Resizer(size_t New_Height_, size_t New_Width_, EDGE_OPTION Edge_ = CLAMP_EDGE, FILTER_OPTION Filter_ = DEFAULT_FILTER)
			: to_hgt_((int)New_Height_), to_wid_((int)New_Width_), edge_(Edge_), filter_(Filter_)
		{}

		constexpr size_t toHeight() const { return (size_t)to_hgt_; }
		constexpr size_t toWidth() const { return (size_t)to_wid_; }

		friend class ImageLoader;
		template<class FormatImpl> friend class ImageWriter;
	};


}//namespace stbi end

