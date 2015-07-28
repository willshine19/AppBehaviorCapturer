/*
 * TimeUtils.cpp
 *
 *  Created on: 2015-7-21
 *      Author: long
 */

#include "TimeUtils.h"

TimeUtils::TimeUtils() {

}

TimeUtils::~TimeUtils() {

}

//静态成员变量初始化
TimeUtils* TimeUtils::timeUtilsInstance = NULL;
//获取实例方法
TimeUtils* TimeUtils::getInstance() {
	if (timeUtilsInstance == NULL) {
		timeUtilsInstance = new TimeUtils();
	}
	return timeUtilsInstance;
}
bool TimeUtils::setT1StartTime() {
	//获取系统当前时间
	long timeNow = time(NULL);
	//将当前时间结构体存入数组
	t1_start_handle_tm[t1_start_handle_count] = localtime(&timeNow);
	// 获取毫秒和微秒
	gettimeofday(&t1_start_handle_tv[t1_start_handle_count], NULL);
	string timeString = timeToString(t1_start_handle_tm[t1_start_handle_count],
			t1_start_handle_tv[t1_start_handle_count]);
	t1_start_handle_string[t1_start_handle_count] = timeString;
	LOGD(
			"t1_start_handle_string is %s", t1_start_handle_string[t1_start_handle_count].c_str());
	++t1_start_handle_count;
	if (t1_start_handle_count > 1000)
		t1_start_handle_count = 0;
	return true;
}
bool TimeUtils::setT2EndTime() {
	//获取系统当前时间
	long timeNow = time(NULL);
	//将当前时间结构体存入数组
	t2_end_handle_tm[t2_end_handle_count] = localtime(&timeNow);
	// 获取毫秒和微秒
	gettimeofday(&t2_end_handle_tv[t2_end_handle_count], NULL);
	string timeString = timeToString(t2_end_handle_tm[t2_end_handle_count],
			t2_end_handle_tv[t2_end_handle_count]);
	t2_end_handle_string[t2_end_handle_count] = timeString;
	LOGD(
			"t2_end_handle_string is %s", t2_end_handle_string[t2_end_handle_count].c_str());

	++t2_end_handle_count;
	if (t2_end_handle_count > 1000)
		t2_end_handle_count = 0;
	return true;
}

string TimeUtils::timeToString(struct tm* tmTemp, struct timeval timevalTemp) {
	ss << tmTemp->tm_year + 1900 << "-" << tmTemp->tm_mon + 1 << "-"
			<< tmTemp->tm_mday << " " << tmTemp->tm_hour << ":"
			<< tmTemp->tm_min << ":" << tmTemp->tm_sec << ":"
			<< timevalTemp.tv_usec / 1000 << ":" << timevalTemp.tv_usec % 1000;
	tempString = ss.str();
	//将ss清空
	ss.str("");
//	ss.clear();
	return tempString;
}

string TimeUtils::timevalToString(struct timeval* temp) {
	ss << temp->tv_sec << ":" << temp->tv_usec / 1000 << ":"
			<< temp->tv_usec % 1000;
	tempString = ss.str();
	ss.str("");
	//stringstream的clear方法无法清除缓存，而是使用ss.str("");
//	ss.clear();
	return tempString;
}

//计算时间间隔，并将结果存储到对应数组（结果只显示秒，毫秒，微秒）
int TimeUtils::timevalSubtract(struct timeval* result, struct timeval* stop,
		struct timeval* start) {
	int nsec;

	if (start->tv_sec > stop->tv_sec)
		return -1;

	if ((start->tv_sec == stop->tv_sec) && (start->tv_usec > stop->tv_usec))
		return -1;

	result->tv_sec = (stop->tv_sec - start->tv_sec);
	result->tv_usec = (stop->tv_usec - start->tv_usec);

	if (result->tv_usec < 0) {
		result->tv_sec--;
		result->tv_usec += 1000000;
	}
	return 0;
}

//此方法支持秒，毫秒，微妙级的加法
int TimeUtils::timevalAvgSubtract(struct timeval* result, struct timeval* stop,
		struct timeval* start) {
	return 0;
}
//暂时不需要写入文件
bool TimeUtils::writeToFile() {

	file.open("time-test.txt", ios::app); //ios::app是尾部追加的意思
	if (file.is_open()) {
		file << "写入内容" << endl;
	}
	file.close();
	return true;
}

