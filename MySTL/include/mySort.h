#pragma once
#include<iostream>
#include<vector>
#include<map>
using namespace std;

void input(vector<int>& v, int n) {
	int num;
	cout << "Please enter the digits you want to sort:";
	for (int i = 0; i < n; ++i) {
		cin >> num;
		v.push_back(num);
	}
}

void output(const vector<int>& v) {
	cout << "The sorted numbers are:";
	for (int num : v) {
		cout << num << " ";
	}
	cout << '\n';
}

void bubble_Sort(vector<int>& p, int n) {
	for (int i = 0;i < n - 1;i++) {
		for (int j = 0;j < n - i - 1;j++) {
			if (p[j] > p[j + 1]) {
				int temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
}

void select_Sort(vector<int>& p, int n) {
	for (int i = 0;i < n - 1;i++) {
		int k = i;
		for (int j = i + 1;j < n;j++) {
			if (p[k] > p[j]) {
				k = j;
			}
		}
		int temp = p[i];
		p[i] = p[k];
		p[k] = temp;
	}
}

void insert_sort(vector<int>& p, int n) {
	for (int i = 1;i < n ;i++) {
		int j = i;
		int temp = p[j];
		while ((j>0)&&(temp<p[j-1])) {
			p[j] = p[j - 1];
			j--;
		}
		p[j] = temp;
	}
}

void shell_sort(vector<int>& p, int n) {
	int intervals = n/2;
	while (intervals > 0) {
		for (int i = intervals;i < n;i++) {
			int j = i;
			int temp = p[j];
			while ((j >= intervals) && (temp < p[j - intervals])) {
				p[j] = p[j - intervals];
				j-= intervals;
			} 
			p[j] = temp;
		}
		intervals /= 2;
	}
}



void merge_sort(vector<int>&  arr, int n) {

}

void select_sortAlgorithm() {
	cout << '\n';
	cout << "********************************" << '\n';
	cout << "***bubble_Sort please press 1***" << '\n';
	cout << "***select_Sort please press 2***" << '\n';
	cout << "***insert_sort please press 3***" << '\n';
	cout << "***shell_sort please press 4***" << '\n';
	cout << "***merge_sort please press 5***" << '\n';
	cout << "********************************" << '\n';
	cout << "Please enter your choice: ";
	int i;
	cin >> i;
	map<int, void(*)(vector<int>& p, int n)> sortActions = {
		{1, bubble_Sort},
		{2, select_Sort},
		{3, insert_sort},
		{4, shell_sort},
		{5, merge_sort},
		{0, [](vector<int>& p, int n) { cout << "Welcome to use next time."<< '\n'; return; }}
	};

	if (sortActions.find(i) != sortActions.end()) {
		int n;
		vector<int> arr;
		cout << "Please enter the number of digits you want to sort: ";
		cin >> n;
		input(arr, n);
		sortActions[i](arr, n);
		output(arr);
	}
	else {
		cout << "Please enter the correct number corresponding to the desired operation."<< '\n';
	}
}