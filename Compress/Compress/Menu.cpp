#include "Huffman.h"
#include "Folder.h"
#include "Image.h"
#include "Menu.h"


using namespace std;

void Menu::ZoomConsole() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

}


void Menu::Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void Menu::_Menu() {

	cout << space << " ______________________________________________" << endl;
	cout << space << "| STT |" << setw(23) << "CHUC NANG" << setw(18) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << space << "|  0  | Thoat khoi chuong trinh" << setw(17) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << space << "|  1  | Nen du lieu" << setw(29) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << space << "|  2  | Giai nen du lieu " << setw(23) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << endl << space << "Lua chon cua ban: ";
}

void Menu::_Menu_compress() {

	cout << space << " ______________________________________________" << endl;
	cout << space << "| STT |" << setw(23) << "CHUC NANG" << setw(18) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << space << "|  0  | Thoat khoi chuong trinh" << setw(17) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << space << "|  1  | Quay ve menu chinh" << setw(22) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << space << "|  2  | Nen 1 file " << setw(29) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << space << "|  3  | Nen 1 anh bitmap " << setw(23) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << space << "|  4  | Nen 1 thu muc" << setw(27) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << endl << space << "Lua chon cua ban: ";
}

void Menu::_Menu_decompress() {

	cout << space << " ______________________________________________" << endl;
	cout << space << "| STT |" << setw(23) << "CHUC NANG" << setw(18) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << space << "|  0  | Thoat khoi chuong trinh" << setw(17) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << space << "|  1  | Quay ve menu chinh" << setw(22) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << space << "|  2  | Giai nen 1 file" << setw(25) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << space << "|  3  | Giai nen 1 anh bitmap" << setw(19) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << space << "|  4  | Giai nen 1 thu muc" << setw(22) << "|" << endl;
	cout << space << "|_____|________________________________________|" << endl;
	cout << endl << space << "Lua chon cua ban: ";
}

void Menu::Select() {

	_Menu();
	int _choice_main;
	cin >> _choice_main;
	
	while (_choice_main != 0) {
		switch (_choice_main) {

		case 1: {
			system("cls");
			cout << endl << endl << endl;
			_Menu_compress();

			int _choice_compress;
			fflush(stdin);
			cin >> _choice_compress;

			while (_choice_compress != 1) {

				switch (_choice_compress) {

				case 0: {
					system("cls");
					cout << "\n\n\n\n\n\n";
					cout << space << "            TAM BIET VA HEN GAP LAI" << endl;
					cout << "\n\n\n\n\n\n";
					Sleep(3000);
					exit(0);
				}
				
				case 2: {
					cout << endl;
					cout << endl << space << "Nhap ten file ban muon nen: ";
					string _in, _out;
					cin.ignore();
					getline(cin, _in);
					_out = _in.substr(0, _in.size() - 4);

					Huffman::Encoding(_in, _out);
					cout << space << "Da nen thanh cong. File da nen ten la: " << _out << endl;
					break;
				}
				case 3: {
					Image a;
					int checkCompress = a.InputImageEncoding();
					if (checkCompress)
						cout << space << "Da nen thanh cong" << endl;
					else
						cout << space << "Nen that bai\n";
					break;

				}

				case 4: {
					Folder a;
					a.Input(1);
					cout << space << "Da nen thanh cong" << endl;
					break;
				}

				default: {
					cout << space << "Khong co chuc nang nay" << endl;
					break;
				}
				
				}

				cout << endl << space << "Moi chon thao tac tiep theo: ";
				fflush(stdin);
				cin >> _choice_compress;
			}
			break;
		}

		case 2: {
			system("cls");
			cout << endl << endl << endl;
			_Menu_decompress();

			int _choice_decompress;
			fflush(stdin);
			cin >> _choice_decompress;

			while (_choice_decompress != 1) {
				
				switch (_choice_decompress) {

				case 0: {
					system("cls");
					cout << "\n\n\n\n\n\n";
					cout << space << "            TAM BIET VA HEN GAP LAI" << endl;
					cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
					Sleep(3000);
					exit(0);
				}

				case 2: {
					cout << endl;
					cout << endl << space << "Nhap ten file ban muon giai nen: ";
					string _in, _out;
					cin.ignore();
					getline(cin, _in);
					_out = _in;
					
					Huffman::Decoding(_in, _out);
					cout << space << "Giai nen thanh cong. File giai nen ten la: " << _out << endl;
					break;
				}

				case 3: {
					Image a;
					bool  checkImage = a.InputImageDecoding();
					if (checkImage == 0)
						cout << space << "Giai nen that bai\n";
					else
						cout << space << "Da giai nen thanh cong" << endl;
					break;
				}

				case 4: {
					Folder a;
					a.Input(0);
					cout << space << "Da giai nen thanh cong" << endl;
					break;
				}

				default: {
					cout << space << "Khong co chuc nang nay" << endl;
					break;
				}
				
				}
				
				cout << endl << space << "Moi chon thao tac tiep theo: ";
				fflush(stdin);
				cin >> _choice_decompress;
			}
			break;
		}
		
		default: {
			cout << space << "Khong co chuc nang nay" << endl;
			break;
		}
		
		}

		cout << endl;
		system("cls");
		cout << endl << endl << endl;
		_Menu();
		fflush(stdin);
		cin >> _choice_main;
	}

	cout << endl;
	system("cls");
	cout << "\n\n\n\n\n\n";
	cout << space << "            TAM BIET VA HEN GAP LAI" << endl;
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	Sleep(3000);
	exit(0);
}


