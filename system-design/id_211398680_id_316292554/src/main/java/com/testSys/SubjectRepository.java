
package com.testSys;



import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Arrays;

public class SubjectRepository {
	public static Subject[] SR = new Subject[0];

	public Subject[] getSR() {
		return SR;
	}

	public static void setSR(Subject[] sR) {
		SR = sR;
	}
	
	public Subject getSR(int i) {
		return SR[i];
	}

	public boolean isSubjectInRep(Subject s) {
		for (int i = 0; i < SR.length; i++) {
			if (SR[i].equals(s))
				return true;
		}
		return false;
	}

	public boolean addSubject(Subject s) {
		if (!(isSubjectInRep(s))) {
			Subject[] newSList = Arrays.copyOf(SR, SR.length + 1);
			newSList[newSList.length - 1] = s;
			SR = newSList;
			return true;
		}
		return false;
	}
	
	public boolean addSubject(String name) {
		Subject s = new Subject(name);
		if (!(isSubjectInRep(s))) {
			Subject[] newSList = Arrays.copyOf(SR, SR.length + 1);
			newSList[newSList.length - 1] = s;
			SR = newSList;
			return true;
		}
		return false;
	}

	public void rmSubject(int index) {
		Subject[] newSubjectArray = new Subject[SR.length - 1];
		int k = 0;
		for (int i = 0; i < SR.length; i++) {
			if (i != index) {
				newSubjectArray[k++] = SR[i];
			}
		}
		setSR(newSubjectArray);
	}
	
	public AnswerRepository getAR(int i) {
		return SR[i].getAR();
	}
	
	public QueryRepository getQR(int i) {
		return SR[i].getQR();
	}

	public String getName(int i) {
		return SR[i].getName();
	}

	public void setName(String name, int i) {
		SR[i].setName(name);
	}

	public boolean addQuery(Query q, int i) {
		return SR[i].addQuery(q);
	}

	public void rmQuery(int index, int i) {
		SR[i].rmQuery(index);
	}

	public Query[] getAllQueryArray(int i) {
		return SR[i].getAllQueryArray();
	}

	public openQuery[] getOpenQueryArray(int i) {
		return SR[i].getQR().getOpenQueryArray();
	}

	public closedQuery[] getClosedQueryArray(int i) {
		return SR[i].getQR().getClosedQueryArray();
	}

	public String closedQuerytoString(int i) {
		return SR[i].getQR().closedQuerytoString();
	}

	public String openQuerytoString(int i) {
		return SR[i].getQR().openQuerytoString();
	}

	public String[] getClosedAns(int i) {
		return SR[i].getAR().getClosedAns();
	}

	public String[] getOpenAns(int i) {
		return SR[i].getAR().getOpenAns();
	}
	
	public String closedAnstoString(int i) {
		return SR[i].getAR().closedAnstoString();
	}

	// so that the user won't see the answer he already chose
	public String closedAnsLimitedtoString(int[] toShowAnswerList, int i) {
		return SR[i].getAR().closedAnsLimitedtoString(toShowAnswerList);
	}
	
	public int[] closedAnsLimitedArray(Answer[] AnswerList, int i) {
		return SR[i].getAR().closedAnsLimitedArray(AnswerList);
	}
	
	public boolean isInLimitedArray(int i, int[] arr, int j) {
		return SR[j].getAR().isInLimitedArray(i, arr);		
	}
 
	public String openAnstoString(int i) {
		return SR[i].getAR().openAnstoString();
	}

	public void saveToFile() throws FileNotFoundException, IOException {
		ObjectOutputStream outFile = new ObjectOutputStream(
				new FileOutputStream("//home//vitrobiani//Documents//proj_files//SR.dat"));
		outFile.writeObject(SR);
		outFile.close();
	}
	
	public void readFromFile() throws FileNotFoundException, IOException, ClassNotFoundException {
		ObjectInputStream inFile = new ObjectInputStream(
				new FileInputStream("//home//vitrobiani//Documents//proj_files//SR.dat"));
		Subject[] sub = (Subject[]) inFile.readObject();
		inFile.close();
		setSR(sub);
	}
	
	public void writeTestToFile(QueryRepository examQuerries, int i) throws FileNotFoundException {
		SR[i].writeTestToFile(examQuerries);
	}
	
	public String QRtoString(int i) {
		return SR[i].QRtoString();
	}
	
	public String ARtoString(int i) {
		return SR[i].ARtoString();
	}
		
	@Override
	public String toString() {
		 StringBuffer s = new StringBuffer();
		 s.append("\n all Subjects:   " + '\n');
		 for (int i = 0; i < SR.length; i++) {
			s.append((i+1) + ")  " + SR[i].getName() + '\n');
		}
		return s.toString();
	}
	
	public boolean equals(SubjectRepository s) {
		for (int i = 0; i < SR.length; i++) {
			boolean isEqual = true;
			for (int j = 0; j < s.getSR().length; j++) {
				isEqual = true;
				if (!(SR[i].equals(s.getSR()[j]))) {
					isEqual = false;
				}
			}
			if (!(isEqual)) {
				return false;
			}
		}
		return true;
	}
}
