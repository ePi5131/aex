#pragma once
#include <aex_effect.hpp>

namespace aex {
    
inline PF_Boolean IsEmptyRect(const PF_LRect *r){
	return r->left >= r->right || r->top >= r->bottom;
}

inline void UnionLRect(const PF_LRect *src, PF_LRect *dst)
{
	if (IsEmptyRect(dst)) {
		*dst = *src;
	} else if (!IsEmptyRect(src)) {
		dst->left 	= (std::min)(dst->left, src->left);
		dst->top  	= (std::min)(dst->top, src->top);
		dst->right 	= (std::max)(dst->right, src->right);
		dst->bottom = (std::max)(dst->bottom, src->bottom);
	}
}

inline PF_Boolean IsEdgePixel(PF_LRect *rectP, A_long x, A_long y) {
	PF_Boolean x_hitB = x == rectP->left || x == rectP->right;
	PF_Boolean y_hitB = y == rectP->top || y == rectP->bottom;
	
	if (x_hitB) y_hitB = rectP->top <= y && y <= rectP->bottom;
	else if (y_hitB) x_hitB = rectP->left <= x && x <= rectP->right;	

	return x_hitB && y_hitB;
}

}
