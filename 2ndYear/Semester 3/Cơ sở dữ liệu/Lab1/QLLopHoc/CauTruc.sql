USE [QLLopHoc]
GO
/****** Object:  Table [dbo].[GIAOVIEN]    Script Date: 6/7/2023 11:08:27 AM ******/
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
/****** Object:  Table [dbo].[HOCSINH]    Script Date: 6/7/2023 11:08:27 AM ******/
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
/****** Object:  Table [dbo].[LOPHOC]    Script Date: 6/7/2023 11:08:27 AM ******/
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
