/** ======================================================================== **\
	Pointers

| Description:
	This library provides the opportunity to use the pointers in Pawn.

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

#define pointer@end
#define pointer@ pointer@array:pointer@assign:pointer@none
#define pointer@array:%7(%0)%8pointer@end)%5[%6] %7(ptr:(%0)+_:(%6))%8pointer@end)%5
#define pointer@assign:%7(%0)%8pointer@end)%9=   %7(TDW_gPointerValue = _:TDW_gPointerAddress = (%0)),deptr:TDW_gPointerValue)%9=
#define pointer@none:%7(%0)%8pointer@end)        %7(pointer_read(ptr:(%0))))

//
// This is macro for dereferencing pointers.
//

#define @(%1) (_:pointer@:(%1)pointer@end)

//
// Common constants
//

const ptr:NULL = ptr:0;

stock
	TDW_gPointerValue,        // used to store the current value.
	ptr:TDW_gPointerAddress;  // used to store the address pointed to by a pointer.

//
// Helper functions.
//

stock ptr:ref(...)
{
	#emit load.s.pri 12
	#emit retn
	return ptr:0;  // make compiler happy.
}

stock pointer_read(ptr:address)
{
	#emit lref.s.pri address
	#emit retn
	return 0;  // make compiler happy.
}

stock pointer_write(ptr:address, ...)
{
	assert(numargs() == 2);
	#emit load.s.pri 16
	#emit sref.s.pri address
	#emit retn
	return 0;  // make compiler happy.
}

//
// Overloaded operators for arithmetic operations on pointers.
//

// PLUS
// ============================================================================
stock ptr:operator+(ptr:left, _:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit shl.c.alt 2
	#emit add
	#emit retn
	return ptr:0;  // make compiler happy.
}
stock ptr:operator+(ptr:left, ptr:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit add
	#emit retn
	return ptr:0;  // make compiler happy.
}
stock ptr:operator+(_:left, ptr:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit shl.c.pri 2
	#emit add
	#emit retn
	return ptr:0;  // make compiler happy.
}

// MINUS
// ============================================================================
stock ptr:operator-(ptr:left, _:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit shl.c.alt 2
	#emit sub
	#emit retn
	return ptr:0;  // make compiler happy.
}
stock ptr:operator-(ptr:left, ptr:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit sub
	#emit retn
	return ptr:0;  // make compiler happy.
}
stock ptr:operator-(_:left, ptr:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit shl.c.pri 2
	#emit sub
	#emit retn
	return ptr:0;  // make compiler happy.
}

// ASSIGN
// ============================================================================
stock ptr:operator=(ptr:val)
{
	#emit load.s.pri val
	#emit retn
	return ptr:0;  // make compiler happy.
}

// INCREMENT and DECREMENT
// ============================================================================
stock ptr:operator++(ptr:val)
{
	#emit load.s.pri val
	#emit add.c 4
	#emit retn
	return ptr:0;  // make compiler happy.
}
stock ptr:operator--(ptr:val)
{
	#emit load.s.pri val
	#emit const.alt 4
	#emit sub
	#emit retn
	return ptr:0;  // make compiler happy.
}

// COMPARATORS: > < >= <= == !=
// ============================================================================
stock bool:operator>(ptr:left, _:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit grtr
	#emit retn
	return false;  // make compiler happy.
}
stock bool:operator>(_:left, ptr:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit grtr
	#emit retn
	return false;  // make compiler happy.
}
stock bool:operator<(ptr:left, _:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit less
	#emit retn
	return false;  // make compiler happy.
}
stock bool:operator<(_:left, ptr:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit less
	#emit retn
	return false;  // make compiler happy.
}
stock bool:operator>=(ptr:left, _:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit geq
	#emit retn
	return false;  // make compiler happy.
}
stock bool:operator>=(_:left, ptr:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit geq
	#emit retn
	return false;  // make compiler happy.
}
stock bool:operator<=(ptr:left, _:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit leq
	#emit retn
	return false;  // make compiler happy.
}
stock bool:operator<=(_:left, ptr:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit leq
	#emit retn
	return false;  // make compiler happy.
}
stock bool:operator!=(ptr:left, _:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit neq
	#emit retn
	return false;  // make compiler happy.
}
stock bool:operator!=(_:left, ptr:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit neq
	#emit retn
	return false;  // make compiler happy.
}
stock bool:operator==(ptr:left, _:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit eq
	#emit retn
	return false;  // make compiler happy.
}
stock bool:operator==(_:left, ptr:right)
{
	#emit load.s.pri left
	#emit load.s.alt right
	#emit eq
	#emit retn
	return false;  // make compiler happy.
}

//
// Dereferenced pointers.
//

// ASSIGN
// ============================================================================
stock deptr:operator=(_:val)
{
	#emit load.s.pri val
	#emit sref.pri TDW_gPointerAddress
	return deptr:TDW_gPointerAddress;  // make compiler happy.
}
stock deptr:operator=(Float:val)
{
	#emit load.s.pri val
	#emit sref.pri TDW_gPointerAddress
	return deptr:TDW_gPointerAddress;  // make compiler happy.
}
stock deptr:operator=(bool:val)
{
	#emit load.s.pri val
	#emit sref.pri TDW_gPointerAddress
	return deptr:TDW_gPointerAddress;  // make compiler happy.
}
