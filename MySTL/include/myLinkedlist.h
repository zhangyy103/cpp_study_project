#pragma once
#include<iostream>
using namespace std;
#include<string>
class myNode {
public:
	string n;
	myNode* next = nullptr;
	myNode(string str = "") { this->n = str; }
};

class myLinkedlist {
public:
	typedef char* iterator;

	myLinkedlist() { 
		head = new myNode();
		tail = head;
	}
	~myLinkedlist() {
		myNode* temp = head;
		while (temp != nullptr) {
			myNode* nextNode = temp->next;
			delete temp;
			temp = nextNode;
		}
	}
	void addLinkedlist() {
		string str;
		cout << "Please input the data you want to add(input @ to exit)"<<endl;
		while (cin >> str && str != "@") {
			myNode* temp = new myNode(str);
			tail->next = temp;
			tail = temp;
		}			//尾不含数据,首为""
	}

	void showData() {
		myNode* temp = head ->next;
		int i = 1;
		while (temp != tail->next) {
			cout << i << "." << temp->n << "  ";
			temp = temp->next;
			i++;
		}
	}

	void deleteData() {
		myNode* prtemp = head;
		myNode* temp = head->next;
		string str;
		cout << "Please input the data you want to delete:";
		cin >> str;
		bool swi = true;
		for (;temp != tail;temp = temp->next,prtemp = prtemp->next) {
			if (temp->n == str) {
				prtemp->next = temp->next;
				delete temp;
				cout << "The data has been deleted" << endl;
				swi = false;
				break;
			}
		}
		if (swi)cout << "You did not enter this data";
	}

	void changeData() {
		myNode* temp = head->next;
		string str;
		cout << "Please input the data you want to delete:";
		cin >> str;
		bool swi = true;
		for (;temp != tail->next;temp = temp->next) {
			if (temp->n == str) {
				cout << "Please input the new data:";
				cin >> str;
				temp->n = str;
			}
		}
		if (swi)cout << "You did not enter this data";
	}

private:
	myNode* head;	//单链表头结点指针
	myNode* tail; //单链表尾结点指针
};

void Linkedlist() {
	myLinkedlist linkedlist;
	cout << '\n';
	cout << "********************************" << '\n';
	cout << "***addlinkedList please press 1***" << '\n';
	cout << "***showData please press 2***" << '\n';
	cout << "***deleteData please press 3***" << '\n';
	cout << "***changeData please press 4***" << '\n';
	cout << "********************************" << '\n';
	cout << "Please enter your choice: ";
	int i;
	cin >> i;
	switch (i) {
	case 1:linkedlist.addLinkedlist();break;
	case 2:linkedlist.showData();break;
	case 3:linkedlist.deleteData();break;
	case 4:linkedlist.changeData();break;
	default:cout << "Please enter the right numbers";
	}
}
///////////////////////////////////////////////////循环双向链表/////////////////////////////
//////////////////////////////class Node {					
//////////////////////////////public:						   
//////////////////////////////	Node* prev = nullptr;        
//////////////////////////////	Node* next = nullptr;         
//////////////////////////////	string data;                
//////////////////////////////};                         
//////////////////////////////
//////////////////////////////class Doublelist {
//////////////////////////////public:
//////////////////////////////	Doublelist() {
//////////////////////////////		head = new Node();
//////////////////////////////		tail = head;
//////////////////////////////	}
//////////////////////////////	~Doublelist() {
//////////////////////////////		Node* temp = head;
//////////////////////////////		while (temp != tail) {
//////////////////////////////			Node* nextNode = temp->next;
//////////////////////////////			delete temp;
//////////////////////////////			temp = nextNode;
//////////////////////////////		}
//////////////////////////////	}
//////////////////////////////	void addDoublelist() {
//////////////////////////////		string str;
//////////////////////////////		cout << "Please input the data you want to add(input @ to exit)" << endl;
//////////////////////////////		while (cin >> str && str != "@") {
//////////////////////////////			Node* temp = new Node();
//////////////////////////////			temp->data = str;
//////////////////////////////			tail->next = temp;
//////////////////////////////			temp->prev = tail;
//////////////////////////////			tail = temp;
//////////////////////////////		}
//////////////////////////////		tail->next = head;
//////////////////////////////		head->prev = tail;
//////////////////////////////	}
//////////////////////////////	void showDoublelist() {
//////////////////////////////		Node* temp = head->next;
//////////////////////////////		int i = 1;
//////////////////////////////		while (temp != tail->next) {
//////////////////////////////			cout << i << "." << temp->data << "  ";
//////////////////////////////			temp = temp->next;
//////////////////////////////			i++;
//////////////////////////////		}
//////////////////////////////
//////////////////////////////	}
//////////////////////////////private:
//////////////////////////////	Node* head;	//单链表头结点指针
//////////////////////////////	Node* tail; //单链表尾结点指针
//////////////////////////////};