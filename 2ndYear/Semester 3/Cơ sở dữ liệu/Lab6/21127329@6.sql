use QLDT1
go

-- Cau 35
select distinct gv.LUONG
from GIAOVIEN gv
where gv.LUONG >= all(select gv1.LUONG
						from GIAOVIEN gv1)

-- Cau 36
select gv.HOTEN, gv.LUONG
from GIAOVIEN gv
where gv.LUONG >= all(select gv1.LUONG
						from GIAOVIEN gv1)
--Cau 37
select distinct gv.LUONG
from GIAOVIEN gv, BOMON bm
where bm.MABM = 'HTTT' and gv.MABM = bm.MABM
	 and gv.LUONG >= all(select gv1.LUONG
						from GIAOVIEN gv1, BOMON bm
						where bm.MABM = 'HTTT' and gv1.MABM = bm.MABM)
--Cau 38
select distinct gv.HOTEN, gv.NGSINH
from GIAOVIEN gv, BOMON bm
where bm.MABM = 'HTTT' and gv.MABM = bm.MABM
	 and gv.NGSINH <= all(select gv1.NGSINH
						from GIAOVIEN gv1, BOMON bm
						where bm.MABM = 'HTTT' and gv1.MABM = bm.MABM)

--Cau 39
select gv.HOTEN, gv.NGSINH
from GIAOVIEN gv, BOMON bm, KHOA k
where gv.MABM = bm.MABM and k.MAKHOA = bm.MAKHOA and k.MAKHOA = 'CNTT'
	 and gv.NGSINH >= all(select gv1.NGSINH
						from GIAOVIEN gv1, BOMON bm, KHOA k
						where gv1.MABM = bm.MABM and k.MAKHOA = bm.MAKHOA and k.MAKHOA = 'CNTT')

--Cau 40
select gv.HOTEN, bm.MAKHOA, k.TENKHOA
from GIAOVIEN gv, BOMON bm, KHOA k
where gv.LUONG >= all(select gv1.LUONG
						from GIAOVIEN gv1)
	and gv.MABM = bm.MABM and bm.MAKHOA = k.MAKHOA

--Cau 41
select *
from GIAOVIEN gv
where gv.LUONG = (select max(LUONG)
				from GIAOVIEN gv1
				where gv1.MABM = gv.MABM)

--Cau 42
select d.TENDT
from DETAI d
where d.MADT not in (select d.MADT
				from THAMGIADT t, DETAI d, GIAOVIEN gv
				where gv.MAGV = t.MAGV and d.MADT = t.MADT and gv.HOTEN = N'Nguyễn Hoài An')

--Cau 43
select d.TENDT, gv.Hoten as Chunhiem
from DETAI d, GIAOVIEN gv
where d.MADT not in (select d.MADT
				from THAMGIADT t, DETAI d, GIAOVIEN gv
				where gv.MAGV = t.MAGV and d.MADT = t.MADT and gv.HOTEN = N'Nguyễn Hoài An')
	 and d.GVCNDT = gv.MAGV

--Cau 44
select gv.hoten, gv.MAGV
from GIAOVIEN gv, BOMON bm
where gv.MAGV not in (select t.MAGV
						from THAMGIADT t)
and gv.MABM = bm.MABM and bm.MAKHOA = 'CNTT'

--Cau 45
select gv.hoten, gv.MAGV
from GIAOVIEN gv
where gv.MAGV not in (select t.MAGV
						from THAMGIADT t)

--Cau 46
select gv.*
from GIAOVIEN gv
where gv.LUONG > (select gv1.LUONG
					from GIAOVIEN gv1
					where gv1.HOTEN = N'Nguyễn Hoài An')

--Cau 47
select gv.*
from GIAOVIEN gv, BOMON bm
where gv.MAGV = bm.TRUONGBM and gv.MAGV in (select t.MAGV
											from THAMGIADT t)

--Cau 48
select *
from GIAOVIEN gv1, GIAOVIEN gv2
where gv1.HOTEN = gv2.HOTEN and gv1.PHAI = gv2.PHAI and gv1.MAGV != gv2.MAGV and gv1.MABM = gv2.MABM

--Cau 49
select gv.*
from GIAOVIEN gv
where gv.LUONG >= ANY(select gv.LUONG
						from GIAOVIEN gv, BOMON bm
						where gv.MABM = bm.MABM and bm.MAKHOA = N'CNTT')

--Cau 50
select gv.*
from GIAOVIEN gv
where gv.LUONG > (select max(gv.LUONG)
						from GIAOVIEN gv, BOMON bm
						where gv.MABM = bm.MABM and bm.MABM = N'HTTT')

--Cau 51
select k.MAKHOA, count(gv.MAGV) as SoGV
from KHOA k,BOMON bm, GIAOVIEN gv
where k.MAKHOA = bm.MAKHOA and gv.MABM = bm.MABM
group by k.MAKHOA
having count(gv.MAGV) >= ALL(select count(gv1.MAGV)
						from KHOA k,BOMON bm, GIAOVIEN gv1
						where k.MAKHOA = bm.MAKHOA and gv1.MABM = bm.MABM
						group by k.MAKHOA)

--Cau 52
select gv.HOTEN, count(d.MADT)
from GIAOVIEN gv, DETAI d
where gv.MAGV = d.GVCNDT
group by gv.HOTEN
having count(d.MADT) >= ALL(select count(d1.MADT)
							from DETAI d1, GIAOVIEN gv1
							where gv1.MAGV = d1.GVCNDT
						group by gv1.HOTEN)
--Cau 53
select bm.MABM, count(gv.MAGV) as SoGV
from BOMON bm, GIAOVIEN gv
where gv.MABM = bm.MABM
group by bm.MABM
having count(gv.MAGV) >= ALL(select count(gv1.MAGV)
						from BOMON bm, GIAOVIEN gv1
						where gv1.MABM = bm.MABM
						group by bm.MABM)

--Cau 54
select gv.HOTEN, bm.TENBM, count(d.MADT) as SoDT
from GIAOVIEN gv, BOMON bm, thamgiadt t, detai d
where gv.MAGV = t.MAGV and t.MADT = d.MADT and gv.MABM = bm.MABM
group by gv.HOTEN, bm.TENBM
having count(d.MADT) >= ALL(select count(d.MADT)
							from GIAOVIEN gv1, THAMGIADT t, DETAI d
							where t.MAGV = gv1.MAGV and t.MADT = d.MADT
							group by gv1.MAGV)

--Cau 55
select gv.HOTEN, bm.TENBM, count(d.MADT) as SoDT
from GIAOVIEN gv, BOMON bm, thamgiadt t, detai d
where gv.MAGV = t.MAGV and t.MADT = d.MADT and gv.MABM = bm.MABM and bm.MABM = 'HTTT'
group by gv.HOTEN, bm.TENBM
having count(d.MADT) >= ALL(select count(d.MADT)
							from GIAOVIEN gv1, THAMGIADT t, DETAI d
							where t.MAGV = gv1.MAGV and t.MADT = d.MADT
							group by gv1.MAGV)

--Cau 56
select gv.HOTEN, bm.TENBM, count(n.MAGV) as SoNT
from NGUOITHAN n, GIAOVIEN gv, BOMON bm
where gv.MAGV = n.MAGV and gv.MABM = bm.MABM
group by gv.HOTEN, bm.TENBM
having count(n.MAGV)  >= ALL(select count(n.MAGV)
							from GIAOVIEN gv1, NGUOITHAN n
							where n.MAGV = gv1.MAGV
							group by gv1.MAGV)

--Cau 57
select gv.HOTEN, count(d.MADT) as SoDT
from GIAOVIEN gv, DETAI d, BOMON bm
where gv.MAGV = d.GVCNDT and gv.MAGV = bm.TRUONGBM
group by gv.HOTEN
having count(d.MADT) >= ALL(select count(d1.MADT)
							from DETAI d1, GIAOVIEN gv1
							where gv1.MAGV = d1.GVCNDT
						group by gv1.HOTEN)