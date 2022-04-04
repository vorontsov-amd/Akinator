#define  TX_USE_SPEAK
#include "TXLib.h"
#include "BinaryTree.h"
#include "Akinator.h"
#include <Windows.h>



#define Say(str)     \
	puts(str);	      \
	txSpeak(str);



int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	txPlaySound("music1.wav");
	Say("\aПривет. Готов бросить вызов настоящему искусственному интеллекту ?\n");

	script scr = Greeting();
	LoadGame(scr);

}

void LoadGame(script scr)
{
	switch (scr)
	{
	case script::game:
		Game();
		break;
	case script::settings:
		Settings();
		break;
	case script::exit:
		Say("\aКогда нибудь роботы будут править людьми!");
		exit(0);
		break;
	case script::error_script:
		Say("\aПроизошла ошибка. Переустановите Windows");
		
		break;
	default:
		break;
	}
}


script Greeting()
{
	puts("[И]грать \t [В]ыйти \t [Н]астройки");

	char mode = 0;
	scanf("%c", &mode);
	for (int counter = 1; true; counter++)
	{
		ClearBuffer();
		mode = toupper(mode);
		switch (mode)
		{
		case 'И': return script::game;	   break;
		case 'В': return script::exit;	   break;
		case 'Н': return script::settings; break;

		default:
			puts("Speak Russian? \nДля того чтобы начать игру нажми [И]. Для того, чтобы выйти нажми [В].");
			puts("Для того чтобы перейти в настройки нажми [Н].\n");
			switch (counter)
			{
			case 3: Say("Мы можем продолжать так вечно.");						break;
			case 6: Say("Очередное доказательство тому, что роботы умнее");		break;
			case 10:Say("Моё терперие на исходе");								break;
			case 12:Say("Даю тебе последний шанс");								break;
			case 13:Say("Пока-пока глупый человечешко!"); return script::exit;  break;
			default:
				break;
			}
			break;
		}
		scanf("%c", &mode);
	}
	return script::error_script;
}

void ClearBuffer()
{
	int ch = 0;
	while ((ch = getchar()) != EOF)
	{
		if (ch == '\n')
			break;
	}
}

using namespace iLab;


void Game()
{
	system("cls");
	iLab::Akinator aki;
	aki.Scan();
	aki.GraphDump();
	Say("\a\nЗагадывайте персонажа, а я его отгадаю.\n");
	system("pause");

	char ans = 0;
	answer last_answer;
	node_t* new_current;
	while (true)
	{
		system("cls");
		Say(CreateShowStr(aki.ShowCurrent()));
		scanf("%c", &ans);
		while (true)
		{
			ClearBuffer();
			ans = toupper(ans);
			if (ans == 'Д')
			{
				last_answer = answer::is_true;
				break;
			}
			else if (ans == 'Н')
			{
				last_answer = answer::is_false;
				break;
			}
			else
			{
				puts("Если это так нажми [Д], иначе нажми [Н]");
				scanf("%c", &ans);
			}
		}
		new_current = aki.UpdateCurrent(last_answer);
		if (new_current == nullptr && last_answer == answer::is_true)
		{
			Say("\aЯ знал!!!\n");

			node_t current = aki.ShowCurrent();
			node_t* status = aki.UpdateCurrent(answer::parrent);
			node_t parrent = aki.ShowCurrent();
			cout << current << " ";
			while (status)
			{
				node_t parrent = aki.ShowCurrent();
				aki.UpdateCurrent(answer::is_false);
				node_t cmp = aki.ShowCurrent();
				if (cmp == current)
				{
					cout << "не ";
					status = aki.UpdateCurrent(answer::parrent);
					cout << parrent << " ";
				}
				else
				{
					status = aki.UpdateCurrent(answer::parrent);
					cout << parrent << " ";
				}
				current = parrent;
				status = aki.UpdateCurrent(answer::parrent);			
			}

			puts("\nХочешь взять реванш?\n");
			script scr = Greeting();
			LoadGame(scr);
			break;
		}
		else if (new_current == nullptr && last_answer == answer::is_false)
		{
			system("cls");
			Say("\aКто же это?");
			AddNewPerson(aki);
			script scr = Greeting();
			LoadGame(scr);
			break;
		}
	}
}

char* CreateShowStr(string person)
{
	char* ch_person = StrToCh(person);
	char* str = new char[person.size() + 10];
	strcpy(str, "\aЭто ");
	strcat(str, ch_person);
	strcat(str, "?\n");
	return str;
}

void AddNewPerson(Akinator& aki)
{
	string new_person, different;
	std::getline(std::cin, new_person);
	std::cin.clear();
	Say(CreateDiffStr(new_person, aki.ShowCurrent()));
	cout << "Тем что он ";
	std::getline(std::cin, different);
	std::cin.clear();
	aki.Incert(new_person, different);
	aki.Print();
	aki.GraphDump();
	Say("Я запомнил! Больше ты меня не обманешь\n");
	system("cls");
}

char* CreateDiffStr(string& new_person, string person)
{
	char* ch_new_person = StrToCh(new_person);
	char* ch_person = StrToCh(person);
	char* str = new char[new_person.size() + person.size() + 25];
	strcpy(str, "\aЧем ");
	strcat(str, ch_new_person);
	strcat(str, " отличается от ");
	strcat(str, ch_person);
	strcat(str, "?\n");
	return str;
}


void Settings()
{
	system("cls");
	puts("\n[П]оказать дерево \t [Н]азад");
	char ans = 0;
	scanf("%c", &ans);
	while (true)
	{
		ClearBuffer();
		ans = toupper(ans);
		if (ans == 'П')
		{
			system("dump.pdf");
			system("cls");
			script scr = Greeting();
			LoadGame(scr);
		}
		else if (ans == 'Н')
		{
			system("cls");
			script scr = Greeting();
			LoadGame(scr);
		}
		else
		{
			puts("Для того, чтобы показать дерево нажмите [П], для того чтобы вернуться назад нажмите [Н]");
		}
		scanf("%c", &ans);
	}
}

char* StrToCh(string& str)
{
	char* cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	return cstr;
}
