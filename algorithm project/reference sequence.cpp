///*
//�˰��� ������Ʈ Reference Sequence
//�й� : 2016112127
//�̸� : ������
//*/
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <cstdlib>
//#include <ctime>
//#define n_len 1000000
//#define mis_count 10000
//using namespace std;
//
//void main()
//{
//   ifstream fin;
//   ofstream fout;
//   char result[4] = { 'A', 'C', 'G', 'T' };
//   char buf;
//   int i, j = 0, randidx;
//   int len = n_len / mis_count;
//   srand((unsigned int)time(NULL));
//   fin.open("input.txt");
//   fout.open("input_ref.txt");
//   if (fin.is_open() == false)
//      cout << "����!" << endl;
//   if (fout.is_open() == false)
//      cout << "����!" << endl;
//   randidx = rand() % len;
//   /*
//   ���� �����ϰ� �����ϰ� �ٲ��شٸ�, ���������� 40000~50000���� �ٲ�� ��찡 ���� ���� �ִ�.
//   �̷��� ��� �ƿ� pattern string�� ã�� �� ���ٰ� �Ǵ��Ͽ���, 
//   ���Ҿ� mismatch�� �� pattern string�� ���� �� 2�� ���� ����� ������
//   1000000/50000=20���� 20�� �߿� ������ �� ���� ������ �� ���� �ٲٵ��� �Ͽ���,
//   ���� �ٲ�µ� ������ ���� �״�� ������ ��찡 ���� ���� �ֱ� ������ �� 40000���� 50000���� mismatch�� 
//   ���� ���̶�� �Ǵ��Ͽ���.
//   */
//   for (i = 0; i < n_len/*, j<n_len*/; i++)
//   {
//      fin >> buf;
//      if (i==j+randidx)
//      {
//         fout << result[rand() % 4];
//         j += len;
//         randidx = rand() % len;
//      }
//      else {
//         fout << buf;
//      }
//   }
//
//   if (fin.is_open() == true)
//      fin.close();
//   if (fout.is_open() == true)
//      fout.close();
//
//   cout << "����!" << endl;
//}