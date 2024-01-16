use master
create database DT1
go
use DT1
go

--use master drop database DT1
create table THANHVIEN (
	IDThanhVien int,
	HoTen nchar(50),
	SoCMND char(10),
	DiaChi nchar(50),
	NgaySinh datetime

	PRIMARY KEY(IDThanhVien)
); 

create table DOI (
	IDDoi int,
	TenDoi nchar(50),
	DoiTruong int,
	
	PRIMARY KEY(IDDoi) 
);

create table BOTRI (
	IDDoi int,
	IDThanhVien int,
	DiaChi nchar(50),
	NhiemVu nchar(50),
	QuanLi int

	PRIMARY KEY(IDThanhVien, IDDoi)
);

alter table DOI add
	constraint FK_DOI_THANHVIEN foreign key (DoiTruong) references THANHVIEN(IDThanhVien)

alter table BOTRI add
	constraint FK_BOTRI_THANHVIEN foreign key (QuanLi) references THANHVIEN(IDThanhVien),
	constraint FK_BOTRI_DOI foreign key (IDDoi)	references DOI(IDDoi)

set dateformat dmy
insert into THANHVIEN values(1, N'Nguyễn Quan Tùng', '240674018', N'TPHCM', '30/1/2000')
insert into THANHVIEN values(2, N'Lưu Phi Nam', '240674027', N'Quảng Nam', '12/3/2001')
insert into THANHVIEN values(3, N'Lê Quang Bảo', '240674063', N'Quảng Ngãi', '14/5/1999')
insert into THANHVIEN values(4, N'Hà Ngọc Thúy', '240674504', N'TPHCM', '26/7/1998')
insert into THANHVIEN values(5, N'Trương Thị Minh', '240674405', N'Hà Nội', null)
insert into THANHVIEN values(6, N'Ngô Thị Thùy', '240674306', null, '18/9/2000')

insert into DOI values(2, N'Đội Tân Phú', 1)
insert into DOI values(7, N'Đội Bình Phú', 5)

insert into BOTRI values (2,2, N'123 Vườn Lài Tân Phú', N'Trực khu vực vòng xoay 1',1)
insert into BOTRI values (2,1, N'45 Phú Thọ Hòa Tân Phú', N'Theo dõi hoạt động',1)
insert into BOTRI values (7,3, N'11 Chợ lớn Bình Phú', null , 5)
insert into BOTRI values (7,4, N'2 Bis Nguyễn Văn Cừ Q5', null, 3)
insert into BOTRI values (7,5, N'1Bis Trần Đình Xu Q1', null, null)

select distinct d.TenDoi, tv.HoTen
from DOI d, THANHVIEN tv, BOTRI bt
where bt.DiaChi like N'%Tân Phú%' and d.DoiTruong = tv.IDThanhVien and bt.IDDoi = d.IDDoi and bt.NhiemVu is not null 

select tv.HoTen, count(tv.NgaySinh) numtvdate
from BOTRI bt, THANHVIEN tv
where bt.QuanLi = tv.IDThanhVien and tv.NgaySinh is not null 
group by tv.HoTen
