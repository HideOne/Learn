#include <stdio.h>

#define LOG(format, ...) printf(format, __VA_ARGS__)
#define fu(name) #name 

#define Splicing(name, num) #name#num

#define KO(name) name##1
#define KO1(x) KO2(x)
#define KO2(x) #x



int main()
{
#ifdef __cplusplus
	printf("C++\n");
#endif
	//LOG("%d %s", 100, "niaho");

	printf("%s\n", Splicing(ni, 3));
	//KO(wuuu);
	//printf("%s", );
	
	int KO(ni) = 33003;
	//printf("%d\n", KO(ni));
	printf("%s\n", KO1(KO(guo)));

	return 0;
}