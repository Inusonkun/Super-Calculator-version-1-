#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#define m 100

void PhepCong(char so1[], char so2[], char *tong);
void PhepTru(char so1[], char so2[], char *hieu);
void PhepNhan(char so1[], char so2[], char *tich);
void PhepChia(char so1[], char so2[], char *thuong, char *du);

void ThemKyTu(char s[], char kytuthem, int vitrithem)
{ 
	int l = strnlen_s(s, m);
	for (int i = l - 1; i >= vitrithem; --i)
	{
		s[i + 1] = s[i];
	}
	s[vitrithem] = kytuthem;
	s[l + 1] = '\0';
}

void LamBangSo(char s1[], char s2[])
{
	int l1 = strnlen_s(s1, m);
	int l2 = strnlen_s(s2, m);

	int min = l1 < l2 ? l1 : l2;
	int max = l1 > l2 ? l1 : l2;

	if (min == l1)
	{
		for (int i = 0; i < max - min; ++i)
		{
			ThemKyTu(s1, '0', 0);
		}
	}
	else if (min == l2)
	{
		for (int i = 0; i < max - min; ++i)
		{
			ThemKyTu(s2, '0', 0);
		}
	}
	
}

void XoaKyTu(char s[], int vitrixoa)
{
	int l = strnlen_s(s, m);
	for (int i = vitrixoa + 1; i < l; ++i)
	{
		s[i - 1] = s[i];
	}
	s[l - 1] = '\0';
}

void PhepCong(char so1[], char so2[], char *tong)
{
	char *s1 = _strdup(so1);
	char *s2 = _strdup(so2);

	if (s1[0] == '-' && s2[0] != '-')//so1 < 0
	{
		XoaKyTu(s1, 0);
		PhepTru(s2, s1, tong);
		return;
	}

	if (s2[0] == '-' && s1[0] != '-')// so2 < 0
	{
		XoaKyTu(s2, 0);
		PhepTru(s1, s2, tong);
		return;
	}

	if (s1[0] == '-' && s2[0] == '-')// so1 & so2 < 0
	{
		XoaKyTu(s1, 0);
		XoaKyTu(s2, 0);
	}

	int l1 = strnlen_s(s1, m);
	int l2 = strnlen_s(s2, m);
	int max = l1 >= l2 ? l1 : l2;
	LamBangSo(s1, s2);

	int sonho = 0, k = 0;

	for (int i = max - 1; i >= 0; --i)
	{
		int t = (s1[i] - 48) + (s2[i] - 48) + sonho;
		sonho = t / 10;
		t %= 10;
		tong[k++] = t + 48;
	}
	if (sonho != 0)
	{
		tong[k++] = sonho + 48;
	}

	tong[k] = '\0';
	_strrev(tong);

	if (so1[0] == '-' && so2[0] == '-')// trả về kết quả âm khi so1, so2 < 0
	{
		ThemKyTu(tong, '-', 0);
	}
}

void PhepTru(char so1[], char so2[], char *hieu)
{
	char *s1 = _strdup(so1);
	char *s2 = _strdup(so2);

	if (s1[0] == '-' && s2[0] != '-')// so1 < 0
	{
		char *s = _strdup(s2);	
		ThemKyTu(s, '-', 0);
	    PhepCong(s1, s, hieu);
		return;
	}
	if (s2[0] == '-' && s1[0] != '-')// so2 < 0
	{
		XoaKyTu(s2, 0);		
		PhepCong(s1, s2, hieu);
		return;
	}

	if (s1[0] == '-' && s2[0] == '-')// so1, so2 < 0
	{
		XoaKyTu(s1, 0);
		XoaKyTu(s2, 0);
	}

	int l1 = strnlen_s(s1, m);
	int l2 = strnlen_s(s2, m);

	int max = l1 >= l2 ? l1 : l2;
	LamBangSo(s1, s2);

	int somuon = 0, j = 0;
	int sotru, sobitru;

	for (int i = max - 1; i >= 0; --i)
	{
		if (s1[0] >= s2[0])
		{
			sotru = (s1[i] - 48) - somuon;
			sobitru = s2[i] - 48;
		}
		else
		{
			sotru = (s2[i] - 48) - somuon;
			sobitru = s1[i] - 48;
		}

		if (sotru >= sobitru)
		{
			hieu[j++] = (sotru - sobitru) + 48;
			somuon = 0;
		}
		else
		{
			somuon = (10 + sotru);
			hieu[j++] = (somuon - sobitru) + 48;
			somuon /= 10;
			if (somuon == 0)
			{
				somuon = 1;
			}
		}
	}
	hieu[j] = '\0';
	_strrev(hieu);

	for (int k = 0; k < j - 1; ++k)
	{
		if (hieu[k] == '0')
		{
			XoaKyTu(hieu, k);
			k--;
			j--;
		}
	}
	
	if (so1[0] == '-')
	{
		if (s1[0] > s2[0])
		{
			ThemKyTu(hieu, '-', 0);
		}
	}
	else
	{
		if (s1[0] < s2[0])
		{
			ThemKyTu(hieu, '-', 0);
		}
	}
}

void NhanMotChuoiVaMotKyTu(char so1[], char sox, char *tich)
{
	char *s1 = _strdup(so1);
	char x = sox;
	int k = 0;
	int thuaso, sonho = 0;

	if (s1[0] == '-')
	{
		XoaKyTu(s1, 0);
	}

	int l1 = strnlen_s(s1, m);

	for (int i = l1 - 1; i >= 0; --i)
	{
		thuaso = (s1[i] - 48) * (x - 48) + sonho;
		sonho = thuaso / 10;
		thuaso %= 10;
		tich[k++] = thuaso + 48;
	}
	if (sonho != 0)
	{
		tich[k++] = sonho + 48;
	}

	tich[k] = '\0';
	_strrev(tich);

	if (so1[0] == '-')
	{
		ThemKyTu(tich, '-', 0);
	}
}

void PhepNhan(char so1[], char so2[], char *tich)
{
	char *s1 = _strdup(so1);
	char *s2 = _strdup(so2);

	int l1 = strnlen_s(s1, m);
	int l2 = strnlen_s(s2, m);

	if (l1 == 1)// so1 < 10
	{
		NhanMotChuoiVaMotKyTu(s2, s1[0], tich);
		return;
	}

	if (l2 == 1)// so2 < 10
	{
		NhanMotChuoiVaMotKyTu(s1, s2[0], tich);
		return;
	}

	if (s1[0] == '-')// so1 < 0
	{
		XoaKyTu(s1, 0);
		if (l1 == 2 && so2[0] != '-') // -10 < so1 < 0
		{
			ThemKyTu(s2, '-', 0);
			NhanMotChuoiVaMotKyTu(s2, s1[0], tich);
			return;
		}
	}
	if (s2[0] == '-')// so2 < 0
	{
		XoaKyTu(s2, 0);
		if (l2 == 2 && so1[0] != '-') //-10 < so2 < 0
		{
			ThemKyTu(s1, '-', 0);
			NhanMotChuoiVaMotKyTu(s1, s2[0], tich);
			return;
		}
	}
	if (so1[0] == '-' && so2[0] == '-')
	{
		if (l1 == 2)
		{
			NhanMotChuoiVaMotKyTu(s2, s1[0], tich);
			return;
		}
		if (l2 == 2)
		{
			NhanMotChuoiVaMotKyTu(s1, s2[0], tich);
			return;
		}
	}	
	
	l1 = strnlen_s(s1, m);
	l2 = strnlen_s(s2, m);
	
	int x = 0, l3;
	char tich1[m], tich2[m];

	NhanMotChuoiVaMotKyTu(s1, s2[l2 - 1], tich1);
	
	for (int i = l2 - 2; i >= 0; --i)
	{
		NhanMotChuoiVaMotKyTu(s1, s2[i], tich2);
		l3 = strlen(tich2);
		x++;
		for (int j = 0; j < x; ++j)
		{
			ThemKyTu(tich2, '0', l3);		
		}

		if (x == 1)
		{			
			PhepCong(tich1, tich2, tich);
			strcpy_s(tich1, tich);
		}
		if (x > 1)
		{
			PhepCong(tich1, tich2, tich);
			strcpy_s(tich1, tich);
		}
	}

	if ((so1[0] == '-' && so2[0] != '-') || (so1[0] != '-' && so2[0] == '-'))
	{
		ThemKyTu(tich, '-', 0);
	}
}

void CatChuoi(char s[], int vitribatdau, int sokytu, char *chuoicat)
{
	int i = 0;
	for (int j = vitribatdau; j <= sokytu + vitribatdau - 1; ++j)
	{
		chuoicat[i++] = s[j];
	}
	chuoicat[i] = '\0';
}

void PhepChia(char so1[], char so2[], char *thuong, char *du)
{
	char *s1 = _strdup(so1);
	char *s2 = _strdup(so2);

	if (s1[0] == '-')
	{
		XoaKyTu(s1, 0);
	}
	if (s2[0] == '-')
	{
		XoaKyTu(s2, 0);
	}

	int l1 = strlen(s1);
	int l2 = strlen(s2);
	int j = 0, k = 0;

	if (l1 < l2)
	{
		thuong[j++] = '0';
		thuong[j] = '\0';
		if ((so1[0] == '-' && so2[0] != '-') || (so1[0] != '-' && so2[0] == '-'))
		{
			ThemKyTu(s1, '-', 0);
		}
		
		strcpy(du, s1);
		return;
	}
	else if (l1 == l2)
	{
		if (strcmp(s1, s2) == 0)
		{		
			if ((so1[0] == '-' && so2[0] != '-') || (so1[0] != '-' && so2[0] == '-'))
			{
				thuong[j++] = '-';
			}
			thuong[j++] = '1';
			thuong[j] = '\0';
			du[k++] = '0';
			du[k] = '\0';
			return;
		}
		else if (strcmp(s1, s2) < 0)
		{
			thuong[j++] = '0';
			thuong[j] = '\0';
			strcpy(du, s1);

			if ((so1[0] == '-' && so2[0] != '-') || (so1[0] != '-' && so2[0] == '-'))
			{
				int l3 = strlen(du);
				ThemKyTu(du, '-', 0);
			}
			
			return;
		}
		else if(strcmp(s1, s2) > 0)
		{
			char a = (s1[0] - 48) / (s2[0] - 48) + 48;// chia lấy phần nguyên của 2 phần tử đầu của s1, s2
			char kq[m], t[m];
			NhanMotChuoiVaMotKyTu(s2, a, kq);
			strcpy(t, s1);
			LamBangSo(kq, t);

			if ((so1[0] == '-' && so2[0] != '-') || (so1[0] != '-' && so2[0] == '-'))
			{
				thuong[j++] = '-';
			}

			if (strcmp(kq, t) > 0)// so sánh kết quả thu được với s1 
			{

				if (s1[0] <= '5')
				{
					thuong[j++] = a - 1;
					NhanMotChuoiVaMotKyTu(s2, a - 1, kq);
				}
				else
				{
					thuong[j++] = a - 2;
					NhanMotChuoiVaMotKyTu(s2, a - 2, kq);
				}
				thuong[j] = '\0';

				PhepTru(s1, kq, du);
				return;
			}
			else if (strcmp(kq, t) < 0)
			{
				thuong[j++] = a;
				thuong[j] = '\0';
				PhepTru(s1, kq, du);
				return;
			}
		}
	}
	else
	{
		char temp1[m], temp2[m], temp3[m];
		char a;
		int vitri = 0;
		CatChuoi(s1, vitri, l2, temp1);// lấy temp1 có độ dài bằng s2

		if (strcmp(temp1, s2) >= 0)
		{
			vitri = l2;
			a = (atoi(temp1) / atoi(s2)) + 48;
			thuong[j++] = a;
			NhanMotChuoiVaMotKyTu(s2, a, temp2);
			PhepTru(temp1, temp2, temp3);// lưu dư lần đầu vào temp3			
		}
		else// temp1 < s2
		{
			CatChuoi(s1, vitri, l2 + 1, temp1);
			vitri = l2 + 1;
			a = (atoi(temp1) / atoi(s2)) + 48;
			thuong[j++] = a;
			NhanMotChuoiVaMotKyTu(s2, a, temp2);
			PhepTru(temp1, temp2, temp3);// lưu dư lần đầu vào temp3		
		}

		while (vitri != l1)
		{
			CatChuoi(s1, vitri, 1, temp2);

			int l3 = strlen(temp3);
			int dem = 0;
			for (int i = 0; i < l3; ++i)
			{
				if (temp3[i] == '0')
				{
					dem++;
				}
			}
			if (dem != l3)
			{
				strcat(temp3, temp2);
				strcpy(temp2, temp3);
			}
			a = (atoi(temp2) / atoi(s2)) + 48;
			thuong[j++] = a;
			NhanMotChuoiVaMotKyTu(s2, a, temp1);
			PhepTru(temp2, temp1, temp3);
			vitri++;
		}

		thuong[j] = '\0';
		PhepNhan(s2, thuong, temp3);
		PhepTru(s1, temp3, du);
		if ((so1[0] == '-' && so2[0] != '-') || (so1[0] != '-' && so2[0] == '-'))
		{
			ThemKyTu(thuong, '-', 0);
		}
		return;
	}
}

int KiemTra(char so1[])
{
	char *s1 = _strdup(so1);
	int l1 = strlen(s1);
	char c1 = '-';
	int dem = 0;

	for (int i = 0; i < l1; ++i)
	{
		if ((s1[i] < '0' || s1[i] > '9') && s1[i] != c1)
		{
			return 0;
		}
		if (s1[i] == c1)
		{
			dem++;
			if (dem > 1)
			{
				return 0;
			}
			if (i > 0)
			{
				return 0;
			}
		}

	}
	return 1;
}

int main()
{
	char so1[m];
	char so2[m];

nhap:

	fflush(stdin);
	printf_s("\n\nNhap so thu nhat: ");
	gets_s(so1, m);
	fflush(stdin);
	printf_s("\nNhap so thu hai: ");
	gets_s(so2, m);

	if (KiemTra(so1) == 1 && KiemTra(so2) == 1)
	{
		char tong[m];
		PhepCong(so1, so2, tong);
		printf_s("\nTong = %s", tong);

		char hieu[m];
		PhepTru(so1, so2, hieu);
		printf_s("\nHieu = %s", hieu);

		char tich[m];
		PhepNhan(so1, so2, tich);
		printf_s("\nTich = %s", tich);

		char thuong[m], du[m];
		PhepChia(so1, so2, thuong, du);
		printf_s("\nThuong = %s va du = %s", thuong, du);
	}
	else
	{
		printf_s("\nCac so nhap vao gia tri khong hop le! Hay nhap lai!");
		goto nhap;
	}
	
	goto nhap;
	_getch();
	return 0;
}