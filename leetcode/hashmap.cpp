///***************************HashMap****************************/
//1.用数组形式建立哈希表
//2.使用链式方法解决冲突
//3.平方取中法通过字符串Hash函数求hash值（还有很多种其他的hash函数）
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef unsigned long(*GetKeyValue)(const string& );

//该类用来处理冲突的节点
template<class TypeA,class TypeB>
struct HashNode{
	TypeA key;
	TypeB value;
	HashNode *next;
	HashNode(TypeA key,TypeB value){
		HashNode::key = key;
		HashNode::value = value;
		next = NULL;
	}
	HashNode& operator=(const HashNode& node){
		key = node.key;
		value = node.key;
		next = node.next;
		return *this;
	}
};


//该类是HashMap用来存放hash表
template<class TypeA,class TypeB,class FuncType>
class HashMap{
	HashNode<TypeA,TypeB> **table;
	unsigned long capacity;
	FuncType GetKeyValue;
	const TypeB TYPEB_NULL;
public:
	HashMap(FuncType func,const TypeB& _null);
	~HashMap();
	TypeB Put(const HashNode<TypeA,TypeB>& hashNode);  //插入一个HashNode 返回该节点的value值
	TypeB GetValue(const TypeA& key);  // 查找某个hashNode 其key为“key“的元素
	TypeB Delete(const TypeA& key);  // 查找某个hashNode 其key为“key“的元素
};


template<class TypeA,class TypeB,class FuncType> //在调用的时候指定函数
HashMap<TypeA,TypeB,FuncType>::HashMap(FuncType func,const TypeB& _null) : TYPEB_NULL(_null){
	capacity = 10000000;
	GetKeyValue = func;
	table = new HashNode<TypeA,TypeB>*[capacity];
	for(unsigned i = 0;i < capacity;i++)
		table[i] = NULL;
}


template<class TypeA,class TypeB,class FuncType>
HashMap<TypeA,TypeB,FuncType>::~HashMap(){
	for(unsigned i = 0;i < capacity;i++){
		HashNode<TypeA,TypeB> *currentNode = table[i];
		while(currentNode){
			HashNode<TypeA,TypeB> *temp = currentNode;
			currentNode = currentNode->next;
			delete temp;
		}
	}
	delete table;
}


//新增节点操作，用鏈式法解決衝突
template<class TypeA,class TypeB,class FuncType>
TypeB HashMap<TypeA,TypeB,FuncType>::Put(const HashNode<TypeA,TypeB>& hashNode){
	HashNode<TypeA,TypeB> *newNode = NULL;
	unsigned long index = GetKeyValue(hashNode.key);
	if(table[index] == NULL){
		table[index] = new HashNode<TypeA,TypeB>(hashNode.key,hashNode.value);
		newNode = table[index];
	}
	else{
		newNode = table[index];
		while(newNode->next){
			newNode = newNode->next;
		}
		newNode->next = new HashNode<TypeA,TypeB>(hashNode.key,hashNode.value);
		newNode = newNode->next;
	}
	return newNode->value;
}


//由键值获得value
template<class TypeA,class TypeB,class FuncType>
TypeB HashMap<TypeA,TypeB,FuncType>::GetValue(const TypeA& key){
	unsigned long index = GetKeyValue(key);
	if(table[index] == NULL)
		return TYPEB_NULL;
	else{
		HashNode<TypeA,TypeB> *currentNode = table[index];
		while(currentNode){
			if(currentNode->key == key)
				return currentNode->value;
			currentNode = currentNode->next;
		}
	}
	return TYPEB_NULL;
}


//由键值查找后，删除该节点，返回该删除的节点的value
template<class TypeA,class TypeB,class FuncType>
TypeB HashMap<TypeA,TypeB,FuncType>::Delete(const TypeA& key){
	TypeB deletedNodeValue = TYPEB_NULL;
	unsigned long index = GetKeyValue(key);
	if(table[index] == NULL)
		return deletedNodeValue;
	else{
		HashNode<TypeA,TypeB> *currentNode = table[index];
		if(currentNode->key == key){
			table[index] = currentNode->next;
			deletedNodeValue = currentNode->value;
			delete currentNode;
			return deletedNodeValue;
		}
		while(currentNode){
			if(currentNode->next->key == key){
				HashNode<TypeA,TypeB> *temp = currentNode->next;
				currentNode->next = currentNode->next->next;
				deletedNodeValue = temp->value;
				delete temp;
				return deletedNodeValue;;
			}
			currentNode = currentNode->next;
		}
	}
	return deletedNodeValue;
}



/***************************************测试****************************/
//平方取中法
//实现，取字符串中间3个字母，不足3个用0补足
unsigned long GetKeyValue_1(const string& key){
	unsigned long keyValue = 0;
	int strSize = key.size();
	string tempStr(key);
	for(int i = strSize;i < 3;i++)
		tempStr = "0" + tempStr;
	//如果大于3就取中间3位
	if(strSize >= 3){
		tempStr[0] = key[strSize / 2 - 1];
		tempStr[1] = key[strSize / 2];
		tempStr[2] = key[strSize / 2 + 1];
	}
	tempStr = tempStr.substr(0,3);
	unsigned long num = 10000 * (unsigned long)(48);
	num += 100 * (unsigned long)(tempStr[1]);
	num += (unsigned long)(tempStr[2]);
	num *= num;
	char *numStr = new char[15];
	numStr = itoa(num,numStr,10) ;
	int strLen = strlen(numStr);
	tempStr = "000000";
	for(int i = -2;i < 4;i++)
		tempStr[2 + i] = numStr[strLen / 2 + i];
	keyValue = atoi(tempStr.c_str());

	delete []numStr;
	return keyValue;
}

int main(){
    clock_t start = clock();
    //传入一个求哈希散列值的方法GetKeyValue_1
    HashMap<string,string,GetKeyValue> hashMap(GetKeyValue_1,"NULL");
    for(int i = 0;i < 100000;i++){
        char *ckey = new char[20];
        char *cvalue = new char[20];
        ckey = itoa(i,ckey,10);
        cvalue = itoa(i,cvalue,10);
        string key(ckey);
        string value(cvalue);
        if(i == 67){
            key = "67";
            value = "hello hash No.67";
        }
        HashNode<string,string> node1(key,value);
        //插入该节点
        hashMap.Put(node1);
//        cout << "index: " <<GetKeyValue_1(key) << " nodeValue: "
//             << hashMap.Put(node1) << endl;

    }
    clock_t end = clock();
    cout << "Test Result: \n";
    //调用了time.h文件的CLOCKS_PER_SEC，表示每过千分之一秒，clock()函数返回值加1
    cout << "插入100000条数据耗时： "
         << double(end - start) / CLOCKS_PER_SEC << " 秒" << endl;
    cout << "hashMap.GetValue(\"67\"): " << hashMap.GetValue("67") << endl;
    cout << "hashMap.Delete(\"67\"): " << hashMap.Delete("67") << endl;
    cout << "hashMap.GetValue(\"67\"): " << hashMap.GetValue("67") << endl;
    return 0;
}
