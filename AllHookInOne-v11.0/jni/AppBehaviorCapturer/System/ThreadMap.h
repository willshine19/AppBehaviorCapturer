/*
 * ThreadMap.h
 *
 *  Created on: 2015-10-26
 *      Author: zds
 */

#ifndef THREADMAP_H_
#define THREADMAP_H_

using namespace std;
#include <pthread.h>
#include <stdio.h>
#include "common.h"
#include <unordered_map>

class ThreadMap {
private:
	//使用单例模式，构造方法私有，声明一个private static变量，由getInstance方法访问
	static ThreadMap* mThreadMap;
	ThreadMap();
	virtual ~ThreadMap();

public:
	//成员变量
	unordered_map<long, long> mMap; //hashmap变量声明
	unordered_map<long, long> mpid_father_son_Map; //hashmap变量声明
	unordered_map<long, long> mpid_javason_father_Map; //hashmap变量声明
	unordered_map<long, char*> mpid_contextMap;
	static pthread_mutex_t lock;

	//单例模式实例访问接口
	static ThreadMap* getInstance();
	//成员函数

};

#endif /* THREADMAP_H_ */
