/*
 * TimeUtils.h
 *
 *  Created on: 2015-7-21
 *      Author: long
 */

#ifndef TIMEUTILS_H_
#define TIMEUTILS_H_
#include "common.h"
#include <time.h>
#include <sys/time.h>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

/*
 * Time Test Class
 * 1，内部有很多成员，因为整个系统的时间需要用两个结构体（tm,timeval）来表示，其它成员基本都是由这两个结构体演变出来的；
 * 2，在类中，所有的数组成员都有着对应关系，如
 * 		在用的过程中，保证t1_start_handle_count与t2_end_handle_count，其实只需setT1StartTime，setT2EndTime在一次调用中成对出现就可；
 * 		time_subtract[t] = t2_end_handle_tv[t]-t1_start_handle_tv[t]；
 * 		t1_start_handle_string[t]是由t1_start_handle_tm[t]与t1_start_handle_tm[t]转换来的，这个数组需要发送至HookerManager；
 * 		t2_end_handle_string[t]是由t2_end_handle_tm[t]与t2_end_handle_tv[t]转换来的，这个数组需要发送至HookerManager；
 * 		time_subtract_string[t]是由time_subtract[t]转换来的，这个数组需要发送至HookerManager；
 */

class TimeUtils {
private:
	string tempString;
	stringstream ss;
	ofstream file;
	static TimeUtils* timeUtilsInstance;  // 单例

	TimeUtils();
	static bool setNowTm(int count, tm* time);
	static bool setNowTV(int count, timeval* timeval);
	//将tm，timaval类型的时间信息转化为string并返回
	string timeToString(struct tm* tmTemp,struct timeval timevalTemp);


public:

	//用于控制存储位置
	int t1_start_handle_count = 0;
	int t2_end_handle_count = 0;

	//存储t1当前时间，精确到到毫秒（年，月，日，小时，分钟，秒，毫秒）
	struct tm* t1_start_handle_tm[ARY_NUMBER];
	//存储t1当前时间，精确到微秒(秒，毫秒，微秒)，与tm达到精确时间
	struct timeval t1_start_handle_tv[ARY_NUMBER];
	//t1对应的string,格式为   年-月-日 小时：分钟：秒：毫秒：微秒
	string t1_start_handle_string[ARY_NUMBER];

	//存储t2当前时间，精确到到毫秒（年，月，日，小时，分钟，秒，毫秒）
	struct tm* t2_end_handle_tm[ARY_NUMBER];
	//存储t2当前时间，精确到微秒(秒，毫秒，微秒)，与tm达到精确时间
	struct timeval t2_end_handle_tv[ARY_NUMBER];
	//t2对应的string，格式为   年-月-日 小时：分钟：秒：毫秒：微秒
	string t2_end_handle_string[ARY_NUMBER];

	//存储时间间隔
	struct timeval time_subtract[ARY_NUMBER];
	//存储时间间隔string格式
	string time_subtract_string[ARY_NUMBER];
	//存储平均时间间隔
	struct timeval avg_time_subtract;
	string avg_time_subtract_string;


	static TimeUtils* getInstance();
	// 获取当前时间，并将时间存储到t1_start_handle_tm,t1_start_handle_tv数组
	bool setT1StartTime();
	// 获取当前时间，并将时间存储到t2_end_handle_tm,t2_end_handle_tv数组
	bool setT2EndTime();

	//用于将时间差转换为string
	//将timeval转换成string
	string timevalToString(struct timeval* temp);

	//计算获得时间间隔
	int timevalSubtract(struct timeval* result, struct timeval* stop, struct timeval* start);
	//计算时间间隔平均值
	int timevalAvgSubtract(struct timeval* result, struct timeval* stop, struct timeval* start);
	//将数组内容写入文件

	bool writeToFile();
	~TimeUtils();
};

#endif /* TIMEUTILS_H_ */
