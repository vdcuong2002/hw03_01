/*
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
Trong chương trình, có sử dụng một số hàm sleep, tổng thời gian sleep là 1.8 giây
*/
#include <iostream>                                                 // Vào ra cơ bản
#include <vector>                                                   // Xử lý vector
#include <string>                                                   // Xử lý chuỗi
#include <fstream>                                                  // Xử lý file
#include <windows.h>                                                // Xử lý các lệnh của cửa sổ Console
// BẢNG MÀU CHO CONSOLE ////////////////////////////////////////////////////////////////////////////////////////////////
#define RED         12                                              // Màu đỏ
#define PURPLE      13                                              // Màu tím
#define WHITE       7                                               // Màu xám 
// CÁC HÀM CON /////////////////////////////////////////////////////////////////////////////////////////////////////////
int letter2morse(std::string letter);                               // Chuyển đổi 1 ký tự sang mã morse
int morse2letter(std::string morse);                                // Chuyển đổi 1 mã morse sang ký tự
void printERROR();                                                  // Hàm in ra dòng chữ ERROR màu đỏ
// BẢNG MÃ MORSE ////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::string>Morses {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
                   "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
                   "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", 
                   ".....", "-....", "--...", "---..", "----.", "-----", "--..--", "/",
                   ".-.-.-", "..--..", "-....-", "---...", "........"};
// BẢNG MÃ TEXT /////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::string>Letters {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
                    "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
                    "u", "v", "w", "x", "y", "z", "1", "2", "3", "4",
                    "5", "6", "7", "8", "9", "0", ",", " ",
                    ".", "?", "-", ":", "#"};
        // Lưu ý khi xây dựng bảng mã: Sẽ ưu tiên duyệt từ chữ cái duyệt xuống đến các chứ số ở sau. Bởi
        // trong bảng mã ASCII thì số đừng trước.
        // VD minh họa: Nếu để chữ số lên trước trong vector, khi có mã "P" = 80 ASCII, khi duyệt đến số "0" = 48
        // thì sẽ bị lỗi ở phần chuyển từ Letter -> Morse do trong hàm có phần kiểm tra chữ hoa chữ thường, trong 
        // chữ thường = chữ hoa + 32, thể nên duyệt đến số là sẽ bị hỏng ngay lập tức. Và lưu ý khi duyệt, nếu gặp
        // được chữ/số trùng thì phải out ra luôn, không được duyệt tiếp kẻo gặp phải sai sót
        // KHI MỞ RỘNG THÊM MÃ, PHẢI LƯU Ý, CHỈNH SỬA LẠI HÀM "letter2morse()", NẾU KHÔNG, CÓ THỂ SẼ BỊ GẶP LỖI
// HÀM MAIN /////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int number_of_input, char *command[])
{
// KIỂM TRA SỐ LƯỢNG ĐỐI SỐ TRUYỂN VÀO TỪ COMMAND LINE /////////////////////////////////////////////////////////////////
    if (number_of_input != 3)
    {                                                               // Kiểm tra lượng đối số đã đủ chưa
        printERROR();
        (number_of_input < 3)? std::cout << "not enough arguments! Please re-enter!" : std::cout << "too many arguments! Please re-enter!" ;
        exit(0);                                                    // Exit nếu số lượng đối số sai
    }
// CHECK FILE OUTPUT CÓ TỒN TẠI HAY KHÔNG //////////////////////////////////////////////////////////////////////////////
    std::ifstream check(command[2]);                                // Mở thử file output ở chế độ đọc
    if (check.is_open())                                            // Nếu mở được thì chứng tỏ file đã tồn tại
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PURPLE);
        std::cout << "Warning: ";                                   // In phần chữ Warning màu tím
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
        std::cout << "\"" << command[2] << "\"" << " already exists. Do you wish to overwrite (y,n)? ";
        std::string s;                                              
        std::cin >> s;                                              // Đọc y/n
        if (s == "n")                                               // Nếu nhập vào "n", thì exit khỏi chương trình
            exit(0);                                                // Còn không thì chạy tiếp, và sẽ đóng file lại
    }
    check.close();                                                  // Đóng file check
// MỞ FILE VÀ BẮT ĐẦU LÀM VIỆC //////////////////////////////////////////////////////////////////////////////////////////    
    std::ifstream input(command[1]);                                // Mở file input
    std::ofstream output(command[2]);                               // Mở file output
    std::string str;                                                // str để đọc file
    if (!input.is_open())                                           // Nếu file không mở được thì thông báo lỗi
    {
        printERROR();
        std::cout << "\"" << command[1] << "\" could not be opened!" << std::endl;
        exit(0);                                                    // Thoát chương trình nếu không mở được
    }
    if (!output.is_open())
    {
        printERROR();
        std::cout << "\"" << command[2] << "\" could not be opened!" << std::endl;
        exit(0);                                                    // Thoát chương trình nếu không mở được
    }
    
// CHECK FILE DẠNG MORSE HAY TEXT ///////////////////////////////////////////////////////////////////////////////////////
    int type = 0;                                                   // Type bằng 0 thì là Morse code, bằng 1 thì là file text
    while (std::getline (input,str))                                // Đọc từng dòng của file input
    {
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] != '-' && str[i] != '.' && str[i] != '/' && str[i] != ' ')
                type = 1;                                           // Gặp ký tự khác những ký tự mose thì sẽ cho type  = 1
                break;                                              // Break vòng for để tránh lãng phí thời gian
        }
    }

// THỦ TỤC ĐÓNG MỞ LẠI FILE VÀ TRÌNH BÀY /////////////////////////////////////////////////////////////////////////////////
    input.close();                                                  // Đóng file input
    input.open(command[1]);                                         // Đóng mở file để di chuyển con trỏ lên đầu

    std::cout << "--------------------" << std::endl;               // Thủ tục trình bày
    std::cout << (char)175 << " \"" << command[1] << "\" is a ";
    (type == 0) ? std::cout << "MORSE CODE " : std::cout << "TEXT "; 
    std::cout << "file!" << std::endl << std::endl;
    std::cout << (char)175 << " Please wait a minute . . ." << std::endl << std::endl;
    for (int i = 0; i <= 30; i++)                                   // Tạo một bar loading 
        std::cout << (char)176;                                     // Mã ASCII 176, tạo bar
    std::cout << "\r";                                              // Lùi về đầu dòng
    for (int i = 0; i <= 30; i++)                                   // Bắt đầu chạy loading
    {
        std::cout << (char)219;                                     // ASCII 219 là ô vuông tô kín
        Sleep(33.3);                                                // Delay 1000/30 giây                       
    }
    Sleep(400);                                                     
    std::cout << "\t" << (char)175 << " Convert done!" << std::endl << std::endl;
    Sleep(400);                                                     // Tổng thời gian sleep, 1.8 giây
// NẾU FILE LÀ MOURSE FILE, CẦN CHUYỂN THÀNH TEXT ///////////////////////////////////////////////////////////////////////////
    if (type == 0)
    {   
        int count_line = 1;                                         // Biến đếm dòng   
        while (getline(input, str))                                 // Tách line
        {
            str = str + " ";                                        // Xử lý trước khi tính toán để tránh lỗi, lỗi này phát sinh trong quá trình test  
            std::string this_vocub = "";                            // Chữ hiện tại để duyệt, sau mỗi lần xuất sẽ reset lại
            for (int i = 0; i < str.length(); i++)
            {
                if (str[i] == '.' || str[i] == '-')                 // Nếu là ký tự "." hoặc "-"
                    this_vocub = this_vocub + str[i];               // Thêm ký tự hiện tại vào chuỗi
                
                if (str[i] == ' ' || str[i] == '/')                 // Nấu là dấu cách, phân chia 2 từ
                {   
                    if (this_vocub != "")                       
                    {
                        int num = morse2letter(this_vocub);         // Convert sang letter
                        if (num == -1) 
                        {
                            output << "*";                          // Ký tự mã Morse không xác định, in ra thông báo lỗi
                            printERROR();                           // Xuất lỗi
                            std::cout << "Invalid Morse " << this_vocub << " on line " << count_line << std::endl ;
                        }
                        else output << Letters[num];                // Khi gặp dấu " ", dừng việc ghi chuỗi, giải phóng ra file output 
                    }
                this_vocub = "";                                    // Reset lại chữ hiện tại
                if (str[i] == '/') output << " ";                   // Với dấu "/" thì sẽ cách ra 1 khoảng trắc
                }
            }
            output << std::endl;                                    // Sau mỗi line sẽ thực hiện việc xuống dòng
            count_line ++;                                          // Đếm dòng tăng 1.
        }
    }

// NẾU FILE LÀ TEXT FILE, CẦN CHUYỂN THÀNH MORSE  ////////////////////////////////////////////////////////////////////////////
    if (type == 1)
    {
        int count_line = 1;    
        while (std::getline (input,str))                            // Đọc từng dòng của file input
        {
            for (int i = 0; i < str.size(); i++)
            {
                std::string letter;                                 // Biến letter ở dạng string
                letter.push_back(str[i]);                           // Chuyển đổi từ char về string
                int num = letter2morse(letter);
                if (num == -1 || num == Letters.size() - 1)         // Thông báo lỗi và bỏ qua ký tự này
                {
                    printERROR();                                   // Xuất chữ ERROR màu đỏ
                    std::cout << "Unrecognised character " << letter << " on line " << count_line <<std::endl;
                }
                else output << Morses[num] + " ";                   // Chép ký tự đã chuyển đổi lên file output
            }
            output << "\n";                                         // Xuống dòng sau mỗi lần getline
            count_line ++;                                          // Biến đêm tăng lên 1 đơn vị
        }
    }
// THỦ TỤC TRÌNH BÀY ////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "--------------------" << std::endl;
    std::cout << (char)175 << " Open \"" << command[2] << "\" to see the result!" << std::endl;

// ĐÓNG CÁC FILE SAU KHI SỬ DỤNG ///////////////////////////////////////////////////////////////////////////////////////////
    input.close();                                                  // Đóng file input
    output.close();                                                 // Đóng file output
    std::cout << (char)175 << " ";                                      
    system("pause");                                                // Kết thúc chương trình, nhấn để đóng
//    system(command[2]);                                             // Mở file txt
}

// SOURCE HÀM CON /////////////////////////////////////////////////////////////////////////////////////////////////////////
int letter2morse(std::string letter)                                // Trả về số thứ tự của leter trong vector đã khởi tạo ban đầu
{
    int temp = -1;                                                  // Nếu không tồn tại ký tự, trả về kết quả là -1
    for (int i = 0; i < Letters.size(); i++)
    {
        char x = letter.at(0);                                      // Chuyển về dạng char để so sánh cho tiện
        std::string s = Letters[i];
        char y = s.at(0);
        if ((x == y || x == y - 32))                                // So sánh chuỗi trong C++, có phân biệt chứ hoa, chữ thường
        {                                                           // KHI MỞ RỘNG THÊM CÁC MÃ, PHẢI LƯU Ý PHẦN NÀY
            temp = i;
            break;                                                  // Nếu tìm được thì break ra khỏi vòng for để tiết kiệm thời gian
        }
    }
    return temp;
}

int morse2letter(std::string morse)                                 // Trả về số thứ tự của morse code trong vector bên trên
{                                                                   // về cơ bản thì code giống phần bên trên
    int temp = -1;                                                  // Trả về -1 nếu không tồn tại ký tự giống
    for (int i = 0; i < Morses.size(); i++)                         // Duyệt từ đâu đến cuối vector Morse
    {
        if (morse == Morses[i])                                     // So sánh chuỗi trong C++
        {
            temp = i;                                               // Trả về kết quả là số thứ tự tương ứng
            break;                                                  // Break luôn, giảm thời gian, và hạn chế lỗi chương trình
        }
    }
    return temp;
}

void printERROR()                                                   // Hàm in chữ ERROR với màu đỏ
{
    HANDLE hConsole;                                                // Xuất chữ ERROR màu đỏ ra ngoài Console
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, RED);                         // Chỉnh màu console sang đỏ
    std::cout << "ERROR: ";                                         // In
    SetConsoleTextAttribute(hConsole, WHITE);                       // Chỉnh màu console sang trắng, reset lại màu console
}
// END -----------------------------------------------------------------------------------------------------------------