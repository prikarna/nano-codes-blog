unsigned int GetAPSR()
{
	unsigned int	res = 0;

	asm(
		"mrs sp, apsr\n\t"
		"mov %[result], sp" : [result] "=r" (res)
		);

	//asm(
	//	"mrs r0, apsr\n\t"
	//	"mov %[result], r0" : [result] "=r" (res)
	//	);

	return res;
}