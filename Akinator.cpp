#include "BinaryTree.h"
#include "Akinator.h"


int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	script scr = Greeting();
	switch (scr)
	{
	case script::game:
		Game();
		break;
	case script::settings:
		break;
	case script::exit:
		break;
	case script::error_script:
		break;
	default:
		break;
	}

}

script Greeting()
{
	puts("Привет. Готов бросить вызов настоящему искусственному интеллекту?\n");
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
			case 3: puts("Мы можем продолжать так вечно.");						break;
			case 6: puts("Очередное доказательство тому, что роботы умнее");	break;
			case 10:puts("Моё терперие на исходе");								break;
			case 12:puts("Даю тебе последний шанс");							break;
			case 13:puts("Пока-пока глупый человечешко!"); return script::exit; break;
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
	iLab::Akinator aki;
	aki.Scan();

	puts("Загадывайте персонажа, а я его отгадаю.\n");
	puts("Нажмите на пробел, как придумаете персонажа\n");
	system("pause");

	char ans = 0;
	answer last_answer;
	node_t* new_current;
	while (true)
	{
		std::cout << "Это " << aki.ShowCurrent() << "? [Д]а - [Н]ет\n";
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
		if (new_current == nullptr and last_answer == answer::is_true)
		{
			puts("Я знал!!!");
			break;
		}
		else if (new_current == nullptr and last_answer == answer::is_false)
		{
			puts("Кто же это?");
			AddNewPerson(aki);
			break;
		}
	}
}

void AddNewPerson(Akinator& aki)
{
	string new_person, different;
	std::cin >> new_person;
	cout << "Чем " << new_person << " отличается от " << aki.ShowCurrent() << "?\n";
	cout << "Тем что он ";
	std::cin >> different;
	aki.Incert(new_person, different);
	aki.Print();
	aki.GraphDump();
	puts("Я запомнил! Больше ты меня не обманешь");
}
