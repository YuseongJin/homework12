/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */
//필요한 헤더 파일 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()//메인함수
{
	char command;//char형 변수 선언, 명령어
	//초기화
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));//랜덤 난수 생성

	printf("[----- [Yuseong Jin] [2018038022] -----]");//이름, 학번 출력

	do{//do-while문을 통하여 반복 출력
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");
		//메뉴출력

		printf("Command = ");
		scanf(" %c", &command);
		//명령어 입력받기

		switch(command) {//스위치문
		//소문자와 대문자 모두 입력 받기
		case 'z': case 'Z'://z키를 입력 받았을 때
			initialize(&array);
			//initialize함수 실행
			break;//멈춤
		case 'q': case 'Q'://q키를 입력 받았을 때
			freeArray(array);
			//freeArray 함수 실행
			break;//멈춤
		case 's': case 'S'://s키를 입력 받았을 때
			selectionSort(array);
			//selectionSort함수 실행
			break;//멈춤
		case 'i': case 'I'://i키를 입력 받았을 때
			insertionSort(array);
			//insertionSort함수 실행
			break;//멈춤
		case 'b': case 'B'://b키를 입력 받았을 때
			bubbleSort(array);
			//bubbleSort함수 실행
			break;//멈춤
		case 'l': case 'L'://l키를 입력 받았을 때
			shellSort(array);
			//shellSort함수 실행
			break;//멈춤
		case 'k': case 'K'://k키를 입력 받았을 때
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			//printArray함수 실행
			quickSort(array, MAX_ARRAY_SIZE);
			//quickSort함수 실행
			printf("----------------------------------------------------------------\n");
			printArray(array);
			//printArray함수 실행

			break;//멈춤

		case 'h': case 'H'://h키를 입력 받았을 때
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			//printArray함수 실행
			hashing(array, &hashtable);
			//hashingg함수 실행
			printArray(hashtable);
			//printArray함수 실행
			break;//멈춤

		case 'e': case 'E'://e키를 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);
			//키 값 입력받기

			printArray(hashtable);
			//printArray함수 실행
			index = search(hashtable, key);
			//search함수 실행후 index에 삽입
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			//key, index, hashtable 출력 
			break;//멈춤

		case 'p': case 'P'://p키를 입력 받았을 때
			printArray(array);
			//printArray함수 실행
			break;//멈춤
		default://이외의 입력 받았을 때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			//경고문 출력
			break;//멈춤
		}

	}while(command != 'q' && command != 'Q');
	//q키를 사용하기 전까지 계속 반복

	return 1;//종료
}

int initialize(int** a)//초기화 함수
{
	int *temp = NULL;//temp를 NULL로 초기화

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {//a가 NULL이라면
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		//temp 동적메모리할당
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;//종료
}

int freeArray(int *a)//배열 할당해제 함수
{
	if(a != NULL)//a가 NULL이 아니라면
		free(a);//a 할당해제
	return 0;//종료
}

void printArray(int *a)//배열 출력 함수
{
	if (a == NULL) {//a가 NULL이라면
		printf("nothing to print.\n");
		//출력할 것이 없음을 출력 
		return;//종료
	}

	//for문을 통한 출력
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)//선택정렬 함수
{
	int min;//최솟값
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//출력

/*
<선택정렬>
(1) 주어진 배열에서 최솟값을 찾는다.
(2) 그 최솟값을 맨 앞에 위치한 것과 바꾼다.(swap)
(3) 맨 앞의 것을 제외하고, 나머지 것들을 대상으로 다시 위 (1)~(2) 과정을 반복한다.
*/
	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//출력
	return 0;//종료
}


int insertionSort(int *a)//삽입정렬 함수
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

/*
<삽입정렬>
2번째 인덱스부터 시작해서 그 앞과 자신을 비교하고, 내가 더 크면 더 이상 비교하지 않고 다음 인덱스로 넘어갑니다.

만약 내가 더 작았다면 그 앞에 있던 원소를 한 칸 뒤로 밀고, 자신은 그보다 한칸 더 앞에 있던 원소와 비교를 진행합니다.

앞보다 내가 더 커서 더 이상 비교를 진행하지 않아도 되면, 비어 있는 칸에 자신을 위치시킵니다.

*/

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];
		j = i;
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;//종료
}



int bubbleSort(int *a)//버블정렬 함수
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//출력
/*
<버블정렬>
인접한 두 개의 원소를 비교해서 자리를 교환하는 방식. 
한 단계가 끝나면, 가장 큰 원소 혹은 가장 작은 원소가 마지막 자리로 위치합니다.
*/
	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//출력

	return 0;//종료
}

int shellSort(int *a)//셸 정렬 함수
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//출력
/*
<셸 정렬>
1. 먼저 정렬해야 할 리스트를 일정한 기준에 따라 분류
2. 연속적이지 않은 여러 개의 부분 리스트를 생성
3. 각 부분 리스트를 삽입 정렬을 이용하여 정렬
4. 모든 부분 리스트가 정렬되면 다시 전체 리스트를 더 적은 개수의 부분 리스트로 만든 후에 알고리즘을 반복
5. 위의 과정을 부분 리스트의 개수가 1이 될 때까지 반복
*/

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;//종료
}


int quickSort(int *a, int n)//퀵정렬 함수
{
	int v, t;
	int i, j;
/*
<퀵 정렬>
배열 가운데서 하나의 원소(피벗(pivot))를 고른다.
피벗 앞에는 피벗보다 값이 작은 모든 원소들이 오고, 
피벗 뒤에는 피벗보다 값이 큰 모든 원소들이 오도록 피벗을 기준으로 배열을 둘로(분할) 나눈다. 
분할을 마친 뒤에 피벗은 더 이상 움직이지 않는다.
분할된 두 개의 작은 배열에 대해 재귀(Recursion)적으로 이 과정을 반복한다.
*/
	if (n > 1)
	{
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;//종료
}

int hashCode(int key) {//hashcode
   return key % MAX_HASH_TABLE_SIZE;
   //값 반환
}

int hashing(int *a, int **ht)//해싱
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/
/*
<해싱>
키(Key) 값을 해시 함수(Hash Function)라는 수식에 대입시켜 계산한 후 
나온 결과를 주소로 사용하여 바로 값(Value)에 접근하게 할 수 하는 방법
*/
	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;//종료
}

int search(int *ht, int key)//검색 함수
{
	int index = hashCode(key);//hashcode를 index에 대입

	if(ht[index] == key)//같을때
		return index;//index값 반환

	while(ht[++index] != key)//index증감후 값이 다를때
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;//index값 반환
}



