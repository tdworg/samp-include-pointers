#include <a_samp>
#include <ptr/tdw_ptr>

main()
{
	new variable = 1;
	new ptr:pointer = ref(variable);

	printf("Address in the pointer: 0x%08x", pointer);
	printf("Value in the varialbe:  %d", @(pointer));

	print(!"Test pointer arithmetic");
	new ptr:p = pointer;
	p++;
	printf("p++:    0x%08x", p);
	p += 2;
	printf("p += 2: 0x%08x", p);

	print(!"Test dereferencing");
	new buffer[10];
	new ptr:bptr = ref(buffer);

	printf("@(pointer): %d", @(pointer));
	printf("@(bptr)[1]: %d", @(bptr)[1]);
	@(bptr)[1] = 14;
	printf("@(bptr)[1]: %d", @(bptr)[1]);
}