# # with open("input.txt","rb") as f:
# #     content = f.read()
# #     print(content)


# """
# 196	242	3	881250949
# 186	302	3	891717742
# 196	377	1	878887116
# 244	51	2	880606923
# 166	346	1	886397596
# 186	474	4	884182806
# 186	265	2	881171488
# """
# data = ["196	242	3	881250949",
# "186	302	3	891717742",
# "196	377	1	878887116",
# "244	51	2	880606923",
# "166	346	1	886397596",
# "186	474	4	884182806",
# "186	265	2	881171488"]
# with open("input.txt","wb") as file:
#     for d in data:
#         file.write((d + "\n").encode())

import urllib.request as ur
ur.urlretrieve("https://www.gutenberg.org/cache/epub/20417/pg20417.txt", "pg20417.txt")
ur.urlretrieve("https://www.gutenberg.org/cache/epub/5000/pg5000.txt", "pg5000.txt")
ur.urlretrieve("https://www.gutenberg.org/cache/epub/4300/pg4300.txt", "pg4300.txt")
