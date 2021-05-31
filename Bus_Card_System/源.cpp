/* Copyright Zihao Ma, Xidian University, zihao626@gmail.com*/
#include<iostream>
#include<stdio.h>
#include<mysql.h>
#include<time.h>
#include<string>
#include<vector>
using namespace std;
class Student {
	//在数据库中的存储：
	//stu_card(status INT, name CHAR(20), number CHAR(20), gender CHAR(10), times INT, remain INT, subordinate CHAR(20), date CHAR(20)) 8个字段
private:
	int status;		//1:在用 0:挂失 -1:注销
	string name;
	string number;
	string gender;
	int times;			//乘车次数

	int remain;			//余额
	string subordinate;	//所属单位
	string date;		//有效期
public:
	Student(int, string, string, string, int, int, string, string);
	void show_info(void);
	void top_up(void);
	void get_on(char[]);
	void get_off(char[]);
	void log_out(void);
	void report_loss(void);
	void unlock_report_loss(void);
	~Student();

};
Student::Student(int status, string name, string number, string gender, int times, int remain, string subordinate, string date) {
	this->status = status;
	this->name = name;
	this->number = number;
	this->gender = gender;

	this->times = times;
	this->date = date;
	this->subordinate = subordinate;
	this->remain = remain;
}
Student::~Student() {
	MYSQL mysql;
	if (mysql_init(&mysql) == NULL) {
		cout << "数据库初始化失败" << endl;
	}
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
		cout << "连接失败" << endl;
	}
	char query_delete[255];
	char query_insert[255];
	char name[30], number[30], gender[10], subordinate[30], date[20];
	int i;
	for (i = 0; i < this->name.length(); i++)
		name[i] = this->name[i];
	name[i] = '\0';
	for (i = 0; i < this->number.length(); i++)
		number[i] = this->number[i];
	number[i] = '\0';
	for (i = 0; i < this->gender.length(); i++)
		gender[i] = this->gender[i];
	gender[i] = '\0';
	for (i = 0; i < this->subordinate.length(); i++)
		subordinate[i] = this->subordinate[i];
	subordinate[i] = '\0';
	for (i = 0; i < this->date.length(); i++)
		date[i] = this->date[i];
	date[i] = '\0';

	sprintf_s(query_delete, "delete from stu_card where number='%s'", number);
	if (mysql_query(&mysql, query_delete)) {
		cout << "删除记录失败" << endl;
		printf("%s\n", mysql_error(&mysql));
	}
	else {
		sprintf_s(query_insert, "insert into stu_card values(%d,'%s','%s','%s',%d,%d,'%s','%s')", this->status, name, number, gender, this->times, this->remain, subordinate, date);
		if (mysql_query(&mysql, query_insert)) {
			cout << "更新数据库失败" << endl;
			printf("%s", mysql_error(&mysql));
		}
		else {
			cout << "已更新数据库" << endl;
		}
	}
	mysql_close(&mysql);
}
//Teacher
class Teacher {
//在数据库中的存储：
//tea_card(status INT, name CHAR(20), number CHAR(20), gender CHAR(10), times INT, subordinate CHAR(20), date CHAR(20)) 7个字段
private:
	int status;
	string name;
	string number;
	string gender;
	int times;

	string subordinate;	//所属单位
	string date;
public:
	Teacher(int, string, string, string, int, string, string);
	void show_info(void);
	void get_on(char[]);
	void get_off(char[]);
	void log_out(void);
	void report_loss(void);
	void unlock_report_loss(void);
	~Teacher();
};
Teacher::Teacher(int status, string name, string number, string gender, int times, string subordinate, string date) {
	this->status = status;
	this->name = name;
	this->number = number;
	this->gender = gender;
	this->times = times;
	this->subordinate = subordinate;
	this->date = date;
}
Teacher::~Teacher() {
	//printf("析构Teacher\n");
	MYSQL mysql;
	if (mysql_init(&mysql) == NULL) {
		cout << "数据库初始化失败" << endl;
	}
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
		cout << "连接失败" << endl;
	}
	char query_delete[255];
	char query_insert[255];
	char name[30], number[30], gender[10], subordinate[30], date[20];
	int i;
	for (i = 0; i < this->name.length(); i++)
		name[i] = this->name[i];
	name[i] = '\0';
	for (i = 0; i < this->number.length(); i++)
		number[i] = this->number[i];
	number[i] = '\0';
	for (i = 0; i < this->gender.length(); i++)
		gender[i] = this->gender[i];
	gender[i] = '\0';
	for (i = 0; i < this->subordinate.length(); i++)
		subordinate[i] = this->subordinate[i];
	subordinate[i] = '\0';
	for (i = 0; i < this->date.length(); i++)
		date[i] = this->date[i];
	date[i] = '\0';

	sprintf_s(query_delete, "delete from tea_card where number='%s'", number);
	if (mysql_query(&mysql, query_delete)) {
		cout << "删除记录失败" << endl;
		printf("%s\n", mysql_error(&mysql));
	}
	else {
		sprintf_s(query_insert, "insert into tea_card values(%d,'%s','%s','%s',%d,'%s','%s')", this->status, name, number, gender, this->times, subordinate, date);
		if (mysql_query(&mysql, query_insert)) {
			cout << "更新数据库失败" << endl;
			printf("%s", mysql_error(&mysql));
		}
		else {
			cout << "已更新数据库" << endl;
		}
	}
	mysql_close(&mysql);
}

//Limit
class Limit {
//在数据库中的存储：
//lim_card(status INT, name CHAR(20), number CHAR(20), gender CHAR(10), times INT, remain INT, freetimes INT, subordinate CHAR(20), date CHAR(20)) 9个字段
private:
	int status;
	string name;
	string number;
	string gender;
	int times;

	string subordinate;
	string date;
	int free_times;
	int remain;
public:
	Limit(int,string, string, string, int, int, int, string, string);
	void show_info(void);
	void get_on(char[]);
	void log_out(void);
	void report_loss(void);
	void unlock_report_loss(void);
	~Limit();
};
Limit::Limit(int status,string name, string number, string gender, int times, int remain, int free_times, string subordinate, string date) {
	this->status = status;
	this->name = name;
	this->number = number;
	this->gender = gender;
	this->times = times;
	this->free_times = free_times;
	this->remain = remain;
	this->subordinate = subordinate;
	this->date = date;

}
Limit::~Limit() {
	//printf("析构Limit\n");
	MYSQL mysql;
	if (mysql_init(&mysql) == NULL) {
		cout << "数据库初始化失败" << endl;
	}
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
		cout << "连接失败" << endl;
	}
	char query_delete[255];
	char query_insert[255];
	char name[30], number[30], gender[10], subordinate[30], date[20];
	int i;
	for (i = 0; i < this->name.length(); i++)
		name[i] = this->name[i];
	name[i] = '\0';
	for (i = 0; i < this->number.length(); i++)
		number[i] = this->number[i];
	number[i] = '\0';
	for (i = 0; i < this->gender.length(); i++)
		gender[i] = this->gender[i];
	gender[i] = '\0';
	for (i = 0; i < this->subordinate.length(); i++)
		subordinate[i] = this->subordinate[i];
	subordinate[i] = '\0';
	for (i = 0; i < this->date.length(); i++)
		date[i] = this->date[i];
	date[i] = '\0';

	sprintf_s(query_delete, "delete from lim_card where number='%s'", number);
	if (mysql_query(&mysql, query_delete)) {
		cout << "删除记录失败" << endl;
		printf("%s\n", mysql_error(&mysql));
	}
	else {
		sprintf_s(query_insert, "insert into lim_card values(%d,'%s','%s','%s',%d,%d,%d,'%s','%s')", this->status, name, number, gender, this->times, this->remain, this->free_times,subordinate, date);
		if (mysql_query(&mysql, query_insert)) {
			cout << "更新数据库失败" << endl;
			printf("%s", mysql_error(&mysql));
		}
		else {
			cout << "已更新数据库" << endl;
		}
	}
	mysql_close(&mysql);
}

//Bus
class Bus {
//在数据库中的存储：
//bus_table(number CHAR(20), type CHAR(20), driver CHAR(20), max_num INT, cur_num INT, start_time INT)
private:
	string number;	//车牌号
	string type;	//车类型
	string driver;	//司机名字
	int max_num;	//最大乘客数
	int cur_num;	//现有车上的乘客数
	int start_time;	//发车时间
public:
	Bus(string, string, string, int, int, int);
	~Bus();
	void show_bus(void);
	int get_cur_num(void);
	bool check_bus(void);
	void add_people(string,string);
	void delete_people(string,string);
	void bus_detail(void);
	void clear_bus(void);
};
Bus::Bus(string number, string type, string driver, int max_num, int cur_num, int start_time) {
	this->cur_num = cur_num;
	this->driver = driver;
	this->max_num = max_num;
	this->number = number;
	this->type = type;
	this->start_time = start_time;
}
Bus::~Bus() {

}

//System
class System {
public:
	static void start(void);
	static void moni(void);

	//card
	static Student get_student(char[]);
	static Teacher get_teacher(char[]);
	static Limit get_limit(char[]);

	static void create_card(void);
	static void create_student(void);
	static void create_teacher(void);
	static void create_limit(void);

	static void top_up(void);
	static void top_up_student(void);
	static void top_up_teacher(void);
	static void top_up_limit(void);

	static void show_card(void);
	static void show_student_card(void);
	static void show_teacher_card(void);
	static void show_limit_card(void);

	static void get_on(void);
	static void get_on_student(char[],char[]);
	static void get_on_teacher(char[],char[]);
	static void get_on_limit(char[],char[]);

	static void operate_card(void);

	static void log_out(void);
	static void log_out_student(void);
	static void log_out_teacher(void);
	static void log_out_limit(void);

	static void report_loss(void);
	static void report_loss_student(void);
	static void report_loss_teacher(void);
	static void report_loss_limit(void);

	static void unlock_report_loss(void);
	static void unlock_student(void);
	static void unlock_teacher(void);
	static void unlock_limit(void);

	//bus
	static Bus get_bus(char[]);
	static void add_bus(void);

};
int main() {
	cout << endl;
	cout << "\t\t\t\t\t请选择1-2:" << endl;
	cout << "\t\t\t\t\t[1] 整体模拟" << endl;
	cout << "\t\t\t\t\t[2] 具体到某一张一卡通的操作" << endl;
	int choice;
	cin >> choice;
	if (choice == 1) {
		System::moni();
	}
	else if (choice == 2) {
		System::start();
	}
	
	
	return 0;
}
//Student
void Student::show_info(void) {
	cout << "\t\t|=======================================|" << endl;
	cout << "\t\t|一卡通状态：\t" << this->status << "\t\t\t|" << endl;
	cout << "\t\t| 姓名：\t" << this->name << "\t\t\t|" << endl;
	cout << "\t\t| 一卡通号：\t" << this->number << "\t\t|" << endl;
	cout << "\t\t| 余额：\t" << this->remain << "\t\t\t|" << endl;
	cout << "\t\t| 乘车次数：\t" << this->times << "\t\t\t|" << endl;
	cout << "\t\t|=======================================|" << endl;
}
void Student::top_up(void) {
	int add;
	cout << "\t\t|===========请输入充值的金额==============|" << endl;
	cin >> add;
	this->remain += add;

	this->show_info();
}
void Student::get_on(char number_bus[]) {
	//修改remain times
	Bus b = System::get_bus(number_bus);
	if (b.check_bus()) {
		cout << "刷卡中..." << endl;
		if (this->status == 1) {
			if (this->remain >= 2) {
				this->remain -= 2;
				cout << "扣费成功!" << endl;
				if (this->remain <= 5) {
					cout << "【提示】: 余额过低，请及时充值！" << endl;
				}
				this->times += 1;
				b.add_people("stu_card", this->number);
			}
			else if (this->remain < 2) {
				cout << "余额不足 2 元！请充值！" << endl;
				cout << "不能乘车" << endl;
			}
		}
		else if (this->status == 0) {
			cout << "挂失中，禁止使用该一卡通" << endl;
		}
		else if (this->status == -1) {
			cout << "该一卡通已被注销" << endl;
		}
	}

}
void Student::get_off(char number_bus[]) {
	Bus b = System::get_bus(number_bus);
	b.delete_people("stu_card",this->number);
}
void Student::log_out(void) {
	this->status = -1;
}
void Student::report_loss(void) {
	this->status = 0;
}
void Student::unlock_report_loss(void) {
	this->status = 1;
}

//Teacher
void Teacher::show_info(void) {
	cout << "\t\t|=======================================|" << endl;
	cout << "\t\t|一卡通状态：\t" << this->status << "\t\t|" << endl;
	cout << "\t\t| 姓名：\t" << this->name << "\t\t\t|" << endl;
	cout << "\t\t| 一卡通号：\t" << this->number << "\t\t|" << endl;
	cout << "\t\t| 乘车次数：\t" << this->times << "\t\t\t|" << endl;
	cout << "\t\t|=======================================|" << endl;
}
void Teacher::get_on(char number_bus[]) {
	Bus b = System::get_bus(number_bus);
	if (this->status == 1) {
		cout << "教师卡，免费乘车！" << endl;
		this->times += 1;
		b.add_people("tea_card", this->number);
	}
	else if (this->status == 0) {
		cout << "该一卡通挂失中，禁止使用！" << endl;
	}
	else if (this->status == -1) {
		cout << "该一卡通已注销！！" << endl;
	}
}
void Teacher::log_out(void) {
	this->status = -1;
}
void Teacher::report_loss(void) {
	this->status = 0;
}
void Teacher::unlock_report_loss(void) {
	this->status = 1;
}

//Limit
void Limit::show_info(void) {
	cout << "\t\t|=======================================|" << endl;
	cout << "\t\t|一卡通状态：\t" << this->status << "\t\t|" << endl;
	cout << "\t\t| 姓名：\t" << this->name << "\t\t\t|" << endl;
	cout << "\t\t| 一卡通号：\t" << this->number << "\t\t|" << endl;
	cout << "\t\t| 余额：\t" << this->remain << "\t\t\t|" << endl;
	cout << "\t\t| 乘车次数：\t" << this->times << "\t\t\t|" << endl;
	cout << "\t\t| 剩余免费乘车次数：" << this->free_times << "\t|" << endl;
	cout << "\t\t|=======================================|" << endl;

}
void Limit::get_on(char number_bus[]) {
	Bus b = System::get_bus(number_bus);
	if (this->status == 1) {
		cout << "一卡通正常" << endl;
		if (this->free_times <= 0) {
			cout << "【注意】该限制卡本月已无免费乘车次数！" << endl;
			cout << "【注意】将要进行扣费" << endl;
			if (this->remain < 2) {
				cout << "该一卡通余额不足2元，请充值！" << endl;
				cout << "【注意】不能乘车" << endl;
			}
			else if (this->remain >= 2) {
				this->times += 1;
				this->remain -= 2;
				cout << "扣费成功" << endl;
				if (this->remain <= 5) {
					cout << "【注意】余额过低，请及时充值" << endl;
				}
				b.add_people("lim_card", this->number);
			}
		}
		else if (this->free_times > 1) {
			this->times += 1;
			this->free_times -= 1;
			cout << "本次免费乘车" << endl;
			b.add_people("lim_card", this->number);
		}
		else if (this->free_times == 1) {
			this->times += 1;
			this->free_times -= 1;
			cout << "【注意】该限制卡本月最后一次免费乘车次数只剩最后一次" << endl;
			b.add_people("lim_card", this->number);
		}

	}
	else if (this->status == 0) {
		cout << "该一卡通挂失中，禁止使用！" << endl;
	}
	else if (this->status == -1) {
		cout << "该一卡通已注销！" << endl;
	}
}
void Limit::log_out(void) {
	this->status = -1;
}
void Limit::report_loss(void) {
	this->status = 0;
}
void Limit::unlock_report_loss(void) {
	this->status = 1;
}

//System
void System::start(void) {
	cout << "\t\t\t\t\t||=========Bus-Card-System======||" << endl;
	cout << "\t\t\t\t\t||==============================||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         1. 创建一卡通        ||"<< endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         2. 查询一卡通        ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         3. 操作一卡通        ||"<< endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         4. 乘车              ||"<< endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         5. 增加班车          ||"<< endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||==============================||" << endl;
	cout << "\t\t\t\t\t||==============================||" << endl;
	int choice;
	cin >> choice;
	switch (choice) {
	case 1:
		create_card();
		break;
	case 2:
		show_card();
		break;
	case 3:
		operate_card();
		break;
	case 4:
		get_on();
		break;
	case 5:
		add_bus();
		break;
	}
	start();
}
void System::moni(void) {
	cout << "\t模拟两辆校车从同一起点发车，途径一停车点，最后到达目的地\n" << endl;
	    cout << "\t\t【位置】- - -发车点- - -" << endl;
		cout << "\t\t【状态】- - -发车前- - -" << endl;
		srand(time(NULL));//随机数种子
		vector<string> bus_list;
		MYSQL mysql;
		MYSQL_RES *result;
		MYSQL_ROW one_bus;
		mysql_init(&mysql);
		mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
		if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
			printf("数据库连接失败\n");
		}
		char query_all_bus[255];
		sprintf_s(query_all_bus, "select * from bus_table");
		if (mysql_query(&mysql, query_all_bus)) {
			cout << "查询all_bus失败" << endl;
		}
		result = mysql_store_result(&mysql);
		int bus_num = mysql_num_rows(result);
		cout << "\t\t一共" << bus_num << "辆车" << endl;
		while (one_bus = mysql_fetch_row(result)) {
			//cout << one_bus[0] << endl;
			string bus = one_bus[0];
			bus_list.push_back(bus);
		}
		mysql_free_result(result);
		mysql_close(&mysql);
		for (int i = 0; i < bus_list.size(); i++) {
			char number[20];
			//cout << bus_list[i] << endl;
			int j;
			for (j = 0; j < bus_list[i].length(); j++)
				number[j] = bus_list[i][j];
			number[j] = '\0';
			Bus b = get_bus(number);
			b.clear_bus(); //发车前将乘客清空
			b.show_bus();

			vector<string> student_list;
			vector<string> teacher_list;
			vector<string> limit_list;
			MYSQL mysql;
			MYSQL_RES* result;
			MYSQL_ROW one_student;
			mysql_init(&mysql);
			mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
			if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
				printf("数据库连接失败\n");
			}
			char query_all_bus[255];
			sprintf_s(query_all_bus, "select * from stu_card");
			if (mysql_query(&mysql, query_all_bus)) {
				cout << "查询stu_card失败" << endl;
			}
			result = mysql_store_result(&mysql);
			int student_num = mysql_num_rows(result);
			cout << "\t\t一共" << student_num << "个学生可能上车(随机决定是否上车)" << endl;
			while (one_student = mysql_fetch_row(result)) {
				string student = one_student[2];
				student_list.push_back(student);
			}
			mysql_free_result(result);
			mysql_close(&mysql);
			char student_number[20];
			for (int k = 0; k < student_list.size(); k++) {
				int m;
				for (m = 0; m < student_list[k].length(); m++)
					student_number[m] = student_list[k][m];
				student_number[m] = '\0';
				Student s = System::get_student(student_number);
				s.show_info();
				int choice = rand() % 2;
				if (choice == 0) {
					cout << "\t\t---不上车---" << endl;
				}
				else {
					cout << "\t\t---上车---" << endl;
					s.get_on(number);
				}

			}
			cout << "\n\n" << endl;
		}
		cout << endl;
		cout << "\t\t【位置】- - -省  略- - -" << endl;
		cout << "\t\t【状态】- - -行驶中- - -" << endl;
		for (int i = 0; i < bus_list.size(); i++) {
			char number[20];
			//cout << bus_list[i] << endl;
			int j;
			for (j = 0; j < bus_list[i].length(); j++)
				number[j] = bus_list[i][j];
			number[j] = '\0';
			Bus b = get_bus(number);
			b.show_bus();
			cout << "\t\t具体信息:" << endl;
			b.bus_detail();
			cout << endl;
		}
		cout <<"\n\n"<< endl;
		cout << "\t\t【位置】- - -停车点1- - -" << endl;
		cout << "\t\t【状态】- - -发车前- - -" << endl;
		for (int i = 0; i < bus_list.size(); i++) {
			char number[20];
			//cout << bus_list[i] << endl;
			int j;
			for (j = 0; j < bus_list[i].length(); j++)
				number[j] = bus_list[i][j];
			number[j] = '\0';
			Bus b = get_bus(number);
			b.show_bus();

			vector<string> student_list;
			MYSQL mysql;
			MYSQL_RES* result;
			MYSQL_ROW one_student;
			mysql_init(&mysql);
			mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
			if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
				printf("数据库连接失败\n");
			}
			char query_all_bus[255];
			sprintf_s(query_all_bus, "select * from %s",number);
			if (mysql_query(&mysql, query_all_bus)) {
				cout << "查询stu_card失败" << endl;
			}
			result = mysql_store_result(&mysql);
			int student_num = mysql_num_rows(result);
			cout << "\t\t一共" << student_num << "个学生可能下车(随机决定是否下车)" << endl;
			while (one_student = mysql_fetch_row(result)) {
				string student = one_student[1];
				student_list.push_back(student);
			}
			mysql_free_result(result);
			mysql_close(&mysql);
			char student_number[20];
			for (int k = 0; k < student_list.size(); k++) {
				int m;
				for (m = 0; m < student_list[k].length(); m++)
					student_number[m] = student_list[k][m];
				student_number[m] = '\0';
				Student s = System::get_student(student_number);
				s.show_info();
				int choice = rand() % 2;
				if (choice == 0) {
					cout << "\t\t---不下车---" << endl;
				}
				else {
					cout << "\t\t---下车---" << endl;
					s.get_off(number);
				}

			}
			cout <<"\n\n"<< endl;
		}
		cout << endl;
		cout << "\t\t【位置】- - -省  略- - -" << endl;
		cout << "\t\t【状态】- - -行驶中- - -" << endl;
		for (int i = 0; i < bus_list.size(); i++) {
			char number[20];
			//cout << bus_list[i] << endl;
			int j;
			for (j = 0; j < bus_list[i].length(); j++)
				number[j] = bus_list[i][j];
			number[j] = '\0';
			Bus b = get_bus(number);
			b.show_bus();
			cout << "\t\t具体信息:" << endl;
			b.bus_detail();
			cout << endl;
		}
		cout << "\n\n" << endl;
		cout << "\t\t【位置】- - -目的地- - -" << endl;
		cout << "\t\t【状态】- - -停止运行- - -" << endl;
		cout << "\t\t- -清空车厢，所有乘客下车- -" << endl;
		for (int i = 0; i < bus_list.size(); i++) {
			char number[20];
			int j;
			for (j = 0; j < bus_list[i].length(); j++)
				number[j] = bus_list[i][j];
			number[j] = '\0';
			Bus b = get_bus(number);
			b.clear_bus(); //将乘客清空
			b.show_bus();
		}
}
void System::add_bus(void) {
	//bus_table(number CHAR(20), type CHAR(20), driver CHAR(20), max_num INT, cur_num INT, start_time INT)
	//1 每添加一辆车，就会以该车车牌号创建一个数据库表，存储（cardtype cardnumber）
	char number[20], type[20], driver[20];
	int max_num, cur_num, start_time;
	cout << "请输入车牌号" << endl;
	cin >> number;
	cout << "请输入车的类型" << endl;
	cin >> type;
	cout << "请输入司机名字" << endl;
	cin >> driver;
	cout << "请输入最大载客量" << endl;
	cin >> max_num;
	cout << "请输入出发时间" << endl;
	cin >> start_time;
	MYSQL mysql;
	if (mysql_init(&mysql) == NULL) {
		printf("数据库初始化失败\n");
	}
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
		printf("数据库连接失败\n");
	}
	char query[255];
	sprintf_s(query, "insert into bus_table values('%s', '%s', '%s', %d, 0, %d)", number,type,driver,max_num,start_time);
	if (mysql_query(&mysql, query)) {
		cout << "添加失败" << endl;
		printf("%s", mysql_error(&mysql));
	}
	else {
		
		char query_addtable[255];
		sprintf_s(query_addtable, "create table '%s'(cardtype CHAR(20), cardnumber(20))", number);
		if (mysql_query(&mysql, query_addtable)) {
			cout << "添加新表失败" << endl;
			printf("%s\n", mysql_error(&mysql));
		}
		else {
			cout << "已更新数据库" << endl;
		}
	}
	mysql_close(&mysql);
}
Bus System::get_bus(char number[]) {
	//1. 在数据库表bus_table中查找该车牌号，若没有则返回
	//2. 若找到了该车记录，先用数据库中的数据初始化出一个Bus实例
	MYSQL mysql;
	if (mysql_init(&mysql) == NULL) {
		cout << "数据库初始化失败" << endl;
	}
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
		cout << "连接失败" << endl;
	}
	char select_bus[255];
	MYSQL_RES* result;

	sprintf_s(select_bus, "select * from bus_table where number = '%s'", number);
	if (mysql_query(&mysql, select_bus)) {
		printf("select_bus失败\n%s", mysql_error(&mysql));
	}
	result = mysql_store_result(&mysql);
	if (mysql_num_rows(result) == 0) {
		printf("查无此车\n请重新输入或者注册新的车辆\n");
	}

	//1. 用数据库表中的数据初始化一个Bus实例
	MYSQL_ROW res_row;
	res_row = mysql_fetch_row(result);
	int col_num = mysql_num_fields(result);
	string number_bus = res_row[0];
	string type = res_row[1];
	string driver = res_row[2];
	string max_num = res_row[3];
	string cur_num = res_row[4];
	string start_time = res_row[5];
	int max_num_int = stoi(max_num);
	int cur_num_int = stoi(cur_num);
	int start_time_int = stoi(start_time);
	Bus b(number_bus, type, driver, max_num_int, cur_num_int, start_time_int);
	mysql_free_result(result);
	mysql_close(&mysql);
	return b;
}
void System::create_card(void) {
	int choice_card;
	cout << "请选择创建的一卡通的类型：" << endl;
	cout << "1. student_card" << endl;
	cout << "2. teacher_card" << endl;
	cout << "3. limit_card" << endl;
	cin >> choice_card;
	switch (choice_card) {
	case 1:
		System::create_student();
		break;
	case 2:
		System::create_teacher();
		break;
	case 3:
		System::create_limit();
		break;
	}
}
void System::create_student(void) {
	char name[20], gender[10], number[20], subordinate[20], date[20];
	int remain;
	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入性别(f or m)：" << endl;
	cin >> gender;
	cout << "请输入一卡通号：" << endl;
	cin >> number;
	cout << "请输入充值数额(元)：" << endl;
	cin >> remain;
	cout << "请输入所属单位(学院)：" << endl;
	cin >> subordinate;
	cout << "请输入到期年份：" << endl;
	cin >> date;
	int status = 1;
	int times = 0;
	//Student s(status, name, number, gender, times, remain, subordinate, date);
	MYSQL mysql;
	if (mysql_init(&mysql) == NULL) {
		cout << "数据库初始化失败" << endl;
	}
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
		cout << "连接失败" << endl;
	}
	char query[255];
	sprintf_s(query, "insert into stu_card values(1, '%s', '%s', '%s', 0, %d, '%s', '%s')", name, number, gender, remain, subordinate, date);
	if (mysql_query(&mysql, query)) {
		cout << "添加失败" << endl;
		printf("%s", mysql_error(&mysql));
	}
	else {
		cout << "已更新数据库" << endl;
	}
}
void System::create_teacher(void) {
	char name[20], gender[10], number[20], subordinate[20], date[20];
	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入性别(f or m)：" << endl;
	cin >> gender;
	cout << "请输入一卡通号：" << endl;
	cin >> number;
	cout << "请输入所属单位(学院)：" << endl;
	cin >> subordinate;
	cout << "请输入到期年份：" << endl;
	cin >> date;
	int status = 1;
	int times = 0;
	//Teacher t(status, name, number, gender, times, subordinate, date);
	MYSQL mysql;
	if (mysql_init(&mysql) == NULL) {
		cout << "数据库初始化失败" << endl;
	}
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
		cout << "连接失败" << endl;
	}
	char query[255];
	sprintf_s(query, "insert into tea_card values(1, '%s', '%s', '%s', 0, '%s', '%s')", name, number, gender, subordinate, date);
	if (mysql_query(&mysql, query)) {
		cout << "添加失败" << endl;
		printf("%s", mysql_error(&mysql));
	}
	else {
		cout << "已更新数据库" << endl;
	}
}
void System::create_limit(void) {
	//lim_card(status INT, name CHAR(20), number CHAR(20), gender CHAR(10), times INT, remain INT, freetimes INT, subordinate CHAR(20), date CHAR(20)) 9个字段
	char name[20], gender[10], number[20], subordinate[20], date[20];
	int remain;
	int freetimes = 20;
	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入性别(f or m)：" << endl;
	cin >> gender;
	cout << "请输入一卡通号：" << endl;
	cin >> number;
	cout << "请输入充值数额(元)：" << endl;
	cin >> remain;
	cout << "请输入所属单位(学院)：" << endl;
	cin >> subordinate;
	cout << "请输入到期年份：" << endl;
	cin >> date;
	int status = 1;
	int times = 0;
	//Limit l(status, name, number, gender, times, remain, freetimes, subordinate, date);
	MYSQL mysql;
	if (mysql_init(&mysql) == NULL) {
		cout << "数据库初始化失败" << endl;
	}
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
		cout << "连接失败" << endl;
	}
	char query[255];
	sprintf_s(query, "insert into lim_card values(1, '%s', '%s', '%s', 0, %d, 20, '%s', '%s')", name, number, gender, remain, subordinate, date);
	if (mysql_query(&mysql, query)) {
		cout << "添加失败" << endl;
		printf("%s", mysql_error(&mysql));
	}
	else {
		cout << "已更新数据库" << endl;
	}
}
void System::top_up(void) {
	int choice_type;
	cout << "请输入要充值一卡通的种类：" << endl;
	cout << "\t\t\t\t\t||==============================||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         1. student card     ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         2. teacher card     ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         3. limit card       ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         4. 返回              ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||==============================||" << endl;
	cin >> choice_type;
	switch (choice_type) {
	case 1:
		top_up_student();
		break;
	case 2:
		log_out_teacher();
		break;
	case 3:
		log_out_limit();
		break;
	default:
		start();
	}
}
void System::top_up_student(void) {
	cout << "请输入一卡通卡号" << endl;
	char number[20];
	cin >> number;
	Student s = get_student(number);
	s.top_up();
}
void System::show_card(void) {
	cout << "请输入要查询的一卡通种类" << endl;
	cout << "1. student card" << endl;
	cout << "2. teacher card" << endl;
	cout << "3. limit card" << endl;
	int choice;
	cin >> choice;
	switch (choice) {
	case 1:
		show_student_card();
		break;
	case 2:
		show_teacher_card();
		break;
	case 3:
		show_limit_card();
		break;
	default:
		cout << "无该选项" << endl;
	}
}
void System::show_student_card(void) {
	cout << "请输入一卡通卡号" << endl;
	char number[20];
	cin >> number;
	Student s = get_student(number);
	s.show_info();
}
void System::show_teacher_card(void) {
	cout << "请输入一卡通卡号" << endl;
	char number[20];
	cin >> number;
	Teacher t = get_teacher(number);
	t.show_info();
}
void System::show_limit_card(void) {
	cout << "请输入一卡通卡号" << endl;
	char number[20];
	cin >> number;
	Limit l = get_limit(number);
	l.show_info();
}
Student System::get_student(char number[]) {
	//1. 在数据库表stu_card中查找该一卡通号，若没有则返回
	//2. 若找到了该一卡通，先用数据库中的数据初始化出一个Student实例，并对该实例进行：钱-2；次数+1等操作
	MYSQL mysql;
	if (mysql_init(&mysql) == NULL) {
		cout << "数据库初始化失败" << endl;
	}
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
		cout << "连接失败" << endl;
	}
	char select_student[255];
	MYSQL_RES* result;

	sprintf_s(select_student, "select * from stu_card where number = '%s'", number);
	if (mysql_query(&mysql, select_student)) {
		printf("select_student失败\n%s", mysql_error(&mysql));
	}
	result = mysql_store_result(&mysql);
	if (mysql_num_rows(result) == 0) {
		printf("查无此卡\n请重新输入或者注册新的一卡通\n");
	}
	
		//1. 用数据库表中的数据初始化一个Student实例
		//2. 对该实例进行 余额-2 次数+1
		MYSQL_ROW res_row;
		res_row = mysql_fetch_row(result);
		int col_num = mysql_num_fields(result);
		string status = res_row[0];
		int status_int = stoi(status);
		string name = res_row[1];
		string number_s = res_row[2];
		string gender = res_row[3];
		string times = res_row[4];
		int times_int = stoi(times);
		string remain = res_row[5];
		int remain_int = stoi(remain);
		string subordinate = res_row[6];
		string date = res_row[7];
		Student s(status_int, name, number_s, gender, times_int, remain_int, subordinate, date);
	mysql_free_result(result);
	mysql_close(&mysql);
	return s;
	
}
Teacher System::get_teacher(char number[]) {
	//1. 在数据库表tea_card中查找该一卡通号，若没有则返回
	//2. 若找到了该一卡通，先用数据库中的数据初始化出一个Teacher实例，并对该实例进行次数 +1 等操作
	MYSQL mysql;
	if (mysql_init(&mysql) == NULL) {
		cout << "数据库初始化失败" << endl;
	}
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
		cout << "连接失败" << endl;
	}
	char select_teacher[255];
	MYSQL_RES* result;

	sprintf_s(select_teacher, "select * from tea_card where number = '%s'", number);
	if (mysql_query(&mysql, select_teacher)) {
		printf("select_teacher失败\n%s", mysql_error(&mysql));
	}
	result = mysql_store_result(&mysql);
	if (mysql_num_rows(result) == 0) {
		printf("查无此卡\n请重新输入或者注册新的一卡通\n");
	}
	
		//1. 用数据库表中的数据初始化一个Teacher实例
		//2. 对该实例进行 次数+1
		MYSQL_ROW res_row;
		res_row = mysql_fetch_row(result);
		int col_num = mysql_num_fields(result);
		string status = res_row[0];
		int status_int = stoi(status);
		string name = res_row[1];
		string number_t = res_row[2];
		string gender = res_row[3];
		string times = res_row[4];
		int times_int = stoi(times);
		string subordinate = res_row[5];
		string date = res_row[6];
		Teacher t(status_int, name, number_t, gender, times_int, subordinate, date);
	mysql_free_result(result);
	mysql_close(&mysql);
	return t;
}
Limit System::get_limit(char number[]) {
	//1. 在数据库表lim_card中查找该一卡通号，若没有则返回
	//2. 若找到了该一卡通，先用数据库中的数据初始化出一个Limit实例，并对该实例进行：免费次数-1 或者 钱-2；次数+1等操作
	MYSQL mysql;
	if (mysql_init(&mysql) == NULL) {
		cout << "数据库初始化失败" << endl;
	}
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
		cout << "连接失败" << endl;
	}
	char select_limit[255];
	MYSQL_RES* result;

	sprintf_s(select_limit, "select * from lim_card where number = '%s'", number);
	if (mysql_query(&mysql, select_limit)) {
		printf("select_limit失败\n%s", mysql_error(&mysql));
	}
	result = mysql_store_result(&mysql);
	if (mysql_num_rows(result) == 0) {
		printf("查无此卡\n请重新输入或者注册新的一卡通\n");
	}
	
		//1. 用数据库表中的数据初始化一个Student实例
		//2. 对该实例进行 免费次数-1或者余额-2 次数+1
		MYSQL_ROW res_row;
		res_row = mysql_fetch_row(result);
		int col_num = mysql_num_fields(result);
		string status = res_row[0];
		int status_int = stoi(status);
		string name = res_row[1];
		string number_l = res_row[2];
		string gender = res_row[3];
		string times = res_row[4];
		int times_int = stoi(times);
		string remain = res_row[5];
		int remain_int = stoi(remain);
		string freetimes = res_row[6];
		int freetimes_int = stoi(freetimes);
		string subordinate = res_row[7];
		string date = res_row[8];
		Limit l(status_int, name, number_l, gender, times_int, remain_int, freetimes_int, subordinate, date);
		l.show_info();
	mysql_free_result(result);
	mysql_close(&mysql);
	return l;
}
void System::get_on(void) {
	int choice_get_on;
	
	cout << "请选择一卡通类型" << endl;
	cout << "1. student_card" << endl;
	cout << "2. teacher_card" << endl;
	cout << "3. limit_card" << endl;
	cin >> choice_get_on;
	char number[20];
	cout << "请输入一卡通的卡号" << endl;
	char bus_number[20] = "shanA";
	switch (choice_get_on) {
	case 1:
		cin >> number;
		System::get_on_student(number,bus_number);
		break;
	case 2:
		cin >> number;
		System::get_on_teacher(number,bus_number);
		break;
	case 3:
		cin >> number;
		System::get_on_limit(number,bus_number);
		break;
	}
}
void System::get_on_student(char number[],char number_bus[]) {
	Student s = get_student(number);
	s.get_on(number_bus);
}
void System::get_on_teacher(char number[],char number_bus[]) {
	Teacher t = get_teacher(number);
	t.get_on(number_bus);
}
void System::get_on_limit(char number[],char number_bus[]) {
	Limit l = get_limit(number);
	l.get_on(number_bus);
}
void System::operate_card(void) {	
	int choice_operation;

	cout << "\t\t\t\t\t||==============================||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         1. 充值一卡通        ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         2. 挂失一卡通        ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         3. 注销一卡通        ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         4. 解除挂失一卡通    ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         5. 返回              ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||==============================||" << endl;

	cin >> choice_operation;
	switch (choice_operation) {
	case 1:
		top_up();
		break;
	case 2:
		report_loss();
		break;
	case 3:
		log_out();
		break;
	case 4:
		unlock_report_loss();
		break;
	default:
		start();
	}
}
void System::log_out(void) {


	int choice_type;
	cout << "请输入要注销一卡通的种类：" << endl;
	cout << "\t\t\t\t\t||==============================||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         1. student card     ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         2. teacher card     ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         3. limit card       ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         4. 返回              ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||==============================||" << endl;
	cin >> choice_type;
	switch (choice_type) {
	case 1:
		log_out_student();
		break;
	case 2:
		log_out_teacher();
		break;
	case 3:
		log_out_limit();
		break;
	default:
		start();
	}

}
void System::log_out_student(void) {
	char number[20];
	cout << "请输入一卡通卡号" << endl;
	Student s = get_student(number);
	s.log_out();
}
void System::log_out_teacher(void) {
	char number[20];
	cout << "请输入一卡通卡号" << endl;
	Teacher t = get_teacher(number);
	t.log_out();
}
void System::log_out_limit(void) {
	char number[20];
	cout << "请输入一卡通卡号" << endl;
	Limit l = get_limit(number);
	l.log_out();
}

void System::report_loss(void) {
	int choice_type;
	cout << "请输入要挂失一卡通的种类：" << endl;
	cout << "\t\t\t\t\t||==============================||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         1. student card     ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         2. teacher card     ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         3. limit card       ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         4. 返回              ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||==============================||" << endl;
	cin >> choice_type;
	switch (choice_type) {
	case 1:
		report_loss_student();
		break;
	case 2:
		report_loss_teacher();
		break;
	case 3:
		report_loss_limit();
		break;
	default:
		start();
	}
}
void System::report_loss_student(void) {
	cout << "请输入一卡通卡号" << endl;
	char number[20];
	cin >> number;
	Student s = get_student(number);
	s.report_loss();
}
void System::report_loss_teacher(void) {
	cout << "请输入一卡通卡号" << endl;
	char number[20];
	cin >> number;
	Teacher t = get_teacher(number);
	t.report_loss();
}
void System::report_loss_limit(void) {
	cout << "请输入一卡通卡号" << endl;
	char number[20];
	cin >> number;
	Limit l = get_limit(number);
	l.report_loss();
}
void System::unlock_report_loss(void) {
	int choice_type;
	cout << "请输入要解除注销一卡通的种类：" << endl;
	cout << "\t\t\t\t\t||==============================||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         1. student card     ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         2. teacher card     ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         3. limit card       ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||         4. 返回              ||" << endl;
	cout << "\t\t\t\t\t||                              ||" << endl;
	cout << "\t\t\t\t\t||==============================||" << endl;
	cin >> choice_type;
	switch (choice_type) {
	case 1:
		report_loss_student();
		break;
	case 2:
		report_loss_teacher();
		break;
	case 3:
		report_loss_limit();
		break;
	default:
		cout << "无该选项" << endl;
	}
}
void System::unlock_student(void) {
	cout << "请输入一卡通卡号" << endl;
	char number[20];
	cin >> number;
	Student s = get_student(number);
	s.unlock_report_loss();
}
void System::unlock_teacher(void) {
	cout << "请输入一卡通卡号" << endl;
	char number[20];
	cin >> number;
	Teacher t = get_teacher(number);
	t.unlock_report_loss();
}
void System::unlock_limit(void) {
	cout << "请输入一卡通卡号" << endl;
	char number[20];
	cin >> number;
	Limit l = get_limit(number);
	l.unlock_report_loss();
}

//Bus
void Bus::show_bus(void) {
	cout << "\t\t|============" << this->number << "===============|" << endl;
	cout << "\t\t| 车的类型：" << this->type << "\t\t|" << endl;
	cout << "\t\t| 司机的名字：" << this->driver << "\t\t|" << endl;
	cout << "\t\t| 最大乘客数：" << this->max_num << "\t\t|" << endl;
	cout << "\t\t| 车上现有的乘客数:" << this->get_cur_num() << "\t\t|" << endl;
	cout << "\t\t|===============================|" << endl;
}
int Bus::get_cur_num(void) {
	MYSQL mysql;
	MYSQL_RES* result;
	mysql_init(&mysql);
	mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0);
	char query[255];
	char number[20];
	int i;
	for (i = 0; i < this->number.length(); i++)
		number[i] = this->number[i];
	number[i] = '\0';
	sprintf_s(query, "select * from %s", number);
	if (mysql_query(&mysql, query)) {
		cout << "查询失败" << endl;
	}
	result = mysql_store_result(&mysql);
	int ans = mysql_num_rows(result);
	mysql_free_result(result);
	mysql_close(&mysql);
	return ans;
}
bool Bus::check_bus(void) {
	if (this->max_num > this->get_cur_num()) {
		cout << "...车辆未满,准许上车..." << endl;
		return true;
	}
	else if (this->max_num <= this->get_cur_num()) {
		cout << "...车辆已满,不许上车..." << endl;
		return false;
	}
}
void Bus::add_people(string cardtype, string cardnumber) {
	char type[20], number[20], busnumber[20];
	int i;
	for (i = 0; i < cardtype.length(); i++)
		type[i] = cardtype[i];
	type[i] = '\0';
	for (i = 0; i < cardnumber.length(); i++)
		number[i] = cardnumber[i];
	number[i] = '\0';
	for (i = 0; i < this->number.length(); i++)
		busnumber[i] = this->number[i];
	busnumber[i] = '\0';
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
		printf("数据库连接失败\n");
	}
	char query[255];
	sprintf_s(query, "insert into %s(cardtype,cardnumber) values('%s','%s')", busnumber, type, number);
	if (mysql_query(&mysql, query)) {
		cout << "查询add_people失败" << endl;
		printf("%s\n", mysql_error(&mysql));
	}
	else {
		cout << number << "成功乘上" << busnumber << endl;
	}
	mysql_close(&mysql);

}
void Bus::delete_people(string cardtype, string cardnumber) {
	char type[20], number[20], busnumber[20];
	int i;
	for (i = 0; i < cardtype.length(); i++)
		type[i] = cardtype[i];
	type[i] = '\0';
	for (i = 0; i < cardnumber.length(); i++)
		number[i] = cardnumber[i];
	number[i] = '\0';
	for (i = 0; i < this->number.length(); i++)
		busnumber[i] = this->number[i];
	busnumber[i] = '\0';
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
		printf("数据库连接失败\n");
	}
	char query[255];
	sprintf_s(query, "delete from %s where cardtype='%s' and cardnumber='%s'", busnumber, type, number);
	if (mysql_query(&mysql, query)) {
		cout << "查询add_people失败" << endl;
		printf("%s\n", mysql_error(&mysql));
	}
	else {
		cout << number << "成功下车" << busnumber << endl;
	}
	mysql_close(&mysql);
}
void Bus::bus_detail(void) {
	char number_bus[20];
	int j;
	for (j = 0; j < this->number.size(); j++)
		number_bus[j] = this->number[j];
	number_bus[j] = '\0';
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
		printf("数据库连接失败\n");
	}
	char query[255];
	sprintf_s(query, "select * from %s", number_bus);
	if (mysql_query(&mysql, query)) {
		cout << "bus_detail查询失败" << endl;
	}
	else {
		MYSQL_RES* result;
		MYSQL_ROW res_row;
		result = mysql_store_result(&mysql);

		cout << "\t\t|===========" << this->number << "============|" << endl;
		cout << "\t\t| - cardtype -- cardnumber - |" << endl;
		while (res_row = mysql_fetch_row(result)) {
			cout << "\t\t|===" << res_row[0] << "===" << res_row[1] << "===|" << endl;
		}
	}
	mysql_close(&mysql);

}
void Bus::clear_bus(void) {
	char number_bus[20];
	int j;
	for (j = 0; j < this->number.size(); j++)
		number_bus[j] = this->number[j];
	number_bus[j] = '\0';
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "qazedc12", "CardBusSystem", 3306, NULL, 0) == NULL) {
		printf("数据库连接失败\n");
	}
	char query[255];
	sprintf_s(query, "delete from %s", number_bus);
	if (mysql_query(&mysql, query)) {
		cout << "clear_bus查询失败" << endl;
	}
	mysql_close(&mysql);
}