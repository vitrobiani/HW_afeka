
package com.testSys;


import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.InputMismatchException;
import java.util.Iterator;
import java.util.Random;

public class createExam implements Examable {
	private int questionAmount;
	private static final int autoAns = 4;
	private QueryRepository examQueries;
	private Subject sub;
	
	//for manual
	public createExam(QueryRepository examQueries, int amount) {
		this.examQueries = examQueries;
		questionAmount = amount;
	}
	
	//for automatic exam
	public createExam(Subject sub, int amount) {
		this.sub = sub;
		questionAmount = amount;
	}
	
	@Override
	public void ManualExam() throws FileNotFoundException, Exception {
		writeTestToFile();
	}

	@Override
	public void AutomaticExam() throws Exception {		
		Random r = new Random();
		QueryRepository examQuerries = new QueryRepository();
		QueryRepository copyQueryRep = new QueryRepository(sub.getAllQueryArray());
		
		int[] randomQueryIndexArray = new int[questionAmount];
		for (int i = 0; i < randomQueryIndexArray.length; i++) {
			boolean bool;
			int temp;
			do {
				bool = false;
				temp = r.nextInt(0, copyQueryRep.length() );
				for (int j = 0; j < randomQueryIndexArray.length; j++) {
					if (temp == randomQueryIndexArray[j]) {
						bool = true;
					}
				}
			} while (bool);
			randomQueryIndexArray[i] = temp;
		}
		
		for (int i = 0; i < randomQueryIndexArray.length; i++) {
			int QToAdd = randomQueryIndexArray[i];
			if (copyQueryRep.getAllQueryArray()[QToAdd] instanceof closedQuery) {
				closedQuery q = closedQueryWithSpesificAns((closedQuery)copyQueryRep.getAllQueryArray()[QToAdd]);
				if (examQuerries.addQuery(q)) {
					System.out.println("added query");
				}
			} else {
				if (examQuerries.addQuery(copyQueryRep.getAllQueryArray()[QToAdd])) {
					System.out.println("added query");
				}
			} 
		}
		setExamQueries(examQuerries);
		writeTestToFile();
	}

	public closedQuery closedQueryWithSpesificAns(closedQuery q) throws Exception {
		Random r = new Random();
		closedQuery copyQ = new closedQuery(q.getQues(),q.getDiff() ,q.getQR() , q.getAnswerList());
		Answer[] AnswerList = new Answer[0];
		closedQuery copyq = new closedQuery(q.getQues(),q.getDiff() ,q.getQR() , AnswerList);
 		copyq.setAnswerList(AnswerList);
		
		int[] randomAns = new int[autoAns];
		for (int k = 0; k < randomAns.length; k++) {
			boolean bool;
			int temp;
			do {
				bool = false;
				temp = r.nextInt(0, q.getAnswerList().length );
				for (int j = 0; j < randomAns.length; j++) {
					if (temp == randomAns[j]) {
						bool = true;
					}
				}
			} while (bool);
			randomAns[k] = temp;
		}
	
		for (int j = 0; j < randomAns.length; j++) {
			Answer a = copyQ.getAnswerList()[randomAns[j]];
			copyq.addAnswerToQuery(a);
		}
		return copyq;
	}
	
	public void writeTestToFile() throws FileNotFoundException {
		// formating the time
		LocalDateTime time = LocalDateTime.now();
		DateTimeFormatter timeFormat = DateTimeFormatter.ofPattern("yyyy_MM_dd_HH_mm");
		String rightNow = time.format(timeFormat);
		// there is a problem with my eclipse that it doesn't save the files to the
		// project for some reason so i created a file in documents.
		String fnRes = "C:\\Users\\omer_\\Documents\\filesFromEclipse\\testFiles\\exam_res_" + rightNow + ".txt";
		PrintWriter pwRes = new PrintWriter(fnRes);
		String fn = "C:\\Users\\omer_\\Documents\\filesFromEclipse\\testFiles\\exam_" + rightNow + ".txt";
		File testFile = new File(fn);

		PrintWriter pw = new PrintWriter(testFile);

		pw.println("test");
		pw.println();
			
		pwRes.println("test");
		pwRes.println();

		
		// printing the test
		for (int i = 0; i < examQueries.length(); i++) {
			pw.println(i + 1 + ")  " + examQueries.getAllQueryArray()[i].toStringForTest());
			pw.println();
			pwRes.println(i + 1 + ")  " + examQueries.getAllQueryArray()[i].toStringForTestRes());
			pwRes.println();
		}

		pw.close();
		pwRes.close();
	}
	
	public int getQuestionAmount() {
		return questionAmount;
	}

	public void setQuestionAmount(int questionAmount) {
		this.questionAmount = questionAmount;
	}
	
	public QueryRepository getExamQueries() {
		return examQueries;
	}
		
	public void setExamQueries(QueryRepository examQueries) {
		this.examQueries = examQueries;
	}
	
	public Subject getSub() {
		return sub;
	}
	
	public void setSub(Subject sub) {
		this.sub = sub;
	}
}
