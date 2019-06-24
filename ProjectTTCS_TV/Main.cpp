#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "NhanVien.h"
#include <iomanip>
#include <cstdlib>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <locale>
#include <codecvt> //possible C++11?
using namespace std;
#define M 1024

int StringToInt(wstring NumberAsString) {
	int NumberAsInt;
	wstringstream ss;
	ss << NumberAsString;
	ss >> NumberAsInt;
	return NumberAsInt;
}
wstring IntToString(int NumberAsInt) {
	wstring NumberAsString;
	wstringstream ss;
	ss << NumberAsInt;
	ss >> NumberAsString;
	return NumberAsString;
}
float StringToFloat(wstring NumberAsString) {
	float NumberAsFloat;
	wstringstream ss;
	ss << NumberAsString;
	ss >> NumberAsFloat;
	return NumberAsFloat;
}
string	FloatToString(float NumberAsFloat) {
	string NumberAsString;
	stringstream ss;
	ss << NumberAsFloat;
	ss >> NumberAsString;
	return NumberAsString;
}
bool Equal(wchar_t x, wchar_t y) {
	return (x == y) ? true : false;
}
bool Equal(wstring x, wstring y) {
	//int pos = 0;
	//if (x[0] == y[0]) {
	//	while (x[pos] != '\0' && y[pos] != '\0') {
	//		if (x[pos] != y[pos]) return false;
	//		else pos++;
	//	}
	//	return true;
	//}
	//else return false;
	return (x == y) ? true : false;
}
bool Equal(wstring x, wchar_t y) {
	int pos = 0;
	while (x != L"\0")
	{
		if (x[pos] == y)
			return true;
		else pos++;
	}
	return false;
}
wstring toLower(const wstring input) {
	wstring str = input;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z') {
			//Convert lowercase to uppercase 
			//str[i] = str[i] - 32;
			continue;
		}
		else if (str[i] >= 'A' && str[i] <= 'Z') {
			//Convert uppercase to lowercase 
			str[i] = str[i] + 32;
		}
	}
	return str;
}
wstring toUpper(const wstring input) {
	wstring str = input;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z') {
			//Convert lowercase to uppercase 
			str[i] = str[i] - 32;
		}
		else if (str[i] >= 'A' && str[i] <= 'Z') {
			//Convert uppercase to lowercase 
			//str[i] = str[i] + 32;
			continue;
		}
	}
	return str;
}
wstring setWidth(wstring n, int size) {
	int temp = size - (n).length();
	if (temp < 0) {
		return n;
	}
	else {
		for (int i = 0; i < temp; i++)
		{
			n += ' ';
		}
	}
	return n;
}
wstring setWidth(wchar_t x, int size) {
	wstring temp = &x;
	for (int i = 0; i < size; i++)
	{
		temp += x;
	}
	return temp;
}
int Find(wstring line, wchar_t x)
{
	int pos = 0;
	while (line[pos] != '\0')
	{
		if (Equal(line[pos], x)) {
			return pos;
		}
		else if (line[pos + 1] == '\0') {
			return pos + 1;
		}
		else pos++;
	}
	/*for (int i = 0; i < line.length(); i++)
	{
		if (Equal(line[i], x)) {
			return i;
		}
	}
*/
}
wstring* Split(wstring line, wchar_t x) {
	wstring* substring = new wstring[100];
	int found, pos = 0;
	wstring temp = line;
	while (temp != L"\0") {
		found = Find(temp, x);
		for (int i = 0; i < found; i++)
		{
			substring[pos] += temp[i];
		}
		temp.erase(0, found + 1);
		pos++;
	}
	return substring;
}
NgaySinh outputDOB(wstring line) {
	wstring* a = Split(line, '/');
	NgaySinh ns;
	if (a->length() < 0) {
		ns.ngay = -1;
		ns.thang = -1;
		ns.nam = -1;
	}
	else {
		ns.ngay = StringToInt(*a);
		ns.thang = StringToInt(*(a + 1));
		ns.nam = StringToInt(*(a + 2));
	}
	/*wstring day, mon, year;
	int d = StringToInt(*a);
	int m = StringToInt(*(a + 1));
	if (d > 0 && d < 10) {
		day = L"0" + IntToString(d);
	}
	else day = *a;
	if (m > 0 && m < 10) {
		mon = L"0" + IntToString(m);
	}
	else mon = *(a + 1);
	wstring x = day + L"/" + mon + L"/" + *(a + 2);*/
	return ns;
}
wstring DOBtoSTR(NgaySinh ns) {
	wstring x;
	wstring d, m, y;

	if (ns.ngay < 10 && ns.ngay > 0) {
		d = L'0' + IntToString(ns.ngay);
	}
	else d = IntToString(ns.ngay);
	if (ns.thang < 10 && ns.thang>0) {
		m = L'0' + IntToString(ns.thang);
	}
	else m = IntToString(ns.thang);
	if (ns.nam > 0 && ns.nam < 1000) {
		y = L'0' + IntToString(ns.nam);
	}
	else y = IntToString(ns.nam);

	x = d + L'/' + m + L'/' + y;

	return x;
}
struct LinkedList {
	NhanVien data;
	struct LinkedList* next;
};
typedef LinkedList* node;//Thay kiểu dữ liệu = NODE cho ngắn gọn
node CreateNode(NhanVien value) {
	node temp; //Khai báo 1 node
	//temp = (node)malloc(sizeof(struct LinkedList));//Cấp phát vùng nhớ dùng malloc
	temp = new LinkedList;
	temp->next = NULL; //cho next trỏ tới NULL
	temp->data = value; //gán giá trị cho node
	return temp;//trả về node mới đã có giá trị
}
node AddHead(node head, NhanVien value) {
	node temp = CreateNode(value);//khởi tạo node temp với data = value
	if (head == NULL) {
		head = temp; //nếu liked list đang trống thì node temp là head
	}
	else {
		temp->next = head; //trỏ next của temp = head hiện tại
		head = temp; //đổi head hiện tại = temp (vì temp bây h là head mới)
	}
	return head;
}
node AddTail(node head, NhanVien value) {
	node temp, p; //khai báo 2 node tạm
	temp = CreateNode(value);//gọi hàm createnode để khởi tạo node temp có next trỏ tới NULL và data là value
	if (head == NULL) {
		head = temp;
	}
	else {
		p = head;//khởi tạo p trỏ tới head
		while (p->next != NULL) {
			p = p->next;//duyệt đến cuối.node cuối là node có next = null
		}
		p->next = temp;//gán next của node cuối = temp,khi đó temp sẽ là node cuối(temp.next=NULL)
	}
	return head;
}
node AddAt(node head, NhanVien value, int position) {
	if (position == 0 || head == NULL) {
		head = AddHead(head, value);//nếu vị trí chèn = 0, => thêm vào đầu
	}
	else {
		//bắt đầu tìm vị trí cần chèn. dùng k để đếm vị trí
		int k = 1;
		node p = head;
		while (p->next != NULL && k != position) {
			p = p->next;
			++k;
		}
		if (k != position) {
			//nếu duyệt hết danh sách mà vẫn chưa đến vị trí cần chèn, mặc định chèn cuối
			//nếu k muốn chèn, thông báo vị trí không hợp lệ
			head = AddTail(head, value);
			//wcout<<"Vi tri chen vuot qua vi tri cuoi cung"<<endl;
		}
		else {
			node temp = CreateNode(value);
			temp->next = p->next;
			p->next = temp;
		}
	}
	return head;
}
node DelHead(node head) {
	if (head == NULL) {
		wcout << L"DANH SÁCH RỖNG!!!";
	}
	else
	{
		head = head->next;
	}
	return head;
}
node DelTail(node head) {
	node p = head;
	while (p->next->next != NULL) {
		p = p->next;
	}
	p->next = p->next->next;//cho next = NULL
	//hoặc p->next  = NULL
	return head;
}
node DelAt(node head, int position) {
	if (position == 0 || head == NULL) {
		head = DelHead(head); //nếu vị trí chèn = 0,Xoá đầu
	}
	else {
		//tìm vị trí chèn. dùng k để đếm vị trí
		int k = 1;
		node p = head;
		while (p->next->next != NULL && k != position)
		{
			p = p->next;
			++k;
		}
		if (k != position) {
			//nếu duyệt hết danh sách mà không tìm được vị trí cần xoá, mặc định xoá cuối
			//nếu k muốn xoá,thông báo vị trí xoá k hợp lệ
			head = DelTail(head);
			//wcout << "Vi tri xoa vuot qua vi tri cuoi"<<endl;
		}
		else {
			p->next = p->next->next;
		}
	}
	return head;
}
NhanVien Get(node head, int index) {
	int k = 0;
	node p = head;
	while (p != NULL && k != index) {
		p = p->next;
		++k;
	}
	return p->data;
}
int Search(node head, NhanVien value) {
	int pos = 0;
	for (node p = head; p != NULL; p = p->next)
	{
		if (p->data == value)
		{
			return pos;
		}
		++pos;
	}
	return -1;
}
int Search(node head, NhanVien value, float hsl) {
	int pos = 0;
	for (node p = head; p != NULL; p = p->next)
	{
		if (p->data == value && p->data.getHeSoLuong() == hsl)
		{
			return pos;
		}
		++pos;
	}
	return -1;
}
int Search(node head, wstring value) {
	int pos = 0;
	for (node p = head; p != NULL; p = p->next)
	{
		NgaySinh ns = outputDOB(value);
		if (p->data.getHoTen() == value)
		{
			return pos;
		}
		else if (p->data.getChucVu() == value)
		{
			return pos;
		}
		else if (p->data.getNgaySinh().ngay == ns.ngay
			&& p->data.getNgaySinh().thang == ns.thang
			&& p->data.getNgaySinh().nam == ns.nam)
		{
			return pos;
		}
		++pos;
	}
	return -1;
}
node DelByVal(node head, NhanVien value) {
	int pos = Search(head, value);
	while (pos != -1) {
		DelAt(head, pos);
		pos = Search(head, value);
	}
	return head;
}
bool FindSubString(const wstring str1, const wstring str2) {
	int i = 0, save, temp, size1;
	wstring s1 = toLower(str1);
	wstring s2 = toLower(str2);
	int size2 = str2.length();
	while (s1[i] != '\0') {//LẬP CHUỖI DÀI
		if (s1[i] == s2[0]) {//KT PHẦN TỬ 1 CỦA CHUỖI 2 CÓ BẰNG PHẦN TỬ thứ i CỦA CHUỖI 1
			int j = 1;
			save = i;
			temp = i;//LƯU VỊ TRÍ KHI I = PHẦN TỬ 1 CỦA CHUỖI 2
			size1 = 1;//LƯU LẠI KÍCH THƯỚC CỦA CHUỖI 1(PHẦN TRÙNG VỚI CHUỖI 2)
			while ((s2[j] != '\0' || s1[save + 1] != '\0') && s1[save + 1] == s2[j]) {
				j++;
				save++;
				size1++;
			}
			if (s2[j] == '\0' && size2 == size1)
				return true;
			else {
				i = temp;
				i++;
			}
		}
		else i++;
	}
	return false;
}
bool FindSubString(const NgaySinh ns1, const wstring subString) {
	NgaySinh ns2 = outputDOB(subString);
	if (ns1.ngay == ns2.ngay || ns1.thang == ns2.thang || ns1.nam == ns2.nam)
		return true;
	else return false;
}
node DelByString(node head, wstring subString) {
	for (node p = head; p != NULL; p = p->next)
	{
		if (FindSubString(p->data.getHoTen(), subString))
		{
			int pos = Search(head, p->data);
			head = DelAt(head, pos);
		}
		else if (FindSubString(p->data.getChucVu(), subString))
		{
			int pos = Search(head, p->data);
			head = DelAt(head, pos);
		}
		else if (FindSubString(DOBtoSTR(p->data.getNgaySinh()), subString))
		{
			int pos = Search(head, p->data);
			head = DelAt(head, pos);
		}
		else if (p->data.getHeSoLuong() == StringToFloat(subString))
		{
			int pos = Search(head, p->data, StringToFloat(subString));
			head = DelAt(head, pos);
		}
	}
	return head;
}
int SearchByString(node head, node p, wstring subString) {
	if (FindSubString(p->data.getHoTen(), subString))
	{
		int pos = Search(head, p->data);
		return pos;
	}
	else if (FindSubString(p->data.getChucVu(), subString))
	{
		int pos = Search(head, p->data);
		return pos;
	}
	else if (FindSubString(DOBtoSTR(p->data.getNgaySinh()), subString))
	{
		int pos = Search(head, p->data);
		return pos;
	}
	else if (p->data.getHeSoLuong() == StringToFloat(subString))
	{
		int pos = Search(head, p->data, StringToFloat(subString));
		return pos;
	}
	return -1;
}
void DisplaySBS(node head, wstring sub) {
	int flag = 0;
	wcout << setWidth('@', 100) << endl;
	for (node p = head; p != NULL; p = p->next)
	{
		int i = SearchByString(head, p, sub);
		if (i != -1) {
			flag++;
			NhanVien value = Get(head, i);
			wcout << setWidth('-', 100) << endl;
			wcout << L"STT: " << i + 1 << endl;
			wcout << L"Họ tên : " << value.getHoTen() << endl;
			wcout << L"Chức vụ : " << value.getChucVu() << endl;
			wcout << L"Ngày sinh : " << DOBtoSTR(value.getNgaySinh()) << endl;
			wcout << L"Hệ số lương : " << fixed << setprecision(3) << value.getHeSoLuong() << endl;
			//value.hienThi();
			//wcout << "====================" << endl;
		}
	}
	if (flag == 0) {
		wcout << "====================" << endl;
		wcout << L"KHÔNG TÌM THẤY" << endl;
		wcout << "====================" << endl;
	}
	wcout << setWidth('@', 100) << endl;
}
void Traverser(node head) {
	wcout << endl;
	int i = 0;
	wcout << setWidth(L'=', 100) << endl;
	wcout << setWidth(L"STT", 10) << "|";
	wcout << setWidth(L"Họ và tên", 25) << "|";
	wcout << setWidth(L"Chức vụ", 25) << "|";
	wcout << setWidth(L"Ngày tháng năm sinh", 25) << "|";
	wcout << L"Hệ số lương" << endl;
	for (node p = head; p != NULL; p = p->next)
	{
		wcout << setWidth(IntToString(i + 1), 10) << "|";
		wcout << setWidth(p->data.getHoTen(), 25) << "|";
		wcout << setWidth(p->data.getChucVu(), 25) << "|";
		wcout << setWidth(DOBtoSTR(p->data.getNgaySinh()), 25) << "|";
		wcout << fixed << setprecision(3) << p->data.getHeSoLuong() << endl;
		++i;
	}
	wcout << endl;
}
node InitHead() {
	node head;
	head = NULL;
	return head;
}
int Length(node head) {
	int len = 0;
	for (node p = head; p != NULL; p = p->next)
	{
		++len;
	}
	return len;
}
node Input(NhanVien value) {
	node head = InitHead();
	/*int n;
	NhanVien value;*/
	//do {
	//	/*wcout << "Nhập số nhân viên: ";
	//	wcin >> n;*/
	//	
	//} while (n <= 0);
	//for (int i = 0; i < n; i++)
	//{
	//	/*wcout << "Nhap gia tri can them: ";
	//	wcin >> value;*/
	//	head = AddTail(head, value);
	//}
	head = AddTail(head, value);
	return head;
}
int CountTotal(wfstream &file, wstring dir) {
	file.open(dir);
	int count = 0;
	wstring line;
	getline(file, line);
	while (getline(file, line)) {
		count++;
	}
	file.close();
	return count;
}
node InputList(wfstream &file, wstring name, node head) {

	file.open(name);
	std::locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
	file.imbue(loc);
	wstring line;

	getline(file, line);
	while (getline(file, line)) {
		wstring* ptr = new wstring[4];
		ptr = Split(line, ';');
		wstring hoten = *(ptr);
		wstring chucvu = *(ptr + 1);
		NgaySinh ngaysinh = outputDOB(*(ptr + 2));
		float hsl = (float)StringToFloat(*(ptr + 3));
		NhanVien* nhanvien = new NhanVien(hoten, chucvu, ngaysinh, hsl);
		head = AddTail(head, *nhanvien);
	}
	file.close();
	return head;
}
node OutPutList(node head, wstring name) {
	wfstream _file;

	_file.open(name, ios::out);
	std::locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
	_file.imbue(loc);
	_file << setWidth(L"STT", 10)
		<< setWidth(L"Họ và tên", 25)
		<< setWidth(L"Chức vụ", 25)
		<< setWidth(L"Ngày tháng năm sinh", 25)
		<< setWidth(L"Hệ số lương", 25)
		<< "\n";
	int i = 1;
	for (node p = head; p != NULL; p = p->next)
	{
		float num = p->data.getHeSoLuong();
		_file << setWidth(IntToString(i), 10)
			<< setWidth(p->data.getHoTen(), 25)
			<< setWidth(p->data.getChucVu(), 25)
			<< setWidth(DOBtoSTR(p->data.getNgaySinh()), 25)
			<< fixed << setprecision(2)
			<< num
			<< "\n";
		i++;
	}
	_file.close();
	wcin.get();
	wcout << L"XUẤT FILE THÀNH CÔNG!!!";
	return head;
}
bool compareBD(const NgaySinh d1, const NgaySinh d2) {

	int ngay1 = d1.ngay;
	int ngay2 = d2.ngay;
	int thang1 = d1.thang;
	int thang2 = d2.thang;
	int nam1 = d1.nam;
	int nam2 = d2.nam;
	if (nam1 < nam2) {
		return true;
	}
	if (nam1 == nam2 && thang1 < thang2) {
		return true;
	}
	if (nam1 == nam2 && thang1 == thang2 && ngay1 < ngay2) {
		return true;
	}
	return false;
}
bool compareHSL(float d1, float d2) {
	if (d1 <= d2) {
		return true;
	}
	else return false;
}
int ranking(const wstring str) {
	wstring temp = toLower(str);

	wstring ct = L"chủ tịch";
	wstring pct = L"phó chủ tịch";
	wstring gd = L"giám đốc";
	wstring pgd = L"phó giám đốc";
	wstring tk = L"thư ký";
	wstring ql = L"quản lý";
	wstring tp = L"trưởng phòng";
	wstring pp = L"phó phòng";
	wstring nv = L"nhân viên";
	wstring trainee = L"thực tập sinh";
	int x = 0;

	if (Equal(temp, ct))  x = 10;
	else if (Equal(temp, pct))  x = 9.5;
	else if (Equal(temp, gd))  x = 9;
	else if (Equal(temp, pgd))  x = 8.5;
	else if (Equal(temp, tk))  x = 8;
	else if (Equal(temp, ql))  x = 7.5;
	else if (Equal(temp, tp))  x = 7;
	else if (Equal(temp, pp))  x = 6.5;

	else if (Equal(temp, nv))  x = 5;
	else if (Equal(temp, trainee))  x = 4;
	return x;
}
bool compareCV(const wstring d1, const wstring d2) {
	int x = ranking(d1);
	int y = ranking(d2);
	if (x <= y)return true;
	else return false;
}
bool compareName(wstring d1, wstring d2) {
	wstring s1 = toUpper(d1);
	wstring s2 = toUpper(d2);
	wstring* str1 = Split(s1, ' ');
	wstring* str2 = Split(s2, ' ');
	int p1 = 0;
	int p2 = 0;
	while (*(str1 + p1) != L"\0") {
		++p1;
	}
	while (*(str2 + p2) != L"\0")
	{
		++p2;
	}
	//for (int i = 0; i < (*(str1 + p1 - 1)).length(); i++)
	//{
	//	for (int j = 0; i < (*(str2 + p2 - 1)).length(); i++)
	//	{
	//		if ((*(str1 + p1 - 1))[i] <= (*(str2 + p2 - 1))[j]) {
	//			/*	wcout << *(str1 + p1 - 1) << endl;
	//				wcout << *(str2 + p2 - 1) << endl;*/
	//			return true;
	//		}
	//		else return false;
	//	}
	//}
	int i = 0;
	int j = 0;
	while ((*(str1 + p1 - 1))[i] != '\0' && (*(str2 + p2 - 1))[j] != '\0')
	{
		if ((*(str1 + p1 - 1))[i] == (*(str2 + p2 - 1))[j]) { i++;j++; }
		else if ((*(str1 + p1 - 1))[i] > (*(str2 + p2 - 1))[j]) return false;
		else if ((*(str1 + p1 - 1))[i] < (*(str2 + p2 - 1))[j]) return true;
	}
	return false;
	/*return false;*/
}
node SortedMerge(node a, node b, int thutu, int type) {
	node result = NULL;

	//Base case
	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
	//chọn a hoặc b, và đệ qui
	if (type == 0) { //TÊN
		if (thutu == 1) {
			if (compareName(a->data.getHoTen(), b->data.getHoTen())) {
				result = a;
				result->next = SortedMerge(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = SortedMerge(a, b->next, thutu, type);
			}
		}
		else {
			if (!compareName(a->data.getHoTen(), b->data.getHoTen())) {
				result = a;
				result->next = SortedMerge(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = SortedMerge(a, b->next, thutu, type);
			}
		}
	}
	if (type == 1) { //CHỨC VỤ
		if (thutu == 1) {
			if (compareCV(a->data.getChucVu(), b->data.getChucVu())) {
				result = a;
				result->next = SortedMerge(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = SortedMerge(a, b->next, thutu, type);
			}
		}
		else {
			if (!compareCV(a->data.getChucVu(), b->data.getChucVu())) {
				result = a;
				result->next = SortedMerge(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = SortedMerge(a, b->next, thutu, type);
			}
		}
	}
	if (type == 2) { //NGÀY SINH
		if (thutu == 1) {
			if (compareBD(a->data.getNgaySinh(), b->data.getNgaySinh())) {
				result = a;
				result->next = SortedMerge(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = SortedMerge(a, b->next, thutu, type);
			}
		}
		else {
			if (!compareBD(a->data.getNgaySinh(), b->data.getNgaySinh())) {
				result = a;
				result->next = SortedMerge(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = SortedMerge(a, b->next, thutu, type);
			}
		}

	}
	if (type == 3) { //HỆ SỐ LƯƠNG
		if (thutu == 1) {
			if (compareHSL(a->data.getHeSoLuong(), b->data.getHeSoLuong())) {
				result = a;
				result->next = SortedMerge(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = SortedMerge(a, b->next, thutu, type);
			}
		}
		else {
			if (!compareHSL(a->data.getHeSoLuong(), b->data.getHeSoLuong())) {
				result = a;
				result->next = SortedMerge(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = SortedMerge(a, b->next, thutu, type);
			}
		}
		return result;
	}


	return result;
}
int checkType(wstring line) {
	if (Equal(toLower(line), L"ho va ten")
		|| Equal(toLower(line), L"ten")
		|| Equal(toLower(line), L"hovaten")
		|| Equal(toLower(line), L"hoten")
		|| Equal(toLower(line), L"họ và tên")
		|| Equal(toLower(line), L"tên")
		) {
		return 0;
	}
	if (Equal(toLower(line), L"chuc vu") || Equal(toLower(line), L"chức vụ")
		|| Equal(toLower(line), L"chucvu")) {
		return 1;
	}
	if ((Equal(toLower(line), L"ngay thang nam sinh"))
		|| (Equal(toLower(line), L"ngay thang nam"))
		|| (Equal(toLower(line), L"ngay thang"))
		|| (Equal(toLower(line), L"nam sinh"))
		|| (Equal(toLower(line), L"ngay sinh"))
		|| (Equal(toLower(line), L"ngày tháng năm sinh"))
		|| (Equal(toLower(line), L"ngày tháng năm"))
		|| (Equal(toLower(line), L"ngày tháng"))
		|| (Equal(toLower(line), L"năm sinh"))
		|| (Equal(toLower(line), L"ngày sinh"))
		|| (Equal(toLower(line), L"ngaysinh"))
		|| (Equal(toLower(line), L"namsinh"))
		|| (Equal(toLower(line), L"ngaythangnamsinh"))
		|| (Equal(toLower(line), L"ngaythang")))
	{
		return 2;
	}
	if (Equal(toLower(line), L"luong") || Equal(toLower(line), L"he so luong") || Equal(toLower(line), L"lương") || Equal(toLower(line), L"hệ số lương")
		|| (Equal(toLower(line), L"hesoluong"))) {
		return 3;
	}
	return -1;
}
void FrontBackSplit(node source, node* frontRef, node* backRef) {
	node fast;
	node slow;
	slow = source;
	fast = source->next;
	//di chuyển fast 2 node,di chuyển slow 1 node
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	//'slow' is before the midpoint in the list, so split it in two at that point
	//slow nằm ở phía trước điểm giữa của danh sách, nên chia danh sách làm 2 ở điểm đó
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}
void MergeSort(node* headRef, int thutu, int type) {
	node head = *headRef;
	node a;
	node b;

	//Length = 0 hoặc 1
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}
	//Split head into 'a' and 'b' sublist
	FrontBackSplit(head, &a, &b);
	/* Recursively sort the sublists */
	MergeSort(&a, thutu, type);
	MergeSort(&b, thutu, type);
	//answer=merge the two sorted list together
	*headRef = SortedMerge(a, b, thutu, type);
}
void SortAll(node* headRef) {
	node head = *headRef;
	int order;
	wstring input;
	//fflush(stdin);
	wcin.ignore();
	wcout << setWidth('*', 100) << endl;
	wcout << L"TIÊU CHÍ SẮP XẾP: " << endl;
	getline(wcin, input);
	int type = checkType(input);
	if (type == -1) {
		wcout << L"LỖI CÚ PHÁP!!!";
		return;
	}
	wcout << L"THỨ TỰ SẮP XẾP: " << endl;
	wcout << L"1.TĂNG DẦN \n";
	wcout << L"2.GIẢM DẦN \n";
	wcin >> order;

	if (order == 1) {
		MergeSort(headRef, 1, type);
		/*	wcout << setWidth('*', 100) << endl;
			Traverser(head);
			wcout << setWidth('*', 100) << endl;*/
	}
	else
	{
		MergeSort(headRef, 2, type);
		/*	wcout << setWidth('*', 100) << endl;
			Traverser(head);
			wcout << setWidth('*', 100) << endl;*/
	}
	//wcout << setWidth('*', 100) << endl;
	//Traverser(head);
	//wcout << setWidth('*', 100) << endl;
}
node AddEmp(node head) {
	wcin.ignore();
	wstring ht;
	wstring cv;
	wstring ns;
	float hsl;
	int pos;
	wcout << setWidth('#', 100) << endl;
	wcout << L"HỌ VÀ TÊN: \n";
	getline(wcin, ht);
	wcout << L"CHỨC VỤ: \n";
	getline(wcin, cv);
	wcout << L"NGÀY THÁNG NĂM SINH: \n";
	getline(wcin, ns);
	wcout << L"HỆ SỐ LƯƠNG: \n";
	wcin >> hsl;
	wcout << L"VỊ TRÍ CẦN CHÈN: \n";
	wcin >> pos;
	wcout << setWidth('#', 100) << endl;
	NgaySinh ngaysinh = outputDOB(ns);
	NhanVien nv = NhanVien(ht, cv, ngaysinh, hsl);
	head = AddAt(head, nv, pos - 1);
	return head;
}
node DelAll(node head) {
	wcin.ignore();
	wstring s;
	wcout << setWidth('#', 100) << endl;
	wcout << L"NHẬP CHUỖI CẦN XOÁ: \n";
	getline(wcin, s);
	wcout << setWidth('#', 100) << endl;
	head = DelByString(head, s);
	return head;
}
void Display(node head) {
	wcin.ignore();
	wstring s;
	wcout << setWidth('#', 100) << endl;
	wcout << L"NHẬP CHUỖI TÌM KIẾM: \n";
	getline(wcin, s);
	wcout << setWidth('#', 100) << endl;
	DisplaySBS(head, s);
}
int main()
{
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	HANDLE hdlConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX consoleFont;
	consoleFont.cbSize = 16;
	GetCurrentConsoleFontEx(hdlConsole, FALSE, &consoleFont);
	memcpy(consoleFont.FaceName, L"Consolas", sizeof(consoleFont.FaceName));
	SetCurrentConsoleFontEx(hdlConsole, FALSE, &consoleFont);

	wfstream file;
	wstring line;
	std::locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
	file.imbue(loc);
	wcout << setWidth('*', 100) << endl;
	wcout << L"NHẬP DANH SÁCH NHÂN VIÊN: ";
	wcin >> line;
	int n = CountTotal(file, line);
	wcout << L"TỔNG SỐ NHÂN VIÊN: " << n << endl;
	wcout << setWidth('*', 100) << endl;
	node head = InitHead();
	head = InputList(file, line, head);
	Traverser(head);
	wcout << setWidth('*', 100) << endl;
	int chon = -1;

	while (chon != 0) {
		//system("cls");
		wcout << setWidth('*', 100) << endl;

		wcout << L"1.SẮP XẾP NHÂN VIÊN THEO TIÊU CHÍ, THỨ TỰ" << endl;

		wcout << L"2.THÊM NHÂN VIÊN VÀO VỊ TRÍ" << endl;

		wcout << L"3.XOÁ NHÂN VIÊN THEO TỪ KHOÁ" << endl;

		wcout << L"4.TÌM NHÂN VIÊN THEO TỪ KHOÁ" << endl;

		wcout << L"5.XUẤT DANH SÁCH" << endl;

		wcout << L"0.THOÁT" << endl;

		wcout << setWidth('*', 100) << endl;

		wcin >> chon;


		if (chon == 1) {
			SortAll(&head);
			wcout << setWidth('*', 100) << endl;
			Traverser(head);
			wcout << setWidth('*', 100) << endl;
		}

		if (chon == 2) {
			head = AddEmp(head);
			wcout << setWidth('*', 100) << endl;
			Traverser(head);
			wcout << setWidth('*', 100) << endl;
		}
		if (chon == 3) {
			head = DelAll(head);
			wcout << setWidth('*', 100) << endl;
			Traverser(head);
			wcout << setWidth('*', 100) << endl;
		}
		if (chon == 4) {
			Display(head);
		}
		if (chon == 5) {
			wcin.ignore();
			wstring dir;
			wcout << setWidth('~', 100) << endl;
			wcout << L"NHẬP ĐỊA CHỈ: ";
			getline(wcin, dir);
			OutPutList(head, dir);
			wcout << setWidth('~', 100) << endl;
		}
	}
	std::system("pause");
	return 0;
}