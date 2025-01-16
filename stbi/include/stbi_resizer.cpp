//	stbi_resizer.cpp		-*- C++20 -*-
//
//
//----------------------------content begins----------------------------

#include <stbi_resizer.h>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_origin/stb_image_resize2.h>




namespace stbi {


	void Resizer::resize_(const void* In_Pixels_, int Width_, int Heigt_, int Num_of_Channls_, void* Out_pixels_) const
	{
		stbir_edge edge = STBIR_EDGE_CLAMP;
		stbir_filter filter = STBIR_FILTER_DEFAULT;

		switch (edge_)
		{
		case CLAMP_EDGE:
			edge = STBIR_EDGE_CLAMP;
			break;
		case REFLECT_EDGE:
			edge = STBIR_EDGE_REFLECT;
			break;
		case WRAP_EDGE:
			edge = STBIR_EDGE_WRAP;
			break;
		case ZERO_EDGE:
			edge = STBIR_EDGE_ZERO;
			break;
		}

		switch (filter_)
		{
		case DEFAULT_FILTER:
			filter = STBIR_FILTER_DEFAULT;
			break;
		case BOX_FILTER:
			filter = STBIR_FILTER_BOX;
			break;
		case TRIANGLE_FILTER:
			filter = STBIR_FILTER_TRIANGLE;
			break;
		case CUBICBSPLINE_FILTER:
			filter = STBIR_FILTER_CUBICBSPLINE;
			break;
		case CATMULLROM_FILTER:
			filter = STBIR_FILTER_CATMULLROM;
			break;
		case MITCHELL_FILTER:
			filter = STBIR_FILTER_MITCHELL;
			break;
		case POINTSAMPLE_FILTER:
			filter = STBIR_FILTER_POINT_SAMPLE;
			break;
		}

		switch (Num_of_Channls_)
		{
		case 1:
			stbir_resize(In_Pixels_, Width_, Heigt_, Width_, Out_pixels_, to_wid_, to_hgt_, to_wid_, STBIR_1CHANNEL, STBIR_TYPE_UINT8, edge, filter);
			break;
		case 2:
			stbir_resize(In_Pixels_, Width_, Heigt_, Width_ * 2, Out_pixels_, to_wid_, to_hgt_, to_wid_ * 2, STBIR_2CHANNEL, STBIR_TYPE_UINT8, edge, filter);
			break;
		case 3:
			stbir_resize(In_Pixels_, Width_, Heigt_, Width_ * 3, Out_pixels_, to_wid_, to_hgt_, to_wid_ * 3, STBIR_RGB, STBIR_TYPE_UINT8_SRGB, edge, filter);
			break;
		case 4:
			stbir_resize(In_Pixels_, Width_, Heigt_, Width_ * 4, Out_pixels_, to_wid_, to_hgt_, to_wid_ * 4, STBIR_RGBA, STBIR_TYPE_UINT8_SRGB_ALPHA, edge, filter);
			break;
		}
	}


}//namespace stbi end