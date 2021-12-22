# Homework 03
 Bài tập dài 03 - KTLT 
 Chuyển một mã Morse - Text hoặc ngược lại, chuyển một Text thành mã Morse
 
 Cách giải: 
    Khi nhập input, kiếm tra xem input là loại file gì, file morse hay text
    Nếu là morse, chuyển từ morse sang text. 
    Cách làm: Đọc file theo từng dòng, trong từng dòng đó ta sẽ cho một biến chạy từ đầu dòng tới cuối dòng
                khi biến đó di chuyển từ đầu dòng đến cuối dóng, nếu nó là "-" hoặc "." thì sẽ ghi nó thêm vào 
                string, khi gặp khoảng trắng hoặc dấu gạch chéo, kiểm tra xem string đó có những gì, tiến hành 
                chuyển nó sang chữ cái.
                Sau đó reset lại string và cho nó chạy tiếp đến cuối dòng
                Khi chạy đến cuối dòng thì sẽ xuống dòng, làm tương tự với các dòng còn lại ta sẽ thu được kết quả
    Nếu là text: phần này nếu đã làm được bên trên rồi thì rất dễ, chỉ cần đọc từng ký tự, chuyển qua mã morse và
                in ra fie, thêm một dấu cách nữa là xong.
                Do không phân biệt chữ hoa chữ thường nên convert sang kiểu char, +-32 để chuyển đổi qua lại giữa
                2 chữ hoa chữ thường.
    Thuật toán chuyển đổi qua lại giữa 2 mã: Tạo 2 vector, có các mã morse và chữ cái tương ứng, để khi ta lấy được 
                chỉ số của mã morse thì nó cũng chính là chỉ số của chữ cái trong vector chữ cái. Vậy việc chuyển đổi 
                thì sẽ rất đơn giản
Tại sao lại sử dụng C++: C++ hỗ trợ rất mạnh trong việc xử lý chuỗi, cộng chuỗi, so sánh chuỗi bằng thư viện <string>
