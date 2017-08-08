/** ======================================================================== **\
	Pointers

| Description:

| Version:
	1.0.0

| Dependencies:
	- n\a

| Compatible with the JIT plugin:
	- Yes

| License:
	Copyright (c) 2017 Double V

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software
		in a product, an acknowledgement in the product documentation would be
		appreciated but is not required.
	2.	Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
	3.	This notice may not be removed or altered from any source distribution.
\** ======================================================================== **/

#if defined _inc_tdw_ptr
	#undef _inc_tdw_ptr
#endif

#if defined _TDW_POINTERS
	#endinput
#endif

#define _TDW_POINTERS

const __PTR_BYTES_PER_CELL = cellbits / charbits;

// move the expr token (',' or ';') to the end
#define PTR_MOVE_EXPR PTR_MOVE_EXPR_SEMICOLON:PTR_MOVE_EXPR_COMMA
#define PTR_MOVE_EXPR_SEMICOLON:%8(%1;%0)) PTR_IS_POINTER:%8(%1));
#define PTR_MOVE_EXPR_COMMA:%8(%1,%0))     PTR_IS_POINTER:%8(%1)),

// check the pointer is dereferenced or not
#define PTR_IS_POINTER PTR_IS_POINTER_NO:PTR_IS_POINTER_YES
#define PTR_IS_POINTER_YES:%8(%1))   _:PTR_PARSE_EXPR:(%1))
#define PTR_IS_POINTER_NO:%8(%9*%1)) _:PTR_DE_PARSE_EXPR:(%1))

// parse the expressions for pointers
#define PTR_PARSE_EXPR PTR_PARSE_SET_PLUS:PTR_PARSE_SET_MINUS:PTR_PARSE_SET_MUL:PTR_PARSE_SET_DIV:PTR_PARSE_SET_MOD:PTR_PARSE_SET:PTR_PARSE_GET
// #define PTR_PARSE_SET_POST_DEC:%8(%1--)     (%1) -= (__PTR_BYTES_PER_CELL)
// #define PTR_PARSE_SET_POST_INC:%8(%1++)     (%1) += (__PTR_BYTES_PER_CELL)
// #define PTR_PARSE_SET_PRE_INC:%8(--%1)      (%1) -= (__PTR_BYTES_PER_CELL)
// #define PTR_PARSE_SET_PRE_INC:%8(++%1)      (%1) += (__PTR_BYTES_PER_CELL)
#define PTR_PARSE_SET_MOD:%8(%1%=%2)           (%1) %= ((%2) * __PTR_BYTES_PER_CELL)
#define PTR_PARSE_SET_DIV:%8(%1/=%2)           (%1) /= ((%2) * __PTR_BYTES_PER_CELL)
#define PTR_PARSE_SET_MUL:%8(%1*=%2)           (%1) *= ((%2) * __PTR_BYTES_PER_CELL)
#define PTR_PARSE_SET_MINUS:%8(%1-=%2)         (%1) -= ((%2) * __PTR_BYTES_PER_CELL)
#define PTR_PARSE_SET_PLUS:%8(%1+=%2)          (%1) += ((%2) * __PTR_BYTES_PER_CELL)
#define PTR_PARSE_SET:%8(%1=%2)                (%1)  = ((%2) * __PTR_BYTES_PER_CELL)
#define PTR_PARSE_GET:%8(%1)                   (%1)

// parse the expressions for dereferenced pointers
#define PTR_DE_PARSE_EXPR PTR_DE_PARSE_SET_PLUS:PTR_DE_PARSE_SET_MINUS:PTR_DE_PARSE_SET_MUL:PTR_DE_PARSE_SET_DIV:PTR_DE_PARSE_SET_MOD:PTR_DE_PARSE_SET:PTR_DE_PARSE_GET
// new __TDW_PTR_INC_DEC_TEMP;
// #define PTR_DE_PARSE_SET_POST_DEC:%8(%1--)     Pointer_Set((%1),Pointer_Get(%1)-1),Pointer_Get(%1)
// #define PTR_DE_PARSE_SET_POST_INC:%8(%1++)     Pointer_Set((%1),Pointer_Get(%1)+1),Pointer_Get(%1)
// #define PTR_DE_PARSE_SET_PRE_DEC:%8(--%1)      Pointer_Set((%1),(__TDW_PTR_INC_DEC_TEMP = Pointer_Get(%1))-1),__TDW_PTR_INC_DEC_TEMP
// #define PTR_DE_PARSE_SET_PRE_INC:%8(++%1)      Pointer_Set((%1),(__TDW_PTR_INC_DEC_TEMP = Pointer_Get(%1))+1),__TDW_PTR_INC_DEC_TEMP
#define PTR_DE_PARSE_SET_MOD:%8(%1%=%2)        Pointer_Set((%1),Pointer_Get(%1)%(%2))
#define PTR_DE_PARSE_SET_DIV:%8(%1/=%2)        Pointer_Set((%1),Pointer_Get(%1)/(%2))
#define PTR_DE_PARSE_SET_MUL:%8(%1*=%2)        Pointer_Set((%1),Pointer_Get(%1)*(%2))
#define PTR_DE_PARSE_SET_MINUS:%8(%1-=%2)      Pointer_Set((%1),Pointer_Get(%1)-(%2))
#define PTR_DE_PARSE_SET_PLUS:%8(%1+=%2)       Pointer_Set((%1),Pointer_Get(%1)+(%2))
#define PTR_DE_PARSE_SET:%8(%1=%2)             Pointer_Set((%1),(%2))
#define PTR_DE_PARSE_GET:%8(%1)                Pointer_Get(%1)

// entry point
#define @ptr%0\32;%1\10; (PTR_MOVE_EXPR:(%0%1))


stock ref(...)
{
	#emit load.s.pri 12
	#emit retn
	return 0;
}
stock Pointer_Set(const Pointer:ptr, const val)
{
	// in C: *(*ptr) = val
	#emit load.s.pri val
	#emit sref.s.pri ptr
	return 0;
}
stock Pointer_Get(const Pointer:ptr)
{
	// in C: return *(*ptr)
	#emit lref.s.pri ptr
	#emit retn
	return 0;
}