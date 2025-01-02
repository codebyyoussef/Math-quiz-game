#include <iostream>
using namespace std;

enum enQuestionsLevel {easy = 1, medium = 2, hard = 3, mix = 4};
enum enOperationType {addition = 1, substraction = 2, multiplication = 3, division = 4, mixOp = 5};

struct stQuestion
{
  short number1;
  short number2;
  enOperationType operationType;
  enQuestionsLevel questionLevel;
  short correctAnswer;
  short playerAnswer;
  bool answerResult;
};
struct stQuizz
{
  stQuestion questionList[100];
  short numberOfQuestions;
  enQuestionsLevel questionsLevel;
  enOperationType operationType;
  short numberOfWrongAnswers = 0;
  short numberOfRightAnswers = 0;
  bool isPass;
};

short readHowManyQuestions()
{
  short numberOfQuestions;
  do
  {
    cout << "How many questions do you want to answer? ";
    cin >> numberOfQuestions;
  } while (numberOfQuestions < 1 || numberOfQuestions > 10);
  return numberOfQuestions;
}

enQuestionsLevel readQuestionsLevel()
{
  short questionsLevel;
  do
  {
    cout << "Enter questions level [1] Easy, [2] Med, [3] Hard, [4] Mix? ";
    cin >> questionsLevel;
  } while (questionsLevel < 1 || questionsLevel > 4);
  return (enQuestionsLevel) questionsLevel;
}

enOperationType readOperationsType()
{
  short opsType;
  do
  {
    cout << "Enter operation type [1] add, [2] sub, [3] multi, [4] div, [5] Mix? ";
    cin >> opsType;
  } while (opsType < 1 || opsType > 5);
  return (enOperationType) opsType;
}

short randomNumber(short from, short to)
{
  short randNum = rand() % (to - from + 1) + from;
  return randNum;
}

enOperationType getRandomOperationType()
{
  return (enOperationType) randomNumber(1, 4);
}

short simpleCalculator(short number1, short number2, enOperationType opType)
{
  switch (opType)
  {
    case addition:
      return number1 + number2;
    case substraction:
      return number1 - number2;
    case multiplication:
      return number1 * number2;
    case division:
      return number1 / number2;
    default:
      return number1 + number2;
  }
  return 0;
}

stQuestion generateQuestion(enQuestionsLevel questionLevel, enOperationType opType)
{
  stQuestion question;
  if (questionLevel == mix)
  {
    questionLevel = (enQuestionsLevel) randomNumber(1, 3);
  }

  if (opType == mixOp)
  {
    opType = getRandomOperationType();
  }

  question.operationType = opType;

  switch (questionLevel)
  {
    case easy:
      question.number1 = randomNumber(1, 10);
      question.number2 = randomNumber(1, 10);
      question.correctAnswer = simpleCalculator(question.number1, question.number2, question.operationType);
      question.questionLevel = questionLevel;
      return question;
    case medium:
      question.number1 = randomNumber(10, 50);
      question.number2 = randomNumber(10, 50);
      question.correctAnswer = simpleCalculator(question.number1, question.number2, question.operationType);
      question.questionLevel = questionLevel;
      return question;
    case hard:
      question.number1 = randomNumber(50, 100);
      question.number2 = randomNumber(50, 100);
      question.correctAnswer = simpleCalculator(question.number1, question.number2, question.operationType);
      question.questionLevel = questionLevel;
      return question;
  }
  return question;
}

void generateQuizzQuestions(stQuizz &quizz)
{
  for (short question = 0; question < quizz.numberOfQuestions; question++)
  {
    quizz.questionList[question] = generateQuestion(quizz.questionsLevel, quizz.operationType);
  }
}

string getOpTypeSymbol(enOperationType opType)
{
  switch (opType)
  {
    case addition:
      return "+";
    case substraction:
      return "-";
    case multiplication:
      return "*";
    case division:
      return "/";
    default:
      return "Mix";
  }
  return "";
}

void printTheQuestion(stQuizz quizz, short questionNumber)
{
  cout << "\nQuestion [" << questionNumber + 1 << "/" << quizz.numberOfQuestions << "]\n\n";
  cout << quizz.questionList[questionNumber].number1 << "\n";
  cout << quizz.questionList[questionNumber].number2 << " ";
  cout << getOpTypeSymbol(quizz.questionList[questionNumber].operationType) << "\n";
  cout << "_______________\n";
}

short readPlayerAnswer()
{
  short answer;
  cin >> answer;
  return answer;
}

void setScreenColor(bool result)
{
  if (result)
    system("color 2F");
  else
  {
    system("color 4F");
    cout << '\a';
  }
}

void correctTheQuestionAnswer(stQuizz &quizz, short questionNumber)
{
  if (quizz.questionList[questionNumber].playerAnswer != quizz.questionList[questionNumber].correctAnswer)
  {
    quizz.questionList[questionNumber].answerResult = false;
    quizz.numberOfWrongAnswers++;
    cout << "Wrong Answer :(\n";
    cout << "The right answer is: ";
    cout << quizz.questionList[questionNumber].correctAnswer << "\n";
  }
  else
  {
    quizz.questionList[questionNumber].answerResult = true;
    quizz.numberOfRightAnswers++;
    cout << "Right Answer :)\n\n";
  }

  setScreenColor(quizz.questionList[questionNumber].answerResult);
}

void askAndCorrectQuestionListAnswers(stQuizz &quizz)
{
  for (short questionNumber = 0; questionNumber < quizz.numberOfQuestions; questionNumber++)
  {
    printTheQuestion(quizz, questionNumber);
    quizz.questionList[questionNumber].playerAnswer = readPlayerAnswer();
    correctTheQuestionAnswer(quizz, questionNumber);
  }
  quizz.isPass = (quizz.numberOfRightAnswers >= quizz.numberOfWrongAnswers);
}

string getFinalResultsText(bool pass)
{
  if (pass)
    return "Pass :)";
  else
   return "Fail :(";
}

string getQuestionsLevelText(enQuestionsLevel questionsLevel)
{
  string arrQuestionsLevelText[4] = {"Easy", "Medium", "Hard", "Mix"};
  return arrQuestionsLevelText[questionsLevel - 1];
}

void printQuizzResults(stQuizz quizz)
{
  cout << "\n__________________________\n\n";
  cout << "  Final Result is " << getFinalResultsText(quizz.isPass);
  cout << "\n__________________________\n\n";

  cout << "Number of Question: " << quizz.numberOfQuestions << "\n";
  cout << "Questions Level   : " << getQuestionsLevelText(quizz.questionsLevel) << "\n";
  cout << "Operation Type   : " << getOpTypeSymbol(quizz.operationType) << "\n";
  cout << "Number of right answers: " << quizz.numberOfRightAnswers << "\n";
  cout << "Number of wrong answers: " << quizz.numberOfWrongAnswers << "\n";
  cout << "__________________________\n";

  setScreenColor(quizz.isPass);
}

void playMathGame()
{
  stQuizz quizz;
  quizz.numberOfQuestions = readHowManyQuestions();
  quizz.questionsLevel = readQuestionsLevel();
  quizz.operationType = readOperationsType();

  generateQuizzQuestions(quizz);
  askAndCorrectQuestionListAnswers(quizz);
  printQuizzResults(quizz);
}

void resetScreen()
{
	system("cls");
	system("color 0F");
}

void startGame()
{
  char playAgain;
  do
  {
    resetScreen();
    playMathGame();
    cout << "\nDo you want to play again? Y/N: ";
    cin >> playAgain;
  } while (playAgain == 'Y' || playAgain == 'y');
  
}

int main()
{
  srand((unsigned)time(NULL));

  startGame();
  return 0;
}