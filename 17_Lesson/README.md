## goto statement 
- jumping another line of project
    - long jump: f5-f4-f3-f2-f1 sýralý jumping yerine f5-f1 jump yapýldýðýnda
    - local jump (near jump): ayný state frame içinde (ayný yerel deðiþkenlerin bulunduðu alanda - yani C gibi bir dilde ayný fonksiyon içinde) yapýlan sýçramalardýr.  
    - long ve local jump iþlemleri farklý syntaxlar ile ifade ediliyor olabilir. 
    - local jump --> goto (C, C++)
    - long jump  --> standard kütüphanenin bazý fonksiyonlarý ile yapýlýr. (setjmp, longjmp)
      - setjmp: saves the context
      - longjmp: jumps to specified location
- program akýþýný bir noktadan baþka bir noktaya yöneltmektir. 


* goto kullanma sebepleri: (alýnan ekran görüntüsünden ekleme yapýlacak!!!)
- Cleanly exiting a function 
- Exiting nested loops
- low level performance improvements (only for performance critical codes)


* labels : fonksiyon içinde tanýmlanan isimlerdir. 
- function scope'a dahildir. Bir label fonksiyon içinde herhangi bir noktada kullanýlabilir. 
- labellar sadece goto deyimleri ile birlikte kullanýlmaktadýr. 
- goto out; --> ile ilk out: labeline ait statement'a atlar ve o satýrdan itibaren program akýþý devam eder. 
- out: label mutlaka NULL bile olsa bir statement a sahip olmalýdýr. --> out: ;
- ayný label birden fazla kez ayný function scope altýnda kullanýlamaz.
- kodun okunabilirliðini, test edilebilmesini ve deðiþtirilebilmesini zorlaþtýrdýðý için genellikle kullanýmý tercih edilmez.
- switch-case bloklarýnda yer alan case isimlendirmeleri de labeldýr.
- hangi senaryolarda goto kullanýmý tercih edilmektedir? 
    - goto kullanýmý ile program akýþý daha öncesinde bir noktaya yönlendiriliyorsa, bu durumda kötü bir kullaným yapýldýðý söylenebilir. 
    - iç içe döngülerin hepsinden çýkmak için kullanýmý yaygýndýr. 
    
/----------------------------------------------
* Preferable type of the usage of goto statement: 

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	goto out;
out:;
}
```

/----------------------------------------------

* Not preferable type of the usage of goto statement: 

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
out:;
	goto out;
}
```

/----------------------------------------------
/----------------------------------------------

* Example: Without using goto statement, how to jump to the end of the outermost loop? 

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int is_true(int, int, int);

int main() {

	int flag = 0;

	for (size_t i = 0; i < 1'000'000; ++i)
	{
		//...
		for (size_t j = 0; i < 10'000; ++j)
		{
			//...
			for (size_t k = 0; k < 100; ++k)
			{
				//...
				if (is_true(i,j,k))
				{
					//..
					flag = 1;
					break;
				}
			}
			// 1: with using of break
			if (flag)
				break;
		}
		// 2: 
		if (flag)
			break;
	}
	// 3: with using of If - flag - break - not guaranteed
}
```

/----------------------------------------------
/----------------------------------------------

* Example: With using goto statement, how to jump to the end of the outermost loop? 

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int is_true(int, int, int);

int main() {

	int flag = 0;

	for (size_t i = 0; i < 1'000'000; ++i)
	{
		//...
		for (size_t j = 0; i < 10'000; ++j)
		{
			//...
			for (size_t k = 0; k < 100; ++k)
			{
				//...
				if (is_true(i,j,k))
				{
					//..
					goto out;
				}
			}// 1
		}// 2
	}// 3 : with using goto statement 
	
out:
	//...
	;
}
```

/----------------------------------------------
/----------------------------------------------

* Example: Goto statement example with if-else block

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SUCCESS 1
#define ERROR   0

int allocate_memory(void) {
	//...
	return 1;
}

int setup_interrupts(void) {
	//...
	return 1;
}

int setup_registers(void) {
	//...
	return 0;
}

void teardown_interrupts(void) {}
void free_memory(void){}


int init_device(void) {

	if (allocate_memory() != SUCCESS) goto out1;
	if (setup_interrupts() != SUCCESS) goto out2;
	if (setup_registers() != SUCCESS) goto out3;
	//...
	return SUCCESS;
out1:
	teardown_interrupts();
out2:
	free_memory();
out3:
	return ERROR;
}

int main() {
	if (init_device()) {
		printf("The initialization is successful");
	}
}
```

/----------------------------------------------
/----------------------------------------------

* The same function defining with different style of code for the previous example (specifically int init_device(void) function): 

```cpp
int init_device(void) {

	if (allocate_memory() == ERROR) 
		goto out1;
	if (setup_interrupts() == ERROR) 
		goto out2;
	if (setup_registers() == ERROR) 
		goto out3;
	//...
	return SUCCESS;
out1:
	teardown_interrupts();
out2:
	free_memory();
out3:
	return ERROR;
}
```

/----------------------------------------------
/----------------------------------------------

## Type Conversion:
- makine seviyesinde farklý türdeki  sayýlar arasýnda aritmetik iþlemler uygulanamaz. Ayný türde olmalarý gerekmektedir. 

- int ival; 
  double dval; 
  ival + dval; --> double temp = ival; 
				   temp + double; olacak þekilde arka planda iþlem uygulanýr.

- usual arithmetic conversions 
- assignment type conversion 
ival = dval; --> double --> int dönüþümü yapýldýktan sonra atama iþlemi uygulanýr.

- implicit type conversion : hiçbir iþlem uygulamadan derleyici tarafýndan otomatik olarak gerçekleþtirilmektedir. 
- Not 
- int ival;
  long lval;
  (long)ival + lval; --> Type Casting: operator yoluyla yapýlan tür dönüþümleri

- Syntax hatasýndan ziyade, undefined behaviour, unspecifed behaviour veya data loss sebebiyle, en fazla kodlama hatasýna yol açacak iþlemlerden biridir.

* Type Conversions and Ranks: 
- Tür dönüþümü sýra seviyesi (rank) yüksek olana göre gerçekleþtirilmektedir. (ekran görüntüsünde yer alan açýklamalar eklenecek.) 
- Ayný tamsayý türünün signed ve unsigned olanlarý da ayný rank tedir.???
- unsigned long - unsigned short --> unsigned long 
- unsigned long - signed int  --> unsigned long 
- signed long - unsigned int  --> signed long, unsigned int türünün alabileceði tüm deðerleri temsil edebilebiliyorsa --> signed long türünde iþlem görülür. 
  Ancak signed long (4 byte), unsigned int (4 byte) olduðunda bu temsil gerçekleþtirilemez. Bu durumda --> unsigned long türünde iþlem görülür. 

- double - float --> double
- float - int --> float
- unsigned long - long --> same rank --> unsigned long
- unsigned long - signed int --> unsigned long
- long - unsigned int --> long, unsigned int türünün alabileceði deðerleri temsil edebiliyorsa, long ile iþlem görecektir. 
  eðer temsil edilemiyorsa --> unsigned long ile iþlem görecektir. 
  temsil edilip edilmeme kararý türlerin size'ýna göre verilmektedir. 
  long: 4 byte
  unsigned int : 4 byte olduðudan ;
  long - unsigned int --> unsigned long ile iþlem görecektir.

 - The rank of data types: 
long double
double
float 
long long
long 
int 
/----------------------------------------------
short
char 
_Bool 

* integral promotion (int altý türlerin int e yükseltilmesi)
- int altý türlerin hepsi iþleme int e çevrildikten sonra sokulmaktadýr. 

/----------------------------------------------
/----------------------------------------------

Example: Finding the size of signed/unsinged data types, considering their rank

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {

	// The size of signed data types 
	printf("sizeof(long double) : %ld\n", sizeof(long double));
	printf("sizeof(double)      : %lu\n", sizeof(double));
	printf("sizeof(float)       : %lu\n", sizeof(float));
	printf("sizeof(long long)   : %lu\n", sizeof(long long));
	printf("sizeof(long)        : %lu\n", sizeof(long));
	printf("sizeof(int)         : %lu\n", sizeof(int));
	printf("sizeof(short)       : %lu\n", sizeof(short));
	printf("sizeof(_Bool)       : %lu\n\n", sizeof(_Bool));

	// The size of unsigned data types 
	printf("sizeof(unsigned long long) : %lu\n", sizeof(unsigned long long));
	printf("sizeof(unsigned long)      : %lu\n", sizeof(unsigned long));
	printf("sizeof(unsigned int)       : %lu\n", sizeof(unsigned int));
	printf("sizeof(unsigned short)     : %lu\n", sizeof(unsigned short));

/*
	sizeof(long double) : 8
	sizeof(double)      : 8
	sizeof(float)       : 4
	sizeof(long long)   : 8
	sizeof(long)        : 4
	sizeof(int)         : 4
	sizeof(short)       : 2
	sizeof(_Bool)       : 1
*/

/*
	sizeof(unsigned long long) : 8
	sizeof(unsigned long)      : 4
	sizeof(unsigned int)       : 4
	sizeof(unsigned short)     : 2
*/
}
```

/----------------------------------------------
/----------------------------------------------

* Example: Comparing signed and unsigned variables

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {

	int ival = -1;
	unsigned int uival = 1;

	// prints True!!! BUT we have a warning:
	// warning C4018: '>': signed/unsigned mismatch
	if (ival> uival) 
		printf("True!!\n");
	else
		printf("Wrong!!\n");
}
```

/----------------------------------------------
/----------------------------------------------

* Example: Aritmetik iþlemlerin uygulanmasý

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {

	int first_val = 10;
	int second_val = 7;
	double dval;

	dval = first_val / second_val;
	printf("%f\n", dval); // 1.000000
}
```

/----------------------------------------------
/----------------------------------------------

* Example: Char veriler için tür dönüþüm iþlemleri

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {

	char name = 178;
	
	// Prints False!!!
	// Not returning a warning message with Windows compiler
	if (name == 178)
		printf("True!!!\n"); 
	else
		printf("False!!!\n"); 
}
```

/----------------------------------------------
/----------------------------------------------
