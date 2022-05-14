#pragma once
template <typename T>
class myList {
public:
	myList();
	~myList();
	int getSize();//返回链表中元素个数
	void addNode(T&);//在链表末尾添加元素
	void printList();//遍历链表并输出。
	void swapNodes(int ,int);//交换链表中两个元素位置
	void deleteNode(int);//链表中删除元素
	T* getNode(int);//获得一个元素

private:
	T* listHead;//链表头，其若不为NULL，则指向链表的第一个元素
	T* listEnd;//链表尾
	int size;//链表大小
};