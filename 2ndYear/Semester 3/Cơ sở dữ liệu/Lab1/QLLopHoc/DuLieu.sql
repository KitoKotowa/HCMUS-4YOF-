USE [QLLopHoc]
GO
/****** Object:  Table [dbo].[GIAOVIEN]    Script Date: 6/7/2023 11:12:09 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GIAOVIEN](
	[magv] [nchar](10) NOT NULL,
	[hoten] [nvarchar](50) NULL,
	[gioitinh] [int] NULL,
	[ngaysinh] [date] NULL,
	[diachi] [nvarchar](50) NULL,
 CONSTRAINT [PK_GIAOVIEN] PRIMARY KEY CLUSTERED 
(
	[magv] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[HOCSINH]    Script Date: 6/7/2023 11:12:09 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[HOCSINH](
	[mahs] [nchar](10) NOT NULL,
	[hoten] [nvarchar](50) NULL,
	[gioitinh] [int] NULL,
	[ngaysinh] [date] NULL,
	[diachi] [nvarchar](50) NULL,
	[malop] [nchar](10) NULL,
 CONSTRAINT [PK_HOCSINH] PRIMARY KEY CLUSTERED 
(
	[mahs] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[LOPHOC]    Script Date: 6/7/2023 11:12:09 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LOPHOC](
	[malop] [nchar](10) NOT NULL,
	[tenlop] [nchar](10) NULL,
	[nam] [int] NULL,
	[gvcn] [nchar](10) NULL,
	[lop_tr] [nchar](10) NULL,
 CONSTRAINT [PK_LOPHOC] PRIMARY KEY CLUSTERED 
(
	[malop] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[GIAOVIEN] ([magv], [hoten], [gioitinh], [ngaysinh], [diachi]) VALUES (N'GV1       ', N'Nguyễn Văn A', 1, CAST(N'2001-01-01' AS Date), N'Địa chỉ 1')
INSERT [dbo].[GIAOVIEN] ([magv], [hoten], [gioitinh], [ngaysinh], [diachi]) VALUES (N'GV2       ', N'Lê Văn B', 1, CAST(N'2002-02-02' AS Date), N'Địa chỉ 2')
INSERT [dbo].[GIAOVIEN] ([magv], [hoten], [gioitinh], [ngaysinh], [diachi]) VALUES (N'GV3       ', N'Bùi Thị C', 0, CAST(N'2003-03-03' AS Date), N'Địa chỉ 3')
INSERT [dbo].[GIAOVIEN] ([magv], [hoten], [gioitinh], [ngaysinh], [diachi]) VALUES (N'GV4       ', N'Phùng Khắc D', 1, CAST(N'2004-04-04' AS Date), N'Địa chỉ 4')
INSERT [dbo].[GIAOVIEN] ([magv], [hoten], [gioitinh], [ngaysinh], [diachi]) VALUES (N'GV5       ', N'Võ Văn V', 0, CAST(N'2005-05-05' AS Date), N'Địa chỉ 5')
GO
INSERT [dbo].[HOCSINH] ([mahs], [hoten], [gioitinh], [ngaysinh], [diachi], [malop]) VALUES (N'HS1       ', N'Nguyễn Thị E', 0, CAST(N'2001-01-01' AS Date), N'Nhà 1', N'L1        ')
INSERT [dbo].[HOCSINH] ([mahs], [hoten], [gioitinh], [ngaysinh], [diachi], [malop]) VALUES (N'HS2       ', N'Bò Thị Heo', 1, CAST(N'2007-05-06' AS Date), N'Nhà 2', N'L2        ')
INSERT [dbo].[HOCSINH] ([mahs], [hoten], [gioitinh], [ngaysinh], [diachi], [malop]) VALUES (N'HS3       ', N'Lê Nguyễn T', 1, CAST(N'2002-01-01' AS Date), N'Nhà 3', N'L3        ')
INSERT [dbo].[HOCSINH] ([mahs], [hoten], [gioitinh], [ngaysinh], [diachi], [malop]) VALUES (N'HS4       ', N'Lý Nhật H', 0, CAST(N'2009-02-08' AS Date), N'Nhà 4', N'L4        ')
INSERT [dbo].[HOCSINH] ([mahs], [hoten], [gioitinh], [ngaysinh], [diachi], [malop]) VALUES (N'HS5       ', N'Châu Quang C', 1, CAST(N'1968-05-03' AS Date), N'Nhà 5', N'L5        ')
GO
INSERT [dbo].[LOPHOC] ([malop], [tenlop], [nam], [gvcn], [lop_tr]) VALUES (N'L1        ', N'A1        ', 2023, N'GV1       ', N'HS1       ')
INSERT [dbo].[LOPHOC] ([malop], [tenlop], [nam], [gvcn], [lop_tr]) VALUES (N'L2        ', N'A2        ', 2077, N'GV2       ', N'HS2       ')
INSERT [dbo].[LOPHOC] ([malop], [tenlop], [nam], [gvcn], [lop_tr]) VALUES (N'L3        ', N'A3        ', 1996, N'GV3       ', N'HS3       ')
INSERT [dbo].[LOPHOC] ([malop], [tenlop], [nam], [gvcn], [lop_tr]) VALUES (N'L4        ', N'A4        ', 1888, N'GV4       ', N'HS4       ')
INSERT [dbo].[LOPHOC] ([malop], [tenlop], [nam], [gvcn], [lop_tr]) VALUES (N'L5        ', N'A5        ', 1666, N'GV5       ', N'HS5       ')
GO
ALTER TABLE [dbo].[HOCSINH]  WITH CHECK ADD  CONSTRAINT [FK_HOCSINH_LOPHOC] FOREIGN KEY([malop])
REFERENCES [dbo].[LOPHOC] ([malop])
GO
ALTER TABLE [dbo].[HOCSINH] CHECK CONSTRAINT [FK_HOCSINH_LOPHOC]
GO
ALTER TABLE [dbo].[LOPHOC]  WITH CHECK ADD  CONSTRAINT [FK_LOPHOC_GIAOVIEN] FOREIGN KEY([gvcn])
REFERENCES [dbo].[GIAOVIEN] ([magv])
GO
ALTER TABLE [dbo].[LOPHOC] CHECK CONSTRAINT [FK_LOPHOC_GIAOVIEN]
GO
ALTER TABLE [dbo].[LOPHOC]  WITH CHECK ADD  CONSTRAINT [FK_LOPHOC_HOCSINH] FOREIGN KEY([lop_tr])
REFERENCES [dbo].[HOCSINH] ([mahs])
GO
ALTER TABLE [dbo].[LOPHOC] CHECK CONSTRAINT [FK_LOPHOC_HOCSINH]
GO
