use QLDT1
go

--Cau 58
select distinct gv.HOTEN, count(distinct c.MACD) SoChuDe
from GIAOVIEN gv, THAMGIADT t, CHUDE c, DETAI d
where t.MAGV = gv.MAGV and d.MACD = c.MACD and t.MADT = d.MADT
group by gv.HOTEN
having count(distinct d.MACD) = (select count(c.MACD)
									from chude c)



--Cau 59
select TENDT
from DETAI d
where d.MADT in (select d.MADT
				 from DETAI d
				 where not exists(select gv.MAGV 
							      from GIAOVIEN gv 
								  where gv.MABM = 'HTTT'
								 except
								 select t.MAGV 
								 from THAMGIADT t 
								 where d.MADT = t.MADT))
								

--Cau 60
select TENDT
from DETAI d
where d.MADT in (select d.MADT
				 from DETAI d
				 where not exists(select gv.MAGV 
							      from GIAOVIEN gv, BOMON bm
								  where gv.MABM = bm.MABM and bm.TENBM = N'Hệ thống thông tin'
								 except
								 select t.MAGV 
								 from THAMGIADT t 
								 where d.MADT = t.MADT))

--Cau 61
select distinct gv.HOTEN
from GIAOVIEN gv, THAMGIADT t
where gv.MAGV = t.MAGV and
not exists (select d.MADT
				 from DETAI d, THAMGIADT t
				 where d.MADT = t.MADT and d.MACD != 'QLGD' and gv.MAGV = t.MAGV)

--Cau 62
select distinct gv.HOTEN
from THAMGIADT t, GIAOVIEN gv
where t.MAGV = gv.MAGV
and t.MADT in (select t2.MADT 
				from THAMGIADT t2, GIAOVIEN tth
				where t2.MAGV = tth.MAGV 
				and tth.HOTEN =  N'Trần Trà Hương' )
except select gv1.HOTEN
from GIAOVIEN gv1
where gv1.HOTEN =  N'Trần Trà Hương'


--Cau 63		
select d.MADT, d.TENDT
from DETAI d
where d.MADT in(select d.MADT
				from DETAI d
				where not exists (select gv.MAGV
								  from GIAOVIEN gv where gv.MABM = 'HTTT'
except
select t.MAGV
from THAMGIADT t
where t.MADT = d.MADT))

--Cau 64
select gv.MAGV, gv.HOTEN
from GIAOVIEN gv
where not exists ((select cv.MADT, cv.SOTT
				  from CONGVIEC cv 
				  where cv.MADT = '006')
				  except
				  (select t.MADT, t.STT
				  from GIAOVIEN gv2, THAMGIADT t
				  where t.MADT = '006' and gv2.MAGV = t.MAGV
				        and gv2.MAGV = gv.MAGV)
						)
				  

--Cau 65
select gv.MAGV, gv.HOTEN
from GIAOVIEN gv
where not exists ((select d.MADT
				 from DETAI d, CHUDE c
				 where  d.MACD = c.MACD 
				 and c.TENCD = N'Ứng dụng công nghệ')
				  except
				  (select d.MADT
				 from DETAI d, THAMGIADT t, CHUDE c
				 where d.MADT = t.MADT 
				 and d.MACD = c.MACD 
				 and c.TENCD = N'Ứng dụng công nghệ' )
				)
--Cau 66
select distinct gv.HOTEN
from GIAOVIEN gv
where not exists ((select d.MADT
				  from GIAOVIEN tth, DETAI d
				where d.GVCNDT = tth.MAGV
				and tth.HOTEN =  N'Trần Trà Hương')
				except 
				(select t.MADT
				from THAMGIADT t
				where t.MAGV = gv.MAGV)
				)

--Cau 67
select TENDT
from DETAI d
where d.MADT in (select d.MADT
				 from DETAI d
				 where not exists(select gv.MAGV 
							      from GIAOVIEN gv, KHOA k, BOMON bm
								  where gv.MABM = bm.MABM and bm.MAKHOA = k.MAKHOA
								  and k.MAKHOA = 'SH'
								 except
								 select t.MAGV 
								 from THAMGIADT t 
								 where d.MADT = t.MADT))
--Cau 68
select gv.MAGV, gv.HOTEN
from GIAOVIEN gv
where not exists ((select cv.MADT, cv.SOTT
				  from CONGVIEC cv, DETAI d
				  where cv.MADT = d.MADT and d.TENDT = N'Nghiên cứu tế bào gốc')
				  except
				  (select t.MADT, t.STT
				  from GIAOVIEN gv2, THAMGIADT t, DETAI d
				  where t.MADT = d.MADT and d.TENDT = N'Nghiên cứu tế bào gốc' and gv2.MAGV = t.MAGV
				        and gv2.MAGV = gv.MAGV)
						)

--Cau 69
select distinct gv.HOTEN
from GIAOVIEN gv
where gv.MAGV in (select gv.MAGV 
				  from GIAOVIEN gv
				  where not exists (select d.MADT
									from DETAI d
									where d.KINHPHI >= 100.0
									except
									select t.MADT
									from THAMGIADT t
									where t.MAGV = gv.MAGV)
									)

--Cau 70
select TENDT
from DETAI d
where d.MADT in (select d.MADT
				 from DETAI d
				 where not exists(select gv.MAGV 
							      from GIAOVIEN gv, KHOA k, BOMON bm
								  where gv.MABM = bm.MABM and bm.MAKHOA = k.MAKHOA
								  and k.MAKHOA = 'SH'
								 except
								 select t.MAGV 
								 from THAMGIADT t 
								 where d.MADT = t.MADT))

--Cau 71
select gv.MAGV, gv.HOTEN, gv.NGSINH
from GIAOVIEN gv
where gv.MAGV in ((select cv.MADT
				  from CONGVIEC cv, DETAI d 
				  where cv.MADT = d.MADT and d.TENDT = N'Ứng dụng hóa học xanh')
				  except
				  (select t.MADT
				  from GIAOVIEN gv2, THAMGIADT t, DETAI d
				  where t.MADT = d.MADT)
						)

--Cau 72
select gv.MAGV, gv.HOTEN,bm.TENBM,  gv2.HOTEN
from GIAOVIEN gv, GIAOVIEN gv2, BOMON bm
where gv.GVQLCM = gv2.MAGV and gv.MABM = bm.MABM
and not exists ((select d.MADT
				 from DETAI d, CHUDE c
				 where  d.MACD = c.MACD 
				 and c.TENCD = N'Nghiên cứu phát triển')
				  except
				  (select d.MADT
				 from DETAI d, THAMGIADT t, CHUDE c
				 where d.MADT = t.MADT 
				 and d.MACD = c.MACD 
				 and c.TENCD = N'Nghiên cứu phát triển' )
				)
