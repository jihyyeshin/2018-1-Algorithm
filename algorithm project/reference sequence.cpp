///*
//알고리즘 프로젝트 Reference Sequence
//학번 : 2016112127
//이름 : 신지혜
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
//      cout << "실패!" << endl;
//   if (fout.is_open() == false)
//      cout << "실패!" << endl;
//   randidx = rand() % len;
//   /*
//   값을 완전하게 랜덤하게 바꿔준다면, 연속적으로 40000~50000개가 바뀌는 경우가 생길 수도 있다.
//   이러한 경우 아예 pattern string을 찾을 수 없다고 판단하였고, 
//   더불어 mismatch는 한 pattern string의 길이 당 2개 정도 생기기 때문에
//   1000000/50000=20에서 20개 중에 랜덤한 한 개를 선택해 그 값만 바꾸도록 하였고,
//   값을 바꿨는데 원래의 것이 그대로 나오는 경우가 생길 수도 있기 떄문에 총 40000에서 50000개의 mismatch가 
//   생길 것이라고 판단하였다.
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
//   cout << "성공!" << endl;
//}