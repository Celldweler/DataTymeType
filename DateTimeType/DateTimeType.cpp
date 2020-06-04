// DateTimeType.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <windows.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <fstream>

using namespace std;

//                  Variant - 2
/*
         Тип данных – дата и время
    Базовый уровень Задание: изучить набор функций, предназначенных для работы с данными типа дата и время. Написать программу реализации
    индивидуального задания, представленного в таблице. Все указанные значения дат и времени вводить по формату ДДММГГГГ и ЧЧ:ММ:СС соответственно
*/


void low()
{
    /*
1. Ввести две даты и вывести сообщение с информацией, какая из двух введенных дат более 
поздняя. 
2. Написать программу контроля электропитания ноутбука. Исходные параметры: время 
включения ноутбука от батареи и задекларированное производителем время работы от батареи в 
часах без подключения к сети электропитания. Программа информирует о количестве часов работы 
ноутбука от батареи на текущий момент времени и сколько осталось минут до полного разряда 
батареи. При расчете считать, что в момент включения ноутбука батарея имела 100% заряд и 
способна обеспечить задекларированное производителем время работы
    */
    cout << "\nTask low: \n";
    std::string s1{ "19.01.2038" }, s2{ "26.05.1970" }; // даты начиная с 1970 года до 19.01.2038 года

    std::stringstream ss1, ss2;
    ss1.str(s1);
    ss2.str(s2);
    std::tm stm1{}, stm2{};
    ss1 >> std::get_time(&stm1, "%d.%m.%Y");
    ss2 >> std::get_time(&stm2, "%d.%m.%Y");
    stm1.tm_isdst = -1;
    stm2.tm_isdst = -1;
    std::cout << stm1.tm_mday << '.' << stm1.tm_mon << '.' << stm1.tm_year << std::endl;
    std::cout << stm2.tm_mday << '.' << stm2.tm_mon << '.' << stm2.tm_year << std::endl;
    time_t t1 = std::mktime(&stm1);
    time_t t2 = std::mktime(&stm2);
    if (t1 != -1 && t2 != -1)
    {
        double dif = std::difftime(t1, t2);
        std::cout << (dif < 0. ? "first" : dif > 0. ? "second" : "equal") << std::endl;
    }
    else
    {
        std::cerr << "Error\n";
    }
    cout << "\nНажмите <Enter> чтобы продолжить: ";
    while (getchar() != '\n')
        continue;
}
void midle()
{
    /*
   Структура и ее поля:
            Сотрудники предприятия:
               - табельный номер;
               - ФИО сотрудника;
               - дата рождения;
               - пол (м/ж); 
               - дата поступления на работу;
               - должность; 
               - оклад;
    Задача:
          - вывести информацию о возрасте каждого сотрудника на данный момент времени и количестве дней, отработанных
            им на предприятии; 
          - организовать просмотр информации о сотрудниках пенсионного возраста (мужчины – до 60 
              лет, женщины – до 55 лет), проработавших на предприятии более 30 лет. 
    */
    cout << "\nMidel task level: \n";
// current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);

   cout << "The local date and time is: " << dt << endl;

   // convert now to tm struct for UTC
   tm *gmtm = gmtime(&now);
   dt = asctime(gmtm);
   cout << "The UTC date and time is:"<< dt << endl;
	
	time_t now = time(0);

   cout << "Number of sec since January 1,1970:" << now << endl;

   tm *ltm = localtime(&now);

   // print various components of tm structure.
   cout << "Year" << 1970 + ltm->tm_year<<endl;
   cout << "Month: "<< 1 + ltm->tm_mon<< endl;
   cout << "Day: "<<  ltm->tm_mday << endl;
   cout << "Time: "<< 1 + ltm->tm_hour << ":";
   cout << 1 + ltm->tm_min << ":";
   cout << 1 + ltm->tm_sec << endl;
	
    cout << "\nНажмите <Enter> чтобы продолжить: ";
    while (getchar() != '\n')
        continue;
}
struct Book;
struct Book
{
	string fio;
	string book_name;
	int    cost;
	int    count;
};
void CheckDigit(int& anydigit);

Book* FillStruct(Book* mas_book, int count)  //Всего лишь заполняет масив структур
{
	if (mas_book == nullptr)
		mas_book = new Book[count];
	for (size_t i = 0; i < count; i++)
	{
		mas_book[i].fio = "FIO" + to_string(i + 1);
		mas_book[i].book_name = "BooksName" + to_string(i + 1);
		mas_book[i].cost = 100 + rand() % 1000;
		mas_book[i].count = 1 + rand() % 100;
	}
	return mas_book;
}
void ShowBooks(Book* mas_books, int count)
{
	cout << "\nИнформация о всех книах: \n";
	for (size_t i = 0; i < count; i++)
	{
		printf("\nИнформация о %d книге: \n\t", i + 1);
		cout << mas_books[i].fio << " ";
		cout << mas_books[i].book_name << " ";
		cout << mas_books[i].cost << " ";
		cout << mas_books[i].count << "\n";
	}
}
Book* LoadFile(int count)  //Прочитать данные с файла
{
	ifstream f_in; f_in.open("database.bin", ios::binary | ios::in);
	Book* buffer = new Book[count];
	f_in.read((char*)buffer, count * sizeof(Book));
	f_in.close();
	return buffer;
}
void SaveFile(Book* mas_book, int count)
{
	ofstream f_out; f_out.open("database.bin", ios::binary | ios::out);
	int BufferSize = count * sizeof(Book);
	f_out.write((char*)mas_book, BufferSize);
	f_out.close();
}
int IsSetDiscount(int count) //Установление скидки если соблюдается условие 
{
	ifstream f_in; f_in.open("database.bin", ios::binary | ios::in);
	Book* buffer = new Book[count];
	f_in.read((char*)buffer, count * sizeof(Book));
	f_in.close();
	bool flag = false;
	for (size_t i = 0; i < count; i++)
	{
		if (buffer[i].fio[i] == 'K')
		{
			flag = true;
			for (size_t i = 0; i < count; i++)
			{
				printf("\nИнформация о %d книге: \n\t", i + 1);
				cout << buffer[i].fio << " ";
				cout << buffer[i].book_name << " ";
				cout << buffer[i].cost << " ";
				cout << buffer[i].count << "\n";
			}
		}
	}
	if (!flag)
		cout << "\nНет не одного автора фамилия которого начинается на <K>!!!\n";
	//SaveFile(buffer, count);
	return 0;
}
void CheckDigit(int& anydigit)
{
	while (true)
	{
		cin >> anydigit;
		if (!cin.good() || cin.fail())
		{
			cin.clear();
			cin.ignore(32567, '\n');
			cout << "\nВведите коректное числовое значение...\n";
			cout << "\nПовторите ввод: ";
		}
		break;
	}
}

void hard()
{
/*
        - ввести две даты и подсчитать для указанного периода количество сотрудников, поступивших на работу и их 
          средний оклад;
        - вывести информацию о самом молодом инженере и количестве дней отработанных им на предприятии;
        - расчетному отделу для начисления премии подготовить информацию по всем юбилярам текущего года (возраст 
          кратен 5). Результат оформить в виде файла.
 */
    cout << "\nHard task level: \n";
struct tm *u;
  char s1[40] = { 0 }, s2[40] = { 0 };
  const time_t timer = time(NULL);
  u = localtime(&timer);
  strftime(s1, 80, "%d.%m.%Y %H:%M:%S ", u);
  printf("%s\n", s1);
  u->tm_mday += ADD_DAYS;
  time_t next = mktime(u);
  u = localtime(&next);
  strftime(s2, 80, "%d.%m.%Y %H:%M:%S ", u);
  printf("%s\n", s2);
int count = 10;
	Book* mas_book = new Book[count];
	mas_book = FillStruct(mas_book, count);
	SaveFile(mas_book, count);
	mas_book = LoadFile(count);
	cout << "\nСодержимое файла до внесенных изминений: \n";
	cout << "\nВ файле хранится масив структур содержащих следущие поля: \n";
	cout << "\t-ФИО автора\n\t-название книги\n\t-цена за ед.\n\t-количетсво экзэмпляров";
	ShowBooks(mas_book, count);
	cout << "\nСодержимое файла после внесенных изминений: "
		 <<  "\nДанные про книги авторов, фамилия которых начинается с буквы “К”: \n";
	IsSetDiscount(count);
	Book* buffer = new Book[count];
	buffer = LoadFile(count);
	SaveFile(buffer, count);
	ShowBooks(buffer, count);
    cout << "\nНажмите <Enter> чтобы продолжить: ";
    while (getchar() != '\n')
        continue;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    srand(time(NULL));
     low();
     midle();
     hard();
}

