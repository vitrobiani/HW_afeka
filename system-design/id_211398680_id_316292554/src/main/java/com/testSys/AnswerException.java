package com.testSys;


@SuppressWarnings("serial")
public class AnswerException extends Exception {
	String message = "to little Answers";
	
	public String getMessage() {
		return message;
	}
}
