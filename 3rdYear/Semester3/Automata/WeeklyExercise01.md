## Automata và Ngôn ngữ hình thức - Weekly Exercise 1

### Giảng viên hướng dẫn: Phạm Trọng Nghĩa, Lê Ngọc Thành

Sinh viên thực hiện: 
MSSV | Họ tên | Email
-|-|-
21127329 | Châu Tấn Kiệt | ctkiet212@clc.fitus.edu.vn

#### 1. Gọi ${A_i} = \{ 1,2,3,..,i \}, i \in Z^+ $. Tìm:
a) ${\bigcap}_{i=1}^n {A_i} = {A_1} \cup {A_2} \cup ... \cup{A_n} = {A_n} = \{1,2,3,..,n \}$

b) $\bigcup_{i=1}^n {A_i} = {A_1} \cap {A_2} \cap ... \cap{A_n} = {A_1} = \{1\}$	

#### 2. Tìm ${{\bigcap}_{i=1}^\infty {A_i}}$, ${\bigcup}_{i=1}^\infty {A_i}$ với mỗi số dương i:

Ta có: $i\in Z^+$ 

a) ${A_i} = \{ -i,-i+1,-i+2,...,-1,0,1,...,i-1,i \}$

${{\bigcup}_{i=1}^\infty {A_i}} = Z$ 

${{\bigcap}_{i=1}^\infty {A_i}} = A_1 = \{ -1,0,1 \} $

b) ${A_i} = \{ -i,i \}$

${{\bigcup}_{i=1}^\infty {A_i}} = \{ -1,1 \} \cup \{ -2,2 \} \cup ... \cup \{-i,i \} = Z \setminus \{0\}$ 

${{\bigcap}_{i=1}^\infty {A_i}} = \{ -1,1 \} \cap \{ -2,2 \} \cap ... \cap \{-i,i \} = \varnothing $

c) ${A_i} = [-i,i]$ là tập của các số thực $r$ thỏa $ -i \leq r \leq i$

${{\bigcup}_{i=1}^\infty {A_i}} = [ -1,1 ] \cup [ -2,2 ] \cup ... \cup [-i,i ] = R$

${{\bigcap}_{i=1}^\infty {A_i}} = [ -1,1 ] \cap [ -2,2 ] \cap ... \cap [-i,i ] = A_1 = [-1,1] $

#### 3. Giả sử A và B là 2 tập con của tập vũ trụ U. Những khả năng nào có thể xảy ra? Giải thích?
a) $2^{(A \cup B)} = 2^A  \cup 2^B (i)$ 

$2^{(A \cup B)} \subset 2^A  \cup 2^B (ii)$

$2^{(A \cup B)} \supset 2^A  \cup 2^B (iii)$

$2^{(A \cup B)}$ bao gồm tất cả tập con của ${(A \cup B)}. $2^A  \cup 2^B$ gồm những phần tử tồn tại hoặc ở A hoặc ở B. Vậy trường hợp (i) đúng chỉ khi $ A \subseteq B $ hoặc $ B \subseteq A $ hoặc $ A = B $. Trường hợp (iii) đúng với mọi A,B và (ii) sai  

b) $2^{(A \cap B)} = 2^A  \cap 2^B (i)$

$2^{(A \cap B)} \subset 2^A  \cap 2^B (ii)$

$2^{(A \cap B)} \supset 2^A  \cap 2^B (iii)$

$2^{(A \cap B)}$ bao gồm tất cả tập con của ${(A \cap B)}$. $2^A  \cap 2^B$ chỉ gồm những phần tử tồn tại ở cả A hoặc ở B. Vậy trường hợp (i) đúng chỉ khi $ A \subseteq B $ hoặc $ B \subseteq A $ hoặc $ A \cap B = \varnothing $. Trường hợp (ii) và (iii) luôn sai vì cần thỏa điều kiện của (i)  

#### 5. Sử dụng quy nạp toán học, chứng minh rằng $\forall n \in N$
$$
\displaystyle\sum_{i=1}^{n} \frac{1}{i(i+1)} = \frac{n}{n+1}
$$

Gọi $S(n)$ là phát biểu:
$$
\displaystyle\sum_{i=1}^{n} \frac{1}{i(i+1)} = \frac{n}{n+1}
$$
Bước cơ sở: Đặt $n_0 = 1$, ta có $S(n_0) =  \frac{1}{2} = \frac{1}{2}$ (đúng)
<br/>
Bước quy nạp:
<br/>
 $$S(n+1) = \sum_{i=1}^{n} \frac{1}{i(i+1)} + \frac{1}{(n+1)(n+2)} = \frac{n}{n+1} + \frac{1}{(n+1)(n+2)} =\ 
\frac{n(n+2)+1}{(n+1)(n+2)} = \frac{n^2+2n+1}{(n+1)(n+2)} = \frac{(n+1)^2}{(n+1)(n+2)} = \frac{n+1}{n+2}$$

Vậy $S(n+1)$ đúng -> $S(n)$ đúng

#### 6. Sử dụng quy nạp toán học, chứng minh rằng $\forall n \in Z^+$
$$
\displaystyle\sum_{i=1}^{n} \frac{2}{3^i} = 1 - \frac{1}{3^n}$$

Gọi $S(n)$ là phát biểu:
$$
\displaystyle\sum_{i=1}^{n} \frac{2}{3^i} = 1 - \frac{1}{3^n}
$$

Bước cơ sở: Đặt $n_0 = 1$, ta có $S(n_0) =  \frac{2}{3} = \frac{2}{3}$ (đúng)

Bước quy nạp:
<br/>
 $$S(n+1) = \sum_{i=1}^{n} \frac{2}{3^i} + \frac{2}{3^{n+1}} = 1 - \frac{3}{3^{n+1}} + \frac{2}{3^{n+1}} = 1 - \frac{1}{3^{n+1}}$$

Vậy $S(n+1)$ đúng -> $S(n)$ đúng
#### 7. Sử dụng quy nạp toán học, chứng minh rằng $\forall n \in Z^+$

$$
\displaystyle\sum_{i=1}^{n} i2^i = (n-1)2^{n+1} + 2
$$

Gọi $S(n)$ là phát biểu:
$$
\displaystyle\sum_{i=1}^{n} i2^i = (n-1)2^{n+1} + 2
$$

Bước cơ sở: Đặt $n_0 = 1$, ta có $S(n_0) = 2 = 2$ (đúng)

Bước quy nạp:
<br/>
 $$S(n+1) = \sum_{i=1}^{n} i2^i + n2^{n+2} + 2 = (n-1)2^{n+1} +  (n+1).2^{n+1} + 2 =  2n.2^{n+1} + 2 = n.2^{n+2} +2  $$

Vậy $S(n+1)$ đúng -> $S(n)$ đúng

#### 8. Sử dụng quy nạp toán học, chứng minh rằng $2^n > n^3$ khi $n$ là số nguyên lớn hơn 9
Gọi $S(n)$ là phát biểu:
$2^n > n^3$ khi $n$ là số nguyên lớn hơn 9
<br/>
Bước cơ sở: Đặt $n_0 = 10$, ta có $S(n_0) = 1024 > 1000$ (đúng)
<br/>
Bước quy nạp:
 $$ S(n+1) = 2^{n+1} \geq 2n^3 = n^3 + n^3 = n^3 + n.n^2 = n^3 + 10n^2 = n^3 + 3n^2 + 3n^2 + 4n^2 \geq
 (n+1)^3$$

Vậy $S(n+1)$ đúng -> $S(n)$ đúng

#### 9. Với những số tự nhiên n nào thì $2n + 3 \leq 2^n$
Gọi $S(n)$ là phát biểu:
$2n + 3 \leq 2^n$
<br/>
Bước cơ sở: Đặt $n_0 = 4 $, ta có 11 < 16 (đúng)
<br/>
Bước quy nạp:
$$
S(n+1) = 2(n+1) + 3 < 2^{n+1} = 2n+3+ 2 < 2^n + 2^n
$$
Có: $2 < 2^n $ với $n=4$.
Vậy $S(n+1)$ đúng -> $S(n)$ đúng.
<br/>
Kết luận: Với $n \geq 4$ thì $2^n > n^3$

#### 12. Gọi $\mathcal L = \{ w \in  \{a, b\}^*: |w| \equiv_3 0 \}$. Liệt kê 10 chuỗi đầu tiên theo thứ tự chuẩn tắc của ngôn ngữ $\mathcal L$
Tập các chuỗi ${ w \in  \{a, b\}^*}$ và $|w|$ chia hết cho 3 gồm:
$\{ \epsilon, aaa, aab, aba, abb, baa, bab, bba, bbb, aaaaaa \}$

#### 13. Cho bảng chữ cái $\Sigma = \{ a,b\}$. Hãy đưa ra lời mô tả ngắn gọn cho mỗi ngôn ngữ $\mathcal L$ sau:
a) $\mathcal L$ là ngôn ngữ gồm các chuỗi $w$ có đặc điểm chỉ chứa duy nhất một tiền tố kết thúc bằng ký tự $a$
<br/>
-> Có thể hiểu là các chuỗi $w$ này chỉ có 1 ký tự $a$:
<br/>
-> $\mathcal L = \{  w \in  \{a, b\}^* \mid |w|_a = 1 \}$ 

b) $\mathcal L$ là ngôn ngữ gồm các chuỗi $w$ có đặc điểm mọi tiền tố khác rỗng của nó đều kết thúc bằng ký tự $a$
<br/>
-> Có thể hiểu là các chuỗi $w$ chứa toàn bộ là ký tự $a$
<br/>
-> $\mathcal L = \{  w \in  \{a, b\}^* \mid |w|_a = |w| \}$ 

#### 14. Hãy cho biết mỗi phát biểu sau là đúng hay sai cùng lời giải thích ngắn gọn
- Ở đây em chọn 5 câu: a,b,c,d,e

a) $\forall \mathcal L: (\mathcal L^+)^+ = \mathcal L^+ $ : Đúng
<br/> 
Vì $(\mathcal L^+)^+ = (\mathcal L^1 \cup \mathcal L^2 \cup \mathcal L^3 \cup ....)^+ = \mathcal L^+ $
<br/> 

b) $\forall \mathcal L: (\mathcal L^*)^+ = (\mathcal L^+)^* $ : Sai
<br/>
Vì $(\mathcal L^*)^+$ không bao gồm chuỗi rỗng $\epsilon$ và $(\mathcal L^+)^* $ có bao gồm chuỗi rỗng $\epsilon$
<br/> 

c) $\forall \mathcal L: \mathcal L^* = \mathcal L^+ \cup \varnothing $: Sai
<br/>
Vì $\mathcal L^* = \mathcal L^+ \cup \mathcal L^0 = \mathcal L^+ \cup \epsilon$ và $ \epsilon \neq \varnothing $
 <br/> 

d) $\forall \mathcal L: \mathcal L^*\mathcal L = \mathcal L^+ $ : Sai
<br/>
Vì tồn tại $\mathcal L =\{\epsilon \} \rightarrow \mathcal L^* \neq \mathcal L^+ $
 <br/> 

e) $\forall \mathcal L_1,\mathcal L_2: (\mathcal L_1\mathcal L_2)^* = \mathcal L_1^*\mathcal L_2^*$
<br/>
Vì $(\mathcal L_1\mathcal L_2)^* = \{s: s \in (\mathcal L_1 \mathcal L_2)^* \} $
và $\mathcal L_1^*\mathcal L_2^* = \{st: s \in \mathcal L_1^*  \wedge t \in \mathcal L_2^* \}$

<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>