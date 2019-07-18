#include "NhanVien.h"
wstring NhanVien::getHoTen() { return this->hoten; }
wstring NhanVien::getChucVu() { return this->chucvu; }
NgaySinh NhanVien::getNgaySinh() { return this->ngaysinh; }
float NhanVien::getHeSoLuong() { return this->hesoluong; }
void NhanVien::setHoTen(wstring ht) { this->hoten = ht; };
void NhanVien::setChucVu(wstring cv) { this->chucvu = cv; };
void NhanVien::setNgaySinh(NgaySinh ns) { this->ngaysinh = ns; };
void NhanVien::setHeSoLuong(float hsl) { this->hesoluong = hsl; };
void NhanVien::hienThi() {
	wcout << hoten << '\t' << chucvu << '\t' << ngaysinh.ngay << ngaysinh.thang << ngaysinh.nam << '\t' << hesoluong << endl;
}
NhanVien::NhanVien()
{
}
NhanVien::~NhanVien()
{
}
NhanVien::NhanVien(wstring hoten, wstring chucvu, NgaySinh ngaysinh, float hsl)
{
	this->hoten = hoten;
	this->chucvu = chucvu;
	this->ngaysinh = ngaysinh;
	this->hesoluong = hsl;
}
bool NhanVien::operator==(const NhanVien& nv) const {
	return ((hoten == nv.hoten) &&
		(ngaysinh.ngay == nv.ngaysinh.ngay &&ngaysinh.thang == nv.ngaysinh.thang&&ngaysinh.nam == nv.ngaysinh.nam) &&
		(chucvu == nv.chucvu) &&
		(hesoluong == nv.hesoluong)) ? true : false;
}
