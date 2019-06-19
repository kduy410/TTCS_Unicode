#include <string>
#include <iostream>
using namespace std;
struct NgaySinh {
	int ngay, thang, nam;
};
class NhanVien
{
	
public:
	NhanVien();
	NhanVien(wstring hoten, wstring chucvu, NgaySinh ngaysinh, float hesoluong);
	~NhanVien();
	wstring getHoTen();
	wstring getChucVu();
	NgaySinh getNgaySinh();
	float getHeSoLuong();
	void setHoTen(wstring ht);
	void setChucVu(wstring cv);
	void setNgaySinh(NgaySinh ns);
	void setHeSoLuong(float hsl);
	void hienThi();
	bool operator==(const NhanVien& nv) const;
	
private:
	wstring hoten;
	wstring chucvu;
	NgaySinh ngaysinh;
	float hesoluong;
};



