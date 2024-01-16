use master
create database DT4
go
use DT4
go

--use master drop database DT4
create table GIAOVIEN (
	IDKhoa int,
	IDMaGV char(10),
	HoTen nchar(50),
	SoCMND char(10),
	NgaySinh datetime,
	IDQuanLi char(10)
		
	PRIMARY KEY(IDKhoa, IDMaGV)
); 

create table LOPHOC (
	IDLop char(10),
	NamBD int,
	ChuNhiem char(10),
	IDKhoa int
	
	PRIMARY KEY(IDLop)
);

create table LICHDAY (
	IDLop char(10),
	IDThuTiet nchar(50),
	IDPhongHoc int,
	GiaoVien char(10),
	IDKhoa int,
	ThoiLuong int,
	ThietBi nchar(50)

	PRIMARY KEY(IDLop, IDThuTiet, IDPhongHoc)
);

alter table GIAOVIEN add
	constraint FK_GIAOVIEN_GIAOVIEN foreign key (IDKhoa, IDQuanLi) references GIAOVIEN(IDKhoa, IDMaGV)
alter table LOPHOC add
	constraint FK_LOPHOC_GIAOVIEN foreign key (IDKhoa,ChuNhiem) references GIAOVIEN(IDKhoa,IDMaGV)

alter table LICHDAY add
	constraint FK_LICHDAY_GIAOVIEN foreign key (IDKhoa,GiaoVien) references GIAOVIEN(IDKhoa,IDMaGV),
	constraint FK_LICHDAY_LOPHOC foreign key (IDLop) references LOPHOC(IDLop)

set dateformat dmy
insert into GIAOVIEN values(1,'1716', N'Nguyễn Quan Tùng', '240674018', '1/2/1988', null)
insert into GIAOVIEN values(2,'0357', N'Lưu Phi Nam', '240674027', '20/7/1980', null)
insert into GIAOVIEN values(2,'1716', N'Lê Quang Bảo', '240674063', null, null)
insert into GIAOVIEN values(1,'0753', N'Hà Ngọc Thúy', '240674504', '2/5/1990', null)
insert into GIAOVIEN values(1,'0357', N'Trương Thị Minh', '240674405', null, null)
insert into GIAOVIEN values(1,'1718', N'Ngô Thị Thùy', '240674306', null, null)

insert into LOPHOC values('L01', 2015, '0357', 2)
insert into LOPHOC values('L02', 2013, '1716', 1)

insert into LICHDAY values ('L01', 'T2(1-6)',2, '1718',1,10, null)
insert into LICHDAY values ('L02','T2(7-12)',1, '0753', 1, 30, null)
insert into LICHDAY values ('L01','T4(4-6)',5, '0357',2, 25, null)

update GIAOVIEN set IDQuanLi = '0753' where IDKhoa = 1 and IDMaGV ='1716'
update GIAOVIEN set IDQuanLi = '1716' where IDKhoa = 2 and IDMaGV ='0357'
update GIAOVIEN set IDQuanLi = '0753' where IDKhoa = 1 and IDMaGV ='0357'
update GIAOVIEN set IDQuanLi = '0357' where IDKhoa = 1 and IDMaGV ='1718'

select distinct gv.hoten, datediff(yy,gv.NgaySinh,getdate()) as Tuoi
from GIAOVIEN gv, LOPHOC l, LICHDAY d 
where l.ChuNhiem = gv.IDMaGV  and l.IDKhoa = gv.IDKhoa and l.IDLop = d.IDLop and d.IDThuTiet like '%6%'

select gv1.hoten TenGV, gv2.HoTen TenQL
from GIAOVIEN gv1, GIAOVIEN gv2
where gv1.IDQuanLi is not null and gv1.IDQuanLi = gv2.IDMaGV and gv2.NgaySinh is null