#include <iostream>
#include<string>
#include<cstdlib>

using namespace std;


// enums and structers needed
enum enQuestionLevel
{
	Easy = 1,
	Medium = 2,
	Hard = 3,
	MixedQuestions = 4
};

enum enOperationType
{
	Add = 1,
	Substract = 2,
	Mutliplication = 3,
	Divide = 4,
	MixedOperations = 5
};

struct stQuestion
{
	int FirstNumber = 0;
	char Operation = '+';
	int SecondNumber = 0;
	int Result = 0;
};

struct stFinalResult
{
	string status;
	int NumberOfQuestions;
	string QuestionLevel;
	string OperationType;
	int NumberOfRightAnswers = 0;
	int NumberOfWrongAnswers = 0;
};



// secondary functions 

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

char GenerateOperation(enOperationType Operation)
{
	switch (Operation)
	{
		case enOperationType::Add:
			return '+';
		case enOperationType::Substract:
			return '-';
		case enOperationType::Divide:
			return '/';
		case enOperationType::Mutliplication:
			return '*';
		case enOperationType::MixedOperations:
			enOperationType Oper = (enOperationType)RandomNumber(1,4);
			return GenerateOperation(Oper);
	}
}

string ReturnOperationType(enOperationType Operation)
{
	switch (Operation)
	{
	case enOperationType::Add:
		return "Addition";
	case enOperationType::Substract:
		return "Substraction";
	case enOperationType::Divide:
		return "Division";
	case enOperationType::Mutliplication:
		return "Mutliplication";
	case enOperationType::MixedOperations:
		return "Mixed operations";
	}
}

string ReturnQuestionLevel(enQuestionLevel QuestionLevel)
{
	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		return "Easy";
	case enQuestionLevel::Medium:
		return "Medium";
	case enQuestionLevel::Hard:
		return "Hard";
	case enQuestionLevel::MixedQuestions:
		return "Mixed questions";
	}
}



// Program primary Functions

int ReadHowManyQuestions()
{
	int NumberOfQuestions;

	cout << "How many questions do you want to answer ?   ";
	cin >> NumberOfQuestions;

	return NumberOfQuestions;
}


enQuestionLevel ReadQuestionsLevel()
{
	short QuestionLevel = 0;

	do
	{
		cout << "Enter questions level [1] Easy  [2] Medium  [3] Hard  [4] Mix ?  ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4);


	return (enQuestionLevel)QuestionLevel;
}


enOperationType ReadOperationType()
{
	short OperationType = 0;

	do
	{
		cout << "Enter operation type [1] Addition  [2] Substraction  [3] Multiplication  [4] Division [5] Mix ?  ";
		cin >> OperationType;
	} while (OperationType < 1 || OperationType > 5);


	return (enOperationType)OperationType;
}


int CalculateResult(stQuestion Question)
{
	if (Question.Operation == '+')
		return Question.FirstNumber + Question.SecondNumber;
	else if (Question.Operation == '-')
		return Question.FirstNumber - Question.SecondNumber;
	else if (Question.Operation == '/')
		return Question.FirstNumber / Question.SecondNumber;
	else if (Question.Operation == '*')
		return Question.FirstNumber * Question.SecondNumber;
}


stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType)
{
	stQuestion Question;

	switch (QuestionLevel)
	{
		case enQuestionLevel::Easy:
		{
			Question.FirstNumber = RandomNumber(1, 9);
			Question.SecondNumber = RandomNumber(1, 9);
			break;
		}
		case enQuestionLevel::Medium:
		{
			Question.FirstNumber = RandomNumber(10, 50);
			Question.SecondNumber = RandomNumber(10, 50);
			break;
		}
		case enQuestionLevel::Hard:
		{
			Question.FirstNumber = RandomNumber(51, 1000);
			Question.SecondNumber = RandomNumber(51, 1000);
			break;
		}
		case enQuestionLevel::MixedQuestions:
		{
			Question.FirstNumber = RandomNumber(1, 1000);
			Question.SecondNumber = RandomNumber(1, 1000);
			break;
		}
			
	}

	Question.Operation = GenerateOperation(OperationType);

	Question.Result = CalculateResult(Question);

	return Question;

}


void ShowQuestion(stQuestion Question)
{
	cout << "\n\n";
	cout << Question.FirstNumber << "\n";
	cout << " " <<Question.Operation << "\n";
	cout << Question.SecondNumber << "\n\n";

	cout << "----------\n";

}


bool IsUserAnswerRight(int RightAnswer, int UserAnswer)
{
	return (RightAnswer == UserAnswer);
}


void ShowResult(stQuestion Question, int UserAnswer)
{
	if (IsUserAnswerRight(Question.Result, UserAnswer))
	{
		system("color 2F");
		cout << "Right answer :-)\n";
	}
	else
	{
		cout << "\a";
		system("color 4F");
		cout << "\n\n";
		cout << "Wrong answer :-(\n";
		cout << "The right answer is " << Question.Result;
	}
	cout << "\n\n";
}


stFinalResult FillFinalResult(int NumberOfQuestions, enQuestionLevel QuestionLevel, enOperationType OperationType, int NumberOfRightAnswers, int NumberOfWrongAnswers)
{
	stFinalResult FinalResult;

	FinalResult.NumberOfQuestions = NumberOfQuestions;
	FinalResult.NumberOfRightAnswers = NumberOfRightAnswers;
	FinalResult.NumberOfWrongAnswers = NumberOfWrongAnswers;
	FinalResult.OperationType = ReturnOperationType(OperationType);
	FinalResult.QuestionLevel = ReturnQuestionLevel(QuestionLevel);


	if (NumberOfRightAnswers >= NumberOfWrongAnswers)
		FinalResult.status = "Pass";
	else
		FinalResult.status = "Fail";

	return FinalResult;
}


void ShowFinalResult(stFinalResult FinalResult)
{
	cout << "\n\n\n\n\n---------------------------\n";
	cout << "  Final result is " << FinalResult.status;
	cout << "\n---------------------------\n\n";
	
	cout << "Number of questions     : " << FinalResult.NumberOfQuestions << "\n";
	cout << "Question level is       : " << FinalResult.QuestionLevel << "\n";
	cout << "Operation type          : " << FinalResult.OperationType << "\n";
	cout << "Number of right answers : " << FinalResult.NumberOfRightAnswers << "\n";
	cout << "Number of wrong answers : " << FinalResult.NumberOfWrongAnswers << "\n";

}




// start quiz function 
void PrintQuiz()
{
	int NumberOfQuestions = ReadHowManyQuestions();
	enQuestionLevel QuestionLevel = ReadQuestionsLevel();
	enOperationType OperationType = ReadOperationType();

	stQuestion Question;

	int UserAnswer = 0;
	int NumberOfRightAnswers = 0;
	int NumberOfWrongAnswers = 0;



	for (int Questions = 1; Questions <= NumberOfQuestions; Questions++)
	{
		cout << "Question [" << Questions << "/" << NumberOfQuestions << "] \n";


		Question = GenerateQuestion(QuestionLevel, OperationType);

		ShowQuestion(Question);

		cin >> UserAnswer;

		ShowResult(Question, UserAnswer);

		if (IsUserAnswerRight(Question.Result, UserAnswer))
			NumberOfRightAnswers++;
		else
			NumberOfWrongAnswers++;

	}

	system("color 0F");
	ShowFinalResult(FillFinalResult(NumberOfQuestions,QuestionLevel,OperationType,NumberOfRightAnswers,NumberOfWrongAnswers));
}

void startQuiz() 
{
	int PlayAgain = 0;

	do
	{
		PrintQuiz();

		cout << "\n\n\n\nDo you want to have another quiz [1] Yes, [0] No?   ";
		cin >> PlayAgain;
		system("cls");
		system("color 0F");

	} while (PlayAgain == 1);


}

int main()
{
	srand(time(NULL));
	startQuiz();

}

