## Lab 4 - Linguagem C | Organização e gestão de memória, ponteiros e passagem de argumentos

:warning: Este laboratório deverá ser executado com base neste repositório inicial de código, através de `git clone`.

> O repositório foi criado a partir de [`CProgram_Template`](https://github.com/estsetubal-atad/CProgram_Template).
>
> Consulte o respetivo README para compreender a estrutura do projeto e módulos incluídos.
>
> **How-To Repositórios**: <https://www.youtube.com/watch?v=THsizwp30r0>

**Objetivos**:

- Compreensão da organização de memória de um programa;

- Uso de ponteiros e passagem de argumentos (valor vs. referência);

- Gestão de memória dinâmica.

**Referências**:

- Slides das aulas TP.

- *"Linguagem C"*, *e-book* disponível no Moodle.

---

### 1 | Análise de execução e organização da memória (tutorial)

> :bulb:  
> Iremos utilizar a ferramenta *online* [PythonTutor](https://pythontutor.com/c.html#mode=edit) para analisarmos e visualizarmos a memória na execução passo-a-passo de programas que utilizam os conceitos-alvo deste laboratório.  
> Todo o trabalho proposto nesta secção será efetuado diretamente nesta ferramenta.

1. Carregue no site o seguinte programa:

	```cpp
	#include <stdio.h>

	int sumEven(int *arr, int arrLength);

	int main() {
	
		int numbers[] = {1, 4, 3, 7, 10, 5};
		
		int sum1 = sumEven(numbers, 6);
		printf("Sum 1 = %d\n", sum1);
		
		int *p = &numbers[3];
		*p = 6; // !
		int sum2 = sumEven(p, 3);
		printf("Sum 2 = %d\n", sum2);
		
		return 0;
	}

	int sumEven(int *arr, int arrLength) {
		int sum = 0;
		for(int i=0; i < arrLength; i++) {
			if( arr[i] % 2 == 0 ) {
				sum += *(arr + i);  
			}        
		}
		return sum;
	}
	```

	- :bulb: Execute o programa passo-a-passo e compreenda que:

		- Todas as variáveis e parâmetros de uma função são alocadas na *memória stack*; durante a execução de uma função é criada uma *frame (página) de memória stack* que contém toda a informação local.

		- Quando uma função é invocada, os argumentos são **copiados** para os parâmetros dessa função e são guardados localmente.

			- Há variáveis/argumentos que contêm valores, outros *referências* (ponteiros). Uma referência pode apontar para uma variável que reside noutra função (na *stack frame*).

		- Enquanto uma função é executada, a função que a invocou (*caller function*) mantém-se em memória com a sua informação. 
		
		- Quando uma função termina, a sua *stack frame* é destruída e toda a informação contida "desaparece". Se houver um ponteiro que referencie memória nessa *frame*, deixará de ser válido.

	- :question: Questões:

		- Na função `sumEven` o que significa `*(arr + i)`?

		- No main, preceda a instrução comentada com `\\ !` com:

			```cpp
			p = 6;
			*p = 6; // !	
			```

			- Execute novamente o programa na plataforma.

			- :robot: Pergunte ao ChatGPT porque a sequência destas duas instruções fazem o programa terminar abruptamente (*segfault*).

2. Defina a função:

	```cpp
	bool isEven(int *pInt) {
		int value = *pInt;
		bool res = value % 2 == 0;
		return res;
	}
	```

	e utilize-a em substituição da condição do `if` na função `sumEven`. Volte a visualizar a execução do programa.


### 2 | Alocação de memória e mutabilidade (tutorial)

3. Carregue o seguinte programa no site **PythonTutor**: 

	```cpp
	#include <stdio.h>
	#include <string.h>

	void eat(char *fruit) {  
		while(*fruit) {
			*fruit = 'x';
			fruit++;
		}  
	}

	char* growAndEat(char *fruit) {
		char otherFruit[20];
		
		strcpy(otherFruit, fruit);
		
		eat(otherFruit);
		
		return otherFruit;
	}

	int main() {
		// Part 1
		int x[] = {10, 20, 30};
		int* p = &x[1]; // pointer into middle

		*p = 1;
		
		char* fruits[3] = {"apples", "bananas", "cherries"};
						
		printf("I have %d %s\n", *p, fruits[1]);
		
		char *fruit1 = "cherries";
		char fruit2[] = "melon";

		// Part 2
		
		eat(fruit2);
		
		char *newFruit = growAndEat(fruit1);
		
		printf("%s\n", fruit2);
		printf("%s\n", newFruit);
	
		return 0;
	}
	```

	- :bulb: Execute passo-a-passo a primeira parte do programa e:

		- Verifique que as *strings literais* são alocadas numa zona de memória de apenas leitura e são "reaproveitadas" sempre que aparecem repetidas no código.

		- :robot: Pergunte ao ChatGPT qual a diferença entre `char *s = "Hello"` e `char s[] = "Hello"`

	- :bulb: Continue e execute passo-a-passo a segunda parte do programa. Note que:

		- A função `eat` recebe uma referência (ponteiro) para a primeira letra da *string*.

		- :robot: Passe ao ChatGPT o código da função `eat` e peça-lhe para explicar a função.

		- :robot: Pergunte ao ChatGPT porque a função `growAndEat` não é semanticamente correta.

	- :keyboard: Substitua, na função `growAndEat`, a alocação na *stack* do array `otherFruit`:

		```cpp
		char otherFruit[20];
		```

		por uma alocação na *heap* (com `malloc` ou `calloc`) de uma *string* com o tamanho estritamente necessário (mesmo tamanho de `fruit`).

		- Volte a visualizar a execução do programa;

		- :robot: Pergunte ao ChatGPT se foi feita uma correta gestão de memória dinâmica.

			- Modifique o programa de acordo com a resposta.

### 3 | Aplicação prática de conceitos

> :bulb:  
> Esta parte do laboratório será efetuada em cima do código contido neste repositório. Contém uma solução do laboratório anterior e é uma continuação do mesmo.

4. Faça `git clone` deste repositório;

5. Compile e execute o programa, verificando o seu funcionamento.

6. Adicione e implemente no módulo `etf` a função:

	```cpp
	void etfPrintByReference(ETF *pEtf)
	```

	cujo propósito é o de receber uma *referência* (ponteiro) para um `ETF` existente e imprimir o seu conteúdo (semelhante à função já existente, mas o parâmetro é passado por *referência* em vez de por *valor*).

7. Substitua a invocação de `etfPrint` pela invocação da função anterior no `main` e na função `etfPrintTable`. Compile e execute o programa, verificando que mantém o comportamento. 

	- Qual foi o "ganho" nesta modificação em termos de optimização do uso de memória? Se não souber, pergunte ao ChatGPT :robot: ...

8. Declare um novo tipo de dados (*alias*) no módulo `etf`:

	```cpp
	typedef ETF* PtETF;
	```

	- :question: O que representa o tipo `PtETF`?

	- Modifique o parâmetro da função `etfPrintByReference` para este tipo. Compile e execute o programa, verificando que nada mudou.

9. As funções de ordenação existentes utilizam o algoritmo *bubble sort* que é baseado em "trocas". Pretende-se tornar estas trocas mais eficazes no que diz respeito ao uso de memória. 

	- Defina e implemente a função seguinte no início do ficheiro `etf.c` (!) :bulb: o modificador `static` indica que esta função só será reconhecida/utilizada dentro deste ficheiro:

		```cpp
		/**
		 * @brief Swaps the values of two ETF pointers.
		* 
		* @param e1 Pointer to the first ETF.
		* @param e2 Pointer to the second ETF.
		*/
		static void swap(PtETF e1, PtETF e2) {
			// TODO ...
		}
		```

	- Substitua o código de troca existente pela invocação desta função, e.g.,:

		```cpp
		ETF temp = arr[j];
		arr[j] = arr[j + 1];
		arr[j + 1] = temp;
		```

		por

		```cpp
		swap(&arr[j], &arr[j + 1]);
		```

	- Compile e execute o programa, verificando que mantém o comportamento.

10. Pretende-se poder importar a informação dos ETFs para um array alocado na *heap* e com o tamanho estritamente necessário para guardar a informação em `etfs.csv`.

	Adicione ao módulo `etf` e implemente a seguinte função de acordo com a sua documentação:

	```cpp
	/**
	 * @brief Imports an array of ETFs from a file and stores it in dynamically allocated memory.
	* 
	* @param filename The name of the file to read from.
	* @param arrLength Pointer to an integer where the function will store the number of ETFs imported.
	* @return A dynamically allocated array of ETFs, or NULL if the import fails.
	* @note The caller is responsible for freeing the allocated memory.
	*/
	ETF* etfImportHeap(const char* filename, int *arrLength);
	```

	- :bulb: Para determinar o tamanho do array alocado terá de saber quantas linhas o ficheiro contém. Isto significa que terá de ler o ficheiro duas (!) vezes: (1) Para determinar o tamanho do array a ser alocado; (2) ler efetivamente a informação de cada linha - o código já existente.

		Após o ficheiro ser lido até ao final, é possível "voltar ao início" com a instrução `rewind(file)`.

	- Substitua no `main` o código:

		```cpp
		ETF etfs[MAX_ETF];
    	int dataLength = etfImport("etfs.csv", etfs, MAX_ETF);
		```

		por

		```cpp
		int dataLength;
    	ETF *etfs = etfImportHeap("etfs.csv", &dataLength);
		```

	- Tudo o resto se mantém inalterado. Compile e execute o programa, verificando que mantém o seu comportamento.

11. Compile o programa em modo *debug* (`make debug`) e execute o programa através do *valgrind*, digitando na linha de comandos:

	```console
	$> bash mem_check.sh
	```

	- Verifique se a gestão da memória dinâmica foi efetuada corretamente. Faça as alterações necessárias em caso de ser sinalizado algum *memory leak*.

---

bruno.silva@estsetubal.ips.pt





