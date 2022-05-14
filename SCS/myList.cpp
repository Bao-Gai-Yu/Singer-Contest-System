#include"myList.h"
#include<iostream>
#include<cmath>
using namespace std;
template <typename T>
myList<T>::myList()
{
	listHead = NULL;
	listEnd = NULL;
	size = 0;
}

template <typename T>
myList<T>::~myList()
{
	while (size--)
		deleteNode(1);
}

template <typename T>
int myList<T>::getSize()//返回链表中元素个数
{
	return size;
}

template <typename T>
void myList<T>::addNode(T& newNode)//在链表的末尾添加新的元素
{
	if (size == 0)
	{
		listHead = &newNode;	//如果size为0，表示链表中尚未存在元素故此时链表中加
		listEnd = &newNode;		//入了第一个元素，表头和表尾均指向该元素。
		newNode.prev = NULL;	//虽然本题中的链表元素singer类对象中的prev和next初
		newNode.next = NULL;	//值都为NULL，但保险起见还是对其进行赋值NULL
	}
	else
	{
		newNode.prev = listEnd;	//新元素的前项指向链表尾
		newNode.next = NULL;	//新元素的后项设置为NULL
		listEnd->next = &newNode;//链表末尾元素的后项指向新元素，完成连接
		listEnd = &newNode;		//更新链表尾指向为新加入的元素
	}
	size += 1;					//最后不要忘记链表元素数量+1
	return;
}

template <typename T>
void myList<T>::printList()//遍历链表并输出
{
	T* p = listHead;
	if (p == NULL)//p为NULL，则表示链表中尚未添加任何元素
	{
		cout << "暂无数据，无法查看！" << endl;
	}
	else
	{
		int tmp = 1;
		while (p != NULL)
		{
			cout << "###########################################################" << endl;
			cout << "->" << tmp << "  " << endl;
			p->display();		//调用display()函数进行输出
			cout << endl;
			p = p->next;
			tmp += 1;
		}
	}
	return;
}

template <typename T>
void myList<T>::swapNodes(int index1,int index2)
{
	if (index1 > size || index1<1 || index2 > size || index2<1)
	{
		cout << "索引出错！" << endl;
		return;
	}
	if (index1 > index2)//保证在查找交换位置后在链表的位置中p1在p2前面
	{
		int t = index2;
		index2 = index1;
		index1 = t;
	}
	T* p1 = listHead;
	T* p2 = listHead;
	while (index1 != 1)//寻找要交换的两个元素
	{
		p1 = p1->next;
		index1 -= 1;
	}
	while (index2 != 1)//p1和p2指向两个要交换的元素
	{
		p2 = p2->next;
		index2 -= 1;
	}
	if (p1 == listHead)	//如果p1指向链表头，则p2将成为新的链表头
		listHead = p2;
	else if (p2 == listHead)//如果p2指向链表头，则p1将成为新的链表头
		listHead = p1;
	if (p1 == listEnd)	//如果p1指向链表尾，则p2将成为新的链表尾
		listEnd = p2;
	else if (p2 == listEnd)//如果p2指向链表尾，则p1将成为新的链表尾
		listEnd = p1;
	T* p1Prev = p1->prev;//预存p1的前后结点信息
	T* p1Next = p1->next;
	T* p2Prev = p2->prev;//预存p2的前后结点信息
	T* p2Next = p2->next;
	if (p1==p2Prev)		//特殊处理要交换两个相邻元素的情况
	{
		p1->prev = p2;
		p1->next = p2Next;
		if (p1Prev != NULL)
			p1Prev->next = p2;
		p2->prev = p1Prev;
		p2->next = p1;
		if (p2Next != NULL)
			p2Next->prev = p1;
	}
	else
	{
		p1->prev = p2Prev;//更新p1的前后结点信息为p2的前后结点信息
		p1->next = p2Next;
		p2->prev = p1Prev;//更新p2的前后结点信息为原先p1的前后结点信息
		p2->next = p1Next;
		if (p1Prev != NULL)
			p1Prev->next = p2;
		if (p1Next != NULL)
			p1Next->prev = p2;
		if (p2Prev != NULL)
			p2Prev->next = p1;
		if (p2Next != NULL)
			p2Next->prev = p1;
	}
	return;
}

template <typename T>
void myList<T>::deleteNode(int index)//删除结点
{
	if (size == 0)
	{
		cout << "数据已全部删除，暂无数据可删除。" << endl;
		return;
	}
	else
	{
		T* p = listHead;
		while (index != 1)
		{
			p = p->next;
			index -= 1;
		}
		if (p == listHead)
			listHead = p->next;
		else if (p == listEnd)
			listEnd = p->prev;
		T* pPrev = p->prev;
		T* pNext = p->next;
		if (pPrev != NULL)
			pPrev->next = pNext;
		if (pNext != NULL)
			pNext->prev = pPrev;
		delete p;
		size -= 1;
	}
}

template <typename T>
T* myList<T>::getNode(int index)//获得指向一个结点的指针
{
	T* p = listHead;
	while (index != 1)
	{
		p = p->next;
		index -= 1;
	}
	return p;
}