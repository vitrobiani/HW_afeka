
package com.testSys;


import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.io.Serializable;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Arrays;
import java.util.Random;

public class Subject implements Serializable{
	/**
	 * 
	 */
		private static final long serialVersionUID = 1L;
	public AnswerRepository AR = new AnswerRepository();
	public QueryRepository QR = new QueryRepository();
	private String name;
	
	public Subject(String name) {
		this.name = name;
	}
	
	public AnswerRepository getAR() {
		return AR;
	}

	public void setAR(AnswerRepository aR) {
		AR = aR;
	}

	public QueryRepository getQR() {
		return QR;
	}

	public void setQR(QueryRepository qR) {
		QR = qR;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public boolean addQuery(Query q) {
		return QR.addQuery(q);
	}

	public void rmQuery(int index) {
		QR.rmQuery(index);
	}

	public Query[] getAllQueryArray() {
		return QR.getAllQueryArray();
	}
	
	public openQuery[] getOpenQueryArray() {
		return QR.getOpenQueryArray();
	}

	public closedQuery[] getClosedQueryArray() {
		return QR.getClosedQueryArray();
	}

	public String closedQuerytoString() {
		return closedQuerytoString();
	}

	public String openQuerytoString() {
		return openQuerytoString();
	}

	public String[] getClosedAns() {
		return AR.getClosedAns();
	}

	public String[] getOpenAns() {
		return AR.getOpenAns();
	}
	
	public String getClosedAns(int i) {
		return AR.getClosedAns(i);
	}

	public String getOpenAns(int i) {
		return AR.getOpenAns(i);
	}

	public String closedAnstoString() {
		return AR.closedAnstoString();
	}
		
	// so that the user won't see the answer he already chose
	public String closedAnsLimitedtoString(int[] toShowAnswerList) {
		return AR.closedAnsLimitedtoString(toShowAnswerList);
	}
	
	public int[] closedAnsLimitedArray(Answer[] AnswerList) {
		return AR.closedAnsLimitedArray(AnswerList);
	}
	
	public boolean isInLimitedArray(int i, int[] arr) {
		return AR.isInLimitedArray(i, arr);		
	}
 
	public String openAnstoString() {
		return AR.openAnstoString();
	}

	public String QRtoString() {
		return "Subject [name=" + name + "]\n"
				+ QR.toString();
	}

	public String ARtoString() {
		return "Subject [name=" + name + "]\n"
				+ AR.toString();
	}
	
	@Override
	public String toString() {
		return "Subject [name=" + name + "]\n"
				+ QR.toString() + '\n' + AR.toString();
	}
	
	public boolean equals(Subject s) {
		if (s.getName() == name) {
			return true;
		}
		return false;
	}

	
	
}
