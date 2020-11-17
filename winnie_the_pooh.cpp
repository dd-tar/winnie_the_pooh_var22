#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

vector<int> forest;
int number_of_tasks;
const int pooh = 0;

/// <summary>
/// Search for Winnie the Pooh by one group of bees.
/// </summary>
/// <param name="start"> The beginning of the working section of this group. </param>
/// <param name="finish"> The ending of the working section of this group. </param>
void search_for_Winnie(int start, int finish)
{
	string result = "\nIn the sector [" + to_string(start) + ';' + to_string(finish) + "] of forest Winnie the Pooh is not found.";
	for (int i = start; i < finish; i++)
		if (forest[i] == pooh) {
			result = "\n    Winnie the Pooh detected in the sector [" + to_string(start) + ';' + to_string(finish) +
				"] of forest!\n    He's hiding in " + to_string(i) +
				" tree.\n    Let's start the attack!\n    BzzZZZzzzzZZ..!\n    The wrecker is punished, we return to the base.";
			break;
		}
	cout << result;
}

/// <summary>
/// Bag of tasks distributed to threads.
/// That is, sections of the forest distributed by groups of bees.
/// </summary>
void bag_of_tasks()
{
	int i_done = 0;
	int start = 0; int finish = 10;
	while (i_done < number_of_tasks && start != -1)
	{
		// getting a task from the bag
		thread thr(search_for_Winnie, start, finish);
		thr.join();
		i_done += 1;
		start = finish + 1 > (int)forest.size() ? -1 : finish + 1;
		finish = finish + 10 > (int)forest.size() ? (forest.size() - 1) : (finish + 10);
	}
}

/// <summary>
/// Plants a forest and hides Winnie the Pooh.
/// </summary>
/// <param name="length"> The number of trees in the forest. </param>
void create_forest(int length)
{
	int poohs_shelter = rand() % length;
	for (int i = 0; i < length; i++)
		if (i != poohs_shelter)
			forest.push_back(1);
		else
			forest.push_back(0);
	number_of_tasks = (length / 10) + (length % 10 == 0 ? 0 : 1);
}


/// <summary>
/// Entering a number from the console and checking it.
/// </summary>
/// <returns> The entered number. </returns>
int get_length()
{
	int length = -1;
		cout << "Enter the number of trees in the forest:\n(a number between 30 and 2147483647)\n";
		try {
			//cin >> length;
			scanf("%d", &length);
			if (length < 30)
				cout << "\nWrong number of trees in the forest.\n";
		}
		catch (exception&) {
			cout << "\nWrong number of trees in the forest.\n";
		}
	return length;
}

int main()
{
	try {
		srand(time(0));
		int length = get_length();
		if(length==-1)
			return 0;

		create_forest(length);
		bag_of_tasks();
	}catch(exception& e)
	{
		cout << e.what();
	}
	system("pause");
	return 0;
}

