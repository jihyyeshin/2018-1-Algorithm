/*
�˰��� ������Ʈ Benchmark File
�й� : 2016112127
�̸� : ������
*/

#include <ctime>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstdio>

#define L_LEN 50
#define M_COUNT 100000//1000000
#define N_LEN 100000//1000000
#define mismatch 1
#define S_arrange 200
#define arrange_len 10

using namespace std;

typedef struct {
	char *S = new char[S_arrange];
	int value;
	int index;
}seq_table;

typedef struct {
	char S;
	int index;
}seq_bwt;

void MergeSort(seq_table *a, int left, int right);
void Merge(seq_table *a, int left, int mid, int right);

void MakeBWT(seq_bwt *, const char *fname);

int charTint(char a);
int CalValue(seq_table *a, int left, int right, int len);
char *FindPS(char *RefSeq, char *Sorted_BWT, int *index_for_ACGT, seq_bwt *BWT_T);

int compare(const void *a, const void *b) {
	return strcmp((char*)a, (char*)b);
}

void main()
{
	clock_t s_b, e_b, s_f, e_f;
	int i, count = 0, count_i = 0, flag = 0, index_for_ACGT[5];
	char buf;
	seq_bwt *BWT_T = new seq_bwt[N_LEN];//BWT(T)
	char *Sorted_BWT = new char[N_LEN];//������ ���ĵ� BWT(T)
	char *ResultSeq;
	char *RefSeq = new char[N_LEN + L_LEN];//�޾ƿ� reference sequence ��ü
	ifstream f_ref;
	f_ref.open("input_ref.txt");
	for (i = 0; i < N_LEN; i++)
		f_ref >> RefSeq[i];//reference�޾ƿ�
	f_ref.close();

	cout << "\n========================================" << endl;
	cout << "  Benchmark BWT Algorithm" << endl;
	cout << "  Length of Origin Sequence : " << N_LEN << endl;
	cout << "  Mismatch : " << mismatch << endl;
	cout << "========================================" << endl;

	s_b = clock();
	MakeBWT(BWT_T, "input_ref.txt");
	cout << "[FIN]" << endl;

	cout << "  Make Sorted BWT(T) ";
	for (i = 0; i < N_LEN; i++)
		Sorted_BWT[i] = BWT_T[i].S;
	qsort(Sorted_BWT, N_LEN, sizeof(Sorted_BWT[0]), compare);//quick sort
	e_b = clock();
	cout << "[FIN]\n----------------------------------------" << endl;
	for (i = 0; i < N_LEN; i++)
	{
		if (charTint(Sorted_BWT[i]) == count_i)
		{
			flag = 1;
		}
		if (flag == 1)
		{
			index_for_ACGT[count_i + 1] = i;
			count_i++;
			flag = 0;
		}
	}

	s_f = clock();
	RefSeq = FindPS(RefSeq, Sorted_BWT, index_for_ACGT, BWT_T);
	e_f = clock();

	ifstream f_origin;

	f_origin.open("input.txt");
	for (int i = 0; i < N_LEN; i++)
	{
		f_origin >> buf;
		if (buf != RefSeq[i])
			count++;
	}
	f_origin.close();

	cout << "----------------------------------------" << endl;
	cout << "  Accuracy : " << ((double)(N_LEN - count) / N_LEN) * 100 << "%" << endl;
	cout << "  Time for BWT(T) : " << (float)(e_b - s_b) / CLOCKS_PER_SEC << " sec" << endl;
	cout << "  Time for Finding : " << (float)(e_f - s_f) / CLOCKS_PER_SEC << " sec" << endl;
	cout << "========================================\n" << endl;
}

char *FindPS(char *RefSeq, char *Sorted_BWT, int *index_for_ACGT, seq_bwt *BWT_T)
{
	int i, j, k, m = 0, n, p, mis_count = 0;
	char PS[L_LEN + 1];//pattern string

	int randIdx;
	cout << "  Find Pattern String and Index ";
	FILE *f_input = fopen("input.txt", "r");
	srand((unsigned int)time(NULL));

	for (i = 0; i < M_COUNT; i++)//short read �о��
	{
		/*�����ϰ� short read �����ͼ� ����*/
		randIdx = rand() % (N_LEN - L_LEN);
		if (fseek(f_input, randIdx, SEEK_SET))//ó������ �����Ѹ�ŭ Ŀ�� �̵�
			exit(1);//���� ������ ����
		fgets(PS, L_LEN + 1, f_input);
		/*Sorted_BWT���� ã��*/

		int i_s, i_e;
		i_s = charTint(PS[L_LEN - 1]) + 1;
		if (i_s != 4) i_e = index_for_ACGT[i_s + 1];
		else i_e = N_LEN - 1;

		for (j = index_for_ACGT[i_s]; j < i_e; j++)
		{
			k = L_LEN - 1;
			n = j;
			mis_count = 0;
			m = 0;
			while (m < N_LEN)
			{
				if (BWT_T[m].index == BWT_T[n].index - 1)
				{
					if (PS[k] == BWT_T[m].S || mis_count <= mismatch)
					{
						if (PS[k] != BWT_T[m].S) mis_count++;
						k--;
						n = m;
						m = -1;
					}
					else break;
				}
				m++;
				if (k < 0 && mis_count <= mismatch) //�� ����
				{
					n = BWT_T[n].index;
					for (p = n; p < n + L_LEN; p++)//���ο� �ؽ�Ʈ ���Ͽ� ����
					{
						RefSeq[p] = PS[p - n];
					}
					break;
				}
			}
		}
	}

	cout << "[FIN]" << endl;

	return RefSeq;
}

void MakeBWT(seq_bwt *BWT_T, const char *fname)
{
	ifstream fin;
	fin.open(fname);
	int i, j, k, sum = 0;
	seq_table *BWT_Table = new seq_table[N_LEN];
	char *value_buf = new char[N_LEN];//�ӽ����� buf
	char *refG = new char[N_LEN + 1];//$�ٿ����ϱ� ������ +1��

	cout << "  Make BWT Table ";

	for (i = 0; i < N_LEN; i++)//reference genome �޾ƿ�
	{
		fin >> refG[i];
	}
	refG[i++] = '$';

	for (i = 0; i < N_LEN; i++)
	{
		BWT_T[i].S = refG[(i + N_LEN) % (N_LEN)];//bwt�� ���� �� �ʿ��� value
		BWT_T[i].index = i;
		for (k = 0; k < S_arrange; k++)
		{
			j = (i + k) % (N_LEN);
			BWT_Table[i].S[k] = refG[j];
		}
	}

	/*BWT Table�� �� ����*/
	for (i = 0; i < N_LEN; i++)
	{
		for (j = 0; j < arrange_len; j++)
		{
			sum += charTint(BWT_Table[i].S[j])*pow(4, arrange_len - j - 1);
		}
		if (j == arrange_len)
		{
			BWT_Table[i].value = sum;
			sum = 0;
		}
		BWT_Table[i].index = i;
	}
	cout << "[FIN]" << endl;
	cout << "  Sorting ";
	MergeSort(BWT_Table, 0, N_LEN - 1);
	cout << "[FIN]" << endl;
	cout << "  Make BWT(T) ";
	///*bwt(t)*/
	for (i = 0; i < N_LEN; i++)
		value_buf[i] = BWT_T[BWT_Table[i].index].S;//buf�� �ӽ� ����
	for (i = 0; i < N_LEN; i++)
	{
		BWT_T[i].S = value_buf[i];//�ٽ� �ű�
		BWT_T[i].index = BWT_Table[i].index;
	}

	delete[] value_buf;
	delete[] BWT_Table;//����
}

void MergeSort(seq_table *a, int left, int right)
{
	int mid, i, j, len;
	if (left < right)
	{
		mid = (left + right) / 2;
		MergeSort(a, left, mid);
		MergeSort(a, mid + 1, right);
		Merge(a, left, mid, right);
	}
}

void Merge(seq_table *a, int left, int mid, int right)
{
	int *index = new int[N_LEN];
	int i, j, flag, len = 0;
	int left_ptr, right_ptr, buf_ptr;
	left_ptr = left;
	right_ptr = mid + 1;
	buf_ptr = left;

	//���� �������� ���� ������ �������� ���� ��
	//���� ������~������ ������ ���� �迭 ����, ������ ������~�� ������ �迭 ������ �̹� ���ĵǾ� �ֱ� ������ ������ ������� ���Ͽ� b�迭�� ����
	while (left_ptr <= mid && right_ptr <= right)
	{
		if (a[left_ptr].value < a[right_ptr].value)
		{
			index[buf_ptr++] = a[left_ptr++].index;
		}
		else if (a[left_ptr].value > a[right_ptr].value)
		{
			index[buf_ptr++] = a[right_ptr++].index;
		}
		else //arrange_len�̻����� ���ؾ��Ѵٴ� ��
		{
			len = 0;
			flag = CalValue(a, left_ptr, right_ptr, len + arrange_len);
			if (flag == 0)
			{
				index[buf_ptr++] = a[left_ptr++].index;
			}
			else
			{
				index[buf_ptr++] = a[right_ptr++].index;
			}
		}
	}
	//left_ptr�� �迭 ������ �׻� �� ���� ���, right �迭�� ������ ������ �ڸ��� ������� ����
	if (left_ptr > mid)
	{
		for (i = right_ptr; i <= right; i++)
		{
			index[buf_ptr++] = a[i].index;
		}
	}
	//right_ptr�� �迭 ������ �׻� �� ���� ���, left �迭�� ������ ������ �ڸ��� ������� ����
	else
	{
		for (i = left_ptr; i <= mid; i++)
		{
			index[buf_ptr++] = a[i].index;
		}
	}
	//���ĵ� b�迭�� ������ �ٽ� a�迭��   
	for (i = left; i <= right; i++)
	{
		a[i].index = index[i];
	}

	delete[]index;
}

int CalValue(seq_table *a, int left, int right, int len)
{
	int j;
	int bufL = 0;
	int bufR = 0;
	for (j = len; j < len + arrange_len; j++)
	{
		bufL += charTint(a[left].S[j])*pow(4, len + arrange_len - j - 1);
		bufR += charTint(a[right].S[j])*pow(4, len + arrange_len - j - 1);
	}
	if (bufL < bufR)
		return 0;
	else if (bufL > bufR)
		return 1;
	else CalValue(a, left, right, len + arrange_len);

	return 0;
}

int charTint(char a)
{
	switch (a) {
	case 'A':
		return 0;
	case 'C':
		return 1;
	case 'G':
		return 2;
	case 'T':
		return 3;
	case '$':
		return -1;
	default:
		std::cout << "error" << a;
		break;
	}
}
