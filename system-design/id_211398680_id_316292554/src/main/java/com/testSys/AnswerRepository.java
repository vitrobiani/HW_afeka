
package com.testSys;


import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.Arrays;

public class AnswerRepository implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public String[] closeAnswerList = new String[0];
	public String[] openAnswerList = new String[0];
	
	public String[] getClosedAns() {
		return closeAnswerList;
	}

	public String[] getOpenAns() {
		return openAnswerList;
	}

	public void setCloseAnswerList(String[] closeAnswerList) {
		this.closeAnswerList = closeAnswerList;
	}

	public void setOpenAnswerList(String[] openAnswerList) {
		this.openAnswerList = openAnswerList;
	}
	
	public String getClosedAns(int i) {
		return closeAnswerList[i];
	}

	public String getOpenAns(int i) {
		return openAnswerList[i];
	}

	public boolean isAnsInClosedAnsRep(String nA) {
		for (int i = 0; i < closeAnswerList.length; i++) {
			if (nA == closeAnswerList[i])
				return true;
		}
		return false;
	}

	public boolean isAnsInOpenAnsRep(String nA) {
		for (int i = 0; i < openAnswerList.length; i++) {
			if (nA == openAnswerList[i])
				return true;
		}
		return false;
	}

	public boolean addCloseAnswer(String nA) {
		if (!(isAnsInClosedAnsRep(nA))) {
			String[] newAnswerList = Arrays.copyOf(closeAnswerList, closeAnswerList.length + 1);
			newAnswerList[newAnswerList.length - 1] = nA;
			closeAnswerList = newAnswerList;
			return true;
		}
		return false;
	}

	public boolean addOpenAnswer(String nA) {
		if (!(isAnsInOpenAnsRep(nA))) {
			String[] newAnswerList = Arrays.copyOf(openAnswerList, openAnswerList.length + 1);
			newAnswerList[newAnswerList.length - 1] = nA;
			openAnswerList = newAnswerList;
			return true;
		}
		return false;
	}

	public void rmCloseAnswer(int j) {
		String[] newAnswerList = Arrays.copyOf(closeAnswerList, closeAnswerList.length - 1);

		for (int i = 0, k = 0; i < newAnswerList.length; i++) {
			if (i != j) {
				newAnswerList[k++] = closeAnswerList[i];
			}
		}

		closeAnswerList = newAnswerList;
	}

	public void rmOpenAnswer(int j) {
		String[] newAnswerList = Arrays.copyOf(openAnswerList, openAnswerList.length - 1);

		for (int i = 0, k = 0; i < newAnswerList.length; i++) {
			if (i != j) {
				newAnswerList[k++] = openAnswerList[i];
			}
		}

		openAnswerList = newAnswerList;
	}

	public void updateCloseAnswer(int i, String nA) {
		closeAnswerList[i] = nA;
	}

	public void updateOpenAnswer(int i, String nA) {
		openAnswerList[i] = nA;
	}

	public String closedAnstoString() {
		StringBuffer A = new StringBuffer();
		A.append("\n the closed answers: \n");
		for (int i = 0; i < closeAnswerList.length; i++) {
			String temp = ((i + 1) + ")  " + closeAnswerList[i] + "\n");
			A.append(temp);
		}
		return A.toString();
	}

	// so that the user won't see the answer he already chose
	public String closedAnsLimitedtoString(int[] toShowAnswerList) {
		StringBuffer A = new StringBuffer();
		A.append("\n the closed answers: \n");
		for (int i = 0; i < toShowAnswerList.length; i++) {
			String temp = ((toShowAnswerList[i] + 1) + ")  " + closeAnswerList[toShowAnswerList[i]] + "\n");
			A.append(temp);
		}
		return A.toString();
	}
	
	public int[] closedAnsLimitedArray(Answer[] AnswerList) {
		int[] newAnswerList = new int[closeAnswerList.length - AnswerList.length];
		
		for (int i = 0, k = 0; i < closeAnswerList.length; i++) {
			boolean toAdd = true;
			for (int j = 0; (j < AnswerList.length) ; j++) {
				if (closeAnswerList[i] == AnswerList[j].getAnswer()) {
					toAdd = false;
				}
			}
			if (toAdd) {
				newAnswerList[k++] = i;
			}
		}
		return newAnswerList;
	}
	
	public boolean isInLimitedArray(int i, int[] arr) {
		for (int j = 0; j < arr.length; j++) {
			if (i == arr[j]) return true;
		}
		return false;
		
	}
 
	public String openAnstoString() {
		StringBuffer A = new StringBuffer();
		A.append("\n the open answers: \n");
		for (int i = 0; i < openAnswerList.length; i++) {
			String temp = ((i + 1) + ")  " + openAnswerList[i] + "\n");
			A.append(temp);
		}
		return A.toString();
	}

	public void saveToFile() throws FileNotFoundException, IOException {
		ObjectOutputStream outFile1 = new ObjectOutputStream(new FileOutputStream("//home//vitrobiani//Documents//proj_files//closeAnswerRep.dat"));
		outFile1.writeObject(closeAnswerList);
		outFile1.close();

		ObjectOutputStream outFile2 = new ObjectOutputStream(new FileOutputStream("//home//vitrobiani//Documents//proj_files//openAnswerRep.dat"));
		outFile2.writeObject(openAnswerList);
		outFile2.close();
	}
	
	public void readFromFile() throws FileNotFoundException, IOException, ClassNotFoundException {
		ObjectInputStream inFile1 = new ObjectInputStream(new FileInputStream("//home//vitrobiani//Documents//proj_files//closeAnswerRep.dat"));
		String[] arr1 = (String[]) inFile1.readObject();
		inFile1.close();
		closeAnswerList = arr1;

		ObjectInputStream inFile2 = new ObjectInputStream(new FileInputStream("//home//vitrobiani//Documents//proj_files//openAnswerRep.dat"));
		String[] arr2 = (String[]) inFile2.readObject();
		inFile2.close();
		openAnswerList = arr2;
	}
	
	public String toString() {
		StringBuffer A = new StringBuffer();
		A.append("\n the closed answers: \n");
		for (int i = 0; i < closeAnswerList.length; i++) {
			String temp = ((i + 1) + ")  " + closeAnswerList[i] + "\n");
			A.append(temp);
		}
		A.append("\n the open answers: \n");
		for (int i = 0; i < openAnswerList.length; i++) {
			String temp = ((i + 1) + ")  " + openAnswerList[i] + "\n");
			A.append(temp);
		}
		return A.toString();
	}
	
	public boolean equals(AnswerRepository A) {
		return false;
	}
}
