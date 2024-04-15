package omerAttia;

import java.io.*;
import java.time.*;
import java.time.format.DateTimeFormatter;
import java.util.*;
import omerAttia.Answer.eType;
import omerAttia.Query.difficulty;

public class main {

	public static Scanner s = new Scanner(System.in);
	// databases and db mangement
	public static Query[] allQueryArray = new Query[0];
	public static String[] closedAnswerList = new String[0];
	public static String[] openAnswerList = new String[0];
	public static AnswerRepository AR = new AnswerRepository(closedAnswerList, openAnswerList);
	public static QueryRepository QR = new QueryRepository(allQueryArray);

	public static void main(String[] args) throws IOException, ClassNotFoundException {
		//addQuerries();
		try {
			hello();
		} catch (FileNotFoundException e) {
			System.out.println("no backup files found");
		} catch (Exception e1) {
			System.out.println("an error happend loading the backup");
		}
		lobby();
	}

	public static void lobby() throws IOException {
		int choise=-1;
		do {
			System.out.println("\n \n hello what would you like to do? \n"
					+ "1. print out all the questions and its answers in the repository \n"
					+ "2. print all the answers in the repository" + "\n"
					+ "3. adding a new answer to the repository \n" + "4. adding a new question \n"
					+ "5. updating answers to a question (add, remove, update) \n"
					+ "6. removing a question from the repository \n" + "7. creating a test manually \n" + "0. exit \n");
			
			try {
				choise = s.nextInt();
			} catch (InputMismatchException e) {
				System.out.println("enter a number!");
				s.next();
			}

			switch (choise) {
			case 1: {
				printAll_1();
				break;
			}
			case 2: {
				printAnsRep_2();
				break;
			}
			case 3: {
				addNewAnswerToRepository_3();
				break;
			}
			case 4: {
				addQ_4();
				break;
			}
			case 5: {
				updatingAnAnswerToQues_5();
				break;
			}
			case 6: {
				rmQuestion_6();
				break;
			}
			case 7: {
				personalTest_7();
				;
				break;
			}

			case 0: {
				goodbye();
				System.out.println("goodbye");
			}
			}
		} while (choise != 0);
	}

	// printing all the questions and answers
	public static void printAll_1() {
		System.out.println("printing Querys");
		System.out.println(QR.toString());
		System.out.println("finished printing");
	}

	// printing the answer repository
	public static void printAnsRep_2() {
		System.out.println("printing Answers!");
		System.out.println(AR.toString());
		System.out.println("finished printing!");
	}

	// adding new answer to repository
	public static void addNewAnswerToRepository_3() {

		// TODO try-catch block
		char aType;
		do {
			System.out.println("what kind of answer would you like to add - closed or open: <c/0>");
			aType = s.next().charAt(0);
		} while (aType != 'c' && aType != 'o');

		if (aType == 'c') {
			addNewClosedAnswerToRep_3();
		} else {
			addNewOpenAnswerToRep_3();
		}
	}

	// created distinct functions for adding answers because their useful in other
	// funcs aswell
	public static void addNewClosedAnswerToRep_3() {
		s.nextLine(); // clear buffer
		System.out.println("write the answer:  ");
		String newAns = s.nextLine();
		if (AR.addCloseAnswer(newAns)) {
			System.out.println("added answer!");
		} else {
			System.out.println("answer already in repository");
		}
	}

	public static void addNewOpenAnswerToRep_3() {
		s.nextLine(); // clear buffer
		System.out.println("write the answer:  ");
		String newAns = s.nextLine();
		if (AR.addOpenAnswer(newAns)) {
			System.out.println("added answer!");
		} else {
			System.out.println("answer already in repository");
		}
	}

	// adding a question to the Query repository
	public static void addQ_4() {
		char qType;
		do {
			System.out.println("what kind of question would you like to add - closed or open: <c/0>");
			qType = s.next().charAt(0);
		} while (qType != 'c' && qType != 'o');

		System.out.println("how difficult will the question be:  ");
		for (int i = 0; i < difficulty.values().length; i++) {
			System.out.println((i + 1) + ") " + difficulty.values()[i]);
		}

		int diff=-1;
		do {
			try {
				diff = s.nextInt() - 1;
			} catch (InputMismatchException e) {
				System.out.println("enter a number");
				s.next();
			}
		} while (diff >= difficulty.values().length || diff < 0);

		s.nextLine(); // clear buffer

		System.out.println("what is the question: ");
		String Ques = s.nextLine();

		if (qType == 'c')
			addClosedQ_4(diff, Ques);
		else
			addOpenQ_4(diff, Ques);
	}

	public static void addClosedQ_4(int diff, String Ques) {
		System.out.println("you can choose up to 10 answers maximum!\n");

		// giving a chance to add an answer
		char addAnsToRep;
		do {
			System.out.println("would you like to add an answer to the repository: <y/n> ");
			addAnsToRep = s.next().charAt(0);
			if (addAnsToRep == 'y') {
				addNewClosedAnswerToRep_3();
			}
		} while (addAnsToRep != 'n');

		// setting up the Query
		Answer[] AnswerList = new Answer[0];
		closedQuery newClosedQuery = new closedQuery(Ques, difficulty.values()[diff], QR, AnswerList);

		int ansToAdd = 0;
		int answerArrIndex = 0;
		do {
			System.out.println("choose a correct answer from the repository to the Query: <enter -1 to stop>");
			// printing only what was not chosen by the user
			System.out.println(AR.closedAnsLimitedtoString(AR.closedAnsLimitedArray(newClosedQuery.getAnswerList())));

			try {
				ansToAdd = s.nextInt() - 1;
			} catch (InputMismatchException e) {
				System.out.println("enter a number");
				s.next();
			}

			if (ansToAdd >= 0 && ansToAdd < AR.getClosedAns().length
					&& newClosedQuery.addAnswerToQuery(ansToAdd, true, AR)) {
				answerArrIndex++;
				System.out.println("answer added!");
			} else {
				System.out.println("answer was not added");
			}
		} while (ansToAdd != -2 && answerArrIndex < newClosedQuery.getMaxAns());

		if (answerArrIndex < newClosedQuery.getMaxAns()) {
			do {
				System.out.println("choose an incorrect answer from the repository to the Query: <enter -1 to stop>");
				System.out.println(AR.closedAnsLimitedtoString(AR.closedAnsLimitedArray(newClosedQuery.getAnswerList())));

				try {
					ansToAdd = s.nextInt() - 1;
				} catch (InputMismatchException e) {
					System.out.println("enter a number");
					s.next();
				}
				
				if (ansToAdd >= 0 && ansToAdd < AR.getClosedAns().length
						&& newClosedQuery.addAnswerToQuery(ansToAdd, false, AR)) {
					answerArrIndex++;
					System.out.println("answer added!");
				} else {
					System.out.println("answer was not added");
				}
			} while (ansToAdd != -2 && answerArrIndex < newClosedQuery.getMaxAns());
		}

		if (QR.addQuery(newClosedQuery)) {
			System.out.println("Query added!");
		} else {
			System.out.println("Query already exists");
		}
	}

	public static void addOpenQ_4(int diff, String Ques) {
		char addAnsToRep;
		do {
			System.out.println("would you like to add a new answer or choose from repository: <a/r> ");
			addAnsToRep = s.next().charAt(0);
		} while (addAnsToRep != 'a' && addAnsToRep != 'r');

		openQuery newOpenQuery;
		if (addAnsToRep == 'a') {
			addNewOpenAnswerToRep_3();
			Answer newOpenAns = new Answer((AR.getOpenAns().length - 1), AR, eType.open);
			newOpenQuery = new openQuery(Ques, difficulty.values()[diff], QR, newOpenAns);
		} else {
			System.out.println(AR.openAnstoString());

			// TODO try-catch
			int ansChoose = 0;
			do {
				ansChoose = s.nextInt() - 1;
			} while (ansChoose >= AR.getOpenAns().length && ansChoose < 0);

			Answer newOpenAns = new Answer(ansChoose, AR, eType.open);
			newOpenQuery = new openQuery(Ques, difficulty.values()[diff], QR, newOpenAns);
		}
		if (QR.addQuery(newOpenQuery)) {
			System.out.println("Query added!");
		} else {
			System.out.println("Query already exists");
		}
	}

	// updating is deleting and changing answer to Query
	public static void updatingAnAnswerToQues_5() {
		System.out.println(QR.toString());

		int qIndex=0;
		do {
			System.out.println("what question would you like to add to or update: ");
			try {
				qIndex = s.nextInt() - 1;
			} catch (InputMismatchException e) {
				System.out.println("enter a number");
				s.next();
			}
		} while (qIndex > QR.getAllQueryArray().length && qIndex <= 0);

		if (QR.getAllQueryArray()[qIndex].getClass().equals(closedQuery.class)) {
			char addOrRm;
			do {
				System.out.println("would you like to remove or add an answer: <r/a>");
				addOrRm = s.next().charAt(0);
			} while (addOrRm != 'r' && addOrRm != 'a');

			if (addOrRm == 'a') {
				addAnswerToClosedQuery_5(qIndex);
			} else {
				rmAnswerFromQues_5(qIndex);
			}
		} else {
			updateAnswerOpenQuery_5(qIndex);
		}
	}

	public static void addAnswerToClosedQuery_5(int qIndex) {
		closedQuery q = ((closedQuery) QR.getAllQueryArray()[qIndex]);
		char addAnsToRep;
		do {
			System.out.println("would you like to add an answer to the repository: <y/n> ");
			addAnsToRep = s.next().charAt(0);
			if (addAnsToRep == 'y') {
				addNewClosedAnswerToRep_3();
			}
		} while (addAnsToRep != 'n');

		char tOrF;
		do {
			System.out.println("is the answer you want to add true or false: <t/f>");
			tOrF = s.next().charAt(0);
		} while (tOrF != 't' && tOrF != 'f');

		boolean b = false;
		if (tOrF == 't')
			b = true;

		int ansToAdd = 0;
		int[] limArrayIndex = AR.closedAnsLimitedArray(q.getAnswerList());
		System.out.println("choose an answer from the repository to the Query: ");
		System.out.println(AR.closedAnsLimitedtoString(limArrayIndex));
		do {
			try {
				ansToAdd = s.nextInt() - 1;
			} catch (InputMismatchException e) {
				System.out.println("enter a number");
				s.next();
			} 
		} while (!(AR.isInLimitedArray(ansToAdd, limArrayIndex)));
			
		Answer nA = new Answer(ansToAdd, b, AR, eType.close);
		try {
			((closedQuery) QR.getAllQueryArray()[qIndex]).addAnswerToQuery(nA);
		} catch (Exception e) {
			System.out.println(e.getMessage());	
		}
		
	}

	public static void rmAnswerFromQues_5(int qIndex) {
		closedQuery cQ = ((closedQuery) QR.getAllQueryArray()[qIndex]);

		System.out.println(QR.getAllQueryArray()[qIndex].toString());

		// TODO try catch
		int ansToRm;
		do {
			System.out.println("what answer would you like to remove: ");
			ansToRm = s.nextInt() - 1;
		} while (ansToRm > cQ.getAnswerList().length && ansToRm <= 0);

		cQ.rmAnAnswer(ansToRm);
		System.out.println("answer removed!");
	}

	public static void updateAnswerOpenQuery_5(int qIndex) {
		System.out.println("would you like to write a new answer or choose from repository: <w/r>");

		// TODO try catch
		char newOrRep;
		do {
			newOrRep = s.next().charAt(0);
		} while (newOrRep != 'w' && newOrRep != 'r');

		if (newOrRep == 'w') {
			System.out.println("write a new answer to the question: ");
			String newAns = s.nextLine();
			AR.addOpenAnswer(newAns);
			Answer nA = new Answer(AR.getOpenAns().length - 1, AR, eType.open);
			((openQuery) QR.getAllQueryArray()[qIndex]).setSchoolAnswer(nA);
		} else {
			AR.openAnstoString();
			// TODO try catch
			int ansToAdd;
			do {
				System.out.println("choose an answer from the repository: ");
				ansToAdd = s.nextInt();
			} while (ansToAdd < AR.getOpenAns().length);
			Answer nA = new Answer(ansToAdd, AR, eType.open);
			((openQuery) QR.getAllQueryArray()[qIndex]).setSchoolAnswer(nA);
		}
	}

	// removing a question
	public static void rmQuestion_6() {
		System.out.println(QR.toString());

		// TODO try catch
		int qToRm;
		do {
			System.out.println("what Query would you like to remove: ");
			qToRm = s.nextInt() - 1;
			if (qToRm < QR.getAllQueryArray().length && qToRm >= 0) {
				QR.rmQuery(qToRm);
			}
		} while (qToRm > QR.getAllQueryArray().length || qToRm < 0);
	}

	// creating a personal test
	public static void personalTest_7() throws FileNotFoundException {
		System.out.println("how many question will there be in the test: ");
		int questionAmount = s.nextInt();

		Query[] examQuerries = new Query[questionAmount];
		int[] addedQuerries = new int[questionAmount];

		int qToAdd = 0;
		do {
			System.out.println("what question would you like to add: ");
			System.out.println(QR.toString());
			qToAdd = s.nextInt() - 1;

			// checking if the q was already in the new array
			boolean wasQpicked = false;
			if (qToAdd >= 0 && qToAdd < QR.getAllQueryArray().length) {
				wasQpicked = true;
				for (int i = 0; i < addedQuerries.length; i++) {
					if (qToAdd + 1 == addedQuerries[i]) {
						wasQpicked = false;
					}
				}
			}

			if (wasQpicked && (QR.getAllQueryArray()[qToAdd]) instanceof closedQuery) {
				// to create a new object distinct from the og
				closedQuery q0 = ((closedQuery) (QR.getAllQueryArray()[qToAdd]));
				closedQuery q = new closedQuery(q0.getQues(), q0.getDiff(), QR, q0.getAnswerList());

				System.out.println(q.toString());
				System.out.println("which answers would you like to add to the question in the test: (-1 to stop) ");

				Answer[] answersForExam = answersOutOfQurries(q);

				q.setAnswerList(answersForExam);
				examQuerries[examQuerries.length - questionAmount] = q;
				addedQuerries[addedQuerries.length - questionAmount] = qToAdd + 1;
				questionAmount--;
				System.out.println("Question added!");

			} else if (wasQpicked && (QR.getAllQueryArray()[qToAdd]) instanceof openQuery) {
				System.out.println("open Query");
				examQuerries[examQuerries.length - questionAmount] = QR.getAllQueryArray()[qToAdd];
				addedQuerries[addedQuerries.length - questionAmount] = qToAdd + 1;
				questionAmount--;
				System.out.println("Question added!");
			}
		} while (questionAmount > 0);

		writeTestResToFile(examQuerries);
		writeTestToFile(examQuerries);
	}

	public static Answer[] answersOutOfQurries(closedQuery q) {
		Answer[] answersForExam = new Answer[0];
		int[] addedAnswers = new int[q.getAnswerList().length];
		int ansToAdd, t = 0;
		do {
			ansToAdd = s.nextInt() - 1;

			boolean bool = false;
			if (ansToAdd >= 0 && ansToAdd < q.getAnswerList().length) {
				bool = true;
				for (int i = 0; i < answersForExam.length; i++) {
					if (ansToAdd + 1 == addedAnswers[i]) {
						bool = false;
					}
				}
			}
			if (bool) {
				answersForExam = Arrays.copyOf(answersForExam, answersForExam.length + 1);
				answersForExam[answersForExam.length - 1] = q.getAnswerList()[ansToAdd];
				addedAnswers[t++] = ansToAdd + 1;
				System.out.println("answer added!");
			}
		} while (ansToAdd != -2 && answersForExam.length < q.getAnswerList().length);

		return answersForExam;
	}

	public static void writeTestResToFile(Query[] qList) throws FileNotFoundException {
		// formating the time
		LocalDateTime time = LocalDateTime.now();
		DateTimeFormatter timeFormat = DateTimeFormatter.ofPattern("yyyy_MM_dd_HH_mm");
		String rightNow = time.format(timeFormat);
		// there is a problem with my eclipse that it doesnt save the files to the
		// project for some reason so i created a file in the desktop.
		String fn = "C:\\Users\\omer_\\Desktop\\exam_res_" + rightNow + ".txt";
		PrintWriter pw = new PrintWriter(fn);

		pw.println("test");
		pw.println();

		// printing the test
		for (int i = 0; i < qList.length; i++) {
			pw.println(i + 1 + ")  " + qList[i].toStringForTestRes());
			pw.println();
		}

		pw.close();
	}

	public static void writeTestToFile(Query[] qList) throws FileNotFoundException {
		// formating the time
		LocalDateTime time = LocalDateTime.now();
		DateTimeFormatter timeFormat = DateTimeFormatter.ofPattern("yyyy_MM_dd_HH_mm");
		String rightNow = time.format(timeFormat);
		// there is a problem with my eclipse that it doesnt save the files to the
		// project for some reason so i created a file in the desktop.
		String fn = "C:\\Users\\omer_\\Desktop\\exam_" + rightNow + ".txt";
		File testFile = new File(fn);

		PrintWriter pw = new PrintWriter(testFile);

		pw.println("test");
		pw.println();

		// printing the test
		for (int i = 0; i < qList.length; i++) {
			pw.println(i + 1 + ")  " + qList[i].toStringForTest());
			pw.println();
		}

		pw.close();

	}

	public static void hello() throws FileNotFoundException, IOException, ClassNotFoundException {
		QR.readFromFile();
		AR.readFromFile();
	}
	
	public static void goodbye() throws FileNotFoundException, IOException {
		QR.saveToFile();
		AR.saveToFile();
	}

}
