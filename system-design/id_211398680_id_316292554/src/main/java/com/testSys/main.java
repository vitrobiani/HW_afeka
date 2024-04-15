
package com.testSys;



import java.io.*;
import java.time.*;
import java.time.format.DateTimeFormatter;
import java.util.*;

import com.testSys.Answer.eType;
import com.testSys.Query.difficulty;

public class main {
	public static Scanner s = new Scanner(System.in);
	public static int SubIn = -1;
	public static SubjectRepository SR = new SubjectRepository();
	
	public static void main(String[] args) throws Exception {
		try {
			hello();
		} catch (FileNotFoundException e) {
			System.out.println("no backup files found");
		} catch (Exception e1) {
			System.out.println("an error happend loading the backup");
			System.out.println(e1.getMessage());
		}
		
		subjectChoose();
		
	}

	public static void subjectChoose() throws Exception {
		System.out.println("1. choose a subject \n" + "2. create a new subject \n"
				+ "3. delete a subject");
		int choise = 0;
		do {
			try {
				choise = s.nextInt();
			} catch (InputMismatchException e) {
				System.out.println("enter a numer");
				s.next();
			} 
		} while (choise == 0);
		
		switch(choise) {
		case 1:{
			break;
		}
		case 2:{
			createNewSubject();
			break;
		}
		case 3:{
			rmSubject();
			break;
		}
		}
		
		System.out.println("what subject would you like to choose: \n");
		do {
			System.out.println(SR.toString());
			try {
				SubIn = s.nextInt()-1;
			} catch (InputMismatchException e) {
				System.out.println("enter a number");
				s.next();
			} 
		} while (SubIn >= SR.getSR().length || SubIn < 0);
		
		lobby();
		
	}
	
	public static void createNewSubject() throws Exception {		
		char add;
		do {
			s.nextLine();
			System.out.println("what is the name of the subject:  \n");
			String subName = s.nextLine();
			if(SR.addSubject(subName)) System.out.println("added!");;
			System.out.println(SR.toString());
			
			System.out.println("would you like to add another <y/n>:  ");
			add = s.next().charAt(0);
			
		} while (add != 'n');
		subjectChoose();
	}
	
	public static void rmSubject() throws Exception {		
		System.out.println(SR.toString());
		int choise = 0;
		do {
			System.out.println("which one would you like to remove: ");
			try {
				choise = s.nextInt()-1;
			} catch (InputMismatchException e) {
				System.out.println("enter a number!");
				s.next();
			} 
		} while (choise < 0 || choise > SR.getSR().length);
		
		SR.rmSubject(choise);
		subjectChoose();
	}
	
	public static void lobby() throws Exception {
		int choise = -1;
		do {
			System.out.println("the subject: " + SR.getSR()[SubIn].getName() 
					+ "\n hello what would you like to do? \n"
					+ "1. print out all the questions and its answers in the repository \n"
					+ "2. print all the answers in the repository" + "\n"
					+ "3. adding a new answer to the repository \n" + "4. adding a new question \n"
					+ "5. updating answers to a question (add, remove, update) \n"
					+ "6. removing a question from the repository \n" + "7. creating a test manually \n"
					+ "8. go back to subject choise \n" + "0. exit \n");
			
			try {
				choise = s.nextInt();
			} catch (InputMismatchException e) {
				System.out.println("enter a number!");
				s.next();
			}
			s.nextLine();
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
			case 8: {
				subjectChoose();;
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
		System.out.println(SR.QRtoString(SubIn));
		System.out.println("finished printing");
	}

	// printing the answer repository
	public static void printAnsRep_2() {
		System.out.println("printing Answers!");
		System.out.println(SR.ARtoString(SubIn));
		System.out.println("finished printing!");
	}

	// adding new answer to repository
	public static void addNewAnswerToRepository_3() {

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

	// created distinct functions for adding answers because their useful in other functions as well
	public static void addNewClosedAnswerToRep_3() {
		s.nextLine(); // clear buffer
		System.out.println("write the answer:  ");
		String newAns = s.nextLine();
		if (SR.getSR(SubIn).getAR().addCloseAnswer(newAns)) {
			System.out.println("added answer!");
		} else {
			System.out.println("answer already in repository");
		}
	}

	public static void addNewOpenAnswerToRep_3() {
		s.nextLine(); // clear buffer
		System.out.println("write the answer:  ");
		String newAns = s.nextLine();
		if (SR.getSR(SubIn).getAR().addOpenAnswer(newAns)) {
			System.out.println("added answer!");
		} else {
			System.out.println("answer already in repository");
		}
	}

	// adding a question to the Query repository
	public static void addQ_4() throws AnswerException {
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

	public static void addClosedQ_4(int diff, String Ques) throws AnswerException {
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
		closedQuery newClosedQuery = new closedQuery(Ques, difficulty.values()[diff], SR.getSR(SubIn).getQR(), AnswerList);

		int ansToAdd = 0;
		int answerArrIndex = 0;
		try {
			do {
				System.out.println("choose a correct answer from the repository to the Query: <enter -1 to stop>");
				// printing only what was not chosen by the user
				System.out.println(SR.closedAnsLimitedtoString(SR.closedAnsLimitedArray(newClosedQuery.getAnswerList(), SubIn) ,SubIn));
				try {
					ansToAdd = s.nextInt() - 1;
				} catch (InputMismatchException e) {
					System.out.println("enter a number");
					s.next();
				}

				if (ansToAdd >= 0 && ansToAdd < SR.getSR(SubIn).getAR().getClosedAns().length
						&& newClosedQuery.addAnswerToQuery(ansToAdd, true, SR.getSR(SubIn).getAR())) {
					answerArrIndex++;
					System.out.println("answer added!");
				} else {
					System.out.println("answer was not added");
				}
			} while (ansToAdd != -2 && answerArrIndex < newClosedQuery.getMaxAns());

			if (answerArrIndex < newClosedQuery.getMaxAns()) {
				do {
					System.out.println("choose an incorrect answer from the repository to the Query: <enter -1 to stop>");
					System.out.println(SR.getSR(SubIn).getAR().closedAnsLimitedtoString(SR.getSR(SubIn).getAR().closedAnsLimitedArray(newClosedQuery.getAnswerList())));

					try {
						ansToAdd = s.nextInt() - 1;
					} catch (InputMismatchException e) {
						System.out.println("enter a number");
						s.next();
					}
					
					if (ansToAdd >= 0 && ansToAdd < SR.getSR(SubIn).getAR().getClosedAns().length
							&& newClosedQuery.addAnswerToQuery(ansToAdd, false, SR.getSR(SubIn).getAR())) {
						answerArrIndex++;
						System.out.println("answer added!");
					} else {
						System.out.println("answer was not added");
					}
				} while (ansToAdd != -2 && answerArrIndex < newClosedQuery.getMaxAns());
			}
			if (answerArrIndex < 3) {
				throw new AnswerException();
			}
		} catch (AnswerException e) {
			System.out.println(e.getMessage());
		}
		if (answerArrIndex > 3 && SR.getSR(SubIn).getQR().addQuery(newClosedQuery)) {
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
			Answer newOpenAns = new Answer((SR.getSR(SubIn).getAR().getOpenAns().length - 1), SR.getSR(SubIn).getAR(), eType.open);
			newOpenQuery = new openQuery(Ques, difficulty.values()[diff], SR.getSR(SubIn).getQR(), newOpenAns);
		} else {
			System.out.println(SR.getSR(SubIn).getAR().openAnstoString());

			// TODO try-catch
			int ansChoose = 0;
			do {
				ansChoose = s.nextInt() - 1;
			} while (ansChoose >= SR.getSR(SubIn).getAR().getOpenAns().length && ansChoose < 0);

			Answer newOpenAns = new Answer(ansChoose, SR.getSR(SubIn).getAR(), eType.open);
			newOpenQuery = new openQuery(Ques, difficulty.values()[diff], SR.getSR(SubIn).getQR(), newOpenAns);
		}
		if (SR.getSR(SubIn).getQR().addQuery(newOpenQuery)) {
			System.out.println("Query added!");
		} else {
			System.out.println("Query already exists");
		}
	}

	// updating is deleting and changing answer to Query
	public static void updatingAnAnswerToQues_5() {
		System.out.println(SR.getSR(SubIn).getQR().toString());

		int qIndex=0;
		do {
			System.out.println("what question would you like to add to or update: ");
			try {
				qIndex = s.nextInt() - 1;
			} catch (InputMismatchException e) {
				System.out.println("enter a number");
				s.next();
			}
		} while (qIndex > SR.getSR(SubIn).getQR().getAllQueryArray().length && qIndex <= 0);

		if (SR.getSR(SubIn).getQR().getAllQueryArray()[qIndex].getClass().equals(closedQuery.class)) {
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
		closedQuery q = ((closedQuery) SR.getSR(SubIn).getQR().getAllQueryArray()[qIndex]);
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
		int[] limArrayIndex = SR.getSR(SubIn).getAR().closedAnsLimitedArray(q.getAnswerList());
		System.out.println("choose an answer from the repository to the Query: ");
		System.out.println(SR.getSR(SubIn).getAR().closedAnsLimitedtoString(limArrayIndex));
		do {
			try {
				ansToAdd = s.nextInt() - 1;
			} catch (InputMismatchException e) {
				System.out.println("enter a number");
				s.next();
			} 
		} while (!(SR.getSR(SubIn).getAR().isInLimitedArray(ansToAdd, limArrayIndex)));
			
		Answer nA = new Answer(ansToAdd, b, SR.getSR(SubIn).getAR(), eType.close);
		try {
			((closedQuery) SR.getSR(SubIn).getQR().getAllQueryArray()[qIndex]).addAnswerToQuery(nA);
		} catch (Exception e) {
			System.out.println(e.getMessage());	
		}
		
	}

	public static void rmAnswerFromQues_5(int qIndex) {
		closedQuery cQ = ((closedQuery) SR.getSR(SubIn).getQR().getAllQueryArray()[qIndex]);

		System.out.println(SR.getSR(SubIn).getQR().getAllQueryArray()[qIndex].toString());

		int ansToRm = -1;
		do {
			System.out.println("what answer would you like to remove: ");
			try {
				ansToRm = s.nextInt() - 1;
			} catch (InputMismatchException e) {
				System.out.println("enter a number");
				s.next();
			}
		} while (ansToRm > cQ.getAnswerList().length && ansToRm <= 0);

		cQ.rmAnAnswer(ansToRm);
		System.out.println("answer removed!");
	}

	public static void updateAnswerOpenQuery_5(int qIndex) {
		System.out.println("would you like to write a new answer or choose from repository: <w/r>");
		
		char newOrRep;
		do {
			newOrRep = s.next().charAt(0);
		} while (newOrRep != 'w' && newOrRep != 'r');

		if (newOrRep == 'w') {
			System.out.println("write a new answer to the question: ");
			String newAns = s.nextLine();
			SR.getSR(SubIn).getAR().addOpenAnswer(newAns);
			Answer nA = new Answer(SR.getSR(SubIn).getAR().getOpenAns().length - 1, SR.getSR(SubIn).getAR(), eType.open);
			((openQuery) SR.getSR(SubIn).getQR().getAllQueryArray()[qIndex]).setSchoolAnswer(nA);
		} else {
			SR.getSR(SubIn).getAR().openAnstoString();
			// TODO try catch
			int ansToAdd;
			do {
				System.out.println("choose an answer from the repository: ");
				ansToAdd = s.nextInt();
			} while (ansToAdd < SR.getSR(SubIn).getAR().getOpenAns().length);
			Answer nA = new Answer(ansToAdd, SR.getSR(SubIn).getAR(), eType.open);
			((openQuery) SR.getSR(SubIn).getQR().getAllQueryArray()[qIndex]).setSchoolAnswer(nA);
		}
	}

	// removing a question
	public static void rmQuestion_6() {
		System.out.println(SR.getSR(SubIn).getQR().toString());

		int qToRm = 0;
			System.out.println("what Query would you like to remove: ");
			do {
				try {
					qToRm = s.nextInt() - 1;
				} catch (InputMismatchException e) {
					System.out.println("enter a number");
					s.next();
				} 
			} while (qToRm < 0 || qToRm > SR.getAllQueryArray(SubIn).length);
			
			SR.getSR(SubIn).getQR().rmQuery(qToRm);
	}

	// creating a personal test
	public static void personalTest_7() throws Exception {
		System.out.println("how many questions will there be in the test: ");
		int questionAmount=0;
		do {
			try {
				questionAmount = s.nextInt();
				if (questionAmount < 10) {
					throw new ExamException();
				}
			} catch (InputMismatchException e) {
				System.out.println("enter a number");
				s.next();
			} catch (ExamException e1) {
				System.out.println(e1.getMessage());
			}
		} while (questionAmount <= 0 || questionAmount > SR.getAllQueryArray(SubIn).length);
		
		System.out.println("would you like to do an automatic exam or manualy create one <a/m>");
		char autoOrMan;
		do {
			autoOrMan = s.next().charAt(0);
		} while (autoOrMan != 'a' && autoOrMan != 'm');
		
		createExam ce = new createExam(SR.getSR(SubIn), questionAmount);
		
		if (autoOrMan == 'm') {
			manualExam(questionAmount, ce);
		}else {
			ce.AutomaticExam();
		}
	}
	
	public static closedQuery closedQueryWithSpesificAns(QueryRepository Querries, int i) throws Exception {
		closedQuery q = (closedQuery) Querries.getQuery(i);
		closedQuery copyQ = new closedQuery(q.getQues(),q.getDiff() ,q.getQR() , q.getAnswerList());
		q.setAnswerList(new Answer[0]);
		char b = 0;
		do {
			System.out.println(copyQ.toString());
			System.out.println("what answers from the Query would you like to be presented in the test:  ");
			int ansToAdd = -1;
			try {
				ansToAdd = s.nextInt();
			} catch (Exception e) {
				System.out.println("enter a number");
				s.next();
			}
			if (ansToAdd >= 0 && ansToAdd < copyQ.getAnswerList().length) {
				q.addAnswerToQuery(copyQ.getAnswerList()[ansToAdd]);
				copyQ.rmAnAnswer(ansToAdd);
			}
			System.out.println("would you like to pick another one? <y/n>");
			b = s.next().charAt(0);
		} while(b != 'n');
		return q;
	}
	
	public static void manualExam(int questionAmount, createExam ce) throws Exception {
		QueryRepository examQuerries = new QueryRepository();
		QueryRepository copyQueryRep = new QueryRepository(SR.getAllQueryArray(SubIn));
		
		while (questionAmount != 0) {
			
			int QToAdd = 1;
			do {
				System.out.println(copyQueryRep.toString());
				System.out.println("choose a Query to add to the test:  ");
				try {
					QToAdd = s.nextInt()-1;
				} catch (InputMismatchException e) {
					System.out.println("enter a number");
					s.next();
				} 
				System.out.println(copyQueryRep.length());
			} while (QToAdd > 0 && QToAdd <= copyQueryRep.length());
			
			if (copyQueryRep.getAllQueryArray()[QToAdd] instanceof closedQuery) {
				closedQuery q = closedQueryWithSpesificAns(copyQueryRep, QToAdd);
				if(examQuerries.addQuery(q)) {
					System.out.println("added!");
					copyQueryRep.rmQuery(QToAdd);									
					questionAmount--;
				};
			} else {
				if(examQuerries.addQuery(copyQueryRep.getAllQueryArray()[QToAdd])) {
					System.out.println("added!");
					copyQueryRep.rmQuery(QToAdd);									
					questionAmount--;
				}
			}
		}
		ce.setExamQueries(examQuerries);
		ce.ManualExam();
	}
	
	public static void hello() throws FileNotFoundException, IOException, ClassNotFoundException {
		SR.readFromFile();
	}
	
	public static void goodbye() throws FileNotFoundException, IOException {
		SR.saveToFile();
	}


}
