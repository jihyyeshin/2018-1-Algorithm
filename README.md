# 2018-1-Algorithm
![os](https://user-images.githubusercontent.com/37070273/64484220-10a25e00-d24a-11e9-9b61-638c8895c5b6.PNG)

algorithm project

## 주제

- N길이의 original sequence를 알기 위해 original sequence에서 불러온 임의의 위치를 가지는 L길이의 short read를 M개 가져와 다시 원래의 original sequence를 만드는 프로젝트

- Reference sequence를 선택적으로 활용할 수 있다.(reference sequence는 original sequence와 같은 길이이며 D개의 mismatch를 가진다.)

- Input: M개의 L 길이 short read, N길이의 reference sequence

- Output: N길이의 origin sequence를 재구성

## 사용한 언어 및 스펙
```
OS : Window 10, Intel® Core™ i3 - 5005U CPU

Language  : C++
```

## 맡은 역할(개인 프로젝트)

1. BWT 알고리즘을 벤치마킹하였는데, BWT table을 만들고, 이 table을 merge sort를 활용하여 정렬한다.

	1-1. A,  C,  G,  T  4개의 문자열만 사용되기 때문에, 4진수화 하고, 다시 10진수로 변경하여 비교 , 정렬하였다.

	1-2. table은 index를 함께 저장한다.

2. BWT table을 이용하여 BWT_T를 만들고, 이를 이용하여 pattern string을 찾는다.
